#include "MiniCADWidget.h"



MiniCADWidget::MiniCADWidget(QWidget *parent)
{
}


MiniCADWidget::~MiniCADWidget()
{
}

void MiniCADWidget::initializeGL()
{
	initializeOpenGLFunctions();
	//ÆäËûinit

}

void MiniCADWidget::paintGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw
}

void MiniCADWidget::resizeGL(int width, int height)
{
}

void MiniCADWidget::mousePressEvent(QMouseEvent * mouseEvent)
{
}

void MiniCADWidget::mouseReleaseEvent(QMouseEvent * mouseEvent)
{
}

void MiniCADWidget::mouseMoveEvent(QMouseEvent * mouseEvent)
{
}
