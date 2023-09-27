#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem D (4/7)
 * codeforces, codeforces-round-900-div3
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
int n, k;
string s;
vi lefts, rights;
int q;
vi queries;

// define functions here

int read_input() {
    cin >> n >> k >> s;
    lefts.resize(k);
    rights.resize(k);
    for (int i: range(k)) {
        cin >> lefts[i];
        lefts[i]--;
    }
    for (int i: range(k)) {
        cin >> rights[i];
        rights[i]--;
    }
    cin >> q;
    queries.resize(q);
    for (int i: range(q)) {
        cin >> queries[i];
        queries[i]--;
    }
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    vector<pii> points;
    sort(all(queries));
    int idx = 0;
    for (int x: queries) {
        while (rights[idx] < x)
            idx++;
        int a = min(x, lefts[idx] + rights[idx] - x);
        int b = max(x, lefts[idx] + rights[idx] - x);
        points.push_back({a, idx});
        points.push_back({b + 1, idx});
    }
    sort(all(points));
    int dir = 1;
    idx = 0;
    int i = 0;
    string ans;
    // trace(points);
    while (i < n) {
        while (idx < sz(points) && points[idx].X <= i) {
            idx++;
            dir ^= 1;
        }
        int index = points[idx - 1].Y;
        // trace(index _ dir);
        if (!dir)
            ans += s[lefts[index] + rights[index] - i];
        else
            ans += s[i];
        i++;
    }
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
