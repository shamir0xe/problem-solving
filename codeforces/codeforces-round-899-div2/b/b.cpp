#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem B (2/5)
 * codeforces, codeforces-round-899-div2
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
vector<set<int>> sets;
set<int> nums;

// define functions here

int read_input() {
    cin >> n;
    sets.clear();
    sets.assign(50, {});
    nums.clear();
    for (int i: range(n)) {
        int t;
        cin >> t;
        for (int j: range(t)) {
            int a;
            cin >> a;
            a--;
            nums.insert(a);
            sets[i].insert(a);
        }
    }
    return 0;
}

void smax(int &a, const int b) {
    if (a < b)
        a = b;
}

auto solve() {
    /**
     * main logic goes here
     **/
    int ans = -1;
    for (int i: nums) {
        set<int> cur;
        for (const auto &st: sets) {
            if (st.find(i) == st.end()) {
                // for (auto temp: st) {
                //     cur.insert(temp);
                // }
                cur.insert(all(st));
            }
        }
        smax(ans, sz(cur));
        // for (auto temp: cur) {
        //     trace(temp);
        // }
        // trace(i _ sz(cur));
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
