#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QMessageBox>


void MainWindow::on_pbControlExit_clicked()
{
    ui->widgetControl->setVisible(false);
}

// Добавляем клиента в вектор и в таблицу
void MainWindow::on_pbControlAdd_clicked()
{
    // check!!!
    bool check_number = true;
    quint32 num = ui->leControlID->text().toInt();
    foreach(Radio* r, v_rad)
        if (r->m_radioNum == num )
        {
            check_number = false;
            QMessageBox::information(this,"Информация","Такой ИД уже есть");
        }
    if(check_number)
    {
        radio = new Radio(num, ui->leControlName->text());
        radio->m_regNum = 0;
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

}

void MainWindow::on_pbControlDel_clicked()
{
    // Удаляем выделенную строку
    quint32 radId = (ui->tableWidget->item(ui->tableWidget->currentRow(),1))->text().toInt();
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());

    // стираем это радио из вектора
    foreach(Radio* r, v_rad)
        if (r->m_radioNum == radId )
            v_rad.removeOne(r);

    // Стираем таблицу, запивываем изменения в файл
    ui->tableWidget->clear();
    fill_table();
    file.close();
    file.open(QIODevice::WriteOnly);
    foreach(Radio* r, v_rad)
        file.write(r->toString().toUtf8());
    file.flush();
    file.close();
    file.open(QIODevice::ReadOnly);
}

void MainWindow::on_pbRegistration_clicked()
{
    ui->widgetRegistration->setVisible(true);

}

void MainWindow::on_pbRegExit_clicked()
{
    ui->widgetRegistration->setVisible(false);
    ui->tableWidgetRegAlrm->clear();
}

// Открыть таблицу регистрации
void MainWindow::on_pbReg_clicked()
{
    ui->tableWidgetRegAlrm->clear();
    QByteArray ba;
    quint32 rc = 1;// начальная строка
    while(!fileReg.atEnd())//заносим из файла все радио в таблицу
    {
        ba = fileReg.readLine();
        QList<QByteArray> lba = ba.split(',');

        ui->tableWidgetRegAlrm->setRowCount(rc+1);// сколько всего строк будет видно

        QTableWidgetItem *twi = new QTableWidgetItem(QString(lba[0]));
        ui->tableWidgetRegAlrm->setItem(rc,0, twi);

        QTableWidgetItem *twi1 = new QTableWidgetItem(QString(lba[1]));
        ui->tableWidgetRegAlrm->setItem(rc,1, twi1);

        QTableWidgetItem *twi2 = new QTableWidgetItem(QString(lba[2]));
        ui->tableWidgetRegAlrm->setItem(rc,2, twi2);

        QTableWidgetItem *twi3 = new QTableWidgetItem(QString(lba[3]).trimmed());
        ui->tableWidgetRegAlrm->setItem(rc,3, twi3);

        rc++;
    }
}

// Открыть таблицу тревог
void MainWindow::on_pbAlrm_clicked()
{
    ui->tableWidgetRegAlrm->clear();
    QByteArray ba;
    quint32 rc = 1;// начальная строка
    while(!fileAlrm.atEnd())//заносим из файла все радио в таблицу
    {
        ba = fileAlrm.readLine();
        QList<QByteArray> lba = ba.split(',');

        ui->tableWidgetRegAlrm->setRowCount(rc+1);// сколько всего строк будет видно

        QTableWidgetItem *twi = new QTableWidgetItem(QString(lba[0]));
        ui->tableWidgetRegAlrm->setItem(rc,0, twi);

        QTableWidgetItem *twi1 = new QTableWidgetItem(QString(lba[1]));
        ui->tableWidgetRegAlrm->setItem(rc,1, twi1);

        QTableWidgetItem *twi2 = new QTableWidgetItem(QString(lba[2]));
        ui->tableWidgetRegAlrm->setItem(rc,2, twi2);

        QTableWidgetItem *twi3 = new QTableWidgetItem(QString(lba[3]).trimmed());
        ui->tableWidgetRegAlrm->setItem(rc,3, twi3);

        rc++;
    }
}



