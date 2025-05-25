#!/bin/bash
# в msys2 ucrt64 переходим в папку проекта
cd "D:/Projects/cpp/qt/nastKP"

# удаляем все детали сборки
rm -rf build

# собираем
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:/msys64/ucrt64" -G "Ninja"
cmake --build .

# запускаем
./MyQtApp.exe