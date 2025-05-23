#include <bits/stdc++.h>

/**
 * problem b-leha-and-another-game-about-graph (1/1)
 * codeforces, problemset
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

    template <typename T, size_t n> static std::array<T, n> array() {
        std::array<T, n> res;
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
vi scores;
vi ones;
vi colors;
vi degrees, par_edges;
std::vector<pii> edges;
vvi adj;

/**
 * define functions here
 **/
void dfs(int u, int par_edge) {
    par_edges[u] = par_edge;
    colors[u] = 1;
    for (int edge: adj[u]) {
        int v = edges[edge].first;
        if (v == u) {
            v = edges[edge].second;
        }
        if (colors[v] == 0) {
            degrees[u]++;
            degrees[v]++;
            dfs(v, edge);
        }
    }
}

auto solve() {
    /**
     * main logic goes here
     **/
    int m;
    std::cin >> n >> m;
    scores = vi(n);
    ones = vi();
    edges = std::vector<pii>();
    adj = vvi(n, vi());

    for (int i: range(n)) {
        scores[i] = Reader::primitive<int>();
        if (scores[i] == 1) {
            ones.push_back(i);
        }
    }
    for (int i: range(m)) {
        auto [u, v] = Reader::array<int, 2>();
        u--, v--;
        edges.emplace_back(u, v);
        adj[u].push_back(i);
        adj[v].push_back(i);
    }
    if (sz(ones) % 2 == 1) {
        trace(ones);
        bool can = false;
        for (int i: range(n)) {
            if (!can) {
                if (scores[i] == -1) {
                    scores[i] = 1;
                    can = true;
                    break;
                }
            }
        }
        if (!can) {
            return vi{-1};
        }
    }
    for (int i: range(n)) {
        scores[i] = scores[i] == -1 ? 0 : scores[i];
    }
    colors = vi(n, 0);
    degrees = vi(n, 0);
    par_edges = vi(n, 0);
    dfs(0, -1);

    std::queue<int> q;
    vi ans;
    for (int u: range(1, n)) {
        if (degrees[u] == 1) {
            q.push(u);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // trace(u _ scores[u] _ degrees[u] _ par_edges[u]);

        int edge = par_edges[u];
        if (edge == -1) {
            continue;
        }

        int v = edges[edge].first;
        if (v == u) {
            v = edges[edge].second;
        }
        degrees[v]--;
        if (degrees[v] == 1) {
            q.push(v);
        }

        if (scores[u] == 0) {
            continue;
        }
        // scores[u] = 1

        ans.push_back(edge);

        scores[u] = 0;
        scores[v] ^= 1;
    }
    return ans;
}

int second_main() {
    auto ans = solve();
    if (sz(ans) > 0 && ans[0] == -1) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << sz(ans) << std::endl;
        for (int i: range(sz(ans))) {
            std::cout << ans[i] + 1 << "\n";
        }
    }
    return 0;
}

int main() {
    Reader::sync();
    bool test_case = false;
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
