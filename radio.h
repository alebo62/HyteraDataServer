#ifndef RADIO_H
#define RADIO_H

#include <QWidget>

namespace Ui {
class Radio;
}

class Radio : public QWidget
{
    Q_OBJECT

public:
    explicit Radio(QWidget *parent = nullptr);
    ~Radio();

private:
    Ui::Radio *ui;
};

#endif // RADIO_H
