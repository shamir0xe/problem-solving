#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem {} ({}/{})
 * {}, {}
 * author: @shamir0xe
 * verdict: [AC/WA/TLE/MLE]
 **/

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
#define trace(x) cerr << #x << " : " << x << endl
#define _ << " " <<
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define X first
#define Y second

/**
 * printing tuples
 **/
template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
__tuple_printer(ostream &os, const tuple<T...> &tup){};

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
__tuple_printer(ostream &os, const tuple<T...> &tup) {
    if (n != 0)
        os << " ";
    os << get<n>(tup);
    __tuple_printer<n + 1>(os, tup);
};

template <typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup) {
    os << "(";
    __tuple_printer<0>(os, tup);
    os << ")";
    return os;
}

/**
 * printing pairs
 **/
template <typename T, typename K>
ostream &operator<<(std::ostream &os, const std::pair<T, K> &p) {
    os << "(" << p.first << " " << p.second << ")";
    return os;
}

/**
 * printing vectors
 **/
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[";
    bool first = true;
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
        if (first)
            first = false;
        else
            os << " ";
        os << (*ii);
    }
    os << "]";
    return os;
}

/**
 * range functions
 **/
inline vi range(int idx, int n) {
    if (n <= idx)
        return vi();
    vi indices(n - idx);
    for (int i = idx; i < n; ++i)
        indices[i - idx] = i;
    return indices;
}

inline vi range(int n) { return range(0, n); }

// define variables here
#define MAX_M 15
int n;
string s1, s2;

// define functions here
inline void smax(int &a, const int b) {
    if (a < b)
        a = b;
}
class Solution {
  public:
    int longestCommonSubsequence(string text1, string text2) {
        int n, m;
        n = sz(text1);
        m = sz(text2);
        vvi dp = vvi(n, vi(m, 0));
        if (text1[0] == text2[0])
            dp[0][0] = 1;
        for (int i: range(1, n)) {
            dp[i][0] = dp[i - 1][0];
            smax(dp[i][0], text1[i] == text2[0] ? 1 : 0);
        }
        for (int j: range(1, m)) {
            dp[0][j] = dp[0][j - 1];
            smax(dp[0][j], text1[0] == text2[j] ? 1 : 0);
        }
        for (int i: range(1, n)) {
            for (int j: range(1, m)) {
                dp[i][j] = dp[i - 1][j];
                smax(dp[i][j], dp[i][j - 1]);
                if (text1[i] == text2[j])
                    smax(dp[i][j], 1 + dp[i - 1][j - 1]);
            }
        }
        return dp[n - 1][m - 1];
    }
};

int read_input() {
    cin >> s1 >> s2;
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.longestCommonSubsequence(s1, s2);
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
