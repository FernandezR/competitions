// alternatively, use __gcd from <algorithm>
int gcd(int a, int b)
{
	while(b)
	{
		int t = a % b;
		a = b;
		b = t;
	}
	return a;
}

void extended_euclidean(int a, int b, int & lx, int & ly)
{
	int x = 0, y = 1;
	lx = 1, ly = 0;
	while(b)
	{
		int t = a % b, q = a / b;
		a = b; b = t;
		t = x; x = lx - q * x; lx = t;
		t = y; y = ly - q * y; ly = t;
	}
}

// modulo inverse using the extended Euclidean algorithm
int mod_inv(int a, int m)
{
	int lx, ly;
	extended_euclidean(a, m, lx, ly);
	if(lx < 0) lx += m;
	return lx;
}

ll mod_pow(ll a, ll b)
{
	if(!b) return 1;
	return M(mod_pow(M(a * a), b / 2) * (b % 2 ? a : 1));
}

// modulo inverse using exponentiation
ll mod_inv(int a)
{
	return mod_pow(a, MOD - 2);
}

vll get_factors(ll n)
{
	vll ans;
	ll f = 1;
	for(; f * f < n; f++) if(!(n % f)) ans.push_back(f), ans.push_back(n / f);
	if(f * f == n) ans.push_back(f);
	sort(all(ans));
	return ans;
}

vector<pair<ll, int>> factorise(ll n)
{
	vector<pair<ll, int>> ans;
	for(ll f = 2; f * f <= n; f++) if(!(n % f))
	{
		int p = 0;
		while(!(n % f)) n /= f, p++;
		ans.push_back({f, p});
	}
	if(n > 1) ans.push_back({n, 1});
	return ans;
}

// A modified sieve of Eratosthenes which generates, the smallest prime factor
// of each integer in [0, ..., n - 1]. This lookup allows us to factorise x
// in O(f), where f is the number of factors of x.
vi smallest_factor(int n)
{
	vi ans(n);
	rep(i, n) ans[i] = i;
	for(int p = 2; p * p < n; p++) if(ans[p] == p)
	for(int q = p * p; q < n; q += p)
		ans[q] = p;
	return ans;
}
