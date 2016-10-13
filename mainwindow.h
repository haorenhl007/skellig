#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void openFileDialog();

private:
    Ui::MainWindow* ui;
    GLWidget* view;
    QString lastFilePath;
};

#endif // MAINWINDOW_H
