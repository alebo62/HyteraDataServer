#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "radio.h"
#include <QLayout>

QVBoxLayout *vBoxLayoutMain;
Radio *rad;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rad = new Radio();
    ui->gridLayout->addWidget(rad);
    //rad->show();
    //vBoxLayoutMain = new QVBoxLayout();
    //this->setLayout(vBoxLayoutMain);
    //this->layout()->addWidget(rad);
    //vBoxLayoutMain = new QVBoxLayout();

    //vBoxLayoutMain->addWidget(rad);
    //setLayout(vBoxLayoutMain);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    rad = new Radio();
    ui->gridLayout->addWidget(rad);
    //vBoxLayoutMain = new QVBoxLayout();

    //vBoxLayoutMain->addWidget(rad);

    //setLayout(vBoxLayoutMain);
}
