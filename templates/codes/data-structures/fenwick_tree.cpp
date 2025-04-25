#include <bits/stdc++.h>

/**
 * Fenwick Tree Implementation
 * author: @shamir0xe
 *
 * inspired by atcoder library
 **/

template <class T> class FenwickTree {
  public:
    FenwickTree(int n) : n(n), tree(n, 0) {}
    void update(int p, T value) {
        assert(0 <= p && p < n);
        p++;
        while (p <= n) {
            tree[p - 1] += value;
            p += p & -p;
        }
    }

    T sum(int le, int ri) {
        assert(0 <= le && le <= ri && ri <= n);
        return sum(ri) - sum(le);
    }

  private:
    int n;
    std::vector<T> tree;
    T sum(int p) {
        T res = 0;
        while (p > 0) {
            res += tree[p - 1];
            p -= p & -p;
        }
        return res;
    }
};
