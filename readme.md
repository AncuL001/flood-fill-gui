# GLUT CMake vcpkg Template
Testing using GLUT with VCPKG and CMake since inserting custom libraries and libs to system folders is full of pain. For my Computer Graphics course.

# Notes
- Set up CMake and vcpkg
- lines to change:
  - `VCPKG_ROOT` on `.vscode/settings.json` to wherever it is on your computer
  - `PROJECT_NAME` on `.vscode/settings.json` to your project name
  - `name` on `vcpkg.json` to your project name
  - `version` on `vcpkg.json` to your project version
  - `VERSION 0.1.0` on the second line of `CMakeLists.txt` to your project version
- Install the following VSCode extensions:
  - [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
  - [CMake Language Support](https://marketplace.visualstudio.com/items?itemName=josetr.cmake-language-support-vscode)
  - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
  - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- Use the ▶️ launch button on the bottom status bar to run the program. Should be visible if the extensions above are enabled
- For me, works using the compiler from Visual Studio but not GCC