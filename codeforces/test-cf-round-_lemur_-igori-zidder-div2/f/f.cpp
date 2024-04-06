#include <bits/stdc++.h>

/**
 * problem F (6/6)
 * codeforces, test-cf-round-_lemur_-igori-zidder-div2
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
    int d;
    std::cin >> n >> d;
    vi w = Reader::vector<int>(n);
    sort(all(w));
    std::vector<std::pair<int, double>> dp(d + 1);
    vi par(d + 1, -1);

    dp[0] = {1, -1. * d / 2};
    for (int i: range(n)) {
        auto alter = dp;
        for (int j: range(d + 1)) {
            if (dp[j].first && j + w[i] <= d) {
                smax(alter[j + w[i]],
                     {1, -std::min(-dp[j].second,
                                   std::min(std::abs(j - 1. * d / 2),
                                            std::abs(j + w[i] - 1. * d / 2)))},
                     [&]() { par[j + w[i]] = i; });
            }
        }
        dp = alter;
    }
    if (dp[d].first == 0) {
        return false;
    }
    // trace(dp);
    vi indices;
    int dd = d;
    while (dd) {
        int x = par[dd];
        indices.push_back(x);
        dd -= w[x];
        // trace(dd _ x _ w[x]);
    }
    sort(all(indices), [&](int i, int j) { return w[i] > w[j]; });
    int m = sz(indices);

    vi dp2(d + 1, 0);
    dp2[0] = 1;
    for (int i: indices) {
        vi alter = dp2;
        for (int j: range(d + 1)) {
            if (dp2[j] && w[i] + j <= d) {
                smax(alter[w[i] + j], 1);
            }
        }
        dp2 = alter;
    }
    int min = d;
    for (int j: range(d + 1)) {
        if (dp2[(d + 1) / 2 - j]) {
            int temp = (d + 1) / 2 - j;
            min = std::min(temp, d - temp);
            break;
        }
    }
    vi not_chosen(n, 1);
    for (int i: indices) {
        not_chosen[i] = 0;
    }
    // trace(indices);
    // trace(min);
    for (int i: range(n)) {
        if (not_chosen[i]) {
            if (w[i] > min) {
                // trace(i+1 _ w[i] _ min);
                return false;
            }
        }
    }
    return true;
}

int second_main() {
    auto ans = solve();
    // for (int i: range(sz(ans))) {
    //     std::cout << ans[i] << " \n"[i == sz(ans) - 1];
    // }
    std::cout << (ans ? "Yes" : "No") << std::endl;
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
