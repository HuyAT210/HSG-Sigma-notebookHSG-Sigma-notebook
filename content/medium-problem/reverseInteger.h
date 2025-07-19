/**
 * Author: Cellul4r
 * Description: None
 */

int reverse(int x) {
    if(x == INT_MIN) {
        return 0;
    }
    bool isneg = false;
    unsigned int xx;
    if(x < 0) {
        isneg = true;
        xx = (unsigned int)-x;
    } else {
        xx = x;
    }
    string xstr = to_string(xx);
    string rev = xstr;
    std::reverse(rev.begin(),rev.end());
    if(isneg) {
        rev = "-" + rev;
        if(rev.length() >= INT_MN_STR.length() && rev > INT_MN_STR) {
            return 0;
        }
    } else {
        if(rev.length() >= INT_MX_STR.length() && rev > INT_MX_STR) {
            return 0;
        }
    }
    return stoi(rev);
}
