# SystemC_AMS_Lua
Объекты для SystemC AMS, позволяющие запускать скрипты Lua 5.3. Проект может быть полезен людям интересующимся моделированием гетерогенных систем.
Язык Lua выбран из-за способности встраиваться во всё что угодно, легкого синтаксиса и концепциям языка не уступающих Python. Главный недостаток Lua - значительно меньшее количество сторонних библиотек, чем у Python.

Варианты использования подобной связки:
1) введение скриптового модуля позволяет менять алгоритм работы этого модуля без пересборки проекта (при отладке/ доведении до ума спорного алгоритма);
2) вывод результатов моделирования в файлы для других средств моделирования (Octave, Matlab, MicroCAP...);
3) чтение выходных файлов других средств моделирования (как вариант, при подключении библиотек Lua можно ещё читать/писать .WAV и RAW - файлы);
4) организовать обмен результатами моделирования через сетевой интерфейс ( в том числе при моделировании в 'реальном времени' с удалёнными компьютерами) с другими средами моделирования;
5) организовать связку SystemC AMS <-> Lua <-> LuaSocket <-> UDP <-> LuaSocket <-> Lua <-> VerilogVPI <-> Verilog
6) повышение платформонезависимости проекта SystemC AMS за счет использования кроссплатформенных модулей Lua.
