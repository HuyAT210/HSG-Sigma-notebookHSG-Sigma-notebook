/**
 * Author: Cellul4r
 * Description: None
 */

bool isIsomorphic(string s, string t) {
    vector<int> mapping(256);
    set<int> revMap[256];
    for(int i = 0; i < 256; i++) {
        mapping[i] = -1;
    }
    int n = s.length();
    for(int i = 0; i < n; i++) {
        int ss = s[i], tt = t[i];
        if(mapping[ss] != tt) {
            if(mapping[ss] != -1) {
                return false;
            }
            mapping[ss] = tt;
            revMap[tt].insert(ss);
        } else {
            revMap[tt].insert(ss);
        }
    }
    for(int i = 0; i < 256; i++) {
        if(revMap[i].size() > 1) {
            return false;
        }
    }
    return true;
}
