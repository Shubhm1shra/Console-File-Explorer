#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

#include "BufferScreen.hpp"
#include "FileExplorer.hpp"
#include "Wcolors.hpp"

int main(){
    int nScreenWidth = 120;
    int nScreenHeight = 30;

    BufferScreen bs(nScreenWidth, nScreenHeight, L"File Explorer");
    FileExplorer fe;

    bs.hideCursor();

    bool bRun = true;
    bool bChange = true;

    std::wstring arrow = L"--> ";
    std::wstring currentpath;

    std::vector<std::wstring> fileNamesW;

    int nItem = 0;
    int offset = 0;
    int maxFiles;

    while(bRun){
        if(bChange){
            bs.clearScreen();
            bs.drawBorder();

            fileNamesW = fe.getFileNamesW();
            maxFiles = std::min(static_cast<int>(fileNamesW.size()), nScreenHeight - 2);

            for(int i = 0; i < maxFiles; i++){
                (nItem == i+offset) ? bs.write(i+1, 1, arrow + fileNamesW[i+offset]) : bs.write(i+1, 1, fileNamesW[i+offset]);
            }

            currentpath = fe.getCurrentPath();
            bs.write(1, nScreenWidth - static_cast<int>(currentpath.size()) - 1, currentpath);

            std::cout << offset << std::endl;

            bs.display();

            bChange = false;
        }
        
        if(GetAsyncKeyState(VK_LEFT) & 0x8000){
            if(fe.backToParent()){
                bChange = true;
                nItem = 0;
                Sleep(260);
            }
        }

        if(GetAsyncKeyState(VK_UP) & 0x8000){
            if(nItem > offset) {
                nItem--;
                if((nItem == offset) && (nItem != 0)) offset--;
                bChange = true;
                Sleep(120);
            }
            else if(nItem == 0){
                nItem = fileNamesW.size() - 1;
                offset = std::max(0, nItem - maxFiles);
                bChange = true;
                Sleep(120);
            }
        }

        if(GetAsyncKeyState(VK_DOWN) & 0x8000){
            if(nItem < fileNamesW.size() - 1){
                if(nItem < offset + maxFiles - 1) nItem++;
                else{
                    nItem++;
                    offset++;
                }
                bChange = true;
                Sleep(120);
            }
            else if(nItem == fileNamesW.size() - 1){
                nItem = 0;
                offset = 0;
                bChange = true;
                Sleep(120);
            }
        }

        if(GetAsyncKeyState(VK_RIGHT) & 0x8000){
            if(fe.openDir(nItem)){
                bChange = true;
                nItem = 0;
                Sleep(260);
            }
        }

        if(GetAsyncKeyState(VK_RETURN) & 0x8000){
            fe.run(nItem);
            Sleep(500);
        }

        if(GetAsyncKeyState(27)){
            CloseHandle(bs.getHandle());
            bRun = false;
        }
    }

    return 0;
}
