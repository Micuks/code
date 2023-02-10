CXX="clang++"
GFLAGS="-std=c++11 -g"
${CXX} ${GFLAGS} t132.cpp -o t132
${CXX} ${GFLAGS} std.cpp -o std
${CXX} ${GFLAGS} data_gen.cpp -o data_gen