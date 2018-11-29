#include "MiniCAD.h"

MiniCAD::MiniCAD(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.checkBox_lineShow, SIGNAL(toggled(bool)), ui.showWidget, SLOT(onDrawLinesCheckBoxSlot(bool)));
	connect(ui.checkBox_volumeShow, SIGNAL(toggled(bool)), ui.showWidget, SLOT(onDrawFacesCheckBoxSlot(bool)));
	

	ui.checkBox_lineShow->setCheckState(Qt::Checked);
	//ui.checkBox_volumeShow->setCheckState(Qt::Checked);
}
