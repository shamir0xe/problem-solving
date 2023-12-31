#include <bits/stdc++.h>

/**
 * problem D (4/5)
 * codeforces, codeforces-round-904-div2
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
const int maxn = 1000 * 1000 + 10;
int n;
vvi primes(maxn);
vi arr;

/**
 * define functions here
 **/

void sieve() {
    std::vector<char> bl(maxn, 1);
    for (int i: range(2, maxn)) {
        if (bl[i]) {
            for (int j = i; j < maxn; j += i) {
                primes[j].push_back(i);
                bl[j] = 0;
            }
        }
    }
}

int read_input() {
    std::cin >> n;
    arr = Reader::vector<int>(n);
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    std::vector<ll> dp(n + 1, 0);
    vi counts(n + 1, 0);
    for (int i: range(n)) {
        counts[arr[i]]++;
    }
    for (int i: rrange(1, n + 1)) {
        ll &res = dp[i];
        int cur = i;
        while (cur <= n) {
            res += counts[cur];
            cur += i;
        }
        res = res * (res - 1) / 2;
        cur = i + i;
        while (cur <= n) {
            res -= dp[cur];
            cur += i;
        }
    }
    std::vector<char> bl(n + 1, 1);
    for (int i: range(1, n + 1)) {
        if (counts[i] > 0) {
            int cur = i;
            while (cur <= n) {
                bl[cur] = 0;
                cur += i;
            }
        }
    }
    ll ans = 1ll * n * (n - 1) / 2;
    for (int i: range(1, n + 1)) {
        if (bl[i] == 0) {
            // trace(i _ dp[i]);
            ans -= dp[i];
        }
    }
    return ans;
}

int second_main() {
    read_input();
    auto ans = solve();
    std::cout << ans << std::endl;
    return 0;
}

int main() {
    Reader::sync();
    bool test_case = true;
    sieve();
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
