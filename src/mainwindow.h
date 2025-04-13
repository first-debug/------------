// Защита от множественного включения файла
#pragma once

// Базовый класс для главного окна
#include <QMainWindow>

// Классы для работы с сетевыми запросами
#include <QNetworkAccessManager>  // Основной класс для HTTP-запросов
#include <QNetworkReply>         // Обработка ответов от сервера

// Классы для работы с JSON-данными
#include <QJsonDocument>         // Для парсинга и создания JSON
#include <QJsonObject>           // Для работы с JSON-объектами

// Контейнер для хранения списка городов
#include <vector>

// Сгенерированный заголовочный файл из UI-формы
#include "ui_my_window.h"

// Класс главного окна приложения
class MainWindow : public QMainWindow {
    Q_OBJECT  // Макрос Qt для поддержки сигналов/слотов
    
public:
    // Конструктор с необязательным родительским виджетом
    MainWindow(QWidget *parent = nullptr);
    
    // Деструктор
    ~MainWindow();

private slots:  // Слоты для обработки событий
    // Обработчик клика по кнопке "Следующий"
    void onNextClicked();
    
    // Обработчик клика по кнопке "Добавить город"
    void onAddClicked();
    
    // Обработчик полученных данных о погоде
    void parseWeatherData(QNetworkReply *reply);

private:  // Внутренние члены класса
    // Менеджер сетевых запросов (выполняет HTTP-запросы)
    QNetworkAccessManager *networkManager;
    
    // API-ключ для сервиса OpenWeatherMap
    QString apiKey = "6107f0dad53fbd910f89342834cedc30";

    // Метод для выполнения запроса погоды по названию города
    void fetchWeather(const QString &city);
        
    // Указатель на сгенерированный UI (форму из Qt Designer)
    Ui::MyWindow *ui;
    
    // Индекс текущего отображаемого города в векторе towns
    int current_town;
    
    // Вектор для хранения списка городов
    std::vector<QString> towns;
};