#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QMessageBox>
extern QPixmap iconUp1;

QVBoxLayout *vBoxLayoutMain;
Radio *rad;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gridLayout_1->setColumnMinimumWidth(0,230);
    ui->gridLayout_1->setColumnMinimumWidth(1,230);
    ui->gridLayout_1->setColumnMinimumWidth(2,230);
    ui->gridLayout_1->setColumnMinimumWidth(3,230);
    ui->gridLayout_2->setColumnMinimumWidth(0,230);
    ui->gridLayout_2->setColumnMinimumWidth(1,230);
    ui->gridLayout_2->setColumnMinimumWidth(2,230);
    ui->gridLayout_2->setColumnMinimumWidth(3,230);
    ui->gridLayout_3->setColumnMinimumWidth(0,230);
    ui->gridLayout_3->setColumnMinimumWidth(1,230);
    ui->gridLayout_3->setColumnMinimumWidth(2,230);
    ui->gridLayout_3->setColumnMinimumWidth(3,230);

    udp = new QUdpSocket();
    udp->bind(QHostAddress("127.0.0.1"), 4004);
    connect(udp, SIGNAL(readyRead()), this , SLOT(packet_arrived()));
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "ИД радиостанции" << "Владелец");
    ui->widgetControl->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //rad->flush_registration();
    //for(int i = 0; i < v_rad.size(); i++)
    //    v_rad.at(i)->setWidth();
   // ui->widget->setVisible(false);

//    char arr[] = {0,0,0,1,1};
//    QByteArray data = QByteArray::fromRawData(arr, sizeof(arr));
//    udp->writeDatagram(data, QHostAddress("127.0.0.1"), 4004);
//    ui->widgetControl->setVisible(false);

    ui->widgetControl->setVisible(true);
}

void MainWindow::packet_arrived()
{
    quint32 len;
    QByteArray ba;
    ba.resize(static_cast<int>(udp->pendingDatagramSize()));
    len = ba.size();
    udp->readDatagram(ba.data(), len);
    qDebug()<< ba;
}

void MainWindow::on_pbAdd_clicked()
{
    radio = new Radio(12345, "Борисов");
    radCnt++;
    v_rad.push_back(radio);
    //ui->gridLayout_1->addWidget(radio);
}



void MainWindow::on_pbControlExit_clicked()
{
    ui->widgetControl->setVisible(false);
}

void MainWindow::on_pbControlAdd_clicked()
{
    // check!!!
    quint32 num = ui->leControlID->text().toInt();
    foreach(Radio* r, v_rad)
        if (r->m_radioNum == num )
        {
            QMessageBox::information();
        }
    radio = new Radio(num, ui->leControlName->text());
    radCnt++;
    v_rad.push_back(radio);

    quint32 rc = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rc+1);

    QTableWidgetItem *twi = new QTableWidgetItem(tr("%1").arg(rc+1));
    ui->tableWidget->setItem(rc,0, twi);
    QTableWidgetItem *twi1 = new QTableWidgetItem(ui->leControlID->text());
    ui->tableWidget->setItem(rc,1, twi1);
    QTableWidgetItem *twi2 = new QTableWidgetItem(ui->leControlName->text());
    ui->tableWidget->setItem(rc,2, twi2);


}
void MainWindow::on_pbControlDel_clicked()
{
    quint32 radId = (ui->tableWidget->item(ui->tableWidget->currentRow(),1))->text().toInt();
    QTableWidgetItem *twi0 = ui->tableWidget->item(ui->tableWidget->currentRow(),0);
    QTableWidgetItem *twi1 = ui->tableWidget->item(ui->tableWidget->currentRow(),1);
    QTableWidgetItem *twi2 = ui->tableWidget->item(ui->tableWidget->currentRow(),2);
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    delete twi0;
    delete twi1;
    delete twi2;
    // стираем это радио из вектора
    qDebug() << v_rad.size();
    foreach(Radio* r, v_rad)
        if (r->m_radioNum == radId )
            v_rad.removeOne(r);
    qDebug() << v_rad.size();
}
