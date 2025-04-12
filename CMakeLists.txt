cmake_minimum_required(VERSION 3.21)
project(MyQtApp LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую обработку Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Явно указываем путь к Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# Включаем стандартные настройки Qt
qt_standard_project_setup()

# Создаем исполняемый файл (UI-файл будет обработан автоматически)
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/mainwindow.h
    src/my_window.ui  # Добавляем UI-файл напрямую
)

# Подключаем Qt модули
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)