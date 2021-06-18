#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QMessageBox>

/*
 * Работа с базой абонентов
 */

// Список абонентов, добавление , удаление
void MainWindow::on_pushButton_clicked()
{
    bool bOk;
    QString str = QInputDialog::getText(0,"Ввод",
                                        "Введите пароль:",
                                        QLineEdit::Password,
                                        "",
                                        &bOk
                                        );
    if (!bOk) {
        // Была нажата кнопка Cancel
    }
    else if(str == "1111")
    {
        ui->widgetControl->setVisible(true);
        ui->pbRegistration->setEnabled(false);
        ui->pbProg->setEnabled(false);
        fill_table();
    }
    else
    {
        QMessageBox* pmbx = new QMessageBox(QMessageBox::Critical, "MessageBox","Неправильный пароль", QMessageBox::Yes);
        pmbx->exec();
        delete pmbx;
    }
}
// Выход из списка абонентов
void MainWindow::on_pbControlExit_clicked()
{
    ui->widgetControl->setVisible(false);
    ui->pbRegistration->setEnabled(true);
    ui->pbProg->setEnabled(true);
}

// Добавляем клиента в вектор и в таблицу и БД
void MainWindow::on_pbControlAdd_clicked()
{

    // check!!! что это число
    bool check_number = true;
    quint32 num = ui->leControlID->text().toInt();

    foreach(Radio* r, v_rad)
    {
        if (r->m_radioNum == num )
        {
            check_number = false;
            QMessageBox::information(this,"Информация","Такой ИД уже есть");
        }
    }

    if(check_number)
    {
        radio = new Radio(num, ui->leControlName->text());
        radio->m_regNum = 0;
        // запись в вектор
        v_rad.push_back(radio);

        // записываем в базу данных
        QString s = QString("INSERT INTO  abonents  (id,  radio_id,  name,  reg) VALUES \
                            (%1, %2,'%3', %4) ").arg(v_rad.size()).arg(num).arg(ui->leControlName->text()).arg(0);
                            query->exec(s);

                // добавляем в таблицу
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
    // Удаляем выделенную строку из таблицы
    quint32 radId = (ui->tableWidget->item(ui->tableWidget->currentRow(),1))->text().toInt();
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());

    // Удаляем абонента из БД
    QString s = QString("DELETE FROM  abonents  WHERE radio_id = %1 ").arg(radId);
    query->exec(s);//"INSERT INTO  abonents  (id,  radio_id,  name,  reg) VALUES (1,111,'Borisov',2) ");


    // стираем это радио из вектора
    foreach(Radio* r, v_rad)
        if (r->m_radioNum == radId )
            v_rad.removeOne(r);

    // Стираем таблицу, обновляем ее
    ui->tableWidget->clear();
    fill_table();
}

/*
 * Работа с журналами регистрации и тревог
 */

// открыть  виджет регистрации и тревог
void MainWindow::on_pbRegistration_clicked()
{
    bool bOk;
    QString str = QInputDialog::getText(0,"Ввод",
                                        "Введите пароль:",
                                        QLineEdit::Password,
                                        "",
                                        &bOk
                                        );
    if (!bOk) {
        // Была нажата кнопка Cancel
    }
    else if(str == "1111")
    {
        ui->widgetRegistration->setVisible(true);
        ui->pushButton->setEnabled(false);
        ui->pbProg->setEnabled(false);
    }
    else
    {
        QMessageBox* pmbx = new QMessageBox(QMessageBox::Critical, "MessageBox","Неправильный пароль", QMessageBox::Yes);
        pmbx->exec();
        delete pmbx;
    }
}
// закрыть виджет регистрации и тревог
void MainWindow::on_pbRegExit_clicked()
{
    ui->widgetRegistration->setVisible(false);
    ui->tableWidgetRegAlrm->clear();
    ui->pushButton->setEnabled(true);
    ui->pbProg->setEnabled(true);
}

// Открыть таблицу регистрации
void MainWindow::on_pbReg_clicked()
{
    // готовим файл для чтения
    fileReg.close();
    fileReg.open(QIODevice::ReadOnly);

    ui->tableWidgetRegAlrm->clear();
    ui->tableWidgetRegAlrm->setHorizontalHeaderLabels(QStringList() << "Дата" << "ИД радиост-ции" << "Владелец" << " Цех ");
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
    // возвращаем файл в исходное
    fileReg.close();
    fileReg.open(QIODevice::Append);
}

// Открыть таблицу тревог
void MainWindow::on_pbAlrm_clicked()
{
    fileAlrm.close();
    fileAlrm.open(QIODevice::ReadOnly);

    ui->tableWidgetRegAlrm->clear();
    ui->tableWidgetRegAlrm->setHorizontalHeaderLabels(QStringList() << "Дата" << "ИД радиост-ции" << "Владелец" << " Цех ");

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
    fileAlrm.close();
    fileAlrm.open(QIODevice::Append);
}

/*
 * Работа с программированием радиостанций
 */

// Открываем виджет програмирования
void MainWindow::on_pbProg_clicked()
{
//    bool bOk;
//    QString str = QInputDialog::getText(0,"Ввод",
//                                        "Введите пароль:",
//                                        QLineEdit::Password,
//                                        "",
//                                        &bOk
//                                        );
//    if (!bOk) {
//        // Была нажата кнопка Cancel
//    }
//    else if(str == "1111")
//    {
        ui->widgetProg->setVisible(true);
        ui->comboBoxRadio->clear();
        // Наполняем комбоБокс
        QStringList lst;
        foreach(Radio* r, v_rad)
            lst.append(QString::number(r->m_radioNum));
        ui->comboBoxRadio->addItems(lst);
        ui->pbRegistration->setEnabled(false);
        ui->pushButton->setEnabled(false);
//    }
//    else
//    {
//        QMessageBox* pmbx = new QMessageBox(QMessageBox::Critical, "MessageBox","Неправильный пароль", QMessageBox::Yes);
//        pmbx->exec();
//        delete pmbx;
//    }

}

// Закрываем виджет программирования
void MainWindow::on_pushButton_3_clicked()
{
    ui->widgetProg->setVisible(false);
    ui->pbRegistration->setEnabled(false);
    ui->pushButton->setEnabled(false);
}

// Запись данных в радио, Цифровой формат qint16
void MainWindow::on_pbRecord_clicked()
{
    QByteArray ba;

    // заполняем поля пакета для программирования радио
    fill_program_packet(ba);

    // делаем строку адреса из данных КомбоБокса
    QString address = QString("12.%1.%2.%3").arg((ui->comboBoxRadio->currentText().toUInt() >> 16) & 0xFF) \
            .arg((ui->comboBoxRadio->currentText().toUInt() >> 8) & 0xFF) \
            .arg( ui->comboBoxRadio->currentText().toUInt() & 0xFF);
    // ... и отравляем на радио
    udp->writeDatagram(ba, QHostAddress(address), 4004);

    //qDebug() << ba;
}




