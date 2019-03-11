#include "setserverdialog.h"
#include "ui_setserverdialog.h"

setServerDialog::setServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setServerDialog)
{
    ui->setupUi(this);
}

setServerDialog::~setServerDialog()
{
    delete ui;
}
