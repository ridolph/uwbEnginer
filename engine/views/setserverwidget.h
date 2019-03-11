#ifndef SETSERVERWIDGET_H
#define SETSERVERWIDGET_H

#include <QWidget>

namespace Ui {
class setServerWidget;
}

class setServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit setServerWidget(QWidget *parent = 0);
    ~setServerWidget();

    void readSetting();

private slots:
    void on_setBtn_clicked();
signals:
    void setServer(QString addr, int port);
    void setOutServer(QString addr, int port);


private:
    Ui::setServerWidget *ui;
};

#endif // SETSERVERWIDGET_H
