rm -rf ./build/
mkdir build/
cd ./build/
cmake ..
make
rm -f ../polynomial
ln ./polynomial ../polynomial
