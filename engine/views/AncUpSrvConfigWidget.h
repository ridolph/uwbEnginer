#ifndef ANCUPSRVCONFIGWIDGET_H
#define ANCUPSRVCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class AncUpSrvConfigWidget;
}

class AncUpSrvConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AncUpSrvConfigWidget(QWidget *parent = 0);
    ~AncUpSrvConfigWidget();
public slots:
    void readSetting();

signals:
    void verChanged(QString ver);

private slots:

    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::AncUpSrvConfigWidget *ui;
};

#endif // ANCUPSRVCONFIGWIDGET_H
