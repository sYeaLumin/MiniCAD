#include "MiniCAD.h"

MiniCAD::MiniCAD(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.checkBox_lineShow, SIGNAL(toggled(bool)), ui.showWidget, SLOT(onDrawLinesCheckBoxSlot(bool)));
	connect(ui.checkBox_volumeShow, SIGNAL(toggled(bool)), ui.showWidget, SLOT(onDrawFacesCheckBoxSlot(bool)));
	
	connect(ui.pushButton_sweep, SIGNAL(clicked()), this, SLOT(pushButtonSweep()));

	ui.checkBox_lineShow->setCheckState(Qt::Checked);
	ui.lineEdit_sweep_x->setText(QString("0.0"));
	ui.lineEdit_sweep_y->setText(QString("0.0"));
	ui.lineEdit_sweep_z->setText(QString("1.0"));
	ui.lineEdit_sweep_l->setText(QString("1.0"));
}

void MiniCAD::pushButtonSweep() {
	float x = ui.lineEdit_sweep_x->text().toFloat();
	float y = ui.lineEdit_sweep_y->text().toFloat();
	float z = ui.lineEdit_sweep_z->text().toFloat();
	float l = ui.lineEdit_sweep_l->text().toFloat();
	qDebug() << "MiniCAD : Click pushButton_sweep !";
	//qDebug() << "		x : " << x << " y : " << y << " z : " << z << "l : " << l;
	ui.showWidget->buttonSweep(x, y, z, l);
}