#include <bits/stdc++.h>

/**
 * problem D (4/6)
 * codeforces, codeforces-round-906-div2
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
int n, c;
vl arr;

/**
 * define functions here
 **/
int read_input() {
    std::cin >> n >> c;
    arr = Reader::vector<ll>(n);
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    vi order = range(n);
    sort(order.begin(), order.end(), [&](const int &i, const int &j) {
        int t1 = arr[order[i]] * 1ll * (j + 1);
        int t2 = arr[order[j]] * 1ll * (i + 1);
        if (t1 != t2)
            return t1 > t2;
        // if (arr[order[i]] != arr[order[j]])
        //     return arr[order[i]] > arr[order[j]];
        return j < i;
    });
    ll sum = arr[order[0]];
    int min = order[0] + 1;
    vi leftover;
    for (int i: range(1, n)) {
        // trace(sum _ order[i]+1 _ arr[order[i]] _ 1ll * (order[i] + 1) * c);
        if (sum + arr[order[i]] >= 1ll * min * (order[i] + 1) * c) {
            sum += arr[order[i]];
            min = std::min(min, order[i] + 1);
        } else {
            leftover.push_back(i);
        }
    }
    std::reverse(all(leftover));
    for (int i: leftover) {
        if (sum + arr[order[i]] >= 1ll * min * (order[i] + 1) * c) {
            sum += arr[order[i]];
            min = std::min(min, order[i] + 1);
        } else {
            return false;
        }
    }
    return true;
}

int second_main() {
    read_input();
    auto ans = solve();
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
