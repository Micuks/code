GFLAGS="-std=c++11 -O2"
g++ ${GFLAGS} ./data_gen.cpp -o data_gen
g++ ${GFLAGS} ./t130.cpp -o t130
g++ ${GFLAGS} ./t130_vanilla.cpp -o vanilla
./data_gen
./t130<in>out
./vanilla<in>out_van
diff out out_van
