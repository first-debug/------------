#pragma once
#include <QMainWindow>
#include "ui_my_window.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        ui.setupUi(this);
    }
private:
    Ui::MyWindow ui;  // UI-класс из Qt Designer
};