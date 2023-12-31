#include <bits/stdc++.h>
using namespace std;

/**
 * problem C (3/4)
 * leetcode, biweekly-contest-115
 * author: @shamir0xe
 * generated by contest-builder
 * https://github.com/shamir0xe/contest-builder
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

// define functions here
int dist(string &a, string &b) {
    if (sz(a) != sz(b)) return -1;
    int cnt = 0;
    for (int i: range(sz(a))) {
        cnt += a[i] != b[i] ? 1 : 0;
    }
    return cnt;
}

class Solution {
  public:
    vector<string> getWordsInLongestSubsequence(int n, vector<string> &words,
                                                vector<int> &groups) {
        vvi adj(n, vi());
        for (int i: range(n)) {
            for (int j: range(i + 1, n)) {
                if (dist(words[i], words[j]) == 1 && groups[i] != groups[j]) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        vi dp(n + 1, 0);
        vi par(n + 1, -1);
        dp[n] = 0;
        int idx = -1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j: adj[i]) {
                if (dp[i] < 1 + dp[j]) {
                    dp[i] = 1 + dp[j];
                    par[i] = j;
                }
            }
            if (idx == -1 || dp[idx] < dp[i]) {
                idx = i;
            }
        }
        vector <string> ans;
        while (idx != -1) {
            ans.push_back(words[idx]);
            idx = par[idx];
        }
        return ans;
    }
};

int read_input() {
    cin >> n;
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.assert_yellow("Hello");
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
