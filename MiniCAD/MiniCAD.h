#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MiniCAD.h"

class MiniCAD : public QMainWindow
{
	Q_OBJECT

public:
	MiniCAD(QWidget *parent = Q_NULLPTR);

public slots:
	void pushButtonSweep();

private:
	Ui::MiniCADClass ui;
};
