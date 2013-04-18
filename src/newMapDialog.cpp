/**
 * newMapDialog.cpp
 * tower/mapedit
 * April 15, 2013
 * Brandon Surmanski
 */

#include "newMapDialog.hpp"

NewMapDialog::NewMapDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Mapedit | New Map");
    success = false;

    widthLabel = new QLabel("Width");
    heightLabel = new QLabel("Height");
    widthSpinBox = new QSpinBox(this);
    heightSpinBox = new QSpinBox(this);
    widthSpinBox->setRange(0, 1000);
    heightSpinBox->setRange(0, 1000);
    widthSpinBox->setValue(32);
    heightSpinBox->setValue(32);
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    layout = new QGridLayout(this);
    layout->addWidget(widthLabel, 0, 0);
    layout->addWidget(widthSpinBox, 0, 1);
    layout->addWidget(heightLabel, 1, 0);
    layout->addWidget(heightSpinBox, 1, 1);
    layout->addWidget(buttonBox, 2, 0, 1, 2);
    setLayout(layout);

    connect(buttonBox, SIGNAL(accepted()), this, (SLOT(ok_clicked())));
    connect(buttonBox, SIGNAL(rejected()), this, (SLOT(cancel_clicked())));
}

NewMapDialog::~NewMapDialog()
{
    delete layout;
    delete buttonBox;
    delete heightSpinBox;
    delete widthSpinBox;
    delete heightLabel;
    delete widthLabel;
}

bool NewMapDialog::succeeded()
{
    return success;
}

void NewMapDialog::ok_clicked()
{
    success = true;
    this->close();
}

void NewMapDialog::cancel_clicked()
{
    success = false;
    this->close();
}

int NewMapDialog::width()
{
    return widthSpinBox->value();
}

int NewMapDialog::height()
{
    return heightSpinBox->value();
}
