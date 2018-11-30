#include "MiniCAD.h"

MiniCAD::MiniCAD(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//show
	bg = new QButtonGroup(this);
	bg->addButton(ui.radioButton_lineShow, 0);
	bg->addButton(ui.radioButton_CDTlineShow, 1);
	bg->addButton(ui.radioButton_volumeShow, 2);
	connect(ui.radioButton_lineShow, SIGNAL(clicked()), this, SLOT(changeShowType()));
	connect(ui.radioButton_CDTlineShow, SIGNAL(clicked()), this, SLOT(changeShowType()));
	connect(ui.radioButton_volumeShow, SIGNAL(clicked()), this, SLOT(changeShowType()));
	ui.radioButton_CDTlineShow->setEnabled(false);
	ui.radioButton_volumeShow->setEnabled(false);

	//sweep
	ui.lineEdit_sweep_x->setText(QString("0.0"));
	ui.lineEdit_sweep_y->setText(QString("0.0"));
	ui.lineEdit_sweep_z->setText(QString("1.0"));
	ui.lineEdit_sweep_l->setText(QString("1.0"));
	connect(ui.pushButton_sweep, SIGNAL(clicked()), this, SLOT(pushButtonSweep()));
	ui.pushButton_sweep->setEnabled(false);

	//subface
	connect(ui.SubfaceButton_Build, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceBuild()));
	connect(ui.SubfaceButton_Reset, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceReset()));
	connect(ui.OutLoopButton_Add, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceOutLoopAdd()));
	connect(ui.InLoopButton_Add, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceInLoopAdd()));
	connect(ui.InLoopButton_New, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceInLoopNew()));
	//ui.InLoopButton_New->setEnabled(false);

	showSubfacePoint();

	string tip = "Tips : \n";
	tip += "1  Push button -New-\n";
	tip += "2  Push button -Build-\n";
	tip += "3  Push button -Sweep-\n";
	tip += "4  Change the show type\n\n";
	tip += "Use -Reset- before -Build-\n";
	tip += "to set your own data.";
	ui.label_tips->setText(QString(tip.c_str()));
}

void MiniCAD::changeShowType()
{
	int id = bg->checkedId();
	qDebug() << "changeShowType() : " << id;
	ui.showWidget->changeDrawType(id);
}

void MiniCAD::pushButtonSweep() {
	showSubfacePoint();
	float x = ui.lineEdit_sweep_x->text().toFloat();
	float y = ui.lineEdit_sweep_y->text().toFloat();
	float z = ui.lineEdit_sweep_z->text().toFloat();
	float l = ui.lineEdit_sweep_l->text().toFloat();
	ui.showWidget->buttonSweep(x, y, z, l);
	ui.radioButton_CDTlineShow->setEnabled(true);
	ui.radioButton_volumeShow->setEnabled(true);
	ui.pushButton_sweep->setEnabled(false);
}

void MiniCAD::pushButtonSubfaceReset()
{
	ui.showWidget->modelSubfaceReset();
	ui.SubfaceButton_Build->setEnabled(false);
	ui.InLoopButton_New->setEnabled(false);
	showSubfacePoint();
}

void MiniCAD::pushButtonSubfaceBuild()
{
	ui.showWidget->modelSubfaceBuild();
	ui.pushButton_sweep->setEnabled(true);
	ui.SubfaceButton_Build->setEnabled(false);
	ui.OutLoopButton_Add->setEnabled(false);
	ui.InLoopButton_Add->setEnabled(false);
	ui.SubfaceButton_Reset->setEnabled(false);
}

void MiniCAD::pushButtonSubfaceOutLoopAdd()
{
	float x = ui.OutLoopInput_x_2->text().toFloat();
	float y = ui.OutLoopInput_y->text().toFloat();
	float z = ui.OutLoopInput_z->text().toFloat();
	ui.showWidget->modelSubfaceAddOutLoopPoint(x, y, z);
	ui.SubfaceButton_Build->setEnabled(true);
	showSubfacePoint();
}

void MiniCAD::pushButtonSubfaceInLoopAdd()
{
	float x = ui.InLoopInput_x->text().toFloat();
	float y = ui.InLoopInput_y->text().toFloat();
	float z = ui.InLoopInput_z->text().toFloat();
	ui.showWidget->modelSubfaceAddInLoopPoint(x, y, z);
	ui.InLoopButton_New->setEnabled(true);
	showSubfacePoint();
}

void MiniCAD::pushButtonSubfaceInLoopNew()
{
	ui.showWidget->modelSubfaceNewInLoopPoint();
	showSubfacePoint();
	ui.InLoopButton_New->setEnabled(false);
}

void MiniCAD::showSubfacePoint()
{
	ui.SubfacePointShowLabel->setText(ui.showWidget->subfacePointShowData());
}
