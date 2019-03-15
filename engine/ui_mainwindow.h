/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include "GraphicsWidget.h"
#include "MinimapView.h"
#include "ViewSettingsWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionConfig;
    QAction *actionSetServer;
    QAction *actionConfigServer;
    QAction *actionScanConfig;
    QAction *actionTagManage;
    QAction *actionDd;
    QAction *actionDddd;
    GraphicsWidget *graphicsWidget;
    QMenuBar *menuBar;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *viewSettings_dw;
    ViewSettingsWidget *viewSettings_w;
    QDockWidget *minimap_dw;
    MinimapView *minimap;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(499, 395);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/DWctrler.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionConfig = new QAction(MainWindow);
        actionConfig->setObjectName(QStringLiteral("actionConfig"));
        actionSetServer = new QAction(MainWindow);
        actionSetServer->setObjectName(QStringLiteral("actionSetServer"));
        actionConfigServer = new QAction(MainWindow);
        actionConfigServer->setObjectName(QStringLiteral("actionConfigServer"));
        actionScanConfig = new QAction(MainWindow);
        actionScanConfig->setObjectName(QStringLiteral("actionScanConfig"));
        actionTagManage = new QAction(MainWindow);
        actionTagManage->setObjectName(QStringLiteral("actionTagManage"));
        actionDd = new QAction(MainWindow);
        actionDd->setObjectName(QStringLiteral("actionDd"));
        actionDddd = new QAction(MainWindow);
        actionDddd->setObjectName(QStringLiteral("actionDddd"));
        graphicsWidget = new GraphicsWidget(MainWindow);
        graphicsWidget->setObjectName(QStringLiteral("graphicsWidget"));
        MainWindow->setCentralWidget(graphicsWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 499, 23));
        viewMenu = new QMenu(menuBar);
        viewMenu->setObjectName(QStringLiteral("viewMenu"));
        helpMenu = new QMenu(menuBar);
        helpMenu->setObjectName(QStringLiteral("helpMenu"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        viewSettings_dw = new QDockWidget(MainWindow);
        viewSettings_dw->setObjectName(QStringLiteral("viewSettings_dw"));
        viewSettings_w = new ViewSettingsWidget();
        viewSettings_w->setObjectName(QStringLiteral("viewSettings_w"));
        viewSettings_dw->setWidget(viewSettings_w);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), viewSettings_dw);
        minimap_dw = new QDockWidget(MainWindow);
        minimap_dw->setObjectName(QStringLiteral("minimap_dw"));
        minimap = new MinimapView();
        minimap->setObjectName(QStringLiteral("minimap"));
        minimap_dw->setWidget(minimap);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), minimap_dw);

        menuBar->addAction(viewMenu->menuAction());
        menuBar->addAction(helpMenu->menuAction());
        menuBar->addAction(menu->menuAction());
        helpMenu->addAction(actionAbout);
        menu->addAction(actionConfigServer);
        menu->addAction(actionScanConfig);
        menu->addAction(actionTagManage);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\271\276\345\235\244\347\211\251\350\201\224\345\256\232\344\275\215\345\274\225\346\223\216", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionConfig->setText(QApplication::translate("MainWindow", "Channel Config", 0));
        actionSetServer->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256TCP\346\234\215\345\212\241\345\231\250", 0));
        actionConfigServer->setText(QApplication::translate("MainWindow", "\351\205\215\347\275\256TCP\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", 0));
        actionScanConfig->setText(QApplication::translate("MainWindow", "\347\263\273\347\273\237\345\217\202\346\225\260\351\205\215\347\275\256", 0));
        actionTagManage->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\347\256\241\347\220\206", 0));
        actionDd->setText(QApplication::translate("MainWindow", "\345\237\272\347\253\231\346\211\253\346\217\217", 0));
        actionDddd->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\344\270\213\345\217\221", 0));
        viewMenu->setTitle(QApplication::translate("MainWindow", "&View", 0));
        helpMenu->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\345\212\237\350\203\275", 0));
        viewSettings_dw->setWindowTitle(QApplication::translate("MainWindow", "Settings", 0));
        minimap_dw->setWindowTitle(QApplication::translate("MainWindow", "Minimap", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
