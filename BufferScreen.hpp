#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>

#define WAIT _getch()

class BufferScreen{
public:
    BufferScreen();
    BufferScreen(const std::wstring& title);
    BufferScreen(int width, int height);
    BufferScreen(int width, int height, const std::wstring& title);

    ~BufferScreen();

    void initialize();

    HANDLE getHandle();
    
    void write(int row, int col, wchar_t ch);
    void write(int row, int col, const std::wstring& s);
    void colored_write(int row, int col, wchar_t ch, WORD attr);
    void colored_write(int row, int col, const std::wstring& s, WORD attr);

    void setTitle(const std::wstring& title);
    void clearScreen();

    void drawBorder();
    void fillRect(int x1, int y1, int x2, int y2, wchar_t ch);

    void hideCursor();

    void display();

private:
    int nScreenWidth;
    int nScreenHeight;
    wchar_t* screenBuffer;
    HANDLE consoleHandle;
    SMALL_RECT windowSize;
    CONSOLE_SCREEN_BUFFER_INFO defaultConsoleInfo;
    WORD saved_attr;
};