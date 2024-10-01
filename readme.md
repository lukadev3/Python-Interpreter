# Instructions

## Python Interpreter for Working with Strings, Lists, and Tuples

- When writing code, use spaces consistently or not at all.
- The `print()` function is used only to print a variable or string (e.g., `print("apple")` or `print(a)`).
- Printing a variable can also be done by simply typing the variable name in the terminal (e.g., `a`).
- Exceptions are not implemented in the code because they interrupt the program, and it must be restarted (the code still recognizes errors).
- When assigning a string to a variable, both double (`""`) and single quotes (`''`) can be used (the code automatically uses `''` like in Python).
- When running the program, code can be immediately entered in the terminal, and to exit, use `exit`.

## Setup Instructions

1. **Install CMake**:
   - Download the latest version of CMake from the [official website](https://cmake.org/download/).
   - Follow the installation instructions for your operating system.

2. **Install MinGW**:
   - Download MinGW from the [MinGW-w64](https://sourceforge.net/projects/mingw/).
   - Follow the instructions to install it. Make sure to choose the correct architecture (32-bit or 64-bit) based on your needs.

3. **Add MinGW to PATH**:
   - Open the Start menu and search for "Environment Variables".
   - Click on "Edit the system environment variables".
   - In the System Properties window, click on the "Environment Variables" button.
   - In the "System variables" section, find the `Path` variable and click "Edit".
   - Click "New" and add the path to the MinGW `bin` directory (e.g., `C:\MinGW\bin` or `C:\TDM-GCC-64\bin`).
   - Click "OK" to save the changes.

4. **Install VS Code Extensions**:
   - Open Visual Studio Code.
   - Go to the Extensions view by clicking on the Extensions icon in the Activity Bar on the side.
   - Search for and install the following extensions:
     - C/C++ (by Microsoft)
     - CMake Tools (by Microsoft)
     - Code Runner (optional, for running code directly)

5. **Select Kit in VS Code**:
   - Open your project folder in Visual Studio Code.
   - Press `Ctrl + Shift + P` to open the Command Palette.
   - Type "CMake: Select a Kit" and select it.
   - Choose the appropriate GCC kit (e.g., GCC 10.3.0) from the list.

6. **Build the Project**:
   - Press `Ctrl + Shift + P` to open the Command Palette again.
   - Type "CMake: Build" and select it to build the project.

7. **Run the Executable**:
   - After the build is complete, you can run the executable from the terminal by typing:
     ```bash
     ./run.exe
     ```
   - Alternatively, you can run it directly by navigating to the build folder and double-clicking on `run.exe`.

