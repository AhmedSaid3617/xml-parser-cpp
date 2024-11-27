# XML Parser

A lightweight and fast XML parser written in C++ for processing and manipulating XML data.

## Features
- Parse XML into a tree structure.
- Support for attribute and tag access.
- Minimal and dependency-free.
- Easy-to-use API.

## Requirements
- C++17 or newer.

## Installation
Clone the repository:
   ```bash
   git clone https://github.com/yourusername/xml-parser.git
   ```
Fetch all branches
   ```bash
   git fetch
   ```

Then checkout to the branch you're supposed to work on.
   ```bash
   git checkout <branch-name>
   ```

## Compilation

### For VS Code Users

1. To build the project, press **`Ctrl` + `Shift` + `B`**, then choose **`CMake: build`** from the popup window.
2. To run the program, use the following commands based on your operating system:

#### Windows:
```bash
build\xml_parser
```

#### Linux:
```bash
build/xml_parser
```

### For other IDEs
#### Option 1
1. Create a project using your IDE.
2. Add all the .cpp files in src to your project, as well as the .h files in inc.

#### Option 2
Find out a way to use CMake in your IDE.

## GUI Compilation
To compile GUI executables, make sure you meet `QT` library requirements and add following parameter to `CMake` using bash scripts or IDE tools.
```shell
-DCOMPILE_GUI=1
```

