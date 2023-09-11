#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem D (4/6)
 * codeforces, codeforces-round-897-div2
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
#define MAX_N 200010
int n, k;
vi b;
int cur_color = 0;
int depths[MAX_N];
vi color;
set<int> cycles;

// define functions here

void dfs(int u, int depth) {
    depths[u] = depth;
    color[u] = 1;
    int v = b[u];
    if (color[v] == 0) dfs(v, depth + 1);
    else {
        if (color[v] == 1) {
            // we have visited this before
            int cycle = depth - depths[v] + 1;
            // trace(cycle _ depth _ depths[v]);
            cycles.insert(cycle);
        } else {
            // color == 2
        }
    }
    color[u] = 2;
}

int read_input() {
    cin >> n >> k;
    b.resize(n);
    for (int i: range(n)) {
        cin >> b[i];
        b[i] --;
    }
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    color.resize(n);
    color.assign(n, 0);
    cycles.clear();
    for (int i: range(n)) {
        if (color[i] == 0) {
            dfs(i, 0);
        }
    }
    if (k == 1) {
        bool ans = true;
        for (int i: range(n)) {
            ans &= b[i] == i;
        }
        return ans;
    }
    // k > 1
    // for (int t: cycles) {
    //     trace(t);
    // }
    return sz(cycles) == 1 && *cycles.begin() == k;
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << (ans ? "YES" : "NO") << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    bool test_case = true;
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
