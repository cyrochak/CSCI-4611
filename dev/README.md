
# Dev Folder

The Dev folder has a list of applications that are in development.  **Your assignments will be submitted by checking your code in into this folder.**  The directory will be structured as follows:

```
dev/MinGfx
dev/App1
dev/App2
...
dev/AppN
```

## Building a New Aplication

#### Configure and Build

* Linux or Mac (command line)
    ```bash
    cd dev/App1
    mkdir build
    cd build
    cmake ..
    make
    ```
* Mac (XCode)
    ```bash
    cd dev/App1
    mkdir build
    cd build
    cmake .. -G Xcode
    # Open solution from build directory with XCode and build all
    ```
* Windows
  * Visual Studio 2015
      ```bash
      cd dev/App1
      mkdir build
      cd build
      cmake .. -G "Visual Studio 14 2015 Win64" 
      # Open solution from build directory with Visual Studio and build all
      ```
  * Visual Studio 2017
      ```bash
      cd dev/App1
      mkdir build
      cd build
      cmake .. -G "Visual Studio 15 2017 Win64" 
      # Open solution from build directory with Visual Studio and build all
      ```
#### Run Application

* Linux or Mac (command line)
    ```bash
    cd dev/App1
    ./build/[App1Exe]
    ```
* Mac (XCode)
    ```bash
    # Run from XCode
    ```
*  Windows
   ```bash
    # Run from Visual Studio
   ```
