/********************************************************************************
** Form generated from reading UI file 'setserverwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSERVERWIDGET_H
#define UI_SETSERVERWIDGET_H

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

class Ui_setServerWidget
{
public:
    QLineEdit *addrEdit;
    QLabel *label_2;
    QLineEdit *portEdit;
    QPushButton *setBtn;
    QLabel *label_3;
    QPushButton *cancelBtn;
    QLabel *label_4;
    QLineEdit *addrEdit_2;
    QLabel *label_5;
    QLineEdit *portEdit_2;

    void setupUi(QWidget *setServerWidget)
    {
        if (setServerWidget->objectName().isEmpty())
            setServerWidget->setObjectName(QStringLiteral("setServerWidget"));
        setServerWidget->setWindowModality(Qt::NonModal);
        setServerWidget->resize(500, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(setServerWidget->sizePolicy().hasHeightForWidth());
        setServerWidget->setSizePolicy(sizePolicy);
        setServerWidget->setMinimumSize(QSize(0, 0));
        setServerWidget->setMaximumSize(QSize(16777215, 16777215));
        setServerWidget->setBaseSize(QSize(0, 0));
        addrEdit = new QLineEdit(setServerWidget);
        addrEdit->setObjectName(QStringLiteral("addrEdit"));
        addrEdit->setGeometry(QRect(270, 50, 161, 31));
        label_2 = new QLabel(setServerWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 90, 101, 20));
        portEdit = new QLineEdit(setServerWidget);
        portEdit->setObjectName(QStringLiteral("portEdit"));
        portEdit->setGeometry(QRect(270, 90, 161, 31));
        setBtn = new QPushButton(setServerWidget);
        setBtn->setObjectName(QStringLiteral("setBtn"));
        setBtn->setGeometry(QRect(150, 280, 81, 31));
        label_3 = new QLabel(setServerWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 50, 171, 20));
        cancelBtn = new QPushButton(setServerWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setGeometry(QRect(330, 280, 81, 31));
        label_4 = new QLabel(setServerWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(80, 140, 181, 20));
        addrEdit_2 = new QLineEdit(setServerWidget);
        addrEdit_2->setObjectName(QStringLiteral("addrEdit_2"));
        addrEdit_2->setGeometry(QRect(270, 130, 161, 31));
        label_5 = new QLabel(setServerWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(150, 190, 101, 21));
        portEdit_2 = new QLineEdit(setServerWidget);
        portEdit_2->setObjectName(QStringLiteral("portEdit_2"));
        portEdit_2->setGeometry(QRect(270, 180, 161, 31));

        retranslateUi(setServerWidget);

        QMetaObject::connectSlotsByName(setServerWidget);
    } // setupUi

    void retranslateUi(QWidget *setServerWidget)
    {
        setServerWidget->setWindowTitle(QApplication::translate("setServerWidget", "Form", 0));
        addrEdit->setText(QString());
        label_2->setText(QApplication::translate("setServerWidget", "\347\253\257\345\217\243\357\274\232", 0));
        portEdit->setText(QString());
        setBtn->setText(QApplication::translate("setServerWidget", "\347\241\256\345\256\232", 0));
        label_3->setText(QApplication::translate("setServerWidget", "\345\206\205\351\203\250TCP\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", 0));
        cancelBtn->setText(QApplication::translate("setServerWidget", "\345\217\226\346\266\210", 0));
        label_4->setText(QApplication::translate("setServerWidget", "\345\244\226\351\203\250TCP\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232     ", 0));
        addrEdit_2->setText(QString());
        label_5->setText(QApplication::translate("setServerWidget", "\347\253\257\345\217\243\357\274\232", 0));
        portEdit_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class setServerWidget: public Ui_setServerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSERVERWIDGET_H
