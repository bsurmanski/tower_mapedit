/**
 * map.c
 * tower
 * March 25, 2013
 * Brandon Surmanski
 */

#include <glb/glb.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <cw/util/math/matrix.h>

#include "map.h"

#define CLAMP(x,min,max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

GLBProgram *drawmap = NULL;

#if 0
static Tile *map_tile(Map *map, int i, int j)
{
    return &map->tiles[map->w * j + i];
}

/**
 * number of faces is variable since tile borders with a height difference
 * requires the side of the tile to be filled
 */
static int faces_required(Map *map)
{
    int nfaces = 0;
    int i, j;
    for(j = 0; j < map->h; j++)
    {
        for(i = 0; i < map->w; i++)
        {
            // check right tile border for height difference
            if((i+1) < map->w && map_tile(map, i, j)->height != map_tile(map, i + 1, j)->height)
            {
                nfaces++;
            }

            // check bottom tile border for height difference
            if((j+1) < map->w && map_tile(map, i, j)->height != map_tile(map, i, j + 1)->height)
            {
                nfaces++;
            }

            nfaces++;
        }
    }
    return nfaces * 2;
}
#endif

typedef struct Map_vert 
{
    float position[3];
    int16_t normal[3];
    uint16_t uv[2];
    uint16_t material;
    uint16_t tileId [2]; //used for picking in map editor
    uint8_t PADDING[4];
} Map_vert;

typedef struct Map_face
{
    uint16_t verts[3];
} Map_face;

static void set_vert(Map_vert *vert, float *position, int16_t *normal, 
                     uint16_t *uv, uint16_t material, int i, int j)
{
    memcpy(vert->position, position, sizeof(float[3])); 
    memcpy(vert->normal, normal, sizeof(int16_t[3]));
    memcpy(vert->uv, uv, sizeof(uint16_t[2]));
    vert->material = material;
    vert->tileId[0] = i;
    vert->tileId[1] = j;
}

static void create_tile_verts(Map_vert *verts, int x, int y, Tile *tile)
{
    float height = tile->height / 8.0f;
    float position[3] = {x - 0.5f, height, y - 0.5f};
    int16_t normal[3] = {0x0000, 0xffff, 0x0000}; // up normal
    uint16_t uv[2] = {0x0000, 0x0000};
    set_vert(&verts[0], position, normal, uv, tile->texture, x, y);

    position[0] = x + 0.5f;
    uv[0] = 0xffff;
    set_vert(&verts[1], position, normal, uv, tile->texture, x, y);

    position[2] = y + 0.5f;
    uv[1] = 0xffff;
    set_vert(&verts[2], position, normal, uv, tile->texture, x, y);

    position[0] = x - 0.5f;
    uv[0] = 0x0000;
    set_vert(&verts[3], position, normal, uv, tile->texture, x, y);
}

static int map_index(Map *map, int i, int j)
{
    return map->w * j + i;
}

static Map_vert *new_verts(Map *map, int *nverts)
{
    *nverts = map->w * map->h * 4;
    Map_vert *verts = malloc(sizeof(Map_vert[*nverts]));
    int i, j;
    for(j = 0; j < map->h; j++)
    {
        for(i = 0; i < map->w; i++)
        {
            Map_vert *vertptr = &verts[map_index(map, i, j) * 4];
            create_tile_verts(vertptr, i, j, &map->tiles[map_index(map, i, j)]);
        }
    }
    return verts;
}

static Map_face *new_faces(Map *map, int *nfaces)
{
    *nfaces = map->w * map->h * 2;//faces_required(map); //TODO
    Map_face *faces = malloc(sizeof(Map_face[*nfaces]));
    int i, j;
    for(j = 0; j < map->h; j++)
    {
        for(i = 0; i < map->w; i++)
        {
            Map_face face_1 = {{map_index(map, i, j) * 4, 
                                 map_index(map, i, j) * 4 + 1, 
                                 map_index(map, i, j) * 4 + 2}};
            Map_face face_2 = {{map_index(map, i, j) * 4, 
                                 map_index(map, i, j) * 4 + 2, 
                                 map_index(map, i, j) * 4 + 3}};
            memcpy(&faces[map_index(map, i, j) * 2], &face_1, sizeof(Map_face));
            memcpy(&faces[map_index(map, i, j) * 2 + 1], &face_2, sizeof(Map_face));
        }
    }
    return faces;
}

static void map_createGeometry(Map *map)
{
    Map_vert *verts;
    Map_face *faces;
    int nverts, nfaces;
    verts = new_verts(map, &nverts);
    faces = new_faces(map, &nfaces);
    
    struct GLBVertexLayout vlayout[] = 
    {
        {3, GL_FLOAT,           false, 32, 0}, //position
        {3, GL_SHORT,           true, 32, 12}, //normal
        {2, GL_UNSIGNED_SHORT,  true, 32, 18}, //uv
        {2, GL_UNSIGNED_SHORT,  false, 32, 22}, //material
        {2, GL_UNSIGNED_SHORT,  false, 32, 24}, //x
    };

    map->vbuffer = glbCreateVertexBuffer(nverts, sizeof(Map_vert), verts, 5, vlayout,
                                         GL_STATIC_DRAW, NULL);
    map->ibuffer = glbCreateIndexBuffer(nfaces, sizeof(Map_face), faces, 
                                         GL_UNSIGNED_SHORT, GL_STATIC_DRAW, NULL);
    free(verts);
    free(faces);
}

static void map_deleteGeometry(Map *map)
{
    glbDeleteBuffer(map->vbuffer);
    glbDeleteBuffer(map->ibuffer);
}

static void map_createTextureArray(Map *map)
{
    map->textureArray = glbCreateTexture(GLB_TEXTURE_ARRAY, GLB_RGBA, 16, 16, 16, NULL, NULL);
    map->sampler = glbCreateSampler(NULL);
    glbSamplerFilter(map->sampler, GLB_NEAREST, GLB_NEAREST);
    glbTextureSampler(map->textureArray, map->sampler);

    int origin[3] = {0,0,0};
    int region[3] = {16,16,1};

    const char *textureFiles[] =
    {
        "res/tex/grass.tga",
        "res/tex/water.tga",
        "res/tex/test.tga",
    };
    
    int i;
    for(i = 0; i < 3; i++)
    {
        origin[2] = i;
        glbWriteTextureWithTGA(map->textureArray, 0, origin, region, textureFiles[i]);
    }
}

Map *map_new(int w, int h, Tile *tiles)
{
    Map *map = calloc(1, sizeof(Map));
    map->position[0] = -(w / 2.0f);
    map->position[2] = -(h * 0.82f + 7.0f); // found experimentally
    //map->zoom = -((w - 32) / 8.0f);
    map->w = w;
    map->h = h;
    map->tiles = malloc(sizeof(Tile[w*h]));
    memcpy(map->tiles, tiles, sizeof(Tile[w*h]));

    map_createGeometry(map);
    map_createTextureArray(map);
    return map;
}

void map_delete(Map *map)
{
    glbDeleteTexture(map->textureArray);
    glbDeleteBuffer(map->vbuffer);
    glbDeleteBuffer(map->ibuffer);
    free(map->tiles);
    free(map);
}

float map_heightAt(Map *map, float x, float y)
{
    float height = map->tiles[
                        (int) 
                         (round(CLAMP(x, 0.0f, (float) map->w)) +
                          round(CLAMP(y, 0.0f, (float) map->h)) * map->w)
                     ].height / 8.0f;
    return height;

}

void map_move(Map *map, float x, float y, float z)
{
    map->position[0] += x;
    map->position[1] += y;
    map->position[2] += z;
}

void map_zoom(Map *map, float zoom)
{
    map->zoom += zoom;
}

void map_setHeight(Map *map, int i, int j, int h)
{
    map_deleteGeometry(map);
    map->tiles[map_index(map, i, j)].height = h;
    map_createGeometry(map);
}

void map_addHeight(Map *map, int i, int j, int h)
{
    map_deleteGeometry(map);
    map->tiles[map_index(map, i, j)].height += h;
    map_createGeometry(map);
}

void map_setTexture(Map *map, int i, int j, int t)
{
    map_deleteGeometry(map);
    map->tiles[map_index(map, i, j)].texture = t;
    map_createGeometry(map);
}

void map_draw(Map *map, GLBProgram *program)
{
    mat4 t_matrix;
    mat4 m_matrix;
    mat4 v_matrix;
    mat4 p_matrix;
    printf("POSZ: %f\n", map->position[2]);

    mat4_identity(m_matrix);
    mat4_identity(v_matrix);
    mat4_identity(p_matrix);

    mat4_translate(v_matrix, 0.0f, -10.0f, 0.0f);
    mat4_rotate(v_matrix, M_PI / 4.0f, 1.0f, 0.0f, 0.0f);
    mat4_translate(v_matrix, 0.0f, 0.0f, map->zoom);
    mat4_frustum(p_matrix, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1677216.0f);
    mat4_translate(m_matrix, map->position[0], map->position[1], map->position[2]);
    mat4_mult(v_matrix, m_matrix, t_matrix);
    mat4_mult(p_matrix, t_matrix, t_matrix);
    glDisable(GL_CULL_FACE);
    glbProgramUniformMatrix(program, GLB_VERTEX_SHADER, 0, sizeof(float[16]), 
                            true, t_matrix);
    glbProgramTexture(program, GL_FRAGMENT_SHADER, 0, map->textureArray);
    glbProgramDrawIndexed(program, map->vbuffer, map->ibuffer);
}
