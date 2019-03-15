/********************************************************************************
** Form generated from reading UI file 'ViewSettingsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWSETTINGSWIDGET_H
#define UI_VIEWSETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewSettingsWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *config_tab;
    QCheckBox *showTagHistory;
    QCheckBox *showGeoFencingMode;
    QDoubleSpinBox *zone1;
    QDoubleSpinBox *zone2;
    QLabel *label_z1;
    QLabel *label_z2;
    QRadioButton *inAlarm;
    QRadioButton *outAlarm;
    QSpinBox *tagHistoryN;
    QCheckBox *showTagTable;
    QCheckBox *showAnchorTable;
    QCheckBox *showAnchorTagCorrectionTable;
    QCheckBox *showNavigationMode;
    QComboBox *filtering;
    QLabel *label_z1_2;
    QCheckBox *useAutoPos;
    QLabel *label_logingstatus;
    QPushButton *logging_pb;
    QLabel *label_logingstatus_2;
    QLabel *label_logfile;
    QLabel *label_logingstatus_3;
    QCheckBox *klmanfilterBox;
    QLabel *label_13;
    QComboBox *vecBox;
    QPushButton *cleanHisBtn;
    QLineEdit *udpPortEdit;
    QLabel *label_14;
    QPushButton *changeUdpBtn;
    QWidget *floorplan_tab;
    QGridLayout *gridLayout_2;
    QLabel *label_11;
    QDoubleSpinBox *floorplanXScale_sb;
    QLabel *label_9;
    QLabel *label_3;
    QSpinBox *floorplanXOff_sb;
    QLabel *floorplanPath_lb;
    QCheckBox *floorplanFlipY_cb;
    QSpacerItem *verticalSpacer;
    QLabel *label_12;
    QDoubleSpinBox *floorplanYScale_sb;
    QLabel *label_10;
    QSpinBox *floorplanYOff_sb;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_4;
    QCheckBox *floorplanFlipX_cb;
    QLabel *label_5;
    QLabel *label_8;
    QGridLayout *gridLayout;
    QCheckBox *showOrigin;
    QPushButton *scaleY_pb;
    QPushButton *scaleX_pb;
    QPushButton *origin_pb;
    QPushButton *floorplanOpen_pb;
    QCheckBox *saveFP;
    QWidget *grid_tab;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QDoubleSpinBox *gridWidth_sb;
    QLabel *label_2;
    QDoubleSpinBox *gridHeight_sb;
    QCheckBox *gridShow;
    QWidget *tab;
    QTextBrowser *tcpDebugBrow;
    QPushButton *clearDebugBtn;

    void setupUi(QWidget *ViewSettingsWidget)
    {
        if (ViewSettingsWidget->objectName().isEmpty())
            ViewSettingsWidget->setObjectName(QStringLiteral("ViewSettingsWidget"));
        ViewSettingsWidget->resize(322, 813);
        verticalLayout = new QVBoxLayout(ViewSettingsWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(ViewSettingsWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(300, 300));
        config_tab = new QWidget();
        config_tab->setObjectName(QStringLiteral("config_tab"));
        showTagHistory = new QCheckBox(config_tab);
        showTagHistory->setObjectName(QStringLiteral("showTagHistory"));
        showTagHistory->setGeometry(QRect(20, 400, 121, 17));
        showGeoFencingMode = new QCheckBox(config_tab);
        showGeoFencingMode->setObjectName(QStringLiteral("showGeoFencingMode"));
        showGeoFencingMode->setGeometry(QRect(20, 50, 109, 17));
        zone1 = new QDoubleSpinBox(config_tab);
        zone1->setObjectName(QStringLiteral("zone1"));
        zone1->setGeometry(QRect(100, 90, 62, 22));
        zone1->setMaximum(300);
        zone1->setValue(2);
        zone2 = new QDoubleSpinBox(config_tab);
        zone2->setObjectName(QStringLiteral("zone2"));
        zone2->setGeometry(QRect(100, 130, 62, 22));
        zone2->setMaximum(300);
        zone2->setValue(4);
        label_z1 = new QLabel(config_tab);
        label_z1->setObjectName(QStringLiteral("label_z1"));
        label_z1->setGeometry(QRect(30, 90, 61, 20));
        label_z2 = new QLabel(config_tab);
        label_z2->setObjectName(QStringLiteral("label_z2"));
        label_z2->setGeometry(QRect(30, 130, 61, 20));
        inAlarm = new QRadioButton(config_tab);
        inAlarm->setObjectName(QStringLiteral("inAlarm"));
        inAlarm->setGeometry(QRect(130, 170, 91, 17));
        inAlarm->setChecked(true);
        outAlarm = new QRadioButton(config_tab);
        outAlarm->setObjectName(QStringLiteral("outAlarm"));
        outAlarm->setGeometry(QRect(20, 170, 91, 17));
        tagHistoryN = new QSpinBox(config_tab);
        tagHistoryN->setObjectName(QStringLiteral("tagHistoryN"));
        tagHistoryN->setGeometry(QRect(140, 400, 51, 22));
        tagHistoryN->setMinimum(1);
        tagHistoryN->setMaximum(128);
        tagHistoryN->setValue(20);
        showTagTable = new QCheckBox(config_tab);
        showTagTable->setObjectName(QStringLiteral("showTagTable"));
        showTagTable->setGeometry(QRect(20, 490, 109, 17));
        showTagTable->setChecked(true);
        showAnchorTable = new QCheckBox(config_tab);
        showAnchorTable->setObjectName(QStringLiteral("showAnchorTable"));
        showAnchorTable->setGeometry(QRect(20, 520, 109, 17));
        showAnchorTable->setChecked(true);
        showAnchorTagCorrectionTable = new QCheckBox(config_tab);
        showAnchorTagCorrectionTable->setObjectName(QStringLiteral("showAnchorTagCorrectionTable"));
        showAnchorTagCorrectionTable->setEnabled(true);
        showAnchorTagCorrectionTable->setGeometry(QRect(20, 550, 191, 17));
        showAnchorTagCorrectionTable->setChecked(false);
        showNavigationMode = new QCheckBox(config_tab);
        showNavigationMode->setObjectName(QStringLiteral("showNavigationMode"));
        showNavigationMode->setGeometry(QRect(20, 20, 151, 17));
        showNavigationMode->setChecked(true);
        filtering = new QComboBox(config_tab);
        filtering->setObjectName(QStringLiteral("filtering"));
        filtering->setGeometry(QRect(120, 260, 111, 22));
        label_z1_2 = new QLabel(config_tab);
        label_z1_2->setObjectName(QStringLiteral("label_z1_2"));
        label_z1_2->setGeometry(QRect(20, 260, 81, 20));
        useAutoPos = new QCheckBox(config_tab);
        useAutoPos->setObjectName(QStringLiteral("useAutoPos"));
        useAutoPos->setEnabled(true);
        useAutoPos->setGeometry(QRect(20, 210, 161, 17));
        useAutoPos->setChecked(false);
        label_logingstatus = new QLabel(config_tab);
        label_logingstatus->setObjectName(QStringLiteral("label_logingstatus"));
        label_logingstatus->setGeometry(QRect(20, 300, 91, 20));
        logging_pb = new QPushButton(config_tab);
        logging_pb->setObjectName(QStringLiteral("logging_pb"));
        logging_pb->setGeometry(QRect(120, 300, 111, 23));
        label_logingstatus_2 = new QLabel(config_tab);
        label_logingstatus_2->setObjectName(QStringLiteral("label_logingstatus_2"));
        label_logingstatus_2->setGeometry(QRect(20, 400, 51, 20));
        label_logfile = new QLabel(config_tab);
        label_logfile->setObjectName(QStringLiteral("label_logfile"));
        label_logfile->setGeometry(QRect(20, 330, 211, 20));
        label_logingstatus_3 = new QLabel(config_tab);
        label_logingstatus_3->setObjectName(QStringLiteral("label_logingstatus_3"));
        label_logingstatus_3->setGeometry(QRect(20, 240, 51, 20));
        klmanfilterBox = new QCheckBox(config_tab);
        klmanfilterBox->setObjectName(QStringLiteral("klmanfilterBox"));
        klmanfilterBox->setGeometry(QRect(20, 370, 101, 16));
        label_13 = new QLabel(config_tab);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(20, 441, 54, 21));
        vecBox = new QComboBox(config_tab);
        vecBox->setObjectName(QStringLiteral("vecBox"));
        vecBox->setGeometry(QRect(110, 440, 69, 22));
        cleanHisBtn = new QPushButton(config_tab);
        cleanHisBtn->setObjectName(QStringLiteral("cleanHisBtn"));
        cleanHisBtn->setGeometry(QRect(210, 400, 51, 23));
        udpPortEdit = new QLineEdit(config_tab);
        udpPortEdit->setObjectName(QStringLiteral("udpPortEdit"));
        udpPortEdit->setGeometry(QRect(70, 590, 61, 21));
        label_14 = new QLabel(config_tab);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(20, 590, 41, 21));
        changeUdpBtn = new QPushButton(config_tab);
        changeUdpBtn->setObjectName(QStringLiteral("changeUdpBtn"));
        changeUdpBtn->setGeometry(QRect(140, 590, 51, 23));
        tabWidget->addTab(config_tab, QString());
        floorplan_tab = new QWidget();
        floorplan_tab->setObjectName(QStringLiteral("floorplan_tab"));
        gridLayout_2 = new QGridLayout(floorplan_tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_11 = new QLabel(floorplan_tab);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 3, 2, 1, 1);

        floorplanXScale_sb = new QDoubleSpinBox(floorplan_tab);
        floorplanXScale_sb->setObjectName(QStringLiteral("floorplanXScale_sb"));
        floorplanXScale_sb->setMaximum(1000);

        gridLayout_2->addWidget(floorplanXScale_sb, 4, 1, 1, 1);

        label_9 = new QLabel(floorplan_tab);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 5, 2, 1, 1);

        label_3 = new QLabel(floorplan_tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        floorplanXOff_sb = new QSpinBox(floorplan_tab);
        floorplanXOff_sb->setObjectName(QStringLiteral("floorplanXOff_sb"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(floorplanXOff_sb->sizePolicy().hasHeightForWidth());
        floorplanXOff_sb->setSizePolicy(sizePolicy);
        floorplanXOff_sb->setMinimum(-65536);
        floorplanXOff_sb->setMaximum(65535);

        gridLayout_2->addWidget(floorplanXOff_sb, 2, 1, 1, 1);

        floorplanPath_lb = new QLabel(floorplan_tab);
        floorplanPath_lb->setObjectName(QStringLiteral("floorplanPath_lb"));

        gridLayout_2->addWidget(floorplanPath_lb, 0, 0, 1, 2);

        floorplanFlipY_cb = new QCheckBox(floorplan_tab);
        floorplanFlipY_cb->setObjectName(QStringLiteral("floorplanFlipY_cb"));

        gridLayout_2->addWidget(floorplanFlipY_cb, 7, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 9, 0, 1, 1);

        label_12 = new QLabel(floorplan_tab);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 2, 2, 1, 1);

        floorplanYScale_sb = new QDoubleSpinBox(floorplan_tab);
        floorplanYScale_sb->setObjectName(QStringLiteral("floorplanYScale_sb"));
        floorplanYScale_sb->setMaximum(1000);

        gridLayout_2->addWidget(floorplanYScale_sb, 5, 1, 1, 1);

        label_10 = new QLabel(floorplan_tab);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 4, 2, 1, 1);

        floorplanYOff_sb = new QSpinBox(floorplan_tab);
        floorplanYOff_sb->setObjectName(QStringLiteral("floorplanYOff_sb"));
        floorplanYOff_sb->setMinimum(-65536);
        floorplanYOff_sb->setMaximum(65536);

        gridLayout_2->addWidget(floorplanYOff_sb, 3, 1, 1, 1);

        label_6 = new QLabel(floorplan_tab);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        label_7 = new QLabel(floorplan_tab);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 6, 0, 1, 1);

        label_4 = new QLabel(floorplan_tab);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        floorplanFlipX_cb = new QCheckBox(floorplan_tab);
        floorplanFlipX_cb->setObjectName(QStringLiteral("floorplanFlipX_cb"));

        gridLayout_2->addWidget(floorplanFlipX_cb, 6, 1, 1, 1);

        label_5 = new QLabel(floorplan_tab);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 5, 0, 1, 1);

        label_8 = new QLabel(floorplan_tab);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 7, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        showOrigin = new QCheckBox(floorplan_tab);
        showOrigin->setObjectName(QStringLiteral("showOrigin"));

        gridLayout->addWidget(showOrigin, 0, 0, 1, 1);

        scaleY_pb = new QPushButton(floorplan_tab);
        scaleY_pb->setObjectName(QStringLiteral("scaleY_pb"));

        gridLayout->addWidget(scaleY_pb, 1, 2, 1, 1);

        scaleX_pb = new QPushButton(floorplan_tab);
        scaleX_pb->setObjectName(QStringLiteral("scaleX_pb"));

        gridLayout->addWidget(scaleX_pb, 1, 0, 1, 1);

        origin_pb = new QPushButton(floorplan_tab);
        origin_pb->setObjectName(QStringLiteral("origin_pb"));

        gridLayout->addWidget(origin_pb, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 8, 0, 1, 2);

        floorplanOpen_pb = new QPushButton(floorplan_tab);
        floorplanOpen_pb->setObjectName(QStringLiteral("floorplanOpen_pb"));
        sizePolicy.setHeightForWidth(floorplanOpen_pb->sizePolicy().hasHeightForWidth());
        floorplanOpen_pb->setSizePolicy(sizePolicy);
        floorplanOpen_pb->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(floorplanOpen_pb, 1, 0, 1, 1);

        saveFP = new QCheckBox(floorplan_tab);
        saveFP->setObjectName(QStringLiteral("saveFP"));

        gridLayout_2->addWidget(saveFP, 1, 1, 1, 1, Qt::AlignHCenter);

        tabWidget->addTab(floorplan_tab, QString());
        grid_tab = new QWidget();
        grid_tab->setObjectName(QStringLiteral("grid_tab"));
        layoutWidget = new QWidget(grid_tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 21, 143, 111));
        gridLayout_3 = new QGridLayout(layoutWidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(45, 0));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        gridWidth_sb = new QDoubleSpinBox(layoutWidget);
        gridWidth_sb->setObjectName(QStringLiteral("gridWidth_sb"));
        gridWidth_sb->setDecimals(2);
        gridWidth_sb->setSingleStep(0.1);
        gridWidth_sb->setValue(0.5);

        gridLayout_3->addWidget(gridWidth_sb, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(45, 0));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        gridHeight_sb = new QDoubleSpinBox(layoutWidget);
        gridHeight_sb->setObjectName(QStringLiteral("gridHeight_sb"));
        gridHeight_sb->setSingleStep(0.1);
        gridHeight_sb->setValue(0.5);

        gridLayout_3->addWidget(gridHeight_sb, 1, 1, 1, 1);

        gridShow = new QCheckBox(layoutWidget);
        gridShow->setObjectName(QStringLiteral("gridShow"));

        gridLayout_3->addWidget(gridShow, 2, 0, 1, 1);

        tabWidget->addTab(grid_tab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tcpDebugBrow = new QTextBrowser(tab);
        tcpDebugBrow->setObjectName(QStringLiteral("tcpDebugBrow"));
        tcpDebugBrow->setGeometry(QRect(20, 30, 261, 631));
        clearDebugBtn = new QPushButton(tab);
        clearDebugBtn->setObjectName(QStringLiteral("clearDebugBtn"));
        clearDebugBtn->setGeometry(QRect(200, 670, 75, 23));
        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        QWidget::setTabOrder(gridWidth_sb, gridHeight_sb);
        QWidget::setTabOrder(gridHeight_sb, floorplanOpen_pb);
        QWidget::setTabOrder(floorplanOpen_pb, floorplanXOff_sb);
        QWidget::setTabOrder(floorplanXOff_sb, floorplanYOff_sb);
        QWidget::setTabOrder(floorplanYOff_sb, floorplanXScale_sb);
        QWidget::setTabOrder(floorplanXScale_sb, floorplanYScale_sb);
        QWidget::setTabOrder(floorplanYScale_sb, floorplanFlipX_cb);
        QWidget::setTabOrder(floorplanFlipX_cb, floorplanFlipY_cb);

        retranslateUi(ViewSettingsWidget);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(ViewSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *ViewSettingsWidget)
    {
        ViewSettingsWidget->setWindowTitle(QApplication::translate("ViewSettingsWidget", "Form", 0));
#ifndef QT_NO_ACCESSIBILITY
        tabWidget->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        showTagHistory->setText(QApplication::translate("ViewSettingsWidget", "Show Tag History", 0));
        showGeoFencingMode->setText(QApplication::translate("ViewSettingsWidget", "Geo-Fencing Mode", 0));
        label_z1->setText(QApplication::translate("ViewSettingsWidget", "Zone 1 (m)", 0));
        label_z2->setText(QApplication::translate("ViewSettingsWidget", "Zone 2 (m)", 0));
        inAlarm->setText(QApplication::translate("ViewSettingsWidget", "Alarm Inside", 0));
        outAlarm->setText(QApplication::translate("ViewSettingsWidget", "Alarm Outside", 0));
        showTagTable->setText(QApplication::translate("ViewSettingsWidget", "Show Tag Table", 0));
        showAnchorTable->setText(QApplication::translate("ViewSettingsWidget", "Show Anchor Table", 0));
        showAnchorTagCorrectionTable->setText(QApplication::translate("ViewSettingsWidget", "Show Anchor-Tag Correction Table", 0));
        showNavigationMode->setText(QApplication::translate("ViewSettingsWidget", "Tracking/Navigation Mode", 0));
        label_z1_2->setText(QApplication::translate("ViewSettingsWidget", "Filtering options:", 0));
        useAutoPos->setText(QApplication::translate("ViewSettingsWidget", "Use Auto - Positioning", 0));
        label_logingstatus->setText(QApplication::translate("ViewSettingsWidget", "Logging:", 0));
        logging_pb->setText(QApplication::translate("ViewSettingsWidget", "Start", 0));
        label_logingstatus_2->setText(QString());
        label_logfile->setText(QApplication::translate("ViewSettingsWidget", "Log filename", 0));
        label_logingstatus_3->setText(QString());
        klmanfilterBox->setText(QApplication::translate("ViewSettingsWidget", "klman filter", 0));
        label_13->setText(QApplication::translate("ViewSettingsWidget", "Demension", 0));
        vecBox->clear();
        vecBox->insertItems(0, QStringList()
         << QApplication::translate("ViewSettingsWidget", "Vec1", 0)
         << QApplication::translate("ViewSettingsWidget", "Vec3", 0)
        );
        cleanHisBtn->setText(QApplication::translate("ViewSettingsWidget", "Clean", 0));
        udpPortEdit->setText(QApplication::translate("ViewSettingsWidget", "52000", 0));
        label_14->setText(QApplication::translate("ViewSettingsWidget", "\347\253\257\345\217\243\357\274\232", 0));
        changeUdpBtn->setText(QApplication::translate("ViewSettingsWidget", "\346\233\264\346\224\271", 0));
        tabWidget->setTabText(tabWidget->indexOf(config_tab), QApplication::translate("ViewSettingsWidget", "Configuration", 0));
        label_11->setText(QApplication::translate("ViewSettingsWidget", "pixels", 0));
        label_9->setText(QApplication::translate("ViewSettingsWidget", "pixesl/m", 0));
        label_3->setText(QApplication::translate("ViewSettingsWidget", "X Offset", 0));
        floorplanPath_lb->setText(QApplication::translate("ViewSettingsWidget", "No Floor Plan", 0));
        floorplanFlipY_cb->setText(QString());
        label_12->setText(QApplication::translate("ViewSettingsWidget", "pixels", 0));
        label_10->setText(QApplication::translate("ViewSettingsWidget", "pixels/m", 0));
        label_6->setText(QApplication::translate("ViewSettingsWidget", "X Scale", 0));
        label_7->setText(QApplication::translate("ViewSettingsWidget", "Flip X", 0));
        label_4->setText(QApplication::translate("ViewSettingsWidget", "Y Offset", 0));
        floorplanFlipX_cb->setText(QString());
        label_5->setText(QApplication::translate("ViewSettingsWidget", "Y Scale", 0));
        label_8->setText(QApplication::translate("ViewSettingsWidget", "Flip Y", 0));
        showOrigin->setText(QApplication::translate("ViewSettingsWidget", "Show Origin", 0));
        scaleY_pb->setText(QApplication::translate("ViewSettingsWidget", "Y Scale", 0));
        scaleX_pb->setText(QApplication::translate("ViewSettingsWidget", "X Scale", 0));
        origin_pb->setText(QApplication::translate("ViewSettingsWidget", "Set Origin", 0));
        floorplanOpen_pb->setText(QApplication::translate("ViewSettingsWidget", "Open", 0));
        saveFP->setText(QApplication::translate("ViewSettingsWidget", "Save Settings", 0));
        tabWidget->setTabText(tabWidget->indexOf(floorplan_tab), QApplication::translate("ViewSettingsWidget", "Floor Plan", 0));
        label->setText(QApplication::translate("ViewSettingsWidget", "Width (m)", 0));
        label_2->setText(QApplication::translate("ViewSettingsWidget", "Height (m)", 0));
        gridShow->setText(QApplication::translate("ViewSettingsWidget", "Show Grid", 0));
        tabWidget->setTabText(tabWidget->indexOf(grid_tab), QApplication::translate("ViewSettingsWidget", "Grid", 0));
        clearDebugBtn->setText(QApplication::translate("ViewSettingsWidget", "\346\270\205\347\251\272\346\230\276\347\244\272", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ViewSettingsWidget", "\350\260\203\350\257\225\344\277\241\346\201\257", 0));
    } // retranslateUi

};

namespace Ui {
    class ViewSettingsWidget: public Ui_ViewSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWSETTINGSWIDGET_H
