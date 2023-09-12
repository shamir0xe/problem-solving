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
string s, t;

// define functions here
void decrease(map<char, int> &mp, char ch) {
    mp[ch]--;
    if (mp[ch] == 0)
        mp.erase(ch);
}

class Solution {
  public:
    string minWindow(string s, string t) {
        pair<int, pii> ans = {-1, {-1, -1}};
        map<char, int> needs, supplies;
        map<char, int> cur;
        for (char ch: t)
            needs[ch]++;
        cur.insert(all(needs));
        // for (auto t: cur) {
        //     trace(t);
        //     trace(t.X _ t.Y);
        // }
        int i = 0;
        int j = 0;
        int n = sz(s);
        while (i < n && j < n) {
            while (sz(cur) > 0 && i < n) {
                char ch = s[i];
                if (cur.find(ch) != cur.end())
                    decrease(cur, ch);
                else
                    supplies[ch]++;
                i++;
            }
            while (sz(cur) == 0 && j < i) {
                if (ans.X == -1 || ans.X > i - j) {
                    ans = {i - j, {j, i}};
                }
                char ch = s[j];
                if (supplies.find(ch) != supplies.end())
                    decrease(supplies, ch);
                else {
                    if (needs.find(ch) != needs.end()) {
                        // we need to add ch to cur
                        cur[ch]++;
                    }
                }
                j++;
            }
        }
        // trace(i _ j);
        // trace(ans);
        if (ans.X == -1)
            return "";
        return s.substr(ans.Y.X, ans.X);
    }
};

int read_input() {
    cin >> s >> t;
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.minWindow(s, t);
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
