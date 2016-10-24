#ifndef MODEL_H
#define MODEL_H

#include <QDir>
#include <QVector>
#include <QString>
#include <QFileInfo>
#include <QMatrix4x4>
#include <QOpenGLFunctions_3_3_Core>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "mesh.h"

struct Node {
    ~Node();
    QString name;
    QVector<Node*> children;
    QMatrix4x4 transformation;
    QVector<unsigned int> meshes;
};

class Model {
public:
    Model(QString filename, QOpenGLFunctions_3_3_Core* context);
    ~Model();
    void draw(QOpenGLFunctions_3_3_Core* context, QOpenGLShaderProgram* program);
    Node* rootNode;

private:
    void drawNode(Node* node, QMatrix4x4 transform, QOpenGLFunctions_3_3_Core* context, QOpenGLShaderProgram* program);
    void processNode(QOpenGLFunctions_3_3_Core* context, aiNode* source, Node* node, const aiScene* scene);
    void processMesh(aiMesh* source, Mesh* mesh, const aiScene* scene);
    void loadTextures(Mesh* mesh, aiMaterial* material, aiTextureType type);

    QFileInfo m_fileInfo;
    QVector<Mesh*> m_meshes;
};

#endif // MODEL_H
