#pragma once

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <vector>
#include <locale>
#include <codecvt>
#include <shellapi.h>

namespace fs = std::filesystem;

class FileExplorer{
public:
    FileExplorer();
    FileExplorer(std::string newPath);

    ~FileExplorer();

    std::wstring toWstring(std::string s);

    std::wstring getCurrentPath();

    bool openDir(int nItem);
    bool openDir(fs::path);

    bool backToParent();

    std::vector<std::string> getFileNames();
    std::vector<std::wstring> getFileNamesW();

    bool run(int nItem);

private:
    fs::path currentPath;
    std::vector<fs::path> files;

    void refreshFiles();
};