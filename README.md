# OpenGL 3D Ultimate Template

This is my template for OpenGL projects. It acts as an engine of sorts, providing a simple way to create OpenGL applications. It is designed to be as simple as possible, while still providing a good amount of functionality. It is not meant to be a full game engine, but rather a starting point for creating one.

## Installation

To use this template, simply clone the repository and open it in Visual Studio Code. It already comes with all the necessary dependencies. However, you need to install gcc/g++ in order to compile the code. You can do this by installing MinGW. To do so please follow this tutorial [here](https://code.visualstudio.com/docs/cpp/config-mingw).

### Run the code

To run the code simply go to the main script (typically called Main.py) and press the play button in the top right corner of the screen. This will compile and run the code. When prompted to chose a compiler please chose the following:
```
g++.exe - Build and debug active file
```

If you chose another and the program isn't running simply reset the tasks.json file by copying again from this repository and try again.

### Change running file

To change the execution options, simply change the tasks.json file. You can do this by going to the .vscode folder and opening the tasks.json file. Here you can change the command to run the code, the arguments to pass to the code.

## Documentation

TODO... For now you can check the code and see how it works. But it is commented so it should be easy to understand.
