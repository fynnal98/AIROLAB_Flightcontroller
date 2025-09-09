@echo off
setlocal

echo ==========================================
echo   Sync database.json -> data/
echo ==========================================

copy /Y extern\Database\database.json data\database.json

if errorlevel 1 (
    echo Fehler: database.json konnte nicht kopiert werden!
    pause
    exit /b 1
)

echo.
echo ==========================================
echo   Upload Filesystem (LittleFS)
echo ==========================================
pio run -t uploadfs
if errorlevel 1 pause & exit /b 1

echo.
echo ==========================================
echo   Upload Firmware
echo ==========================================
pio run -t upload
if errorlevel 1 pause & exit /b 1

echo.
echo ==========================================
echo   Fertig!
echo ==========================================

echo.
echo ==========================================
echo   Starte Serial Monitor
echo ==========================================
pio device monitor -b 115200


endlocal
pause
