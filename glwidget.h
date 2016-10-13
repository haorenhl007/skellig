#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>

#include "model.h"
#include "camera.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    GLWidget(QWidget* parent);
    ~GLWidget();

    void loadModel(QString filename);

public slots:
    void setCameraX(int value);
    void setModelAngle(int value);
    void setPolygonMode(bool wireframe);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    Model* m_model;
    QMatrix4x4 m_modelMat;
    QMatrix4x4 m_projectionMat;

    Camera m_camera;
    QTimer* m_timer;

    QOpenGLShaderProgram* m_program;
};

#endif // GLWIDGET_H
