# IR01_IndustrialRobotics
Industrial Robotics controller

## Compiler
Install MSVC compiler. You can follow this guide:
https://code.visualstudio.com/docs/cpp/config-msvc#_prerequisites

## Qt
Install Qt 5.15

## Eigen
To install the Eigen library on Windows I used vcpkg.
Guide to install vcpkg on Windows: https://vcpkg.io/en/getting-started
I installed vcpkg in this directory: C:\src\vcpkg

To install the Eigen library navigate to the installation directory of vcpkg (cd C:\src\vcpkg) an type the following command: .\vcpkg install eigen3

## Visual Studio Code
Open the Developer Command Prompt for VS 2022 and navigate to the folder of this README.md file.
type the command: code . to open VSCode from this folder.

## CMake tools extension
Open the configuration of the tools extension and scroll down to the section "Configure Args". Add following items:
To use Qt: Set the CMake tools extension "Configure Args" to -DCMAKE_PREFIX_PATH=C:/Qt/5.15.2/msvc2019_64
To use Eigen: Set the CMake tools extension "Configure Args" to -DEigen3_DIR=C:/dev/vcpkg/packages/eigen3_x64-windows/share/eigen3