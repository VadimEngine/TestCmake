Windows PowerShell (Only works for x64):

To build (In /build directory):
- `cmake -S . -B build`
- `cmake --build .\build\`
- Combined: `cmake -S . -B build ; cmake --build .\build\ --clean-first`

To run:
- `.\build\Debug\Sandbox.exe`

To clean (Remove everything in \build):
- `.\clean-build.bat`

TODO
- add soil
