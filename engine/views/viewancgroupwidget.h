#ifndef VIEWANCGROUPWIDGET_H
#define VIEWANCGROUPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox> 

/*  标签大小配置    */
#define LABEL_SIZE_X    100
#define LABEL_SIZE_Y    50

#define COMBOBOX_SIZE_X         40
#define COMBOBOX_SIZE_Y         30
#define COMBOBOX_SIZE_X_2       80

/*  标签位置配置    */
#define GROUP_X 30
#define GROUP_Y 15

#define SAMPLING_X 330
#define SAMPLING_Y 15

#define FILTER_X 30
#define FILTER_Y 80

#define KLAMN_X 30
#define KLAMN_Y 145

#define DEMENTION_X 30
#define DEMENTION_Y 210

/*  COMBOBOX位置配置    */
#define GRPSELBOX_X 72
#define GRPSELBOX_Y 28

#define SAMPSELBOX_X 410
#define SAMPSELBOX_Y 28

#define FILTSELBOX_X 110
#define FILTSELBOX_Y 93

#define DEMEMSELBOX_X 85
#define DEMEMSELBOX_Y 223

/*  勾选框位置配置  */
#define KLMANCHECKBOX_X 98    
#define KLMANCHECKBOX_Y 147


class ViewAncGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewAncGroupWidget(QWidget *parent = 0);
    ~ViewAncGroupWidget();


    /*  下拉选择框  */
    QComboBox *_groupSelectBox;
    QComboBox *_sampleSelectBox;
    QComboBox *_filterSelectBox;
    QComboBox *_dememsionSelectBox;

    /*  勾选框  */
    QCheckBox *_klmanCheckBox;
        
private:


signals:

public slots:
};

#endif // VIEWANCGROUPWIDGET_H
