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
    connect(ui->playButton, &QPushButton::pressed, this, &AnimationDialog::play);
}

AnimationDialog::~AnimationDialog() {
    delete ui;
}

void AnimationDialog::updateAnimation() {
    QTreeWidgetItem* item = ui->treeWidget->currentItem();

    if(item && model != 0) {
        Node* node = nodeMap.value(item);
        node->transformation.setToIdentity();

        currentRotation = QQuaternion::slerp(currentRotation, aimedRotation, 0.1);
        node->transformation.rotate(currentRotation);
    }
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
    currentRotation = QQuaternion();
    aimedRotation = QQuaternion();

    ui->treeWidget->clear();
    ui->xSpinBox->setValue(0);
    ui->ySpinBox->setValue(0);
    ui->zSpinBox->setValue(0);
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

    currentRotation = QQuaternion();
    aimedRotation = QQuaternion();

    ui->xSpinBox->setValue(0);
    ui->ySpinBox->setValue(0);
    ui->zSpinBox->setValue(0);
}

void AnimationDialog::rotateX(double angle) {
    QQuaternion rotX = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, angle);
    QQuaternion rotY = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, ui->ySpinBox->value());
    QQuaternion rotZ = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, ui->zSpinBox->value());

    fieldRotation = rotX * rotY * rotZ;
}

void AnimationDialog::rotateY(double angle) {
    QQuaternion rotX = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, ui->xSpinBox->value());
    QQuaternion rotY = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, angle);
    QQuaternion rotZ = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, ui->zSpinBox->value());

    fieldRotation = rotX * rotY * rotZ;
}

void AnimationDialog::rotateZ(double angle) {
    QQuaternion rotX = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, ui->xSpinBox->value());
    QQuaternion rotY = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, ui->ySpinBox->value());
    QQuaternion rotZ = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, angle);

    fieldRotation = rotX * rotY * rotZ;
}

void AnimationDialog::play() {
    currentRotation = QQuaternion();
    aimedRotation = fieldRotation;
}
