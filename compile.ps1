#builds the project along with it's dependencies.(only required to do the first time)

Remove-Item build -Recurse -Force
mkdir build
Set-Location build
cmake -G "MinGW Makefiles" ..
mingw32-make
cmake --build .
Set-Location ..
build\openglcompile.exe
Pause
Clear-Host