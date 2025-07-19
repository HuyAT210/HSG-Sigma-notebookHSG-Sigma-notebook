/**
 * Author: Cellul4r
 * Description: None
 */

string convert(string s, int numRows) {
    int n = s.size();
    if(numRows == 1) {
        return s;
    }

    vector<char> rows[numRows]; 
    for(int i = 0, type = 1, row = 0; i < n; i++) {
        rows[row].push_back(s[i]);
        if(row == 0 && type == -1) {
            type *= -1;
        } else if(row == numRows - 1 && type == 1) {
            type *= -1;
        }
        row += type;
    }
    string ans;
    for(int i = 0; i < numRows; i++) {
        for(char& c : rows[i]) {
            ans += c;
        }
    }
    return ans;
}
