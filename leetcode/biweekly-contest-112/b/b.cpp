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

// generated template for competetive programming
// problem {} ({}/{})
// {}, {}
// author: @shamir0xe
// verdict: [AC/WA/TLE/MLE]

// define variables here
string s1, s2;

vector<int> range(int n) {
    vector<int> indices(n);
    for (int i = 0; i < n; ++i)
        indices[i] = i;
    return indices;
}

class Solution {
  public:
    bool checkStrings(string s1, string s2) {
        vector<char> evens[2], odds[2];
        int n = sz(s1);
        // trace(n);
        // trace(s1 _ s2);
        int index = 0;
        for (int i = 0; i < n; i += 2) {
            evens[index].push_back(s1[i]);
            evens[1 ^ index].push_back(s2[i]);
        }
        for (int i = 1; i < n; i += 2) {
            odds[index].push_back(s1[i]);
            odds[1 ^ index].push_back(s2[i]);
        }
        // for (auto i: range(n)) {
        // 	trace(i _ evens[0][i]);
        // }
        for (auto i: range(2)) {
            // cout << sz(evens[i]) << endl;
            sort(evens[i].begin(), evens[i].end());
            sort(odds[i].begin(), odds[i].end());
        }
        // trace("here");
        bool bl = true;
        for (auto i: range(sz(evens[0]))) {
            bl &= evens[0][i] == evens[1][i];
        }
        for (auto i: range(sz(odds[0]))) {
            bl &= odds[0][i] == odds[1][i];
        }
        return bl;
    }
};

void read_input() {
    cin >> s1 >> s2;
    // trace(hs[0] _ hs[1] _ sz(edges));
}

auto solve() {
    // main logic comes here
    Solution solution = Solution();
    return solution.checkStrings(s1, s2);
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
