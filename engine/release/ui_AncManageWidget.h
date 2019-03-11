/********************************************************************************
** Form generated from reading UI file 'AncManageWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANCMANAGEWIDGET_H
#define UI_ANCMANAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AncManageWidget
{
public:
    QTableWidget *ancManageTab;

    void setupUi(QWidget *AncManageWidget)
    {
        if (AncManageWidget->objectName().isEmpty())
            AncManageWidget->setObjectName(QStringLiteral("AncManageWidget"));
        AncManageWidget->resize(748, 546);
        ancManageTab = new QTableWidget(AncManageWidget);
        ancManageTab->setObjectName(QStringLiteral("ancManageTab"));
        ancManageTab->setGeometry(QRect(30, 30, 511, 361));

        retranslateUi(AncManageWidget);

        QMetaObject::connectSlotsByName(AncManageWidget);
    } // setupUi

    void retranslateUi(QWidget *AncManageWidget)
    {
        AncManageWidget->setWindowTitle(QApplication::translate("AncManageWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class AncManageWidget: public Ui_AncManageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANCMANAGEWIDGET_H
