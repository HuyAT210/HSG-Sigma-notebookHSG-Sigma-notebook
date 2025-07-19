/**
 * Author: Cellul4r
 * Description: None
 */

bool wordPattern(string pattern, string s) {
        vector<string> maps(26);
        map<string,char> wordToLetter;
        string word;
        int k = 0;
        for(char& c : s) {
            if(c == ' ') {
                if(k >= pattern.size() || word == "") {
                    return false;
                } else if(maps[pattern[k] - 'a'] != "" && maps[pattern[k] - 'a'] != word) {
                    return false;
                } else if(wordToLetter.find(word) != wordToLetter.end() && wordToLetter[word] != pattern[k]) {
                    return false;      
                }else if(maps[pattern[k] - 'a'] == ""){
                    maps[pattern[k] - 'a'] = word;
                    wordToLetter[word] = pattern[k];
                }
                k++;
                word = "";
            } else {
                word += c;
            }
        }
        if(word != "") {
            if(k >= pattern.size()) {
                    return false;
            } else if(maps[pattern[k] - 'a'] != "" && maps[pattern[k] - 'a'] != word) {
                // cout << k;
                return false;
            } else if(wordToLetter.find(word) != wordToLetter.end() && wordToLetter[word] != pattern[k]) {
                return false;      
            } else if(maps[pattern[k] - 'a'] == ""){
                maps[pattern[k] - 'a'] = word;
                wordToLetter[word] = pattern[k];
            }
            k++;

        }
        return (k == pattern.size());
    }
