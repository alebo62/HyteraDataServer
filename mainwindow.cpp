#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    udp->bind(QHostAddress("192.168.10.2"), 4004);
    connect(udp, SIGNAL(readyRead()), this , SLOT(packet_arrived()));

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "ИД радиостанции" << "Владелец");
    ui->tableWidgetRegAlrm->setHorizontalHeaderLabels(QStringList() << "Дата" << "ИД радиост-ции" << "Владелец" << " Цех ");

    ui->widgetControl->setVisible(false);
    ui->widgetRegistration->setVisible(false);

    ui->widgetProg->setVisible(false);
    setFieldsValidation();

    fileReg.setFileName("settingsReg.txt");
    if(!fileReg.open(QIODevice::Append))
    {
        qDebug() << "Не могу открыть файл settingsReg.txt";
    }

    fileAlrm.setFileName("settingsAlrm.txt");
    if(!fileAlrm.open(QIODevice::Append))
    {
        qDebug() << "Не могу открыть файл settingsAlrm.txt";
    }

    QString path = "abonents";
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(path);
    qDebug() << db->open();
    query = new QSqlQuery();
    query->exec("CREATE TABLE abonents \
                (id      integer primary key, \
                 radio_id integer, \
                 name     varchar(30), \
                 reg      integer)");

                // из БД заполним вектор
                query->exec("SELECT * FROM abonents ");
            while(query->next())
    {
        radio = new Radio(query->value(1).toInt(), query->value(2).toString());
        radio->m_regNum = query->value(3).toInt();
        v_rad.push_back(radio);
        fill_shops(radio, radio->m_regNum);// заполним цеха станциями
    }

    query->prepare("SELECT COUNT(*) FROM abonents");
    query->exec();
    int rows= 0;
    if (query->next())
    {
        rows= query->value(0).toInt();
    }
    qDebug() << rows;
    // растяним первый столбец
    ui->tableWidgetRegAlrm->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Udp пакет пришел
void MainWindow::packet_arrived()
{
    quint32 len;
    QByteArray ba;
    quint32 radio_num;
    quint8 shop;
    QHostAddress ha;

    // читаем пакет и определяем кто передал
    ba.resize(static_cast<int>(udp->pendingDatagramSize()));
    len = ba.size();
    udp->readDatagram(ba.data(), len, &ha);
    radio_num = ha.toIPv4Address() & 0x00FFFFFF;
    qDebug() << ba;

    // есть ли станция в списке?
    quint32 index = check_id(v_rad, radio_num);
    // номер цеха
    shop = ba.at(0) & 0x7F;
    if((index >= 0) && (shop > 0) && (shop < 12))// если в списке и существующий цех
    {
        // сигнал тревоги или регистрации (сигнал + 0х80)
        if(ba.at(0) & 0x80) // тревога
        {
            if(v_rad[index]->m_regNum != shop)// если регстрация в другом цеху
            {
                v_rad[index]->m_regNum = shop; // обновим рег-ю в векторе
                fill_shops(v_rad.at(index), shop);// перенесем станцию в новый цех
                // перепишем регистрацию в БД
                QString s1 = QString("UPDATE  abonents  SET reg = %1 WHERE radio_id = %2").arg(shop).arg(radio_num);
                query->exec(s1);//"INSERT INTO  abonents  (id,  radio_id,  name,  reg) VALUES (1,111,'Borisov',2) ");
            }
            // надо включить другую иконку и мигать!!!!!!
            QByteArray ba_alrm;

            QDateTime dt = QDateTime::currentDateTime();
            QString s = dt.toString("dd.MM.yyyy hh:mm:ss,") + v_rad[index]->toString();
            fileAlrm.write(s.toUtf8());
        }
        else // регистрация
        {
            if(v_rad[index]->m_regNum != shop)// если регстрация в другом цеху
            {
                v_rad[index]->m_regNum = shop; // обновим рег-ю в векторе
                fill_shops(v_rad.at(index), shop);// перенесем станцию в новый цех
                QByteArray ba_reg;

                QDateTime dt = QDateTime::currentDateTime();
                QString s = dt.toString("dd.MM.yyyy hh:mm:ss,") + v_rad[index]->toString();
                fileReg.write(s.toUtf8());
                // перепишем регистрацию в БД
                QString s1 = QString("UPDATE  abonents  SET reg = %1 WHERE radio_id = %2 ").arg(shop).arg(radio_num);
                query->exec(s1);//"INSERT INTO  abonents  (id,  radio_id,  name,  reg) VALUES (1,111,'Borisov',2) ");
                qDebug() << s1;
                //ui->tab_2->show();
                // надо помигать и сделать этот цех активным!!!
            }
        }
    }
}

// посылка по Udp (для отладки)
void MainWindow::on_pbAdd_clicked()
{
    char arr[] = {0,0,0,111,(char)0x02};
    QByteArray data = QByteArray::fromRawData(arr, sizeof(arr));
    udp->writeDatagram(data, QHostAddress("12.0.0.111"), 4004);
    qDebug() << "udp";
    //ui->widgetControl->setVisible(false);
}

