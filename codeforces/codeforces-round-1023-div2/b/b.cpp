#include <algorithm>
#include <bits/stdc++.h>

/**
 * problem B (2/6)
 * codeforces, codeforces-round-1023-div2
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
#define range(i, n) for (int i = 0; i < n; ++i)
#define rrange(i, n) for (int i = n - 1; i >= 0; --i)
#define fr(i, a, n) for (int i = a; i < n; ++i)
#define rfr(i, a, n) for (int i = n - 1; i >= a; --i)
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
__tuple_printer(std::ostream &os, const std::tuple<T...> &tup) {};

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
void smin(T &a, T b, const K callable = []() {}) {
    if (a > b) {
        a = b;
        callable();
    }
}

template <typename T, typename K = std::function<void(void)>>
void smax(T &a, T b, const K callable = []() {}) {
    if (a < b) {
        a = b;
        callable();
    }
}

/**
 * Reader class
 **/
class Reader {
  public:
    template <typename T> inline static T primitive() {
        T temp;
        std::cin >> temp;
        return temp;
    }

    template <typename T> static std::vector<T> vector(int n) {
        std::vector<T> res(n);
        range(i, n) { res[i] = Reader::primitive<T>(); }
        return res;
    }

    template <typename T, size_t n> static std::array<T, n> array() {
        std::array<T, n> res;
        range(i, n) { res[i] = Reader::primitive<T>(); }
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
    int k;
    std::cin >> n >> k;
    vi arr = Reader::vector<int>(n);
    int max = *std::max_element(all(arr));
    int cnt = 0;
    range(i, n) {
        if (arr[i] == max)
            cnt++;
    }
    int min = *std::min_element(all(arr));
    if (cnt > 1 && max - min > k || cnt == 1 && max - min - 1 > k)
        return 2;
    int parity = 0;
    range(i, n) { parity = (parity + arr[i]) % 2; }
    if (parity == 0)
        return 2;
    return 1;
}

int second_main() {
    auto ans = solve();
    if (ans == 1)
        std::cout << "Tom\n";
    else
        std::cout << "Jerry\n";
    // for (int i: range(sz(ans))) {
    //     std::cout << ans[i] << " \n"[i == sz(ans) - 1];
    // }
    // std::cout << ans << std::endl;
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
