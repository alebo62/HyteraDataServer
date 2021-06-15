#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "radio.h"
#include <QVector>
#include <QUdpSocket>
#include <QFile>
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

private:
    Ui::MainWindow *ui;
    Radio *radio;
    QVector <Radio *> v_rad;
    quint32 radCnt;
    QVector<quint32> v_radNums;
    QUdpSocket* udp;
    QFile file;

};
#endif // MAINWINDOW_H
