#include "radio.h"
#include "ui_radio.h"
#include "radio.h"

Radio::Radio( quint32 number, QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Radio), m_radioNum(number), m_name(name)
{
    ui->setupUi(this);
    //Radio *rad = new Radio();
    iconUp1  = QPixmap(":/radioIconUp1.png");
    iconUp2  = QPixmap(":/radioIconUp2.png");
    iconDwn1 = QPixmap(":/radioIconDwn1.png");
    iconDwn2 = QPixmap(":/radioIconDwn2.png");

    iconUp1  = iconUp1.scaled(30,30);
    iconUp2  = iconUp2.scaled(30,30);
    iconDwn1 = iconDwn1.scaled(30,30);
    iconDwn2 = iconDwn2.scaled(30,30);

    connect(&timReg, SIGNAL(timeout()), this, SLOT(timRegSlot()));
    connect(&timAlrm, SIGNAL(timeout()), this, SLOT(timAlrmSlot()));

    ui->lblNum->setText(QString::number(m_radioNum));
    ui->lblName->setText(m_name);
    ui->lblIcon->setPixmap(iconUp1);

    m_regNum = 0;
    m_regTime = QDateTime::currentDateTime();
}

void Radio::flush_registration()
{
    timReg.start(500);
}

void Radio::flush_alarm()
{
    timAlrm.start(300);
}

Radio::~Radio()
{
    delete ui;
}

QString Radio::toString()
{
    QString s = QString::number(m_radioNum) + "," + m_name + "," + QString::number(m_regNum) + "\r\n";
    return s;
}

void Radio::timRegSlot()
{
    QPixmap pixmapVal = ui->lblIcon->pixmap(Qt::ReturnByValue);
    if(pixmapVal.toImage() ==  iconUp1.toImage())
        ui->lblIcon->setPixmap(iconUp2);
    else
        ui->lblIcon->setPixmap(iconUp1);
    ui->lblIcon->update();

}

void Radio::timAlrmSlot()
{
    if(ui->lblIcon->pixmap(Qt::ReturnByValue).toImage() == iconDwn1.toImage())
        ui->lblIcon->setPixmap(iconDwn2);
    else
        ui->lblIcon->setPixmap(iconDwn1);
    ui->lblIcon->update();
}

void Radio::setWidth()
{
    if(ui->label->width() == 225){
        ui->label->setFixedWidth(40);
        ui->lblName->hide();
        ui->lblNum->hide();
        ui->lblReg->hide();
    }
    else{
        ui->label->setFixedWidth(225);
        ui->lblName->setVisible(true);
        ui->lblNum->setVisible(true);
        ui->lblReg->setVisible(true);
    }
}
