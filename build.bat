@echo off

title Arithmetic Expression Parser - Build

echo ========================================
echo    ARITHMETIC EXPRESSION PARSER
echo             BUILD SCRIPT
echo ========================================

echo.
echo Compiling project...

gcc -std=c99 -Wall main.c stack.c converter.c validator.c tree.c -o parser.exe

if errorlevel 1 (
    echo.
    echo [ERROR] Compilation failed!
    echo Please check your source code.
    pause
    exit /b 1
)

echo.
echo ========================================
echo [SUCCESS] Project compiled successfully!
echo ========================================

echo.
echo Executable created: parser.exe
echo.
echo To run the program, type: .\parser.exe

echo.
pause