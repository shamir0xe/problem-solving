#include <algorithm>
#include <bits/stdc++.h>
#include <functional>

/**
 * problem C (3/4)
 * leetcode, weekly-contest-440
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

    static void sync() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
};

template <typename K> class Node {
  public:
    std::pair<int, int> idx_range;
    K aggr_value;
    Node<K> *le, *ri;
    int aggr_idx;

    bool is_leaf() {
        return this->idx_range.first == this->idx_range.second - 1;
    }

    Node(int idx, K aggr_value) {
        this->idx_range = {idx, idx + 1};
        this->aggr_idx = idx;
        this->aggr_value = aggr_value;
        this->le = NULL;
        this->ri = NULL;
    }

    Node(std::pair<int, int> idx_range, K aggr_value) {
        this->idx_range = idx_range;
        this->aggr_idx = idx_range.first;
        this->aggr_value = aggr_value;
        this->le = NULL;
        this->ri = NULL;
    }
};

template <typename T> class SegmentTree {
  public:
    SegmentTree(std::vector<T> &nodes, std::function<T(T, T)> aggr_fn,
                T identity)
        : identity(identity), aggr_fn(aggr_fn) {
        this->root = this->initialize(nodes, 0, sz(nodes));
    };

    std::pair<T, int> aggr_range(int le, int ri) {
        // returns (aggregate_range, index) if feasible
        return this->range_query(this->root, le, ri);
    }

    int remove(int idx) { return this->remove(this->root, idx); }

  private:
    std::vector<Node<T> *> nodes;
    Node<T> *root;
    std::function<T(T, T)> aggr_fn;
    T identity;

    int remove(Node<T> *node, int idx) {
        // trace("removing" _ idx _ node->idx_range);
        if (node == NULL || idx < node->idx_range.first ||
            node->idx_range.second <= idx) {
            return -1;
        }
        if (node->is_leaf()) {
            // leaf
            // trace(node->idx_range _ "cleansed");
            node->aggr_value = this->identity;
            node->aggr_idx = -1;
            return idx;
        }
        // not leaf
        int res =
            std::max(this->remove(node->le, idx), this->remove(node->ri, idx));
        this->update(node);
        return res;
    }

    void update(Node<T> *node) {
        if (node->is_leaf()) {
            return;
        }
        T aggr_le = node->le != NULL ? node->le->aggr_value : this->identity;
        T aggr_ri = node->ri != NULL ? node->ri->aggr_value : this->identity;
        node->aggr_value = this->aggr_fn(aggr_le, aggr_ri);
        node->aggr_idx = -1;
        if (node->aggr_value == aggr_ri) {
            if (node->ri != NULL) {
                node->aggr_idx = node->ri->aggr_idx;
            }
        } else {
            if (node->le != NULL) {
                node->aggr_idx = node->le->aggr_idx;
            }
        }
    }

    std::pair<T, int> range_query(Node<T> *node, int le, int ri) {
        if (node == NULL || le >= ri || node->idx_range.first >= ri ||
            node->idx_range.second <= le) {
            return {this->identity, -1};
        }
        if (node->idx_range.first >= le && node->idx_range.second <= ri) {
            return {node->aggr_value, node->aggr_idx};
        }
        int mid = (le + ri) >> 1;
        std::pair<T, int> res_le = range_query(node->le, le, ri);
        std::pair<T, int> res_ri = range_query(node->ri, le, ri);
        T res_aggr = this->aggr_fn(res_le.first, res_ri.first);
        if (res_aggr == res_ri.first) {
            return res_ri;
        }
        return res_le;
    };

    Node<T> *initialize(std::vector<T> &nodes, int le, int ri) {
        if (le >= ri) {
            return NULL;
        }
        if (le == ri - 1) {
            // leaf
            this->nodes.push_back(new Node<T>(le, nodes[le]));
            return this->nodes.back();
        }
        int mid = (le + ri) >> 1;
        Node<T> *node_left = this->initialize(nodes, le, mid);
        Node<T> *node_right = this->initialize(nodes, mid, ri);
        Node<T> *new_node = new Node<T>({le, ri}, this->identity);
        new_node->le = node_left;
        new_node->ri = node_right;
        this->update(new_node);
        this->nodes.push_back(new_node);
        // trace(new_node->idx_range _ new_node->aggr_idx _ new_node->aggr_value);
        return new_node;
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

class Solution {
  public:
    int numOfUnplacedFruits(std::vector<int> &fruits,
                            std::vector<int> &baskets) {
        int res = 0;
        n = sz(baskets);
        // sort(all(fruits));

        // map the values to the ranged sequence numbers
        vi baskets_bak = vi(all(baskets));
        std::map<int, int> mp;
        sort(all(baskets_bak));
        for (int i: range(n)) {
            int basket = baskets_bak[i];
            if (mp.find(basket) != mp.end()) {
                continue;
            }
            mp[basket] = i;
        }

        typedef Node<int> NODE;
        // std::vector<NODE> nodes;
        // for (int i: range(sz(baskets))) {
        //     nodes.push_back(NODE(mp[baskets[i]], i));
        // }
        vi sorted_ids(range(n));
        sort(all(sorted_ids), [&](const int &a, const int &b) {
            // comparator fn
            return baskets[a] < baskets[b];
        });
        // trace(sorted_ids);
        SegmentTree<int> sg = SegmentTree<int>(
            sorted_ids,
            [](const int &a, const int &b) { return std::min(a, b); }, 1e9);
        for (int fruit: fruits) {
            if (mp.lower_bound(fruit) == mp.end()) {
                res++;
                continue;
            }
            int mapped_fruit = mp.lower_bound(fruit)->second;
            pii minimum = sg.aggr_range(mapped_fruit, n);
            // trace(fruit _ mapped_fruit _ mp.rbegin()->second + 1 _ minimum);
            if (minimum.first != 1e9 && minimum.second != -1) {
                // trace("remove" _ minimum.second);
                sg.remove(minimum.second);
            } else {
                res++;
            }
        }
        return res;
    }
};
