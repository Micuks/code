#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::fstream fs;
    std::string arrange = "default";
    std::vector<std::string> preserved({"ascend", "descend"});

    if (argc > 1) {
        arrange = argv[1];
        if (std::find(preserved.begin(), preserved.end(), arrange) !=
            preserved.end()) {
            if (argc > 2) {
                try {
                    fs.open(argv[2], std::ios_base::in);
                } catch (std::system_error &e) {
                    std::cerr << e.code().message() << std::endl;
                }
            } else {
                try {
                    char filename[] = "samples/yet_another_sample.in";
                    fs.open(filename, std::ios_base::in);
                } catch (std::system_error &e) {
                    std::cerr << e.code().message() << std::endl;
                }
            }
        } else {
            try {
                fs.open(argv[1], std::ios_base::in);
            } catch (std::system_error &e) {
                std::cerr << e.code().message() << std::endl;
            }
        }
    } else {
        try {
            char filename[] = "samples/yet_another_sample.in";
            fs.open(filename, std::ios_base::in);
        } catch (std::system_error &e) {
            std::cerr << e.code().message() << std::endl;
        }
    }

    int num;
    fs >> num;
    std::vector<int> arr;
    while (fs >> num) {
        arr.push_back(num);
    }
    fs.close();
    int n = arr.size();
    int *a = new int[n + 1];
    std::memcpy(a, &arr[0], n * sizeof(int));
    auto begin = std::chrono::high_resolution_clock::now();

    std::sort(a, a + n);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout.precision(6);
    if (std::find(preserved.begin(), preserved.end(), arrange) ==
        preserved.end()) {
        std::cout << "[StdSort] Time measured: " << elapsed.count() * 1e-9
                  << " seconds.\n";
    }
    if (arrange == "descend") {
        std::sort(a, a + n, std::greater<int>());
    }
    // If output filename is given, output to fiven file.
    // Else output to yet_another_sample.in.
    if (argc > 2) {
        if (std::find(preserved.begin(), preserved.end(), arrange) !=
            preserved.end()) {
            if (argc > 3) {
                try {
                    fs.open(argv[3], std::ios_base::out);
                } catch (std::system_error &e) {
                    std::cerr << e.code().message() << std::endl;
                }
            } else {
                try {
                    char filename[] = "samples/stdsort.out";
                    fs.open(filename, std::ios_base::out);
                } catch (std::system_error &e) {
                    std::cerr << e.code().message() << std::endl;
                }
            }
        } else {
            try {
                fs.open(argv[2], std::ios_base::out);
            } catch (std::system_error &e) {
                std::cerr << e.code().message() << std::endl;
            }
        }
    } else {
        try {
            char filename[] = "samples/stdsort.out";
            fs.open(filename, std::ios_base::out);
        } catch (std::system_error &e) {
            std::cerr << e.code().message() << std::endl;
        }
    }

    fs << n << std::endl;
    for (int i = 0; i < n; i++) {
        fs << a[i] << " ";
    }
    fs << std::endl;
    fs.close();

    return 0;
}
