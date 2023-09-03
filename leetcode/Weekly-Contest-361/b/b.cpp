#include <bits/stdc++.h>
using namespace std;


/**
 * generated template for competetive programming
 * problem B (2/4)
 * leetcode, Weekly-Contest-361
 * author: @shamir0xe
 * verdict: [AC/WA/TLE/MLE]
**/

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvl;
#define trace(x) cerr << #x << " : " << x << endl
#define _ << " " << 
#define sz(x) ((int) (x).size())
#define X first
#define Y second

vi range(int n) {
	if (n <= 0) return vi();
	vi indices(n);
	for (int i = 0; i < n; ++i) indices[i] = i;
	return indices;
}

// define variables here
#define MAX_N 100005 // 10^5 + 5
int n;


// define functions here
int get_ans_zero(string num) {
	int ans = 0;
	int r = sz(num) - 1;
	while (r >= 0 && num[r] != '0'){ r--; ans ++;}
	int l = r - 1;
	while (l >= 0 && (num[l] != '0' && num[l] != '5')) {l--; ans++;}
	if (r < 0 || l < 0) return -1;
	return ans;
}

int get_ans_five(string num) {
	int ans = 0;
	int r = sz(num) - 1;
	while (r >= 0 && num[r] != '5') {r--; ans++;}
	int l = r - 1;
	while (l >= 0 && (num[l] != '2' && num[l] != '7')) {l--; ans ++;}
	if (r < 0 || l < 0) return -1;
	return ans;
}

int count_zeros(string num) {
	int ans =0;
	for (auto i: range(sz(num))) {
		if (num[i] == '0') ans ++;
	}
	return ans;
}


class Solution {
public:
	string assert_string(string s) {
		return "entered " + s;
	}
	int minimumOperations(string num) {
		int a1 = get_ans_zero(num);
		int a2 = get_ans_five(num);
		trace(a1 _ a2);
		if (a1 == -1 && a2 == -1) return sz(num) - count_zeros(num);
		if (a1 == -1) return a2;
		if (a2 == -1) return a1;
		return min(a1, a2);
    }
};

void read_input() {
	cin >> n;
}

auto solve() {
	/**
	 * main logic goes here
	**/
	Solution solution = Solution();
	auto ans = solution.assert_string("Hello");
	return ans;
}


int second_main() {
	read_input();
	auto ans = solve();
	cout << ans << endl;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	bool test_case = false;
	if (test_case) {
		int t; cin >> t;
		while (t--) {
			second_main();
		}
	} else {
		second_main();
	}
	return 0;
}

