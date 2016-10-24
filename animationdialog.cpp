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
    new QListWidgetItem(model->rootNode->name, ui->listWidget);
}

void AnimationDialog::resetAll() {
    model = 0;
    ui->listWidget->clear();
}
