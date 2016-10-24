#include "animationdialog.h"
#include "ui_animationdialog.h"

AnimationDialog::AnimationDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AnimationDialog),
    model(0)
{
    ui->setupUi(this);
}

AnimationDialog::~AnimationDialog() {
    delete ui;
}

void AnimationDialog::loadNodes(Model* model) {
    Node* rootNode = model->rootNode;
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(ui->treeWidget, QStringList(rootNode->name));

    nodeMap.insert(rootItem, rootNode);
    loadTree(rootNode, rootItem);
}

void AnimationDialog::loadTree(Node* parentNode, QTreeWidgetItem* parentItem) {
    for(int i = 0; i < parentNode->children.size(); i++) {
        Node* childNode = parentNode->children[i];
        QTreeWidgetItem* childItem = new QTreeWidgetItem(parentItem, QStringList(childNode->name));

        nodeMap.insert(childItem, childNode);
        loadTree(childNode, childItem);
    }
}

void AnimationDialog::resetAll() {
    model = 0;
    ui->treeWidget->clear();
}
