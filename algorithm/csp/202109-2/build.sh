GFLAGS="-std=c++11"
g++ ${GFLAGS} ./data_gen.cpp -o data_gen
g++ ${GFLAGS} ./t130.cpp -o t130
g++ ${GFLAGS} ./t130_vanilla.cpp -o vanilla
