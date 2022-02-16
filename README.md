# plasmvm
An interpreted PLASM emulator.

## Precompiled Binaries
Upon major milestone releases, precompiled releases are provided in the 'Releases' section on the right hand side of the desktop website.

## Continous Integration
Below, badges for continous integration are available.
[![Ubuntu Build](https://github.com/noahw2021/plasmvm/actions/workflows/c-ubuntu.yml/badge.svg)](https://github.com/noahw2021/plasmvm/actions/workflows/c-ubuntu.yml)
![macOS Build](https://github.com/noahw2021/plasmvm/actions/workflows/c-macos.yml/badge.svg)](https://github.com/noahw2021/plasmvm/actions/workflows/c-macos.yml)

## Building yourself
### Prerequisites
SDL2 and SDL2_ttf are required for building this project. These can be obtained through your Operating System's package manager, such as `apt`, `brew`, or `vcpkg`.
### Getting the Source
You can download the archive source for building [here](https://github.com/noahw2021/plasmvm/archive/refs/heads/main.zip), or if you want to contribute you can clone repository and use the git command line.<br>On many platforms, the syntax is as follows:
```
git clone https://github.com/[yourusername]/plasmvm.git
git remote set-url origin git@github.com:[yourusername]/plasmvm.git
git push -u origin master
```
### macOS
For macOS, both Xcode 13.0 and makefile projects are available. You can open the project like this, or navigate to the root of the source and enter the following command.
```
make
````
In Xcode, you can use Command + B to build the project. Below the project source on the left hand side, a "Products" section allows you access the generated binary.

### Linux (Ubuntu)
For Linux, a makefile project is available. Download or clone the source, and then navigate to the root folder. You can then build the project by typing the following command.
```
make
```
### Windows
For Windows, there is currently no route to building the project. In the future, a vcxproj should be added to allow for Windows to build the project.

## Contribution
User contributions are considered, but not expected.
### Code Style
The code style of the project should be maintained. Examples are given below.


### Tests

## License
This software is licensed under the BSD-3 license. A full text can be viewed ![here](LICENSE).
