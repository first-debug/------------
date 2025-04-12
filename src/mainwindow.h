#pragma once
#include <QMainWindow>
#include <vector>

#include <QNetworkAccessManager>  // Для HTTP-запросов
#include <QNetworkReply>
#include <QJsonDocument>          // Для работы с JSON
#include <QJsonObject>

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
    // ... существующие поля ...
    QNetworkAccessManager *networkManager;  // Для выполнения запросов
    QString apiKey = "6107f0dad53fbd910f89342834cedc30";

    void fetchWeather(const QString &city);  // Запрос погоды
    void parseWeatherData(QNetworkReply *reply);  // Обработка ответа

private:
    Ui::MyWindow *ui;  // UI-класс из Qt Designer
    int current_town;
    std::vector<QString> towns;
};