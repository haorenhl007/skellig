#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent) :
    QOpenGLWidget(parent),
    m_model(0),
    m_camera(20.0f, 20.0f, 0.0f, 0.0f, 20.0f, 0.0f),
    m_timer(0),
    m_program(0)
{

}

GLWidget::~GLWidget() {
    makeCurrent();

    delete m_model;
    delete m_program;

    doneCurrent();
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shader.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shader.frag");
    m_program->link();

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(1000/60.0f);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
}

void GLWidget::resizeGL(int w, int h) {
    m_projectionMat.setToIdentity();
    m_projectionMat.perspective(45.0f, w / float(h), 1.0f, 1000.0f);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 viewMat = m_camera.view();

    m_program->bind();
    m_program->setUniformValue("model", m_modelMat);
    m_program->setUniformValue("view", viewMat);
    m_program->setUniformValue("projection", m_projectionMat);

    if (m_model != 0)
        m_model->draw(this);
}

void GLWidget::loadModel(QString filename) {
    makeCurrent();
    if (m_model != 0) {
        delete m_model;
    }
    m_model = new Model(filename, this);
    doneCurrent();
}

void GLWidget::setCameraX(int value) {
    m_camera.setPositionX(value);
}

void GLWidget::setModelAngle(int value) {
    m_modelMat.setToIdentity();
    m_modelMat.rotate(value, 0.0f, 1.0f, 0.0f);
}

void GLWidget::setPolygonMode(bool wireframe) {
    makeCurrent();
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    doneCurrent();
}
