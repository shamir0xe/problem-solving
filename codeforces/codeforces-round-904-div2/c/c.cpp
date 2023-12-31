#include <bits/stdc++.h>
using namespace std;

/**
 * problem C (3/5)
 * codeforces, codeforces-round-904-div2
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

template <typename T, typename K = function<void(void)>>
void smin(
    T &a, T b, const K callable = []() {}) {
    if (a > b) {
        a = b;
        callable();
    }
}

template <typename T, typename K = function<void(void)>>
void smax(
    T &a, T b, const K callable = []() {}) {
    if (a < b) {
        a = b;
        callable();
    }
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
vector<pii> intervals;

// define functions here

int read_input() {
    cin >> n >> m;
    intervals.clear();
    for (int i: range(n)) {
        int le, ri;
        cin >> le >> ri;
        le--;
        ri--;
        intervals.push_back({le, ri});
    }
    return 0;
}

int go(vector<pair<int, pii>> &events) {
    sort(all(events));
    int maxi = 0;
    vi stack;
    int best_offset;
    for (auto &event: events) {
        int offset = event.X;
        int ty = event.Y.X;
        int idx = event.Y.Y;
        if (ty == 1) {
            stack.push_back(idx);
            smax(maxi, sz(stack), [&]() { best_offset = offset; });
        } else {
            stack.pop_back();
        }
    }
    return maxi;
}

auto solve() {
    /**
     * main logic goes here
     **/
    vector<pair<int, pii>> events;
    for (int i: range(n)) {
        if (intervals[i].Y < m - 1) {
            pii interval = intervals[i];
            events.push_back({interval.X, {1, i}});
            events.push_back({interval.Y + 1, {0, i}});
        }
    }
    int maxi = go(events);
    events.clear();
    for (int i: range(n)) {
        if (intervals[i].X > 0) {
            pii interval = intervals[i];
            events.push_back({interval.X, {1, i}});
            events.push_back({interval.Y + 1, {0, i}});
        }
    }
    smax(maxi, go(events));
    
    return maxi;
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
