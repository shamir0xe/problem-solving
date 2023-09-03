#include <bits/stdc++.h>
using namespace std;


/**
 * generated template for competetive programming
 * problem A (1/4)
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
//
string turn_to_str(int n) {
	string ans = "";
	while (n) {
		ans += char('0' + n % 10);
		n /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

bool check_symetric(int n) {
	string s = turn_to_str(n);
	if (sz(s) % 2 == 1) return false;
	string rev_s = s;
	reverse(s.begin(), s.end());
	int a = 0;
	int b = 0;
	for (int i = 0; i < sz(s) / 2; ++i) {
		a += s[i] - '0';
		b += rev_s[i] - '0';
	}
	return a == b;
}

class Solution {
public:
	string assert_string(string s) {
		return "entered " + s;
	}
	int countSymmetricIntegers(int low, int high) {
		int ans = 0;
		for (int i = low; i <= high; ++i) {
			if (check_symetric(i)) {
				ans ++;
				trace(i);
			}
		}
		return ans;
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

