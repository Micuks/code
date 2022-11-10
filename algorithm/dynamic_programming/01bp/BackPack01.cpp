#include <algorithm>
#include <assert.h>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

class BackPack01 {
  public:
    BackPack01(std::istream &is) {
        // Initialize array that dp uses.
        for (int i = 0; i < MAXN; i++) {
            dp[i] = new int[MAXN];
        }

        // Read data from is.
        is >> volume >> n;
        for (int i = 0; i < n; i++) {
            is >> w[i] >> val[i];
        }
    }

    BackPack01(std::fstream &fs) {
        // Initialize array that dp uses.
        for (int i = 0; i < MAXN; i++) {
            dp[i] = new int[MAXN];
        }

        // Read data from is.
        fs >> volume >> n;
        for (int i = 0; i < n; i++) {
            fs >> w[i] >> val[i];
        }
    }

    ~BackPack01() {
        delete[] w;
        delete[] val;

        for (int i = 0; i < MAXN; i++) {
            delete[] dp[i];
        }
        delete[] dp;
    }

    std::string constructorDebugString() {
        std::stringstream ss;
        ss << "Volume: " << volume << ", Items: " << n << std::endl;
        for (int i = 0; i < n; i++) {
            ss << std::setw(3) << w[i] << " | " << std::setw(3) << val[i]
               << std::endl;
        }
        return ss.str();
    }

    void backPackDP(); // DP to calculate best maxVal.
                       //
    int getMaxVal() const { return maxVal; }

  private:
    int maxVal; // Max total value of items in backpack.
    int volume; // Volume of backpack.
    int n;      // Number of items.

    const int MAXN = 2600;
    int *w = new int[MAXN];   // Weight of items
    int *val = new int[MAXN]; // Value of items

    int **dp = new int *[MAXN]; // dp[MAXN][MAXN], dp[item][volume].
};

std::ostream &operator<<(std::ostream &os, const BackPack01 &bp) {
    os << bp.getMaxVal();
    return os;
}

void BackPack01::backPackDP() {
    maxVal = -1;

    // Initialize
    for (int j = 0; j <= volume; j++) {
        dp[n - 1][j] = (j >= w[n - 1]) ? val[n - 1] : 0;
    }

    int i = n - 2, j = volume;
    for (; i >= 0; i--) {
        j = volume;
        for (; j >= 0; j--) {

            // Compare total value of items in the backpack between put item[i]
            // in and not put it in.
            dp[i][j] = (j >= w[i]) ? std::max(dp[i + 1][j],
                                              dp[i + 1][j - w[i]] + val[i])
                                   : dp[i + 1][j];
        }
    }

    maxVal = dp[0][volume];
}

int main(int argc, char **argv) {
    // std::ios_base::sync_with_stdio(false);
    std::fstream fs;
    // Will attempt to open given file if received more then one
    // parameters.
    if (argc > 1) {
        try {
            fs.open(argv[1], std::ios_base::in);
        } catch (std::system_error &e) {
            std::cerr << e.code().message() << std::endl;
            exit(-1);
        }
    } else {
        // Open default input file
        try {
            char filename[] = "samples/bag1.in";
            fs.open(filename, std::ios_base::in);
        } catch (std::system_error &e) {
            std::cerr << e.code().message() << std::endl;
        }
    }

    assert(fs.is_open() == true);

    void *p = new char[sizeof(BackPack01)];
    BackPack01 *backPack01 = new (p) BackPack01(fs);
    fs.close();

    std::cout << backPack01->constructorDebugString();

    auto begin = std::chrono::high_resolution_clock::now();

    backPack01->backPackDP();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout.precision(6);
    std::cout << "[BackPack01DP] Time measured: " << elapsed.count() * 1e-9
              << " seconds.\n";

    // char output_file_name[] = "samples/BackPack01.out";
    // fs.open(output_file_name, std::ios_base::out);
    // // Print sorted numbers to output_file_name
    // fs << *backPack01;
    // fs.close();
    std::cout << *backPack01 << std::endl;

    backPack01->~BackPack01();
    delete[] (char *)p;
    return 0;
}
