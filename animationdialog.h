#ifndef ANIMATIONDIALOG_H
#define ANIMATIONDIALOG_H

#include <QMap>
#include <QList>
#include <QDialog>
#include <QQuaternion>
#include <QStringList>
#include <QTreeWidgetItem>
#include "model.h"

namespace Ui {
    class AnimationDialog;
}

class AnimationDialog : public QDialog {
    Q_OBJECT

public:
    explicit AnimationDialog(QWidget* parent = 0);
    ~AnimationDialog();

public slots:
    void loadNodes(Model* model);
    void resetAll();
    void activeItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);

    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);

private:
    void loadTree(Node* parentNode, QTreeWidgetItem* parentItem);

    Ui::AnimationDialog* ui;
    Model* model;
    QMap<QTreeWidgetItem*, Node*> nodeMap;
};

#endif // ANIMATIONDIALOG_H
