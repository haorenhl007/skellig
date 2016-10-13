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
    ui->verticalLayout->insertWidget(0, view);

    QAction* openAction = ui->fileMenu->addAction("Ouvrir un modèle...");
    connect(openAction, &QAction::triggered, this, &MainWindow::openFileDialog);

    connect(ui->rotateSlider, &QSlider::sliderMoved,
            view, &GLWidget::setModelAngle);

    connect(ui->cameraSlider, &QSlider::sliderMoved,
            view, &GLWidget::setCameraX);

    connect(ui->checkBox, &QCheckBox::toggled,
            view, &GLWidget::setPolygonMode);
}

MainWindow::~MainWindow() {
    delete ui;
    delete view;
}

void MainWindow::openFileDialog() {
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un modèle", QDir::homePath(), "Modèles (*.dae *.obj)");
    if (!filename.isNull()) {
        view->loadModel(filename);
    }
}
