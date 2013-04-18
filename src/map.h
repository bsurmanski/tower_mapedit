/**
 * map.h
 * tower
 * March 25, 2013
 * Brandon Surmanski
 */

#ifndef _MAP_H
#define _MAP_H

struct Mesh;
struct GLBTexture;
struct GLBSampler;
struct GLBProgram;

typedef struct Tile
{
    uint16_t height;
    uint16_t texture;
} Tile;

typedef struct Map
{
    float position[3];
    float zoom;
    int w;
    int h;
    int textures;
    struct Tile *tiles;
    struct GLBBuffer *vbuffer;
    struct GLBBuffer *ibuffer;
    struct GLBSampler *sampler;
    struct GLBTexture *textureArray;
} Map;

Map *map_new(int w, int h, struct Tile *tiles);
void map_delete(Map *map);
float map_heightAt(Map *map, float x, float y);
void map_move(Map *map, float x, float y, float z);
void map_zoom(Map *map, float zoom);
void map_setHeight(Map *map, int i, int j, int h);
void map_addHeight(Map *map, int i, int j, int h);
void map_setTexture(Map *map, int i, int j, int t);
void map_draw(Map *map, GLBProgram *program);

#endif
