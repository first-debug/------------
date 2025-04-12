#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QJsonArray>

#include <vector>

#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MyWindow) {
    ui -> setupUi(this);
    networkManager = new QNetworkAccessManager(this);  // Инициализация
    connect(networkManager, &QNetworkAccessManager::finished, 
        this, &MainWindow::parseWeatherData);

    current_town = 0;
    towns = {"Санкт-Петербург", "Москва", "Нью-Йорк"};
    fetchWeather(towns[current_town]);  // Загружаем погоду для первого города
    
    // Соединяем кнопки с обработчиками
    connect(ui -> next, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(ui -> add, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    
    // Инициализируем начальные значения
    ui -> town->setText(towns[current_town]);
    // ui.picture->setText(""); 
}

void MainWindow::onNextClicked() {
    // Логика для кнопки "следующий"
    current_town = (current_town + 1) % towns.size();
    ui -> town->setText(towns[current_town]);
    fetchWeather(towns[current_town]);
}

void MainWindow::onAddClicked() {
    QString add_town = ui->new_town->text().trimmed();
    if (add_town.isEmpty()) return;

    towns.emplace_back(add_town);
    ui->new_town->clear();
    fetchWeather(add_town);  // Загружаем погоду для нового города
}

void MainWindow::fetchWeather(const QString &city) {
    QString url = QString("https://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric&lang=ru")
                     .arg(city)
                     .arg(apiKey);

    networkManager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::parseWeatherData(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        towns.pop_back();
        reply->deleteLater();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject root = doc.object();

    // Извлечение данных о погоде
    QJsonObject weather = root["weather"].toArray().first().toObject();
    QString description = weather["description"].toString();
    QString iconCode = weather["icon"].toString();

    // Извлечение температурных данных
    QJsonObject main = root["main"].toObject();
    QString temp = QString::number(main["temp"].toDouble(), 'f', 1);
    QString feels_like = QString::number(main["feels_like"].toDouble(), 'f', 1);
    QString humidity = QString::number(main["humidity"].toInt());

    ui->prognoz->setText(QString(
        "<b>%1</b><br>"
        "Температура: %2°C<br>"
        "Ощущается: %3°C<br>"
        "Влажность: %4%"
    ).arg(description, temp, feels_like, humidity));
    reply->deleteLater();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

MainWindow::~MainWindow() {
    delete networkManager;
    delete ui;
}