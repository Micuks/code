mkdir build_release
cd build_release
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"
