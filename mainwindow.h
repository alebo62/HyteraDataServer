#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "radio.h"
#include <QVector>
#include <QUdpSocket>
#include <QFile>
#include <QLayout>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pbAdd_clicked();

    void packet_arrived();

    void on_pbControlExit_clicked();

    //void on_pbControlAdd_2_clicked();

    void on_pbControlAdd_clicked();

    void on_pbControlDel_clicked();

    void on_pbRegistration_clicked();

    void on_pbRegExit_clicked();

    void on_pbReg_clicked();

    void on_pbAlrm_clicked();

    void on_pbProg_clicked();

    void on_pushButton_3_clicked();

    void on_pbRecord_clicked();

private:
    Ui::MainWindow *ui;
    Radio *radio;
    QVector <Radio *> v_rad;
    quint32 radCnt;
    QVector<quint32> v_radNums;
    QUdpSocket* udp;
    QFile file;
    QFile fileReg;
    QFile fileAlrm;
    void fill_table();
    quint32 check_id(QVector<Radio*>, quint32);
    void fill_shops(Radio*, quint32);
    void setFieldsValidation();
    void fill_program_packet(QByteArray&);
    QSqlQuery *query;
    QSqlDatabase *db;
};
#endif // MAINWINDOW_H
