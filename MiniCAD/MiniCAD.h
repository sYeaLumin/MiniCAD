#pragma once

#include <QtWidgets/QMainWindow>
#include <QButtonGroup>
#include "ui_MiniCAD.h"

class MiniCAD : public QMainWindow
{
	Q_OBJECT

public:
	MiniCAD(QWidget *parent = Q_NULLPTR);

public slots:
	void changeShowType();
	void pushButtonSweep();
	void pushButtonSubfaceReset();
	void pushButtonSubfaceBuild();
	void pushButtonSubfaceOutLoopAdd();
	void pushButtonSubfaceInLoopAdd();
	void pushButtonSubfaceInLoopNew();

private:
	Ui::MiniCADClass ui;
	QButtonGroup *bg;

	void showSubfacePoint();
};
