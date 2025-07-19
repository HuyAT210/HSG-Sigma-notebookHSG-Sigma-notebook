/**
 * Author: Cellul4r
 * Description: None
 */

int myAtoi(string s) {
    bool number = false;
    int sign = 1;
    string now;
    int n = s.length();
    for(int i = 0; i < n; i++) {
        if(s[i] >= '0' && s[i] <= '9') {
            now += s[i];
            number = true;
        } else if(!number && (s[i] == '-' || s[i] == '+')) {
            number = true;
            if(s[i] == '-') {
                sign = -1;
            }
        } else if(s[i] != ' ' || number){
            break;
        }
    }
    
    unsigned int res = 0;
    for(char& c : now) {
        if(res > UINT_MAX / 10) {
            res = UINT_MAX;
            break;
        }
        res = res * 10 + (c - '0');
    }
    int ans;
    if(sign == 1 && res > INT_MAX) {
        res = INT_MAX;
    } else if(sign == -1 && res > (unsigned int)INT_MAX + 1) {
        res = (unsigned int)INT_MAX + 1;
    }
    if(sign == 1) {
        ans = res;
    } else if(sign == -1 && res == (unsigned int)INT_MAX + 1){
        ans = INT_MIN;
    } else {
        ans = -(int)res;
    }
    return ans;
}
