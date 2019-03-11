#ifndef SETSCANCONFIGWIDGET_H
#define SETSCANCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class setScanConfigWidget;
}

class setScanConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit setScanConfigWidget(QWidget *parent = 0);
    ~setScanConfigWidget();
    void readSetting();

private slots:
    void locCorrectProcess();

    void on_okConfigBtn_clicked();

    void on_cancelConfigBtn_clicked();


private:
    Ui::setScanConfigWidget *ui;

    void writeSetting();
};

#endif // SETSCANCONFIGWIDGET_H
