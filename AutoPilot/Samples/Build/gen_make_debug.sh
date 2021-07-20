mkdir build_debug
cd build_debug
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
