/********************************************************************************
** Form generated from reading UI file 'my_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_WINDOW_H
#define UI_MY_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWindow
{
public:
    QWidget *centralwidget;
    QLabel *weatherIcon;
    QLabel *town;
    QPushButton *add;
    QPushButton *next;
    QLabel *prognoz;
    QLineEdit *new_town;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MyWindow)
    {
        if (MyWindow->objectName().isEmpty())
            MyWindow->setObjectName("MyWindow");
        MyWindow->resize(402, 581);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MyWindow->sizePolicy().hasHeightForWidth());
        MyWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MyWindow);
        centralwidget->setObjectName("centralwidget");
        weatherIcon = new QLabel(centralwidget);
        weatherIcon->setObjectName("weatherIcon");
        weatherIcon->setGeometry(QRect(50, 170, 311, 291));
        town = new QLabel(centralwidget);
        town->setObjectName("town");
        town->setGeometry(QRect(50, 20, 241, 41));
        QFont font;
        font.setPointSize(14);
        town->setFont(font);
        add = new QPushButton(centralwidget);
        add->setObjectName("add");
        add->setGeometry(QRect(270, 490, 91, 23));
        next = new QPushButton(centralwidget);
        next->setObjectName("next");
        next->setGeometry(QRect(290, 30, 75, 23));
        prognoz = new QLabel(centralwidget);
        prognoz->setObjectName("prognoz");
        prognoz->setGeometry(QRect(50, 70, 311, 71));
        new_town = new QLineEdit(centralwidget);
        new_town->setObjectName("new_town");
        new_town->setGeometry(QRect(50, 490, 211, 20));
        MyWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MyWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 402, 22));
        MyWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MyWindow);
        statusbar->setObjectName("statusbar");
        MyWindow->setStatusBar(statusbar);

        retranslateUi(MyWindow);

        QMetaObject::connectSlotsByName(MyWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MyWindow)
    {
        MyWindow->setWindowTitle(QCoreApplication::translate("MyWindow", "MainWindow", nullptr));
        weatherIcon->setText(QCoreApplication::translate("MyWindow", "\320\267\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\320\265\321\202 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\320\260", nullptr));
        town->setText(QCoreApplication::translate("MyWindow", "\320\267\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\320\265\321\202 \320\263\320\276\321\200\320\276\320\264", nullptr));
        add->setText(QCoreApplication::translate("MyWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\263\320\276\321\200\320\276\320\264", nullptr));
        next->setText(QCoreApplication::translate("MyWindow", "\321\201\320\273\320\265\320\264\321\203\321\216\321\211\320\270\320\271", nullptr));
        prognoz->setText(QCoreApplication::translate("MyWindow", "\320\237\321\200\320\276\320\263\320\275\320\276\320\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWindow: public Ui_MyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_WINDOW_H
