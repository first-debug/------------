#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QJsonArray>
#include <QPixmap>
#include <QFile>

#include <fstream>

#include "mainwindow.h"

using namespace std;

// Конструктор главного окна
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MyWindow) {
    // Инициализация пользовательского интерфейса
    ui->setupUi(this);
    
    // Настройка QLabel для отображения иконки погоды:
    // - Выравнивание по центру
    // - Черный фон с закругленными углами
    // - Минимальный размер 100x100 пикселей
    ui->weatherIcon->setAlignment(Qt::AlignCenter);
    ui->weatherIcon->setStyleSheet("QLabel { background-color: #000000; border-radius: 10px; }");
    ui->weatherIcon->setMinimumSize(100, 100);

    // Инициализация менеджера сетевых запросов
    networkManager = new QNetworkAccessManager(this);
    // Подключение сигнала завершения запроса к слоту обработки данных
    connect(networkManager, &QNetworkAccessManager::finished, 
        this, &MainWindow::parseWeatherData);

    // Инициализация списка городов и текущего индекса
    current_town = 0;
    QFile file("towns.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                towns.push_back(line);
            }
        }
        file.close();
    } else {
        qWarning() << "Не удалось открыть towns.txt!";
    }
    QTextStream in(&file);
    file.close();
    
    // Загрузка погоды для первого города в списке
    fetchWeather(towns[current_town]);
    
    // Подключение кнопок к соответствующим слотам:
    // - Кнопка "Следующий" для переключения городов
    // - Кнопка "Добавить" для добавления нового города
    connect(ui->next, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(ui->add, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    
    // Установка начального значения - отображение первого города
    ui->town->setText(towns[current_town]);
}

// Обработчик нажатия кнопки "Следующий"
void MainWindow::onNextClicked() {
    // Циклическое переключение между городами
    current_town = (current_town + 1) % towns.size();
    // Обновление отображаемого города
    ui->town->setText(towns[current_town]);
    // Загрузка погоды для нового текущего города
    fetchWeather(towns[current_town]);
}

// Обработчик нажатия кнопки "Добавить город"
void MainWindow::onAddClicked() {
    // Получение и обработка введенного названия города:
    // - Удаление пробелов
    // - Первая буква - заглавная, остальные - строчные
    QString add_town = ui->new_town->text().trimmed();
    add_town = add_town.left(1).toUpper() + add_town.mid(1).toLower();
    
    // Проверка на пустую строку
    if (add_town.isEmpty()) return;
    
    // Проверка на существование города в списке
    for (auto &town : towns) {
        if (town == add_town) {
            ui->new_town->clear();
            return;
        }
    }
    
    // Добавление нового города в список
    towns.emplace_back(add_town);
    ui->new_town->clear();
    // Загрузка погоды для добавленного города
    fetchWeather(add_town);
}

// Метод для выполнения запроса погоды
void MainWindow::fetchWeather(const QString &city) {
    // Формирование URL запроса к API OpenWeatherMap:
    // - Название города
    // - API ключ
    // - Единицы измерения - метрические
    // - Язык - русский
    QString url = QString("https://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric&lang=ru")
                     .arg(city)
                     .arg(apiKey);

    // Отправка GET-запроса
    networkManager->get(QNetworkRequest(QUrl(url)));
}

// Обработчик полученных данных о погоде
void MainWindow::parseWeatherData(QNetworkReply *reply) {
    // Проверка на ошибки сети
    if (reply->error() != QNetworkReply::NoError) {
        if (!towns.empty()) towns.pop_back(); // Удаляем последний добавленный город при ошибке
        reply->deleteLater(); // Освобождение ресурсов
        return;
    }

    // Парсинг JSON-ответа
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject root = doc.object();

    // Извлечение данных о погодных условиях
    QJsonObject weather = root["weather"].toArray().first().toObject();
    QString description = weather["description"].toString(); // Описание погоды
    QString iconCode = weather["icon"].toString(); // Код иконки (например "04d")

    // Извлечение основных метеорологических данных
    QJsonObject main = root["main"].toObject();
    QString temp = QString::number(main["temp"].toDouble(), 'f', 1); // Температура
    QString feels_like = QString::number(main["feels_like"].toDouble(), 'f', 1); // Ощущается как
    QString humidity = QString::number(main["humidity"].toInt()); // Влажность

    // Форматирование и вывод прогноза погоды
    ui->prognoz->setText(QString(
        "<b>%1</b><br>"
        "Температура: %2°C<br>"
        "Ощущается: %3°C<br>"
        "Влажность: %4%"
    ).arg(description, temp, feels_like, humidity));

    // Загрузка и отображение иконки погоды из ресурсов
    QPixmap weatherIcon(QString(":/icons/resources/weather_icons/%1.png").arg(iconCode));
    if (!weatherIcon.isNull()) {
        // Масштабирование иконки с сохранением пропорций
        weatherIcon = weatherIcon.scaled(ui->weatherIcon->size(), 
                                      Qt::KeepAspectRatio, 
                                      Qt::SmoothTransformation);
        ui->weatherIcon->setPixmap(weatherIcon);
    } else {
        // Если иконка не найдена - отображаем текст
        ui->weatherIcon->setText("Нет иконки");
        qDebug() << "Icon not found:" << iconCode;
    }
    
    // Освобождение ресурсов
    reply->deleteLater();
}

// Деструктор главного окна
MainWindow::~MainWindow() {
    // Освобождение ресурсов
    delete networkManager;
    delete ui;
}