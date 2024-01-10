# Console File-Explorer
Console File Explorer is a simple C++ project that provides a command-line interface for navigating and exploring files and directories. The project leverages the Windows API to create a buffer console with a user-friendly interface.

- - - -

## Logic 🧠
Using the Windows API, A simple Console Buffer is generated and handled for each key-event. It allows the user to have a light experience without any care for lag, It also shows any hidden file allowing the user to easily interact with such applications without the need for seperatly locating the said files.

## Features 🔑
* __Navigation__ : Navigate through files simply with the use of arrow-keys.
* __Exploration__ : Explore your files and directories in a stuctured manner.
* __Light__ : The application is built using win32 api, which allows the user to have a light expereince.
* __Responsive__ : Responsive Key-event handling for optimized user-experience.

## Prerequisites 📚
The following application does not utilize any external libraries, which do not come built-in with mingw compiler.

## Run 🏃
1. Clone the repository to your local machine.
2. Build the project using prefered C++ compiler(can directly run the pre-included main.exe file).
3. Run the executable to open console file explorer.

## Compilation 🔄
To compile the main.cpp file, run the following bash command on terminal(vsCode)/powershell/command-line : 

`g++ BufferScreen.cpp FileExplorer.cpp -o main main.exe`

__Note : Ensure that the path of current directory and the path at which the repository is located are the same.__

## Dependencies 📦
* __Windows API__

## Contributions 🤝
1. __Fork the repository__
2. __Make Improvement or bug fixes__
3. __Submit Pull Request__

## License 📜
This project is licensed under the MIT License.
