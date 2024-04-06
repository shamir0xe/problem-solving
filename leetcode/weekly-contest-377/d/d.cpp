#include <algorithm>
#include <bits/stdc++.h>
#include <limits>
#include <random>
#include <unordered_map>

/**
 * problem D (4/4)
 * leetcode, weekly-contest-377
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
#define trace(x) std::cout << #x << " : " << x << std::endl
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
inline void smin(
    T &a, T b, const K callable = []() {}) {
    if (a > b) {
        a = b;
        callable();
    }
}

template <typename T, typename K = std::function<void(void)>>
inline void smax(
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

template <typename T> class Mapping {
  private:
    T hash_prime;

  public:
    std::vector<T> mappings;
    std::vector<T> pows;
    Mapping(){};
    Mapping(int n, T prime) {
        this->mappings.resize(n);
        this->hash_prime = prime;
        auto rd = std::random_device();
        auto gen = std::mt19937(rd());
        auto distribution =
            std::uniform_int_distribution<T>(0, std::numeric_limits<T>::max());
        std::for_each(all(this->mappings),
                      [&](T &number) { number = distribution(gen); });
    }

    inline T get(char ch) { return mappings[ch - 'a']; }

    T hash(std::string &str) {
        T res = 0;
        for (char ch: str) {
            res = res * hash_prime + get(ch);
        }
        return res;
    }

    T get_prime() { return hash_prime; }

    void create_powers(int n) {
        pows.resize(n);
        pows[0] = hash_prime;
        for (int i: range(1, n)) {
            pows[i] = pows[i - 1] * pows[i - 1];
        }
    }
};

template <typename T> class Table {
  private:
    Mapping<T> mapping;
    std::vector<std::vector<T>> table;

  public:
    Table(Mapping<T> &mapping) { this->mapping = mapping; }
    void create_table(std::string &str) {
        int n = sz(str);
        T prime = mapping.get_prime();
        table.assign(n, std::vector<T>(n));
        for (int i: range(n)) {
            table[i][0] = mapping.mappings[str[i] - 'a'];
        }
        for (int i: range(n)) {
            for (int length: range(2, n + 1)) {
                if (i + length > n) {
                    break;
                }
                table[i][length - 1] =
                    table[i][length - 2] * prime +
                    mapping.mappings[str[i + length - 1] - 'a'];
            }
        }
    }
    T get_hash(int i, int length) { return table[i][length - 1]; }
};

template <typename T> class HashTable {
  private:
    Mapping<T> mapping;
    std::vector<std::vector<T>> table;

  public:
    HashTable(Mapping<T> &mapping) { this->mapping = mapping; }

    void create_table(std::string &str) {
        int n = sz(str);
        int m = std::__lg(n) + 1;
        table.assign(n, std::vector<T>(m, 0));
        for (int i: range(n)) {
            table[i][0] = mapping.mappings[str[i] - 'a'];
        }
        for (int j: range(1, m)) {
            for (int i: rrange(n)) {
                if (i + (1 << j) <= n) {
                    table[i][j] = table[i][j - 1] * mapping.pows[j - 1] +
                                  table[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    T get_hash(int i, int length) {
        T res = 0;
        while (length) {
            int bit = std::__lg(length);
            res = res * mapping.pows[bit] + table[i][bit];
            i += 1 << bit;
            length ^= 1 << bit;
        }
        return res;
    }
};

template <typename T> class Trie {
    class TrieNode {
        int id;
        std::unordered_map<T, TrieNode *> children;

      public:
        TrieNode() {}
        void clear() {
            this->id = -1;
            this->children.clear();
        }
        bool has(T ch) { return children.count(ch); }
        void add(TrieNode *node, T ch) {
            node->clear();
            children[ch] = node;
        }
        TrieNode *next(T ch) { return children[ch]; }
        void set_id(int id) { this->id = id; }
        int get_id() { return id; }
    };
    std::vector<TrieNode> nodes;
    TrieNode *root;
    int node_cnt;
    int strings;

  public:
    Trie(int n) {
        node_cnt = strings = 0;
        nodes.resize(n);
        root = &nodes[node_cnt++];
    }

    void clear() {
        // for (int i: range(node_cnt)) {
        //     nodes[i].clear();
        // }
        root->clear();
        node_cnt = 1;
        strings = 0;
    }

    int strings_count() { return strings; }

    // template <typename InputIterator>
    // void add(InputIterator begin, InputIterator end) {
    //     TrieNode *node = root;
    //     // auto itr = begin;
    //     while (begin != end) {
    //         T cur = *begin;
    //         if (!node->has(cur)) {
    //             node->add(&nodes[node_cnt++], cur);
    //         }
    //         node = node->next(cur);
    //         begin++;
    //     }
    //     if (node->get_id() < 0) {
    //         node->set_id(strings++);
    //     }
    // }

    void add(std::string &str) {
        TrieNode *node = root;
        for (char ch: str) {
            if (!node->has(ch)) {
                node->add(&node[node_cnt++], ch);
            }
            assert(node != nullptr);
            node = node->next(ch);
        }
        if (node->get_id() < 0) {
            node->set_id(strings++);
        }
    }

    int get_id(std::string &str) {
        TrieNode *node = root;
        for (char ch: str) {
            if (!node->has(ch)) {
                return -1;
            }
            node = node->next(ch);
        }
        return node->get_id();
    }

    // template <typename InputIterator>
    // int get_id(InputIterator begin, InputIterator end) {
    //     TrieNode *node = root;
    //     // auto itr = begin;
    //     while (begin != end) {
    //         T cur = *begin;
    //         if (!node->has(cur)) {
    //             return -1;
    //         }
    //         node = node->next(cur);
    //         begin++;
    //     }
    //     return node->get_id();
    // }

    TrieNode *traverse(TrieNode *node, T cur) {
        if (node->has(cur)) {
            return node->next(cur);
        }
        return nullptr;
    }

    TrieNode *get_root() { return root; }
};

/**
 * define variables here
 **/
const int maxn = 1000 * 100 + 5;
int n;
Trie<char> trie(26 << 10);

/**
 * define functions here
 **/

class Solution {
  public:
    long long minimumCost(std::string source, std::string target,
                          std::vector<std::string> &original,
                          std::vector<std::string> &changed,
                          std::vector<int> &cost) {
        trie.clear();
        int n = sz(source);
        for (auto str: original) {
            trie.add(str);
        }
        for (auto str: changed) {
            trie.add(str);
        }
        int m = trie.strings_count();
        trace(n _ m);
        ll MAX = 1e18;
        vvl dist(m, vl(m, MAX));
        for (int i: range(m)) {
            dist[i][i] = 0;
        }
        for (int i: range(sz(original))) {
            int idx_s = trie.get_id(original[i]);
            int idx_e = trie.get_id(changed[i]);
            trace(idx_s _ idx_e);
            smin(dist[idx_s][idx_e], (ll)cost[i]);
        }
        trace("herll");
        for (int k: range(m)) {
            for (int i: range(m)) {
                if (dist[i][k] < MAX) {
                    for (int j: range(m)) {
                        if (dist[k][j] < MAX) {
                            smin(dist[i][j], dist[i][k] + dist[k][j]);
                        }
                    }
                }
            }
        }
        vl dp(n + 1, MAX);
        dp[n] = 0;
        for (int i: rrange(n)) {
            ll &res = dp[i];
            if (source[i] == target[i]) {
                smin(res, dp[i + 1]);
            }
            auto *source_node = trie.get_root();
            auto *target_node = trie.get_root();
            for (int j: range(1, n + 1)) {
                if (i + j > n) {
                    break;
                }
                source_node = trie.traverse(source_node, source[i + j - 1]);
                target_node = trie.traverse(target_node, target[i + j - 1]);
                if (source_node == nullptr || target_node == nullptr) {
                    break;
                }
                int id_s = source_node->get_id();
                int id_t = target_node->get_id();
                if (id_s >= 0 && id_t >= 0) {
                    smin(res, dist[id_s][id_t] + dp[i + j]);
                }
            }
        }
        if (dp[0] < MAX) {
            return dp[0];
        }
        return -1ll;
    }
};

int read_input() {
    std::cin >> n;
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.assert_yellow("Hello");
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
