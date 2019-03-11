/********************************************************************************
** Form generated from reading UI file 'AncTcpSrvPortConfigWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANCTCPSRVPORTCONFIGWIDGET_H
#define UI_ANCTCPSRVPORTCONFIGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AncTcpSrvPortConfigWidget
{
public:
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLineEdit *tcpSrvPortEdit;
    QLabel *label;

    void setupUi(QWidget *AncTcpSrvPortConfigWidget)
    {
        if (AncTcpSrvPortConfigWidget->objectName().isEmpty())
            AncTcpSrvPortConfigWidget->setObjectName(QStringLiteral("AncTcpSrvPortConfigWidget"));
        AncTcpSrvPortConfigWidget->resize(311, 155);
        okBtn = new QPushButton(AncTcpSrvPortConfigWidget);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setGeometry(QRect(70, 90, 75, 41));
        cancelBtn = new QPushButton(AncTcpSrvPortConfigWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setGeometry(QRect(200, 90, 75, 41));
        tcpSrvPortEdit = new QLineEdit(AncTcpSrvPortConfigWidget);
        tcpSrvPortEdit->setObjectName(QStringLiteral("tcpSrvPortEdit"));
        tcpSrvPortEdit->setGeometry(QRect(170, 30, 101, 31));
        label = new QLabel(AncTcpSrvPortConfigWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 141, 41));

        retranslateUi(AncTcpSrvPortConfigWidget);

        QMetaObject::connectSlotsByName(AncTcpSrvPortConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *AncTcpSrvPortConfigWidget)
    {
        AncTcpSrvPortConfigWidget->setWindowTitle(QApplication::translate("AncTcpSrvPortConfigWidget", "Form", 0));
        okBtn->setText(QApplication::translate("AncTcpSrvPortConfigWidget", "\347\241\256\345\256\232", 0));
        cancelBtn->setText(QApplication::translate("AncTcpSrvPortConfigWidget", "\345\217\226\346\266\210", 0));
        label->setText(QApplication::translate("AncTcpSrvPortConfigWidget", "\345\237\272\347\253\231TCP\346\234\215\345\212\241\345\231\250\347\233\221\345\220\254\347\253\257\345\217\243\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class AncTcpSrvPortConfigWidget: public Ui_AncTcpSrvPortConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANCTCPSRVPORTCONFIGWIDGET_H
