/********************************************************************************
** Form generated from reading UI file 'AncUpSrvConfigWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANCUPSRVCONFIGWIDGET_H
#define UI_ANCUPSRVCONFIGWIDGET_H

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

class Ui_AncUpSrvConfigWidget
{
public:
    QLabel *label;
    QLineEdit *upSrvAddrEdit;
    QLabel *label_2;
    QLineEdit *upSrvPortEdit;
    QLabel *label_3;
    QLineEdit *upFilePathEdit;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *label_4;
    QLineEdit *verEdit;

    void setupUi(QWidget *AncUpSrvConfigWidget)
    {
        if (AncUpSrvConfigWidget->objectName().isEmpty())
            AncUpSrvConfigWidget->setObjectName(QStringLiteral("AncUpSrvConfigWidget"));
        AncUpSrvConfigWidget->setEnabled(true);
        AncUpSrvConfigWidget->resize(335, 267);
        AncUpSrvConfigWidget->setMinimumSize(QSize(335, 267));
        AncUpSrvConfigWidget->setMaximumSize(QSize(360, 280));
        label = new QLabel(AncUpSrvConfigWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 20, 91, 31));
        upSrvAddrEdit = new QLineEdit(AncUpSrvConfigWidget);
        upSrvAddrEdit->setObjectName(QStringLiteral("upSrvAddrEdit"));
        upSrvAddrEdit->setGeometry(QRect(160, 20, 141, 31));
        label_2 = new QLabel(AncUpSrvConfigWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 60, 101, 31));
        upSrvPortEdit = new QLineEdit(AncUpSrvConfigWidget);
        upSrvPortEdit->setObjectName(QStringLiteral("upSrvPortEdit"));
        upSrvPortEdit->setGeometry(QRect(160, 60, 141, 31));
        label_3 = new QLabel(AncUpSrvConfigWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 100, 101, 31));
        upFilePathEdit = new QLineEdit(AncUpSrvConfigWidget);
        upFilePathEdit->setObjectName(QStringLiteral("upFilePathEdit"));
        upFilePathEdit->setGeometry(QRect(160, 100, 141, 31));
        okBtn = new QPushButton(AncUpSrvConfigWidget);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setGeometry(QRect(50, 200, 75, 41));
        cancelBtn = new QPushButton(AncUpSrvConfigWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setGeometry(QRect(180, 200, 75, 41));
        label_4 = new QLabel(AncUpSrvConfigWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 140, 101, 31));
        verEdit = new QLineEdit(AncUpSrvConfigWidget);
        verEdit->setObjectName(QStringLiteral("verEdit"));
        verEdit->setGeometry(QRect(160, 140, 141, 31));

        retranslateUi(AncUpSrvConfigWidget);

        QMetaObject::connectSlotsByName(AncUpSrvConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *AncUpSrvConfigWidget)
    {
        AncUpSrvConfigWidget->setWindowTitle(QApplication::translate("AncUpSrvConfigWidget", "Form", 0));
        label->setText(QApplication::translate("AncUpSrvConfigWidget", "\345\215\207\347\272\247\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200:", 0));
        label_2->setText(QApplication::translate("AncUpSrvConfigWidget", "\345\215\207\347\272\247\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243:", 0));
        label_3->setText(QApplication::translate("AncUpSrvConfigWidget", "\345\215\207\347\272\247\346\226\207\344\273\266\350\267\257\345\276\204:", 0));
        okBtn->setText(QApplication::translate("AncUpSrvConfigWidget", "\347\241\256\345\256\232", 0));
        cancelBtn->setText(QApplication::translate("AncUpSrvConfigWidget", "\345\217\226\346\266\210", 0));
        label_4->setText(QApplication::translate("AncUpSrvConfigWidget", "\347\211\210\346\234\254:", 0));
    } // retranslateUi

};

namespace Ui {
    class AncUpSrvConfigWidget: public Ui_AncUpSrvConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANCUPSRVCONFIGWIDGET_H
