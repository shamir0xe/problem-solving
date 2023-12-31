#include <bits/stdc++.h>

/**
 * problem G (7/7)
 * codeforces, codeforces-round-888-div3
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
    int m;
    std::cin >> n >> m;
    vi heights = Reader::vector<int>(n);
    vvi adj(n, vi());
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vi colors(n, 0);
    vvi tree_adj(n, vi());
    const int maxk = std::__lg(n) + 5;
    int cur_color = 1;
    vi group(n, 0);
    for (int i: range(n)) {
        group[i] = i;
    }
    std::function<int(int)> find_par = [&](int u) {
        if (u == group[u]) {
            return u;
        }
        return group[u] = find_par(group[u]);
    };
    auto merge = [&](int u, int v) {
        u = find_par(u);
        v = find_par(v);
        if (u == v) {
            return;
        }
        if (u > v) {
            std::swap(u, v);
        }
        group[v] = u;
    };
    auto mst = [&]() {
        std::priority_queue<std::tuple<int, int, int>,
                            std::vector<std::tuple<int, int, int>>,
                            std::greater<>>
            pq;
        for (int i: range(n)) {
            for (int j: adj[i]) {
                pq.push({std::max(heights[i], heights[j]), i, j});
            }
        }
        while (!pq.empty()) {
            auto [weight, u, v] = pq.top();
            pq.pop();
            if (find_par(u) == find_par(v)) {
                continue;
            }
            tree_adj[v].push_back(u);
            tree_adj[u].push_back(v);
            merge(u, v);
        }
    };
    mst();
    cur_color = 1;
    colors.assign(n, 0);
    vvi papas(n, vi(maxk, -1));
    vi depths(n, 0);
    std::function<void(int, int, int)> dfs = [&](int u, int papa, int depth) {
        colors[u] = cur_color;
        papas[u][0] = papa;
        depths[u] = depth;
        for (int v: tree_adj[u]) {
            if (colors[v] == 0) {
                dfs(v, u, depth + 1);
            }
        }
    };
    for (int u: range(n)) {
        if (colors[u] == 0) {
            dfs(u, u, 0);
            cur_color++;
        }
    }
    vvi max_heights(n, vi(maxk, 0));
    for (int i: range(n)) {
        max_heights[i][0] = heights[i];
    }
    for (int k = 1; k < maxk; k++) {
        for (int u: range(n)) {
            max_heights[u][k] = std::max(max_heights[u][k - 1],
                                         max_heights[papas[u][k - 1]][k - 1]);
            papas[u][k] = papas[papas[u][k - 1]][k - 1];
        }
    }
    int q;
    std::cin >> q;
    std::vector<std::string> results;
    auto ans = [&](int res) { results.push_back(res ? "YES" : "NO"); };
    while (q--) {
        int a, b, c;
        std::cin >> a >> b >> c;
        a--;
        b--;
        if (colors[a] != colors[b]) {
            ans(0);
            continue;
        }
        int aa = a;
        if (depths[a] > depths[b]) {
            std::swap(a, b);
        }
        int max = 0;
        int diff = depths[b] - depths[a];
        while (diff) {
            int k = std::__lg(diff);
            smax(max, max_heights[b][k]);
            b = papas[b][k];
            diff ^= 1 << k;
        }
        if (a == b) {
            smax(max, heights[a]);
        } else {
            for (int k = maxk - 1; k >= 0; k--) {
                if (papas[a][k] != papas[b][k]) {
                    smax(max, max_heights[b][k]);
                    smax(max, max_heights[a][k]);
                    a = papas[a][k];
                    b = papas[b][k];
                }
            }
            if (papas[a][0] != papas[b][0]) {
                while (true) {
                }
            }
            smax(max, heights[papas[a][0]]);
            smax(max, heights[a]);
            smax(max, heights[b]);
        }
        ans(c + heights[aa] >= max);
    }
    return results;
}

int second_main() {
    auto ans = solve();
    char array = true;
    if (array) {
        for (int i: range(sz(ans))) {
            std::cout << ans[i] << "\n";
        }
        std::cout << "\n";
    } else {
        std::cout << ans << std::endl;
    }
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
