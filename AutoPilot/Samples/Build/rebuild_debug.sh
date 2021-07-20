rm -rf build_debug
bash gen_make_debug.sh
cd build_debug
make VERBOSE=1 -j10
