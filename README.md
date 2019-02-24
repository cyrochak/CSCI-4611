
# Student Repository


## Getting Started

#### Download Repository

  ```bash
  git clone https://github.umn.edu/umn-csci-4611-S18/repo-[x500]
  ```
  
#### Configure, Build, and Install Dependencies

* Linux and Mac
    ```bash
    cd /path/to/repo-[x500]
    ./scripts/setup.sh
    ```
* Windows
   * Using Git Bash application (Installed with [Git](https://git-scm.com/downloads)):
      * Visual Studio 2015
        ```bash
        cd C:/path/to/repo-[x500]
        ./scripts/setup.sh "Visual Studio 14 2015 Win64" 
        ```
      * Visual Studio 2017
        ```bash
        cd C:/path/to/repo-[x500]
        ./scripts/setup.sh "Visual Studio 15 2017 Win64" 
        ```
   * Add **C:/path/to/repo-[x500]/bin** to your Windows environment path:
      * Go to Control Panel > System and Security > System, and click “Advanced system settings” on the left.
      * In “System Properties” window, under “Advanced” tab, click “Environment Variables…”
      * In “System variables” pane, click “Path” variable and click “Edit…” button. 
      * In “Edit environment variable” window, Click “New” and “Browse…” to set the path to the “C:/path/to/repo-[x500]/bin” folder under your repo.
      * Click “OK” to save the changes.
      * Log out and log back in.

#### Run Test Application

* Linux
    ```bash
    cd /path/to/repo-[x500]
    ./dev/MinGfx/build/tests/gui_plus_opengl/mingfx-test-gui-plus-opengl
    ```
*  Windows and Mac
   ```bash
   cd /path/to/repo-[x500]
   ./bin/mingfx-test-gui-plus-opengl
   ```

#### Clean Project

* All Platforms
    ```bash
    scripts/clean.sh
    ```
