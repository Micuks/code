rm -rf ./build
mkdir ./build
cd ./build
cmake ..
make
./search < ../data.in
