cmake -B build
cmake --build build 
$PWD/build/bin/ComputerClub $1
rm -rf build
