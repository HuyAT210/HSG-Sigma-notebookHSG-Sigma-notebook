/**
 * Author: Cellul4r
 * Description: None
 */

string convertToTitle(int columnNumber) {
    string res;
    long long curr = 1;
    while(columnNumber > 0) {
        columnNumber -= curr;
        int val = (columnNumber / curr) % 26;
        res += val + 'A';
        columnNumber -= val * curr;
        curr *= 26;
    }
    reverse(res.begin(), res.end());
    return res;    
}
