#include <bits/stdc++.h>
using namespace std;

/**
 * problem A (1/7)
 * codeforces, educational-codeforces-round-156-rated-for-div2
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

int read_input() {
    cin >> n;
    return 0;
}

bool can(vi &arr) {
    sort(all(arr));
    if (arr[0] == arr[1] || arr[1] == arr[2]) return false;
    for (int t: arr) {
        if (t <= 0) return false;
        if (t % 3 == 0) return false;
    }
    return true;
}

tuple<bool, vi> solve() {
    /**
     * main logic goes here
     **/
    vvi possibles = {{1, 2, n - 3}, {1, 4, n - 5}, {2, 4, n - 6}};
    for (auto possibility: possibles) {
        if (can(possibility)) return {true, possibility};
    }
    return {false, vi()};
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << (get<0>(ans) ? "YES" : "NO") << endl;
    if (get<0>(ans)) {
        for (int t: get<1>(ans)) {
            cout << t << ' ';
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
