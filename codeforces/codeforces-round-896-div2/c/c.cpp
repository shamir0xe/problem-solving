#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem C (3/6)
 * codeforces, codeforces-round-896-div2
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
int n, m;

// define functions here

int read_input() {
    cin >> n >> m;
    return 0;
}

pair<int, vvi> solve() {
    /**
     * main logic goes here
     **/
    vvi ans(n, vi(m, 0));
    for (int i: range(min(m - 1, n))) {
        for (int j: range(m)) {
            ans[i][j] = (2 * m - i - 1 + j) % m;
        }
    }
    for (int i: range(m - 1, n)) {
        if (i - 1 >= 0)
            ans[i] = ans[i - 1];
    }
    // cout << ans << endl;
    // vi total(m + 1, 1);
    // // trace(total);
    // for (int j: range(m)) {
    //     vi temp(m + 1, 1);
    //     for (int i: range(n)) {
    //         temp[ans[i][j]] = 0;
    //         // trace(ans[i][j]);
    //         // trace(temp);
    //     }
    //     for (int i: range(m + 1)) {
    //         if (temp[i] > 0) {
    //             total[i] = 0;
    //             // trace(i);
    //             break;
    //         }
    //     }
    // }
    // int res = 0;
    // for (int i: range(m + 1)) {
    //     if (total[i] > 0) {
    //         res = i;
    //         break;
    //     }
    // }
    int res = min(m, n + 1);
    if (m == 1) res = 0;
    return {res, ans};
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << ans.X << endl;
    for (int i: range(n)) {
        for (int j: range(m)) {
            cout << ans.Y[i][j] << ' ';
        }
        cout << endl;
    }
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
