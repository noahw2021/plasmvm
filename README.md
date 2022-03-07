# plasmvm
<br>
![Lines of Code](https://tokei.rs/b1/github/noahw2021/plasmvm)
![Code size](https://img.shields.io/github/languages/code-size/noahw2021/plasmvm.svg)
An interpreted PLASM emulator.

## Continous Integration
Below, badges for continous integration are available.
| Platform                 | Main |
|--------------------------|------|
| macOS (Latest)           |[![macOS Build](https://github.com/noahw2021/plasmvm/actions/workflows/c-macos.yml/badge.svg)](https://github.com/noahw2021/plasmvm/actions/workflows/c-macos.yml)|
| macOS (10.15)            |[![macOS Legacy Build](https://github.com/noahw2021/plasmvm/actions/workflows/c-osxlegacy.yml/badge.svg)](https://github.com/noahw2021/plasmvm/actions/workflows/c-osxlegacy.yml)|
| Linux (Ubuntu Latest)    |[![Ubuntu Build](https://github.com/noahw2021/plasmvm/actions/workflows/c-ubuntu.yml/badge.svg)](https://github.com/noahw2021/plasmvm/actions/workflows/c-ubuntu.yml)|
| Linux (Ubuntu LTS 18.04) |[![Ubuntu LTS Build](https://github.com/noahw2021/plasmvm/actions/workflows/c-ubuntults.yml/badge.svg)](https://github.com/noahw2021/plasmvm/actions/workflows/c-ubuntults.yml)|
| Windows (Latest Release) |[![Windows Build](https://github.com/noahw2021/plasmvm/actions/workflows/c-winlatest.yml/badge.svg)](https://github.com/noahw2021/plasmvm/actions/workflows/c-winlatest.yml)|
| Windows (Latest Debug)   |[![Windows Debug Build](https://github.com/noahw2021/plasmvm/actions/workflows/c-winlatestdbg.yml/badge.svg)](https://github.com/noahw2021/plasmvm/actions/workflows/c-winlatestdbg.yml)|

## Precompiled Binaries
Upon major milestone releases, precompiled releases are provided in the 'Releases' section on the right hand side of the desktop website.

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
<br>
| Example       | Bad 1         | Bad 2          | Good          |
|---------------|---------------|----------------|---------------|
| Variable Name | helloVariable | hello_variable | HelloVariable |
| Function Name | ModFunction   | Function       | mod_function  |
| Type Case 1   | long          | i32            | int           |
| Type Case 2   | unsigned long | unsigned i32   | u32           |
| File Name     | File.cpp      | File.ixx       | File.c        |
<br>
In general, from viewing the code the code style should be easily figured out. It is the descretion of the reviewer to determine what is okay, and this table may not always be consistent.

### Tests
Under all circumstances, a pull request must pass every CI test before and after human contributor review. Afterwards, they may be merged with master.

## License
This software is licensed under the BSD-3 license. A full text can be viewed [here](LICENSE).
