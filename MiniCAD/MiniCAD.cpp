#include "MiniCAD.h"

MiniCAD::MiniCAD(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.checkBox_lineShow, SIGNAL(toggled(bool)), ui.showWidget, SLOT(onDrawLinesCheckBoxSlot(bool)));
	connect(ui.checkBox_volumeShow, SIGNAL(toggled(bool)), ui.showWidget, SLOT(onDrawFacesCheckBoxSlot(bool)));
	
	connect(ui.pushButton_sweep, SIGNAL(clicked()), this, SLOT(pushButtonSweep()));

	//subface
	connect(ui.SubfaceButton_Build, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceBuild()));
	connect(ui.SubfaceButton_Reset, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceReset()));
	connect(ui.OutLoopButton_Add, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceOutLoopAdd()));
	connect(ui.InLoopButton_Add, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceInLoopAdd()));
	connect(ui.InLoopButton_New, SIGNAL(clicked()), this, SLOT(pushButtonSubfaceInLoopNew()));

	ui.checkBox_lineShow->setCheckState(Qt::Checked);
	ui.lineEdit_sweep_x->setText(QString("0.0"));
	ui.lineEdit_sweep_y->setText(QString("0.0"));
	ui.lineEdit_sweep_z->setText(QString("1.0"));
	ui.lineEdit_sweep_l->setText(QString("1.0"));

	ui.checkBox_volumeShow->setEnabled(false);
	ui.pushButton_sweep->setEnabled(false);

	showSubfacePoint();
}

void MiniCAD::checkBoxLine()
{
	bool state = ui.checkBox_lineShow->checkState();
	if (state) {
		ui.checkBox_lineShow->setCheckState(Qt::Unchecked);
		ui.checkBox_volumeShow->setCheckState(Qt::Checked);
	}
	else {
		ui.checkBox_volumeShow->setCheckState(Qt::Unchecked);
		ui.checkBox_lineShow->setCheckState(Qt::Checked);
	}
}

void MiniCAD::checkBoxFace()
{
	bool state = ui.checkBox_volumeShow->checkState();
	if (!state) {
		ui.checkBox_lineShow->setCheckState(Qt::Unchecked);
		ui.checkBox_volumeShow->setCheckState(Qt::Checked);
	}
	else {
		ui.checkBox_volumeShow->setCheckState(Qt::Unchecked);
		ui.checkBox_lineShow->setCheckState(Qt::Checked);
	}
}

void MiniCAD::pushButtonSweep() {
	showSubfacePoint();
	float x = ui.lineEdit_sweep_x->text().toFloat();
	float y = ui.lineEdit_sweep_y->text().toFloat();
	float z = ui.lineEdit_sweep_z->text().toFloat();
	float l = ui.lineEdit_sweep_l->text().toFloat();
	qDebug() << "MiniCAD : Click pushButton_sweep !";
	//qDebug() << "		x : " << x << " y : " << y << " z : " << z << "l : " << l;
	ui.showWidget->buttonSweep(x, y, z, l);
	ui.checkBox_volumeShow->setEnabled(true);
}

void MiniCAD::pushButtonSubfaceReset()
{
	ui.showWidget->modelSubfaceReset();
	showSubfacePoint();
}

void MiniCAD::pushButtonSubfaceBuild()
{
	ui.showWidget->modelSubfaceBuild();
	ui.pushButton_sweep->setEnabled(true);
	ui.SubfaceButton_Build->setEnabled(false);
	ui.OutLoopButton_Add->setEnabled(false);
	ui.InLoopButton_Add->setEnabled(false);
}

void MiniCAD::pushButtonSubfaceOutLoopAdd()
{
	float x = ui.OutLoopInput_x_2->text().toFloat();
	float y = ui.OutLoopInput_y->text().toFloat();
	float z = ui.OutLoopInput_z->text().toFloat();
	ui.showWidget->modelSubfaceAddOutLoopPoint(x, y, z);
	showSubfacePoint();
}

void MiniCAD::pushButtonSubfaceInLoopAdd()
{
	float x = ui.InLoopInput_x->text().toFloat();
	float y = ui.InLoopInput_y->text().toFloat();
	float z = ui.InLoopInput_z->text().toFloat();
	ui.showWidget->modelSubfaceAddInLoopPoint(x, y, z);
	ui.InLoopButton_New->setEnabled(false);
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
