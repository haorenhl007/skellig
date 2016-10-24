#include "animationdialog.h"
#include "ui_animationdialog.h"

AnimationDialog::AnimationDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AnimationDialog),
    model(0)
{
    ui->setupUi(this);
    connect(ui->xSpinBox, SIGNAL(valueChanged(double)), this, SLOT(rotateX(double)));
    connect(ui->ySpinBox, SIGNAL(valueChanged(double)), this, SLOT(rotateY(double)));
    connect(ui->zSpinBox, SIGNAL(valueChanged(double)), this, SLOT(rotateZ(double)));

    connect(ui->treeWidget, &QTreeWidget::currentItemChanged, this, &AnimationDialog::activeItemChanged);
}

AnimationDialog::~AnimationDialog() {
    delete ui;
}

void AnimationDialog::loadNodes(Model* model) {
    this->model = model;

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

void AnimationDialog::activeItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous) {
    if(previous) {
        Node* node = nodeMap.value(previous);
        node->transformation.setToIdentity();
    }

    if(current) {
        Node* node = nodeMap.value(current);
        node->transformation.setToIdentity();
    }

    ui->xSpinBox->setValue(0);
    ui->ySpinBox->setValue(0);
    ui->zSpinBox->setValue(0);
}

void AnimationDialog::rotateX(double angle) {
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item && model != 0) {
        Node* node = nodeMap.value(item);
        node->transformation.setToIdentity();

        node->transformation.rotate(angle, 1.0f, 0.0f, 0.0f);
        node->transformation.rotate(ui->ySpinBox->value(), 0.0f, 1.0f, 0.0f);
        node->transformation.rotate(ui->zSpinBox->value(), 0.0f, 0.0f, 1.0f);
    }
}

void AnimationDialog::rotateY(double angle) {
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item && model != 0) {
        Node* node = nodeMap.value(item);
        node->transformation.setToIdentity();

        node->transformation.rotate(ui->xSpinBox->value(), 1.0f, 0.0f, 0.0f);
        node->transformation.rotate(angle, 0.0f, 1.0f, 0.0f);
        node->transformation.rotate(ui->zSpinBox->value(), 0.0f, 0.0f, 1.0f);
    }
}

void AnimationDialog::rotateZ(double angle) {
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item && model != 0) {
        Node* node = nodeMap.value(item);
        node->transformation.setToIdentity();

        node->transformation.rotate(ui->xSpinBox->value(), 1.0f, 0.0f, 0.0f);
        node->transformation.rotate(ui->ySpinBox->value(), 0.0f, 1.0f, 0.0f);
        node->transformation.rotate(angle, 0.0f, 0.0f, 1.0f);
    }
}
