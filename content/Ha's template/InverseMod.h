/**
 * Author: AsianJS
 * Description: Inverse Mod and Binomial Coefficient
 * Time: O(n)
 * Status: I don't know
 */

 int inv(int a) {
    return a <= 1 ? a : m - (long long)(m/a) * inv(m % a) % m;
  }
  inv[1] = 1;
  for(int a = 2; a < m; ++a)
      inv[a] = m - (long long)(m/a) * inv[m%a] % m;
  long long binomial_coefficient(int n, int k) {
      return factorial[n] * inverse_factorial[k] % m * inverse_factorial[n - k] % m;
  }
  long long binomial_coefficient(int n, int k) {
      return factorial[n] * inverse(factorial[k] * factorial[n - k] % m) % m;
  }