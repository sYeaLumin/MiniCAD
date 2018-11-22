#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class MiniCADWidget :
	public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	MiniCADWidget();
	~MiniCADWidget();

protected:
	// ============== virtual function inherited form QOpenGLWidget ================
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	void mousePressEvent(QMouseEvent *mouseEvent) override;
	void mouseReleaseEvent(QMouseEvent *mouseEvent) override;
	void mouseMoveEvent(QMouseEvent *mouseEvent) override;
};

