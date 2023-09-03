#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vii;
#define trace(x) cerr << #x << " : " << x << endl
#define _ << " " <<
#define sz(x) ((int)(x).size())
#define X first
#define Y second

#define MAX_N 100005

/**
 * generated template for competetive programming
 * problem {} ({}/{})
 * {}, {}
 * author: @shamir0xe
 * verdict: [AC/WA/TLE/MLE]
 **/

vector<int> range(int n) {
    vector<int> indices(n);
    for (int i = 0; i < n; ++i)
        indices[i] = i;
    return indices;
}

// define variables here
int n;

// define functions here

class Solution {
  public:
    bool canBeEqual(string s1, string s2) {
        set<string> total;
        for (auto i: range(2)) {
            for (auto j: range(2)) {
                total.insert(s1);
                swap(s1[1], s1[3]);
            }
            swap(s1[0], s1[2]);
        }
        return total.find(s2) != total.end();
    }
};

void read_input() {
    cin >> n;
    // trace(hs[0] _ hs[1] _ sz(edges));
}

auto solve() {
    // main logic comes here

    int ans = 0;
    return ans;
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << ans << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    bool test_case = false;
    if (test_case) {
        int t;
        cin >> t;
        while (t--) {
            second_main();
        }
    } else {
        second_main();
    }
    return 0;
}
