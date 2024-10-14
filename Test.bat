@echo off
REM Параметры
set SERVER_PORT=12345
set SERVER_MODE=server
set CLIENT_MODE=client
set FILES=file1.txt file2.txt file3.txt

REM Запуск сервера в отдельном окне
start cmd /k "..\Debug\Client_Server_Networking.exe %SERVER_MODE% %SERVER_PORT%"
timeout /t 5

REM Запуск клиента и отправка файлов
cmd /k "..\Debug\Client_Server_Networking.exe %CLIENT_MODE% %SERVER_PORT% %FILES%"

exit