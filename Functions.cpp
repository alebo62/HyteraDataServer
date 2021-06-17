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

// Вводить можно только цифры
void MainWindow::setFieldsValidation()
{
    ui->lineEditCs->setValidator( new QIntValidator(0, 2000000, this) );
    ui->lineEditChPD->setValidator( new QIntValidator(1, 16, this) );
    ui->lineEditCh2_4->setValidator( new QIntValidator(1, 126, this) );
    ui->lineEditTimerMD->setValidator( new QIntValidator(10, 180, this) );
    ui->lineEditTimerReg->setValidator( new QIntValidator(10, 180, this) );
    ui->lineEditZ1max->setValidator( new QIntValidator(1, 30000, this) );
    ui->lineEditZ1min->setValidator( new QIntValidator(1, 30000, this) );
    ui->lineEditZ2max->setValidator( new QIntValidator(-2500, -12500, this) );
    ui->lineEditY1max->setValidator( new QIntValidator(6600, 26600, this) );
    ui->lineEditY1min->setValidator( new QIntValidator(6600, 26600, this) );
    ui->lineEditY2max->setValidator( new QIntValidator(-5000, -25000, this) );
    ui->lineEditY2min->setValidator( new QIntValidator(-5000, -25000, this) );
    ui->lineEditMaxCnt->setValidator( new QIntValidator(7, 10, this) );
    ui->lineEditPorogCnt->setValidator( new QIntValidator(3, 7, this) );
}

void MainWindow::fill_program_packet(QByteArray& ba)
{
    qint16 data = 0;

    if(ui->checkBoxIndoor->isChecked())
        data = 0x0001;
    else
        data = 0x0000;
    ba.append((char)(data >> 8)).append((char)(data & 0xFF));

    if(ui->lineEditCs->text() != "")
    {
        data = ui->lineEditCs->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditChPD->text() != "")
    {
        data = ui->lineEditChPD->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditCh2_4->text() != "")
    {
        data = ui->lineEditCh2_4->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditTimerMD->text() != "")
    {
        data = ui->lineEditTimerMD->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditTimerReg->text() != "")
    {
        data = ui->lineEditTimerReg->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditZ1max->text() != "")
    {
        data = ui->lineEditZ1max->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditZ1min->text() != "")
    {
        data = ui->lineEditZ1min->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditZ2max->text() != "")
    {
        data = ui->lineEditZ2max->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditZ2min->text() != "")
    {
        data = ui->lineEditZ2min->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditY1max->text() != "")
    {
        data = ui->lineEditY1max->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditY1min->text() != "")
    {
        data = ui->lineEditY1min->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditY2max->text() != "")
    {
        data = ui->lineEditY2max->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditY2min->text() != "")
    {
        data = ui->lineEditY2min->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditMaxCnt->text() != "")
    {
        data = ui->lineEditMaxCnt->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }

    if(ui->lineEditPorogCnt->text() != "")
    {
        data = ui->lineEditPorogCnt->text().toInt();
        ba.append((char)(data >> 8)).append((char)(data & 0xFF));
    }
}
