#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>

/**
 * problem D (4/6)
 * codeforces, codeforces-round-914-div2
 * author: @shamir0xe
 * generated by contest-builder
 * https://github.com/shamir0xe/contest-builder
 **/

typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<long long> vl;
typedef std::vector<std::vector<int>> vvi;
typedef std::vector<std::vector<ll>> vvl;
#define trace(x) std::cerr << #x << " : " << x << std::endl
#define _ << " " <<
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define X first
#define Y second

/**
 * printing tuples
 **/
template <size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
__tuple_printer(std::ostream &os, const std::tuple<T...> &tup){};

template <size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
__tuple_printer(std::ostream &os, const std::tuple<T...> &tup) {
    if (n != 0) {
        os << " ";
    }
    os << std::get<n>(tup);
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
std::ostream &operator<<(std::ostream &os, const std::pair<T, K> &p) {
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
        if (first) {
            first = false;
        } else {
            os << " ";
        }
        os << (*ii);
    }
    os << "]";
    return os;
}

template <typename T, typename K = std::function<void(void)>>
void smin(
    T &a, T b, const K callable = []() {}) {
    if (a > b) {
        a = b;
        callable();
    }
}

template <typename T, typename K = std::function<void(void)>>
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
    if (n <= idx) {
        return vi();
    }
    vi indices(n - idx);
    for (int i = idx; i < n; ++i) {
        indices[i - idx] = i;
    }
    return indices;
}

inline vi range(int n) { return range(0, n); }

inline vi rrange(int idx, int n) {
    vi order = range(idx, n);
    reverse(all(order));
    return order;
}

inline vi rrange(int n) { return rrange(0, n); }

class Reader {
  public:
    template <typename T> inline static T primitive() {
        T temp;
        std::cin >> temp;
        return temp;
    }

    template <typename T> static std::vector<T> vector(int n) {
        std::vector<T> res(n);
        for (int &i: range(n)) {
            res[i] = Reader::primitive<T>();
        }
        return res;
    }

    static void sync() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
};

/**
 * define variables here
 **/
const int maxn = 1000 * 100 + 5;
int n;

/**
 * define functions here
 **/

auto solve() {
    /**
     * main logic goes here
     **/
    // max(bef[i], i) <= b[i] || max(i, nex[i]) <= b[i]
    std::cin >> n;
    vi a = Reader::vector<int>(n);
    vi b = Reader::vector<int>(n);
    std::map<int, vi> mp;
    for (int i: range(n)) {
        mp[a[i]].push_back(i);
    }
    int m = std::__lg(n) + 2;
    vvi max_arr(n, vi(m));
    vvi min_arr(n, vi(m));
    for (int i: range(n)) {
        max_arr[i][0] = a[i];
        min_arr[i][0] = b[i];
    }
    for (int j: range(1, m)) {
        for (int i: range(n)) {
            if (i + (1 << j) <= n) {
                max_arr[i][j] = std::max(max_arr[i][j - 1],
                                         max_arr[i + (1 << (j - 1))][j - 1]);
                min_arr[i][j] = std::min(min_arr[i][j - 1],
                                         min_arr[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    auto get_highest = [&](int i, int j) {
        int length = j - i + 1;
        int res = 0;
        while (length) {
            int t = std::__lg(length);
            smax(res, max_arr[i][t]);
            i += (1 << t);
            length ^= 1 << t;
        }
        return res;
    };

    auto get_lowest = [&](int i, int j) {
        int length = j - i + 1;
        int res = 1e9;
        while (length) {
            int t = std::__lg(length);
            smin(res, max_arr[i][t]);
            i += (1 << t);
            length ^= 1 << t;
        }
        return res;
    };

    for (int i: range(n)) {
        vi &indices = mp[b[i]];
        int idx = std::lower_bound(all(indices), i) - indices.begin();
        if (idx < sz(indices)) {
            int high = get_highest(i, indices[idx]);
            int low = get_lowest(i, indices[idx]);
            if (high <= b[i] && low >= b[i]) {
                continue;
            }
        }
        if (idx - 1 >= 0) {
            int high = get_highest(indices[idx - 1], i);
            int low = get_lowest(indices[idx - 1], i);
            if (high <= b[i] && low >= b[i]) {
                continue;
            }
        }
        return false;
    }
    return true;
}

int second_main() {
    auto ans = solve();
    // for (int i: range(sz(ans))) {
    //     std::cout << ans[i] << " \n"[i == sz(ans) - 1];
    // }
    std::cout << (ans ? "YES" : "NO") << std::endl;
    return 0;
}

int main() {
    Reader::sync();
    bool test_case = true;
    if (test_case) {
        int t;
        std::cin >> t;
        while (t--) {
            second_main();
        }
    } else {
        second_main();
    }
    return 0;
}