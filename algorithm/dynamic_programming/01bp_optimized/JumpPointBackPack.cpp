#include <algorithm>
#include <assert.h>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

class Pack {
  public:
    Pack(int weight = 0, int val = 0) : weight(weight), val(val) {}
    int weight;
    int val;
    friend bool operator<(const Pack &ba, const Pack &bb) {
        return (ba.weight != bb.weight) ? ba.weight > bb.weight
                                        : ba.val < bb.val;
    }
};

class BackPackJumpPoint {
  public:
    BackPackJumpPoint(std::istream &is, bool verbose = false) {
        for (int i = 0; i < MAXN * 1000; i++) {
            jp[i] = new int[2];
        }

        // Read data from is.
        is >> volume >> n;
        for (int i = 0; i < n; i++) {
            is >> w[i] >> val[i];
        }

        // Set whether track items in backpack at every step.
        traceBackPackStatus = verbose;
    }

    BackPackJumpPoint(std::fstream &fs, bool verbose = false) {
        for (int i = 0; i < MAXN * 1000; i++) {
            jp[i] = new int[2];
        }

        // Read data from is.
        fs >> volume >> n;
        for (int i = 0; i < n; i++) {
            fs >> w[i] >> val[i];
        }
        // Set whether track items in backpack at every step.
        traceBackPackStatus = verbose;
    }

    ~BackPackJumpPoint() {
        for (int i = 0; i <= n; i++) {
            delete[] jp[i];
        }
        delete[] jp;

        delete[] w;
        delete[] val;
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

    void JumpPointBackPackDP(); // BackPack DP using jump point optimization.
    int getMaxVal() const { return maxVal; }

    std::string itemsInMaxValBackPackToString() {
        std::stringstream ss;
        ss << std::setw(4) << "Item"
           << " | " << std::setw(6) << "Weight"
           << " | " << std::setw(5) << "Value"
           << " |" << std::endl;

        for (auto &a : itemsInMaxValBackPack) {
            ss << std::setw(4) << a << " | " << std::setw(6) << w[a] << " | "
               << std::setw(5) << val[a] << " |" << std::endl;
        }
        return ss.str();
    }

    friend std::ostream &operator<<(std::ostream &os, BackPackJumpPoint &bp);

  private:
    bool traceBackPackStatus = false; // Track items in backpack at every state.
    int maxVal;                       // Max total value of items in backpack.
    int volume;                       // Volume of backpack.
    int n;                            // Number of items.

    static const int MAXN = 100000;
    int *w = new int[MAXN];            // Weight of items
    int *val = new int[MAXN];          // Value of items
    int **jp = new int *[MAXN * 1000]; // Jump points

    std::vector<int> itemsInMaxValBackPack;
};

std::ostream &operator<<(std::ostream &os, BackPackJumpPoint &bp) {
    os << bp.maxVal;
    return os;
}

void BackPackJumpPoint::JumpPointBackPackDP() {
    int *head = new int[n + 2]; // Track jump point start position.
    head[n] = 0;
    jp[0][0] = 0; // Store item weight
    jp[0][1] = 0; // Store item value

    // Left points to first jump point of p[i+1], right points to last jump
    // point of p[i+1]. Next is position where next jump point will store.
    int left = 0, right = 0, next = 1;
    head[n - 1] = 1; // Points to the position of first jump point of item[n-1].

    for (int i = n - 1; i >= 0; i--) {
        int k = left; // k points to jump points of p[], move k to
                      // evaluate controlled points in p[] and
                      // p[]+(w,v)
        for (int j = left; j <= right; j++) {

            if (jp[j][0] + w[i] > volume) {
                // No enough backpack space to fit item[i] in, exit loop.
                break;
            }

            // Compute new jump point as jp[]+(w,v).
            int x = jp[j][0] + w[i];
            int y = jp[j][1] + val[i];

            // If jp[k][0] < x, then it must be a jump point of current
            // item.
            while (k <= right && jp[k][0] < x) {
                jp[next][0] = jp[k][0];
                jp[next++][1] = jp[k++][1];
            }

            // Clear controlled jump point.
            if (k <= right && jp[k][0] == x) {
                if (y < jp[k][1]) {
                    y = jp[k][1];
                }
                k++;
            }

            if (y > jp[next - 1][1]) {
                jp[next][0] = x;
                jp[next++][1] = y;
            }

            while (k <= right && jp[k][1] <= jp[next - 1][1]) {
                k++;
            }
        }

        // Add remaining jump points.
        while (k <= right) {
            jp[next][0] = jp[k][0];
            jp[next++][1] = jp[k++][1];
        }

        left = right + 1;
        right = next - 1;

        head[i - 1] = next;
    }

    if (traceBackPackStatus) {
        std::stringstream ss;
        for (int i = n; i > 0; i--) {
            ss << std::endl;
            ss << "| " << std::setw(4) << "id"
               << " | " << std::setw(4) << "head"
               << " |" << std::endl;
            ss << "| " << std::setw(4) << i << " | " << std::setw(4) << head[i]
               << " |" << std::endl;
            // Begin and end of item[i-1].
            int begin = head[i];
            int end = head[i - 1];

            ss << "jump points:\n";
            for (int j = begin; j < end; j++) {
                ss << "| " << std::setw(4) << jp[j][0] << " | " << std::setw(4)
                   << jp[j][1] << " |" << std::endl;
            }
        }
        std::cout << ss.str();
    }

    maxVal = jp[next - 1][1];
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
            char filename[] = "../samples/bag.in";
            fs.open(filename, std::ios_base::in);
        } catch (std::system_error &e) {
            std::cerr << e.code().message() << std::endl;
        }
    }
    assert(fs.is_open() == true);

    void *pJ = new char[sizeof(BackPackJumpPoint)];
    bool verbose = false;
    BackPackJumpPoint *backPackJumpPoint =
        new (pJ) BackPackJumpPoint(fs, verbose);
    fs.close();

    if (verbose) {
        std::cout << backPackJumpPoint->constructorDebugString();
    }

    auto begin = std::chrono::high_resolution_clock::now();

    backPackJumpPoint->JumpPointBackPackDP();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout.precision(6);
    std::cout << "[JumpPointBackPack] Time measured: " << elapsed.count() * 1e-9
              << " seconds.\n";

    char output_file_name[] = "samples/jump_bag.out";
    fs.open(output_file_name, std::ios_base::out);
    // Print sorted numbers to output_file_name
    fs << *backPackJumpPoint << std::endl;
    std::cout << *backPackJumpPoint << std::endl;
    fs.close();

    delete[] (char *)pJ;
    return 0;
}
