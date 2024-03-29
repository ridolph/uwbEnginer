/********************************************************************************
** Form generated from reading UI file 'GraphicsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSWIDGET_H
#define UI_GRAPHICSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "GraphicsView.h"

QT_BEGIN_NAMESPACE

class Ui_GraphicsWidget
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tagTable;
    GraphicsView *graphicsView;
    QTableWidget *anchorTable;

    void setupUi(QWidget *GraphicsWidget)
    {
        if (GraphicsWidget->objectName().isEmpty())
            GraphicsWidget->setObjectName(QStringLiteral("GraphicsWidget"));
        GraphicsWidget->setWindowModality(Qt::NonModal);
        GraphicsWidget->resize(1074, 668);
        GraphicsWidget->setMaximumSize(QSize(16777215, 800));
        gridLayout = new QGridLayout(GraphicsWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        tagTable = new QTableWidget(GraphicsWidget);
        if (tagTable->columnCount() < 255)
            tagTable->setColumnCount(255);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tagTable->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        tagTable->setObjectName(QStringLiteral("tagTable"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tagTable->sizePolicy().hasHeightForWidth());
        tagTable->setSizePolicy(sizePolicy);
        tagTable->setMinimumSize(QSize(0, 71));
        tagTable->setMaximumSize(QSize(700, 16777215));
        QFont font;
        font.setPointSize(8);
        tagTable->setFont(font);
        tagTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tagTable->setAlternatingRowColors(true);
        tagTable->setRowCount(0);
        tagTable->setColumnCount(255);
        tagTable->horizontalHeader()->setDefaultSectionSize(70);
        tagTable->horizontalHeader()->setMinimumSectionSize(70);
        tagTable->horizontalHeader()->setStretchLastSection(false);
        tagTable->verticalHeader()->setDefaultSectionSize(18);
        tagTable->verticalHeader()->setMinimumSectionSize(18);

        gridLayout->addWidget(tagTable, 0, 1, 1, 1);

        graphicsView = new GraphicsView(GraphicsWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(graphicsView, 2, 0, 1, 2);

        anchorTable = new QTableWidget(GraphicsWidget);
        if (anchorTable->columnCount() < 12)
            anchorTable->setColumnCount(12);
        if (anchorTable->rowCount() < 16)
            anchorTable->setRowCount(16);
        anchorTable->setObjectName(QStringLiteral("anchorTable"));
        sizePolicy.setHeightForWidth(anchorTable->sizePolicy().hasHeightForWidth());
        anchorTable->setSizePolicy(sizePolicy);
        anchorTable->setMinimumSize(QSize(0, 10));
        anchorTable->setMaximumSize(QSize(350, 16777215));
        anchorTable->setFont(font);
        anchorTable->setLayoutDirection(Qt::LeftToRight);
        anchorTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        anchorTable->setAlternatingRowColors(true);
        anchorTable->setRowCount(16);
        anchorTable->setColumnCount(12);
        anchorTable->horizontalHeader()->setDefaultSectionSize(70);
        anchorTable->horizontalHeader()->setMinimumSectionSize(70);
        anchorTable->horizontalHeader()->setStretchLastSection(false);
        anchorTable->verticalHeader()->setVisible(false);
        anchorTable->verticalHeader()->setDefaultSectionSize(18);
        anchorTable->verticalHeader()->setHighlightSections(true);
        anchorTable->verticalHeader()->setMinimumSectionSize(18);

        gridLayout->addWidget(anchorTable, 0, 0, 1, 1);


        retranslateUi(GraphicsWidget);

        QMetaObject::connectSlotsByName(GraphicsWidget);
    } // setupUi

    void retranslateUi(QWidget *GraphicsWidget)
    {
        GraphicsWidget->setWindowTitle(QApplication::translate("GraphicsWidget", "Form", 0));
        QTableWidgetItem *___qtablewidgetitem = tagTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("GraphicsWidget", "11", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tagTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("GraphicsWidget", "12", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tagTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("GraphicsWidget", "13", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tagTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("GraphicsWidget", "14", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tagTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("GraphicsWidget", "15", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tagTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("GraphicsWidget", "16", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tagTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("GraphicsWidget", "17", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tagTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("GraphicsWidget", "18", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tagTable->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("GraphicsWidget", "19", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tagTable->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("GraphicsWidget", "20", 0));
    } // retranslateUi

};

namespace Ui {
    class GraphicsWidget: public Ui_GraphicsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSWIDGET_H
