if not exist build mkdir build
cd build
cmake -S ../ -B . -G "MinGW Makefiles"
make
voxpile.exe
cd ..
