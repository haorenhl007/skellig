#include "camera.h"

Camera::Camera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ, QVector3D& worldUp) :
    m_position(posX, posY, posZ),
    m_target(targetX, targetY, targetZ),
    m_worldUp(worldUp)
{

}

Camera::Camera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ) :
    m_position(posX, posY, posZ),
    m_target(targetX, targetY, targetZ),
    m_worldUp(0.0f, 1.0f, 0.0f)
{

}

QVector3D Camera::position() const {
    return m_position;
}

QVector3D Camera::target() const {
    return m_target;
}

QMatrix4x4 Camera::view() const {
    QMatrix4x4 view;
    view.lookAt(m_position, m_target, m_worldUp);
    return view;
}

void Camera::setPositionX(float x) {
    m_position = QVector3D(x, m_position.y(), m_position.z());
}

void Camera::setPositionY(float y) {
    m_position = QVector3D(m_position.x(), y, m_position.z());
}

void Camera::setPositionZ(float z) {
    m_position = QVector3D(m_position.x(), m_position.y(), z);
}

void Camera::setPosition(float x, float y, float z) {
    m_position = QVector3D(x, y, z);
}
