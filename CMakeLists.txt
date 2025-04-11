cmake_minimum_required(VERSION 3.5)
project(MyQtApp LANGUAGES CXX)

# Включение автоматической обработки .ui-файлов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

# Настройка Qt
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)  # Для обработки сигналов/slots

# Добавление .ui-файла
qt_add_ui_files(ui_files ui/my_window.ui)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
include_directories(${Qt6_INCLUDE_DIRS})

# Создание исполняемого файла
add_executable(${PROJECT_NAME} 
    src/main.cpp
    ${ui_files}
)
target_link_libraries(my_app PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)