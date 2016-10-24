#ifndef ANIMATIONDIALOG_H
#define ANIMATIONDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
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

private:
    Ui::AnimationDialog* ui;
    Model* model;
};

#endif // ANIMATIONDIALOG_H
