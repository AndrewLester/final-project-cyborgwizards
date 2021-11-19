# final-project-cyborgwizards

## Development Environment Setup (DO NOT RUN THIS IN CS128 VM)

1. Install the corresponding [CMake](https://cmake.org/install/) of your OS.
2. Install the CMake VS Code Plugin. If a error prompts and say CMake not found/empty executable, set `cmake.cmakePath` in VSCode settings to the path of CMake executable (in Windows normally `C:\Program Files\CMake\bin\cmake`, in Mac `/Applications/CMake.app/Contents/bin/cmake`).
3. Clone this repository. In Windows, when prompted to select the kit, select `Visual Studio Community ... - amd64`.
4. Run `git submodule update --init --recursive` to initialize submodules.
5. Click "Build" at the bottom of VSCode
6. (Windows only): Use the Windows Launch run and debug system by pushing F5
   (Macos): `cd build`, `make all` (run only once), `./bin/sensations` each time you run
