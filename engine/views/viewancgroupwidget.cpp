#include "viewancgroupwidget.h"
#include <QTextCodec>
#include <QFont>

static QTextCodec *_gbkCode_group;	/*  定义转换编码格式的全局变量   */

#define Mtr(s) (_gbkCode_group->toUnicode(s))

ViewAncGroupWidget::ViewAncGroupWidget(QWidget *parent) : QWidget(parent)
{
	this->setFixedSize(748,548);
    this->setMinimumSize(640,480);

	_gbkCode_group = QTextCodec::codecForName("GB2312");//你完全可以改成GB18080等编码

	/*	设置字体大小	*/
	QFont font ("Microsoft YaHei", 10, 75); 

	
	QLabel *_group	= new QLabel(this);
	QLabel *_sampling	=	new QLabel(this);
    QLabel *_filteringOption	= new QLabel(this);
    QLabel *_KlmanFilter	= new QLabel(this);
    QLabel *_demenTion	= new QLabel(this);
	
	/*	标签相关设置	*/
	_group->setFont(font);
	_group->setText(Mtr("&组: "));
	_group->resize(LABEL_SIZE_X,LABEL_SIZE_Y);
	_group->move(GROUP_X,GROUP_Y);

	_sampling->setFont(font);
	_sampling->setText(Mtr("&采样方法: "));
	_sampling->resize(LABEL_SIZE_X,LABEL_SIZE_Y);
	_sampling->move(SAMPLING_X,SAMPLING_Y);
	
	_filteringOption->setFont(font);
	_filteringOption->setText(Mtr("&过滤方法: "));
	_filteringOption->resize(LABEL_SIZE_X,LABEL_SIZE_Y);
	_filteringOption->move(FILTER_X,FILTER_Y);

	_KlmanFilter->setFont(font);
	_KlmanFilter->setText(Mtr("&卡尔曼: "));
	_KlmanFilter->resize(LABEL_SIZE_X,LABEL_SIZE_Y);
	_KlmanFilter->move(KLAMN_X,KLAMN_Y);

	_demenTion->setFont(font);
	_demenTion->setText(Mtr("&维度: "));
	_demenTion->resize(LABEL_SIZE_X,LABEL_SIZE_Y);
	_demenTion->move(DEMENTION_X,DEMENTION_Y);

	
	/*	下拉选择框相关设置	*/
	_groupSelectBox = new QComboBox(this);
	_groupSelectBox->resize(COMBOBOX_SIZE_X, COMBOBOX_SIZE_Y);
	_groupSelectBox->move(GRPSELBOX_X,GRPSELBOX_Y);

	_sampleSelectBox = new QComboBox(this);
	_sampleSelectBox->resize(COMBOBOX_SIZE_X_2, COMBOBOX_SIZE_Y);
	_sampleSelectBox->move(SAMPSELBOX_X,SAMPSELBOX_Y);

	_filterSelectBox = new QComboBox(this);
	_filterSelectBox->resize(COMBOBOX_SIZE_X_2, COMBOBOX_SIZE_Y);
	_filterSelectBox->move(FILTSELBOX_X,FILTSELBOX_Y);

	_dememsionSelectBox = new QComboBox(this);
	_dememsionSelectBox->resize(COMBOBOX_SIZE_X_2, COMBOBOX_SIZE_Y);
	_dememsionSelectBox->move(DEMEMSELBOX_X,DEMEMSELBOX_Y);

	/*	按键相关设置	*/


	/*	勾选框相关设置	*/
	_klmanCheckBox	=	new	QCheckBox(this);
	_klmanCheckBox->setText("klman filter");
	_klmanCheckBox->resize(LABEL_SIZE_X,LABEL_SIZE_Y);
	_klmanCheckBox->move(KLMANCHECKBOX_X, KLMANCHECKBOX_Y);
	
}


ViewAncGroupWidget::~ViewAncGroupWidget()
{


}

