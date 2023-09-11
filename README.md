# Nicolor
Nicolor is a color manipulation library and CLI tool written in C++.
As I don't know how to name stuff, I just add **Ni** to it and call it a day.  

## What this actually is
This is just a recap of what I know from C/C++ and a farewell (not really, but I'll mostly try to code Rust from now on);
With learning unit tests and TDD in this beautiful language, and how to use CMake thanks to my friend [sepehr](https://github.com/Sephixum).

## Installation
Nicolor will install and build this dependencies. So try to have a internet connection!
### dependencies
- [fmt](https://github.com/fmtlib/fmt)  
- [Google Tests](https://github.com/google/googletest)  

Use the commands below will compile and install `nicmd` and `nicolor` library.  
```
cmake -S . -B build
cmake --build build
sudo cmake --install build
```
## Usage
#### nicmd
nicmd is a commandline tool to show and manipulate colors. darken, lighten, show in other formats and many more. Its a preview to the **nicolor** library.
#### nicolor
After installation, you can `#include <nicolor.h>` inside any C++ project and compile with `g++ some-cool-main.cpp -lnicolor`.
