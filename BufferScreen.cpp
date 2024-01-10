#include "BufferScreen.hpp"

#include <iostream>
#include <windows.h>
#include <conio.h>

BufferScreen::BufferScreen() : nScreenWidth(120), nScreenHeight(30){
    initialize();
    setTitle(L"File Explorer");
}

BufferScreen::BufferScreen(const std::wstring& title) : nScreenWidth(120), nScreenHeight(30){
    initialize();
    setTitle(title);
}

BufferScreen::BufferScreen(int width, int height) : nScreenWidth(width), nScreenHeight(height){
    initialize();
}

BufferScreen::BufferScreen(int width, int height, const std::wstring& title) : nScreenWidth(width), nScreenHeight(height){
    initialize();
    setTitle(title);
}

BufferScreen::~BufferScreen(){
    delete[] screenBuffer;
    CloseHandle(consoleHandle);
}

void BufferScreen::initialize(){
    screenBuffer = new wchar_t[nScreenWidth * nScreenHeight];
    consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    SetConsoleActiveScreenBuffer(consoleHandle);
    SetConsoleScreenBufferSize(consoleHandle, { static_cast<short>(nScreenWidth), static_cast<short>(nScreenHeight)});

    windowSize = {0, 0, static_cast<short>(nScreenWidth - 1), static_cast<short>(nScreenHeight - 1)};

    SetConsoleWindowInfo(consoleHandle, TRUE, &windowSize);

    GetConsoleScreenBufferInfo(consoleHandle, &defaultConsoleInfo);
    saved_attr = defaultConsoleInfo.wAttributes;

    SetConsoleMode(consoleHandle, ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    clearScreen();
}

HANDLE BufferScreen::getHandle(){
    return consoleHandle;
}

void BufferScreen::write(int row, int col, wchar_t ch){
    screenBuffer[row * nScreenWidth + col] = ch;
}

void BufferScreen::write(int row, int col, const std::wstring& s){
    size_t length = s.size();
    size_t maxWrite = static_cast<size_t>(nScreenWidth * nScreenHeight - row * nScreenWidth - col);
    size_t writeCount = std::min(length, maxWrite);

    if (writeCount > 0) {
        for (size_t i = 0; i < writeCount; ++i) {
            screenBuffer[row * nScreenWidth + col + i] = s[i];
        }
    }
}

void BufferScreen::colored_write(int row, int col, wchar_t ch, WORD attr){
    SetConsoleTextAttribute(consoleHandle, attr);
    screenBuffer[row * nScreenWidth + col] = ch;
    SetConsoleTextAttribute(consoleHandle, saved_attr);
}

void BufferScreen::colored_write(int row, int col, const std::wstring& s, WORD attr){
    size_t length = s.size();
    size_t maxWrite = static_cast<size_t>(nScreenWidth * nScreenHeight - row * nScreenWidth - col);
    size_t writeCount = std::min(length, maxWrite);

    SetConsoleTextAttribute(consoleHandle, attr);

    if (writeCount > 0) {
        for (size_t i = 0; i < writeCount; ++i) {
            screenBuffer[row * nScreenWidth + col + i] = s[i];
        }
    }

    SetConsoleTextAttribute(consoleHandle, saved_attr);
}

void BufferScreen::setTitle(const std::wstring& title){
    SetConsoleTitleW(title.c_str());
}

void BufferScreen::clearScreen(){
    for(int i = 0; i < nScreenWidth * nScreenHeight; i++) screenBuffer[i] = L' ';
}

void BufferScreen::drawBorder(){
    // Corners 
    write(0, 0, L'╔');
    write(0, nScreenWidth - 1, L'╗');
    write(nScreenHeight -1, 0, L'╚');
    write(nScreenHeight - 1, nScreenWidth - 1, L'╝');

    //Left and Right Encasing

    for(int row = 1; row < nScreenHeight - 1; row++)
    {
        write(row, 0, L'║');
        write(row, nScreenWidth - 1, L'║');
    }

    //Upper and Lower Encasing

    for(int col = 1; col < nScreenWidth - 1; col++)
    {
        write(0, col, L'═');
        write(nScreenHeight - 1, col, L'═');
    }
}

void BufferScreen::fillRect(int x1, int y1, int x2, int y2, wchar_t ch){
        // Ensure the coordinates are within the buffer bounds
        x1 = std::max(0, std::min(x1, nScreenHeight - 1));
        y1 = std::max(0, std::min(y1, nScreenWidth - 1));
        x2 = std::max(0, std::min(x2, nScreenHeight - 1));
        y2 = std::max(0, std::min(y2, nScreenWidth - 1));

        // Swap coordinates if needed
        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);

        // Fill the rectangular area with the specified character
        for(int row = x1; row <= x2; row++)
            for(int col = y1; col <= y2; col++) write(row, col, ch);
}

void BufferScreen::hideCursor(){
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void BufferScreen::display(){
    DWORD bytesWritten = 0;
    WriteConsoleOutputCharacterW(consoleHandle, screenBuffer, nScreenWidth * nScreenHeight, { 0, 0 }, &bytesWritten);
}