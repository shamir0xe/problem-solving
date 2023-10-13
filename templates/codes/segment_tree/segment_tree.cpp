#include <bits/stdc++.h>
using namespace std;

template <class S, auto op, auto e, auto collect> class Node {
  public:
    S value, lazy_v;
    bool lazy = false;
    Node *le = nullptr, *ri = nullptr;
    pair<int, int> interval = {-1, -1};
    Node(pair<int, int> interval)
        : interval(interval), value(e()), lazy_v(e()) {}

    inline bool within(int lele, int riri) {
        return lele <= interval.first && interval.second <= riri;
    }
    inline bool contains(int idx) {
        return interval.first <= idx && idx <= interval.second;
    }
    inline bool leaf() { return interval.first == interval.second; }
    void relax() {
        value = op(value, lazy_v);
        lazy_v = e();
        lazy = false;
    }
    void propagate() {
        if (lazy) {
            if (!leaf()) {
                ri->lazy_v = op(lazy_v, ri->lazy_v);
                le->lazy_v = op(lazy_v, le->lazy_v);
                ri->lazy = le->lazy = true;
            }
            relax();
        }
    }
    S get_value() {
        propagate();
        return value;
    }
    template <class _S, auto _op, auto _e, auto _collect>
    friend ostream &operator<<(ostream &os,
                               const Node<_S, _op, _e, _collect> &node);
};

template <class S, auto op, auto e, auto collect>
ostream &operator<<(ostream &os, const Node<S, op, e, collect> &node) {
    os << "[(" << node.interval.X << ", " << node.interval.Y
       << ") value: " << node.value << "]";
    return os;
}

template <class S, auto op, auto e, auto collect> class SegTree {
  private:
    typedef Node<S, op, e, collect> SgNode;
    SgNode *root;

    void assign(SgNode *node, vector<S> &v, int le, int ri) {
        if (le == ri) {
            node->value = v[le];
            return;
        }
        int mid = (le + ri) >> 1;
        node->le = new SgNode({le, mid});
        node->ri = new SgNode({mid + 1, ri});
        assign(node->le, v, le, (le + ri) >> 1);
        assign(node->ri, v, ((le + ri) >> 1) + 1, ri);
        node->value = collect(node->ri->value, node->le->value);
    }

    void update_interval(SgNode *node, S x, int le, int ri) {
        if (node->within(le, ri)) {
            node->lazy_v = op(node->lazy_v, x);
            node->lazy = true;
            return;
        }
        if (node->interval.first > ri)
            return;
        if (node->interval.second < le)
            return;
        update_interval(node->le, x, le, ri);
        update_interval(node->ri, x, le, ri);
    }

    S get_node(SgNode *node, int idx) {
        node->propagate();
        if (node->leaf())
            return node->get_value();
        if (node->le->contains(idx))
            return get_node(node->le, idx);
        return get_node(node->ri, idx);
    }

    S get_interval(SgNode *node, int le, int ri) {
        if (le > ri)
            return e();
        if (node->within(le, ri)) {
            return collect(node->get_value(), e());
        }
        if (ri < node->interval.first)
            return e();
        if (le > node->interval.second)
            return e();
        node->propagate();
        return collect(get_interval(node->le, le, ri),
                       get_interval(node->ri, le, ri));
    }

    void set_node(SgNode *node, int idx, S x) {
        node->propagate();
        if (node->leaf()) {
            node->value = x;
            return;
        }
        if (node->le->contains(idx))
            set_node(node->le, idx, x);
        else
            set_node(node->ri, idx, x);
        node->value = collect(node->le->get_value(), node->ri->get_value());
    }

  public:
    SegTree(vector<S> v) {
        root = new SgNode({0, (int)v.size() - 1});
        assign(root, v, 0, (int)v.size() - 1);
    }

    S get(int idx) { return get_node(root, idx); }

    void set(int idx, S x) { set_node(root, idx, x); }

    S get_interval(int le, int ri) { return get_interval(root, le, ri); }

    void update(S x, int le, int ri) { update_interval(root, x, le, ri); }
};

// usage:
//

int sum_26(int a, int b) { return (a + b) % ('z' - 'a' + 1); }

int max_(int a, int b) {
    if (a < b)
        return b;
    return a;
}

int sum_(int a, int b) { return a + b; }

int e_0() { return 0; }

SegTree<int, sum_26, e_0, max_> sg(vector<int>(100000));
