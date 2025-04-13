# Устанавливаем минимальную требуемую версию CMake (3.21 или выше)
cmake_minimum_required(VERSION 3.21)

# Определяем проект с именем MyQtApp и указываем,
# что используем язык C++ (LANGUAGES CXX)
project(MyQtApp LANGUAGES CXX)

# Настройка стандарта C++ (используем C++17)
set(CMAKE_CXX_STANDARD 17)
# Указываем, что стандарт обязателен (не пытаться использовать более старый)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую обработку Qt-специфичных файлов:
# - CMAKE_AUTOMOC: автоматическая обработка мета-объектной системы Qt (moc)
# - CMAKE_AUTOUIC: автоматическая обработка ui-файлов (uic)
# - CMAKE_AUTORCC: автоматическая обработка ресурсов (rcc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Ищем пакет Qt6 и требуемые компоненты:
# - Core: базовые классы Qt
# - Gui: графический интерфейс
# - Widgets: виджеты Qt
# - Network: сетевая функциональность
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# Включаем стандартные настройки Qt (макроопределения, настройки компилятора)
qt_standard_project_setup()

# Добавляем файл ресурсов (resources.qrc) в проект.
# Результат сохраняется в переменной RESOURCE_FILES
qt_add_resources(RESOURCE_FILES "resources.qrc")

# Создаем список исходных файлов проекта:
# - main.cpp: точка входа
# - mainwindow.cpp/.h: реализация главного окна
# - my_window.ui: ui-файл из Qt Designer
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/my_window.ui
)

# Копирование towns.txt в папку сборки
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/towns.txt
    ${CMAKE_CURRENT_BINARY_DIR}/towns.txt
    COPYONLY
)

# Создаем исполняемый файл с именем проекта (${PROJECT_NAME} = MyQtApp)
# Включаем все исходные файлы и скомпилированные ресурсы
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${RESOURCE_FILES}
)

# Подключаем необходимые Qt-модули к нашему исполняемому файлу:
# - Core: базовые классы
# - Gui: графика
# - Widgets: виджеты
# - Network: сетевое взаимодействие
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)