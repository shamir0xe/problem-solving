#include <bits/stdc++.h>
using namespace std;


/**
 * generated template for competetive programming
 * problem {} ({}/{})
 * {}, {}
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

void read_input() {
	cin >> n;
}

auto solve() {
	/**
	 * main logic goes here
	**/
	auto ans = true;
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

