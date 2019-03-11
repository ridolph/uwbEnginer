/********************************************************************************
** Form generated from reading UI file 'setScanConfigWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSCANCONFIGWIDGET_H
#define UI_SETSCANCONFIGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setScanConfigWidget
{
public:
    QLabel *label;
    QPushButton *okConfigBtn;
    QPushButton *cancelConfigBtn;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *stayEdit;
    QLineEdit *othCellEdit;
    QLineEdit *vanishEdit;
    QLabel *label_4;
    QLineEdit *jumpCountEdit;
    QCheckBox *locCorrectEnableBox;

    void setupUi(QWidget *setScanConfigWidget)
    {
        if (setScanConfigWidget->objectName().isEmpty())
            setScanConfigWidget->setObjectName(QStringLiteral("setScanConfigWidget"));
        setScanConfigWidget->resize(272, 306);
        label = new QLabel(setScanConfigWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 40, 121, 31));
        okConfigBtn = new QPushButton(setScanConfigWidget);
        okConfigBtn->setObjectName(QStringLiteral("okConfigBtn"));
        okConfigBtn->setGeometry(QRect(20, 250, 75, 31));
        cancelConfigBtn = new QPushButton(setScanConfigWidget);
        cancelConfigBtn->setObjectName(QStringLiteral("cancelConfigBtn"));
        cancelConfigBtn->setGeometry(QRect(170, 250, 75, 31));
        label_2 = new QLabel(setScanConfigWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 90, 81, 16));
        label_3 = new QLabel(setScanConfigWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 130, 111, 20));
        stayEdit = new QLineEdit(setScanConfigWidget);
        stayEdit->setObjectName(QStringLiteral("stayEdit"));
        stayEdit->setGeometry(QRect(150, 40, 91, 31));
        othCellEdit = new QLineEdit(setScanConfigWidget);
        othCellEdit->setObjectName(QStringLiteral("othCellEdit"));
        othCellEdit->setGeometry(QRect(150, 80, 91, 31));
        vanishEdit = new QLineEdit(setScanConfigWidget);
        vanishEdit->setObjectName(QStringLiteral("vanishEdit"));
        vanishEdit->setGeometry(QRect(150, 120, 91, 31));
        label_4 = new QLabel(setScanConfigWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 170, 101, 20));
        jumpCountEdit = new QLineEdit(setScanConfigWidget);
        jumpCountEdit->setObjectName(QStringLiteral("jumpCountEdit"));
        jumpCountEdit->setGeometry(QRect(150, 160, 91, 31));
        locCorrectEnableBox = new QCheckBox(setScanConfigWidget);
        locCorrectEnableBox->setObjectName(QStringLiteral("locCorrectEnableBox"));
        locCorrectEnableBox->setGeometry(QRect(140, 210, 131, 16));

        retranslateUi(setScanConfigWidget);

        QMetaObject::connectSlotsByName(setScanConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *setScanConfigWidget)
    {
        setScanConfigWidget->setWindowTitle(QApplication::translate("setScanConfigWidget", "Form", 0));
        label->setText(QApplication::translate("setScanConfigWidget", "\345\215\253\347\224\237\351\227\264\346\273\236\347\225\231\350\266\205\346\227\266\357\274\210\347\247\222\357\274\211", 0));
        okConfigBtn->setText(QApplication::translate("setScanConfigWidget", "\347\241\256\345\256\232", 0));
        cancelConfigBtn->setText(QApplication::translate("setScanConfigWidget", "\345\217\226\346\266\210", 0));
        label_2->setText(QApplication::translate("setScanConfigWidget", "\344\270\262\347\233\221\350\266\205\346\227\266\357\274\210\347\247\222\357\274\211", 0));
        label_3->setText(QApplication::translate("setScanConfigWidget", "\344\277\241\345\217\267\346\266\210\345\244\261\350\266\205\346\227\266\357\274\210\347\247\222)", 0));
        stayEdit->setText(QString());
        othCellEdit->setText(QString());
        vanishEdit->setText(QString());
        label_4->setText(QApplication::translate("setScanConfigWidget", "\346\234\200\345\244\247\350\267\263\345\217\230\347\202\271\346\225\260", 0));
        locCorrectEnableBox->setText(QApplication::translate("setScanConfigWidget", "\345\214\272\345\237\237\346\274\202\347\247\273\347\272\240\346\255\243\347\256\227\346\263\225", 0));
    } // retranslateUi

};

namespace Ui {
    class setScanConfigWidget: public Ui_setScanConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSCANCONFIGWIDGET_H
