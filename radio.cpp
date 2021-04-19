#include "radio.h"
#include "ui_radio.h"
#include "radio.h"

Radio::Radio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Radio)
{
    ui->setupUi(this);
    //Radio *rad = new Radio();
}

Radio::~Radio()
{
    delete ui;
}
