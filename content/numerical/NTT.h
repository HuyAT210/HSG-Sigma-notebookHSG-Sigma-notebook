/**
 * Author: Zero_OP
 * Description: Just NTT
 * Status: I don't know
 */
 const int N = 4e5 + 10;
 const int V = 1e7 + 10;
 const long long INF = 1e18;
 const long long M = 998244353;
  
  
  
 long long fact[N + 1],ifact[N + 1],n;
  
 long long power(long long a,long long b,long long c){
     if(b == 0){
         return 1;
     }
     long long t = power(a,b >> 1,c);
     t = (t * t) % c;
     if(b & 1){
         return (t * a) % c;
     }
     return t;
 }
 void precompute(){
     fact[0] = 1;
     for(int i = 1;i <= N;++i){
         fact[i] = (fact[i - 1] * i) % M;
     }
     ifact[N] = power(fact[N],M - 2,M);
     for(int i = N - 1;i >= 0;--i){
         ifact[i] = (ifact[i + 1] * (i + 1)) % M;
     }
 }
  
 const int mod = 998244353;
 //const int root = 5;
 //const int root_1 = 4404020;
 //const int root_pw = 1 << 20;
  
 long long  pw(long long  x, long long  k = mod-2, long long  p = mod) {
     long long  r = 1;
     while (k) {
         if (k & 1) r = r * x % p;
         x = x * x % p;
         k >>= 1;
     }
     return r;
 }
 const long long  G = 3, GIV = pw(G);
 //const int N = 1 << 23;
 long long  iv[N + 1];
  
 void ntt(std::vector<long long> &a, bool invert) {
     int n = a.size();
     for (int i = 1, j = 0; i < n; i++) {
         int bit = n >> 1;
         for (; j & bit; bit >>= 1)
             j ^= bit;
         j ^= bit;
         if (i < j)
             std::swap(a[i], a[j]);
     }
     for (int len = 2; len <= n; len <<= 1) {
         long long  wlen = pw(invert ? GIV : G, (mod - 1) / len);
  
         for (int i = 0; i < n; i += len) {
             long long  w = 1;
             for (int j = 0; j < len / 2; j++) {
                 long long  u = a[i + j];
                 long long  v = (a[i + j + len / 2] * w) % mod;
  
                 a[i + j] = (u + v < mod ? u + v : u + v - mod);
                 a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + mod);
  
                 w = w * wlen % mod;
             }
         }
     }
     if (invert) {
         long long  n_inv = iv[n];
         for (long long  &x : a)
             x = x * n_inv % mod;
     }
 }
 std::vector<long long > multiply(std::vector<long long > a,std::vector<long long > b) {
     int n = 1;
     while (n < (int)a.size() + (int)b.size())
         n <<= 1;
     a.resize(n, 0);
     b.resize(n, 0);
     ntt(a, false);
     ntt(b, false);
     std::vector<long long > c(n);
     for (int i = 0; i < n; i++)
         c[i] = (a[i] * b[i]) % mod;
     ntt(c, true);
     while (c.size() > 1 && c.back() == 0)
         c.pop_back();
     return c;
 }