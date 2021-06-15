#ifndef RADIO_H
#define RADIO_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <QDateTime>

namespace Ui {
class Radio;
}

class Radio : public QWidget
{
    Q_OBJECT

public:
    explicit Radio( quint32, QString,QWidget *parent = nullptr);
    void flush_registration(void);
    void flush_alarm(void);
    void setWidth();
    ~Radio();
    quint32 m_radioNum;
    quint32 m_regNum;
    quint32 m_timerRegValue;
    QDateTime m_regTime;
    QDateTime m_alarmTime;


private:
    Ui::Radio *ui;
    QPixmap iconUp1 = QPixmap(":/radioIconUp1.png");
    QPixmap iconUp2, iconDwn1, iconDwn2;
    QLabel *lblIcon;
    QTimer  timReg, timRegView, timAlrm;
    QString m_name;
//    quint32 m_radioNum;
//    quint32 m_regNum;
//    quint32 m_timerRegValue;
//    QDateTime m_regTime;
//    QDateTime m_alarmTime;

private slots:
    void timRegSlot();
    void timAlrmSlot();

};

#endif // RADIO_H
