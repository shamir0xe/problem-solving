#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem 731-my-calendar-ii (1/1)
 * leetcode, problemset
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
vector<pii> events, pairs;

// define functions here

class MyCalendarTwo {
  public:
    MyCalendarTwo() { events.clear(); }

    bool book(int start, int end) {
        vector<pii> backup;
        backup.assign(all(events));
        events.push_back({start, 1});
        events.push_back({end - 1, 2});
        sort(all(events));
        int cnt = 0;
        for (auto &[index, event_type]: events) {
            cnt += event_type == 1 ? +1 : -1;
            if (cnt > 2) {
                events = backup;
                return false;
            }
        }
        return true;
    }
};

int read_input() {
    cin >> n;
    for (int i: range(n)) {
        int l, e;
        cin >> l >> e;
        pairs.push_back({l, e});
    }
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    MyCalendarTwo solution = MyCalendarTwo();
    for (auto &[l, e]: pairs) {
        auto ans = solution.book(l, e);
        cout << ans << endl;
    }
    // auto ans = solution.assert_yellow("Hello");
    return 0;
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
