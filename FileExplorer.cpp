#include <iostream>

#include "FileExplorer.hpp"

FileExplorer::FileExplorer() : currentPath(fs::current_path()){refreshFiles();}
FileExplorer::FileExplorer(std::string newPath) : currentPath(static_cast<fs::path>(newPath)){refreshFiles();}

FileExplorer::~FileExplorer() = default;

std::wstring FileExplorer::toWstring(std::string s){
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(s);
    return wide;
}

std::wstring FileExplorer::getCurrentPath(){
    return toWstring(currentPath.string());
}

bool FileExplorer::openDir(int nItem){
    if(nItem < 0 || nItem > files.size()) return false;
    if(fs::is_directory(files[nItem])){
        currentPath = files[nItem];
        refreshFiles();
        return true;
    }
    return false;
}

bool FileExplorer::openDir(fs::path filePath){
    if(fs::is_directory(filePath)){
        currentPath = filePath;
        return true;
    }
    return false;
}

bool FileExplorer::backToParent(){
    if(currentPath.has_parent_path()){
        currentPath = currentPath.parent_path();
        refreshFiles();
        return true;
    }
    return false;
}

std::vector<std::string> FileExplorer::getFileNames(){
    std::vector<std::string> fileNames;

    for (const auto& entry : fs::directory_iterator(currentPath)) fileNames.push_back(entry.path().filename().string());
    return fileNames;
}

std::vector<std::wstring> FileExplorer::getFileNamesW(){
    std::vector<std::wstring> fileNamesW;

    for(const auto& entry : fs::directory_iterator(currentPath)) fileNamesW.push_back(toWstring(entry.path().filename().string()));
    return fileNamesW;
}

bool FileExplorer::run(int nItem){
    std::wstring filePathW = files[nItem].wstring();
    HINSTANCE result = ShellExecuteW(nullptr, L"open", filePathW.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

    if(reinterpret_cast<intptr_t>(result) > 32) return true;
    return false;
}

void FileExplorer::refreshFiles(){
    files.clear();

    for (const auto& entry : fs::directory_iterator(currentPath)) files.push_back(entry.path());
}