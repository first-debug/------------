#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include <vector>

#include "mainwindow.h"

using namespace std;

// Реализация методов MainWindow в main.cpp
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MyWindow) {
    ui -> setupUi(this);

    current_town = 0;
    towns = {"Санкт-Петербург", "Москва", "Нью-Йорк"};
    
    // Соединяем кнопки с обработчиками
    connect(ui -> next, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(ui -> add, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    
    // Инициализируем начальные значения
    ui -> town->setText(towns[current_town]);
    // ui -> prognoz->setText("Сегодня солнечно");
    // ui.picture->setText(""); 
}

void MainWindow::onNextClicked() {
    // Логика для кнопки "следующий"
    current_town = (current_town + 1) % towns.size();
    ui -> town->setText(towns[current_town]);
    // ui -> prognoz->setText("Завтра ожидается дождь");
}

void MainWindow::onAddClicked() {
    // Логика для кнопки "Добавить город"
    QString add_town = ui -> new_town -> text();
    towns.emplace_back(add_town);
    ui -> new_town -> clear();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

MainWindow::~MainWindow() {
    delete ui;
}