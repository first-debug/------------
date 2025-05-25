@echo off
rem в msys2 ucrt64 переходим в папку проекта
cd "D:\Projects\cpp\qt\nastKP"
rem удаляем все детали сборки
rem rm -rf build
rmdir /S /Q build
rem делаем сборку заново
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:/msys64/ucrt64" -G "Ninja"
cmake --build .
rem запускаем
.\MyQtApp.exe