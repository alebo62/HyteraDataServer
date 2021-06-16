#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QMessageBox>


// Есть ли номер в векторе станций
quint32 MainWindow::check_id(QVector<Radio*> v_rad, quint32 radio_num)
{
    quint32 find = -1;
    quint32 i = 0;
    foreach(Radio * r , v_rad)
    {
        if(r->m_radioNum == radio_num)
        {
            find = i;
            break;
        }
        i++;
    }
    return find;
}

// Заполняем таблицу (tableWidget) значениями из v_rad, которая была считана из файла
void MainWindow::fill_table()
{
    quint32 rc = 1;// начальная строка
    ui->tableWidget->setRowCount(v_rad.size()+1);// сколько всего строк будет видно
    foreach(Radio* r, v_rad)
    {
        QTableWidgetItem *twi = new QTableWidgetItem(tr("%1").arg(rc));
        ui->tableWidget->setItem(rc,0, twi);

        QTableWidgetItem *twi1 = new QTableWidgetItem(QString::number(r->m_radioNum));
        ui->tableWidget->setItem(rc,1, twi1);

        QTableWidgetItem *twi2 = new QTableWidgetItem(r->m_name);
        ui->tableWidget->setItem(rc,2, twi2);

        rc++;
    }
}

void MainWindow::fill_shops(Radio* r, quint32 num)
{
    switch (num) {
    case 1:
        ui->gridLayout_1->addWidget(r);
        break;
    case 2:
        ui->gridLayout_2->addWidget(r);
        break;
    case 3:
        ui->gridLayout_3->addWidget(r);
        break;
    case 4:

        break;
    case 5:

        break;
    default:
        break;
    }
}
