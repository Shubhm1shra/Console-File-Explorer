#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class FileExplorer{
public:
    FileExplorer() : currentPath(fs::current_path()){
        refreshFiles();
    };

    FileExplorer(fs::path newPath) : currentPath(newPath){
        refreshFiles();
    }

    ~FileExplorer() = default;

    bool openItem(int nItem){
        if(fs::is_directory(files[nItem])){
            currentPath = files[nItem];
            return true;
        }
        return false;
    }

    std::vector<std::string> getFileNames(){
        std::vector<std::string> fileNames;

        for (const auto& entry : fs::directory_iterator(currentPath)) fileNames.push_back(entry.path().filename().string());
        return fileNames;
    }

private:
    fs::path currentPath;
    std::vector<fs::path> files;

    void refreshFiles(){
        files.clear();

        for (const auto& entry : fs::directory_iterator(currentPath)) {
            files.push_back(entry.path());
        }
    }
};

int main(){
    FileExplorer fe(fs::path("C:\\Users\\user\\Desktop\\Gunnu\\C++\\Programms\\Projects\\FileExplorer"));

    std::vector<std::string> fileNames = fe.getFileNames();

    for(const auto& fname : fileNames) std::cout << fname << std::endl;
    
    return 0;
}