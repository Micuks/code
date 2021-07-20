rm -rf build_release
bash gen_make_release.sh
cd build_release
make -j10
