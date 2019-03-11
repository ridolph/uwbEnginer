#ifndef SETSERVERDIALOG_H
#define SETSERVERDIALOG_H

#include <QDialog>

namespace Ui {
class setServerDialog;
}

class setServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit setServerDialog(QWidget *parent = 0);
    ~setServerDialog();

private:
    Ui::setServerDialog *ui;
};

#endif // SETSERVERDIALOG_H
