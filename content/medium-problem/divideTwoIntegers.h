/**
 * Author: Cellul4r
 * Description: None
 */

int divide(int dividend, int divisor) {
    if(dividend == divisor) return 1;
    bool neg = false;
    if((dividend < 0) ^ (divisor < 0)) {
        neg = true;
    }
    unsigned int a,b,ans = 0;
    if(dividend < 0) a = UINT_MAX - (unsigned int)dividend + 1;
    else a = dividend;
    if(divisor < 0) b = UINT_MAX - (unsigned int)divisor + 1;
    else b = divisor;
    while(a >= b) {
        unsigned int bit = 0;
        while(a > (b << (bit + 1))) {
            bit++;
        }
        ans += (1 << bit);
        a -= (b << bit);
    }
    if(ans > INT_MAX && !neg) ans = INT_MAX;
    // unsigned -> signed if default is negative subtract -2^w value
    return (neg ? -ans : ans);  
}
