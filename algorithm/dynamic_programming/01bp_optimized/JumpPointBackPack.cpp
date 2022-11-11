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
        // Initialize array that dp uses.
        for (int i = 0; i < MAXN; i++) {
            dp[i] = new int[MAXN];
        }

        // Read data from is.
        is >> volume >> n;
        for (int i = 0; i < n; i++) {
            is >> w[i] >> val[i];
        }

        // Set whether track items in backpack at every step.
        trackBackPackStatus = verbose;
    }

    BackPackJumpPoint(std::fstream &fs, bool verbose = false) {
        // Initialize array that dp uses.
        for (int i = 0; i < MAXN; i++) {
            dp[i] = new int[MAXN];
        }

        // Read data from is.
        fs >> volume >> n;
        for (int i = 0; i < n; i++) {
            fs >> w[i] >> val[i];
        }
        // Set whether track items in backpack at every step.
        trackBackPackStatus = verbose;
    }

    ~BackPackJumpPoint() {
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
    bool trackBackPackStatus = false; // Track items in backpack at every state.
    int maxVal;                       // Max total value of items in backpack.
    int volume;                       // Volume of backpack.
    int n;                            // Number of items.

    static const int MAXN = 2600;
    int *w = new int[MAXN];   // Weight of items
    int *val = new int[MAXN]; // Value of items
    Pack pack[MAXN];

    int **dp = new int *[MAXN]; // dp[MAXN][MAXN], dp[item][volume].

    class BackPackState {
      public:
        BackPackState(int newItemID, int previousItemID, int previousVolume)
            : newItem(newItemID),
              previousState(std::make_pair(previousItemID, previousVolume)) {}

        int newItem;
        std::pair<int, int> previousState; // Link-list-like store method
    };

    class PairHasher {
      public:
        size_t operator()(const std::pair<int, int> &obj) const {
            return (obj.first) * 10000 + (obj.second);
            // return (obj.first);
        }
    };

    std::unordered_map<std::pair<int, int>, BackPackState, PairHasher>
        backPackStateMap; // backPackState(itemID, remainedVolume) =
    // (itemJustInsertedID,
    // previousBackPackState(itemID, remainedVolume)
    std::vector<int> itemsInMaxValBackPack;
};

void BackPackJumpPoint::JumpPointBackPackDP() {
    std::priority_queue<Pack> pq;
    std::queue<Pack> turn;
    Pack initPack;
    pq.push(initPack);
    for (int i = 0; i < n; i++) {
        std::priority_queue<Pack> newPq;
        for (int j = 0; j < pq.size(); j++) {
            Pack tmp;
            tmp.weight = pq.top().weight + w[i];
            tmp.val = pq.top().val + val[i];
            newPq.push(pq.top());
            newPq.push(tmp);
            pq.pop();
        }
        while (!newPq.empty()) {
            pq.push(newPq.top());
            newPq.pop();
        }
    }

    int preWeight = 0;
    int preVal = 0;
    while (!pq.empty()) {
        if ((preWeight != pq.top().weight || preWeight == 0) &&
            pq.top().weight <= volume) {
            if (preVal >= pq.top().val) {
                pq.pop();
                continue;
            }
            turn.push(pq.top());
            preWeight = pq.top().weight;
            preVal = pq.top().val;
        }
        pq.pop();
    }

    std::cout << "Jump points:" << std::endl;

    std::stringstream ss;
    ss << std::setw(6) << "Weight"
       << " | " << std::setw(5) << "Value"
       << " |" << std::endl;

    while (!turn.empty()) {
        auto &a = turn.front();
        ss << std::setw(6) << a.weight << " | " << std::setw(5) << a.val << " |"
           << std::endl;
        turn.pop();
    }
    std::cout << ss.str();
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
            char filename[] = "../samples/bag1.in";
            fs.open(filename, std::ios_base::in);
        } catch (std::system_error &e) {
            std::cerr << e.code().message() << std::endl;
        }
    }

    assert(fs.is_open() == true);

    void *pJ = new char[sizeof(BackPackJumpPoint)];
    BackPackJumpPoint *backPackJumpPoint = new (pJ) BackPackJumpPoint(fs, true);
    fs.close();

    std::cout << backPackJumpPoint->constructorDebugString();

    auto begin = std::chrono::high_resolution_clock::now();

    backPackJumpPoint->JumpPointBackPackDP();

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

    delete[] (char *)pJ;
    return 0;
}
