#include <algorithm>
#include <iostream>

using namespace std;

int get_overlap(int a, int b, int x1, int y1, int x2, int y2) {
    int lx = max(0, x1);
    int ly = max(0, y1);
    int hx = min(a, x2);
    int hy = min(b, y2);
    int overlap = max(0, (hx - lx)) * max(0, (hy - ly));
    // cout << overlap << endl;
    return overlap;
}

int main(int argc, char *argv[]) {
    int n, a, b;
    int result = 0;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        result += get_overlap(a, b, x1, y1, x2, y2);
    }
    cout << result << endl;
    return 0;
}
