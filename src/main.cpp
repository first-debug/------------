#include <QApplication>
#include <QLabel>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    // QLabel label("Hello, Qt без Creator!");
    window.show();
    return app.exec();
}