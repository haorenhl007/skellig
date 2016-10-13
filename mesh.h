#ifndef MESH_H
#define MESH_H

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>

struct Vertex {
    QVector3D position;
    QVector3D normal;
    QVector2D texCoords;
};

class Mesh {
public:
    Mesh();
    ~Mesh();
    void setup(QOpenGLFunctions_3_3_Core* gl);
    void draw(QOpenGLFunctions_3_3_Core* gl);

    QVector<Vertex> vertices;
    QVector<unsigned int> indices;
    QVector<QOpenGLTexture*> textures;

private:
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLVertexArrayObject m_vertexArray;
};

#endif // MESH_H
