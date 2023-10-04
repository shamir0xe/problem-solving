#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem 1912-design-movie-rental-system (1/1)
 * leetcode, problemset
 * author: @shamir0xe
 * verdict: [AC]
 **/

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
#define trace(x) cerr << #x << " : " << x << endl
#define _ << " " <<
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define X first
#define Y second

/**
 * printing tuples
 **/
template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
__tuple_printer(ostream &os, const tuple<T...> &tup){};

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
__tuple_printer(ostream &os, const tuple<T...> &tup) {
    if (n != 0)
        os << " ";
    os << get<n>(tup);
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
ostream &operator<<(std::ostream &os, const std::pair<T, K> &p) {
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
        if (first)
            first = false;
        else
            os << " ";
        os << (*ii);
    }
    os << "]";
    return os;
}

/**
 * range functions
 **/
inline vi range(int idx, int n) {
    if (n <= idx)
        return vi();
    vi indices(n - idx);
    for (int i = idx; i < n; ++i)
        indices[i - idx] = i;
    return indices;
}

inline vi range(int n) { return range(0, n); }

// define variables here
#define MAX_M 15
const int maxn = 100 * 100 + 10;
int n;
int movie_cnt;
vector<set<pii>> movies;
map<int, int> movie_mp;
map<pii, int> prices;
set<tuple<int, int, int>> reports;
vi rmap;

// define functions here
int get_movie(int original_idx) {
    if (movie_mp.find(original_idx) == movie_mp.end()) {
        rmap[movie_cnt] = original_idx;
        movie_mp[original_idx] = movie_cnt++;
    }
    return movie_mp[original_idx];
}

class MovieRentingSystem {
  public:
    MovieRentingSystem(int n, vector<vector<int>> &entries) {
        rmap.resize(maxn);
        movies.assign(maxn, {});
        reports.clear();
        prices.clear();
        movie_mp.clear();
        movie_cnt = 0;
        for (auto &entry: entries) {
            int movie = get_movie(entry[1]);
            int price = entry[2];
            int shop = entry[0];
            movies[movie].insert({price, shop});
            prices[{movie, shop}] = price;
        }
    }

    vector<int> search(int movie) {
        vi ans;
        int cnt = 0;
        for (auto &en: movies[get_movie(movie)]) {
            cnt++;
            if (cnt > 5)
                break;
            ans.push_back(en.Y);
        }
        return ans;
    }

    void rent(int shop, int movie) {
        movie = get_movie(movie);
        movies[movie].erase({prices[{movie, shop}], shop});
        reports.insert({prices[{movie, shop}], shop, rmap[movie]});
    }

    void drop(int shop, int movie) {
        movie = get_movie(movie);
        movies[movie].insert({prices[{movie, shop}], shop});
        reports.erase({prices[{movie, shop}], shop, rmap[movie]});
    }

    vector<vector<int>> report() {
        vvi ans;
        int cnt = 0;
        for (auto &[price, shop, movie]: reports) {
            if (++cnt > 5)
                break;
            ans.push_back(vi{shop, movie});
        }
        return ans;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */
int read_input() {
    cin >> n;
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    MovieRentingSystem solution = MovieRentingSystem();
    auto ans = solution.assert_yellow("Hello");
    return ans;
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << ans << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    bool test_case = false;
    if (test_case) {
        int t;
        cin >> t;
        while (t--) {
            second_main();
        }
    } else {
        second_main();
    }
    return 0;
}
