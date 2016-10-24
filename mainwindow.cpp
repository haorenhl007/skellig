#include <QDir>
#include <QAction>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new GLWidget(ui->centralWidget);
    ui->centralLayout->insertWidget(0, view, 1);

    QAction* openAction = ui->fileMenu->addAction("Ouvrir un modèle...");
    connect(openAction, &QAction::triggered, this, &MainWindow::openFileDialog);

    connect(ui->wireframeBox, &QCheckBox::toggled,
            view, &GLWidget::setPolygonMode);

    animationDialog = new AnimationDialog(this);

    connect(ui->settingsCheckBox, &QCheckBox::toggled,
            animationDialog, &AnimationDialog::setVisible);

    connect(view, &GLWidget::modelLoaded,
            animationDialog, &AnimationDialog::loadNodes);

    connect(view, &GLWidget::modelDeleted,
            animationDialog, &AnimationDialog::resetAll);
}

MainWindow::~MainWindow() {
    delete ui;
    delete view;
    delete animationDialog;
}

void MainWindow::openFileDialog() {
    QString directory = (lastFilePath.length() > 0) ? lastFilePath : QDir::homePath();
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un modèle", directory, "Modèles (*.dae *.obj)");
    if (!filename.isNull()) {
        lastFilePath = filename;
        view->loadModel(filename);
    }
}
