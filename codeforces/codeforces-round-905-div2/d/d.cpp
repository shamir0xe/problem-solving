#include <bits/stdc++.h>

/**
 * problem D (4/6)
 * codeforces, codeforces-round-905-div2
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

    template <typename T> static std::vector<T> vector(int length) {
        std::vector<T> res(length);
        for (int &i: range(length)) {
            res[i] = Reader::primitive<T>();
        }
        return res;
    }

    static void sync() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(0);
    }
};

// define variables here
#define MAX_M 15
int n, m;
vi arr, brr;

// define functions here

int read_input() {
    std::cin >> n >> m;
    arr = Reader::vector<int>(n - 1);
    brr = Reader::vector<int>(n);
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    sort(all(arr));
    sort(all(brr));
    vi best_idx(n + 1, n);
    vi dp(n + 1, 0);
    vi dpn(n + 1, 0);
    best_idx[0] = 0;
    for (int i: range(n - 1)) {
        int &res = best_idx[i];
        if (i - 1 >= 0) {
            smin(res, best_idx[i - 1] + 1);
        }
        while (res < n && arr[i] >= brr[res]) {
            res++;
        }
    }
    for (int i: rrange(n - 1)) {
        int &res = dp[i];
        if (best_idx[i] < n) {
            res = dp[i + 1] + 1;
        }
    }
    for (int i: rrange(n - 1)) {
        int &res = dpn[i];
        int idxn = best_idx[i] + 1;
        if (idxn < n) {
            if (idxn < best_idx[i + 1]) {
                res = dp[i];
            } else {
                res = dpn[i + 1] + 1;
            }
        }
    }
    ll ans = 0;
    int i = 0;
    int j = 0;
    int cur_value = 1;
    while (i < n - 1 && cur_value <= m) {
        while (i < n - 1 && arr[i] <= cur_value) {
            ++i;
        }
        if (i - 1 >= 0) {
            smax(j, best_idx[i - 1] + 1);
        }
        int ri = m + 1;
        int decision = 0;
        if (j < n) {
            smin(ri, brr[j], [&]() { decision = 1; });
        }
        if (i < n - 1) {
            smin(ri, arr[i], [&]() { decision = 2; });
        }
        smin(ri, m + 1, [&]() { decision = 0; });
        if (i < n && j < n) {
            if (j == best_idx[i]) {
                ans += 1ll * (ri - cur_value) * (n - (dpn[i] + i + 1));
            } else {
                ans += 1ll * (ri - cur_value) * (n - (dp[i] + i + 1));
            }
        } else {
            ans += 1ll * (ri - cur_value) * (n - dp[0]);
        }
        if (decision == 1) {
            j++;
        }
        cur_value = ri;
    }
    trace(ans);
    if (cur_value <= m) {
        bool reach = false;
        while (j < n && !reach) {
            int ri = brr[j];
            smin(ri, m + 1, [&]() { reach = true; });
            ans += 1ll * (ri - cur_value) * (n - dp[0] - 1);
            cur_value = ri;
            ++j;
        }
        if (!reach) {
            ans += 1ll * (m - cur_value + 1) * std::max(n - dp[0], 1);
        }
    }
    return ans;
}

int second_main() {
    read_input();
    auto ans = solve();
    // Writer::vector<int>(ans);
    std::cout << ans << std::endl;
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
