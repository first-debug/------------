#pragma once
#include <QMainWindow>
#include <vector>

#include "ui_my_window.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNextClicked();
    void onAddClicked();

private:
    Ui::MyWindow *ui;  // UI-класс из Qt Designer
    int current_town;
    std::vector<QString> towns;
};