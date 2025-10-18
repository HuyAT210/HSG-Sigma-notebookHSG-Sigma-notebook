/**
 * Author: HuyAT
 * Description: Code from 3 years ago so I don't evne know what did I do (HuyAT)
 * Status: Tested
 */

#include<bits/stdc++.h>
//#define DEBUG_ENABLE
 
 
std::ostream& operator << (std::ostream &out,const std::vector<int>&output)
{
    for(int val : output)
        out << val << " ";
    return out;
}
std::vector<int> sortedClycicShift(const std::string &s)
{
    int n = s.size();
    const int alphabet = 256;
    std::vector<int> c(n),p(n),cnt(std::max(n,alphabet),0);
    for(int i = 0;i < n;++i)
        ++cnt[s[i]];
    for(int i = 1;i < alphabet;++i)
        cnt[i] += cnt[i - 1];
    for(int i = 0;i < n;++i)
        p[--cnt[s[i]]] = i;
    int classes = 1;
    c[p[0]] = 0;
    for(int i = 1;i < n;++i)
    {
        if(s[p[i]] != s[p[i - 1]])
            ++classes;
        c[p[i]] = classes - 1;
    }
    std::vector<int> cn(n),pn(n);
    for(int h = 0;(1 << h) < n;++h)
    {
        #ifdef DEBUG_ENABLE
        std::cerr << h << "\n";
        #endif // DEBUG_ENABLE
        for(int i = 0;i < n;++i)
        {
            pn[i] = p[i] - (1 << h);
            if(pn[i] < 0)
                pn[i] += n;
        }
        std::fill(cnt.begin(),cnt.begin() + classes,0);
        for(int i = 0;i < n;++i)
            ++cnt[c[pn[i]]];
        for(int i = 1;i < classes;++i)
            cnt[i] += cnt[i - 1];
        for(int i = n - 1;i >= 0;--i)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        #ifdef DEBUG_ENABLE
        std::cerr << h << "\n";
        #endif // DEBUG_ENABLE
        for(int i = 1;i < n;++i)
        {
            std::pair<int,int> prev = {c[p[i - 1]],c[(p[i - 1] + (1 << h)) % n]};
            std::pair<int,int> curr = {c[p[i]],c[(p[i] + (1 << h)) % n]};
            if(prev != curr)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}
std::vector<int> suffixArrayConstruction(std::string &s)
{
    s += "$";
    std::vector<int> suffixArray = sortedClycicShift(s);
    return suffixArray;
}
std::vector<int> lcpConstruction(const std::string &s,const std::vector<int> &p)
{
    int n = s.size(),k = 0;
    std::vector<int> lcp(n - 1,0),srank(n);
    for(int i = 0;i < n;++i)
        srank[p[i]] = i;
    for(int i = 0;i < n;++i)
    {
        if(srank[i] == n - 1)
        {
            k = 0;
            continue;
        }
        int j = p[srank[i] + 1];
        while(std::max(i,j) + k < n && s[i + k] == s[j + k])
            ++k;
        lcp[srank[i]] = k;
        if(k)
            --k;
    }
    #ifdef DEBUG_ENABLE
    std::copy(lcp.begin(),lcp.end(),std::ostream_iterator<int>(std::cerr," "));
    std::cerr << "\n";
    #endif // DEBUG_ENABLE
    return lcp;
}
std::vector<int> answer(std::string s)
{
    int n = s.size();
    std::vector<int> suffixArray = suffixArrayConstruction(s),lcp = lcpConstruction(s,suffixArray),res;
    std::sort(lcp.begin(),lcp.end());
    #ifdef DEBUG_ENABLE
    std::cout << lcp << "\n";
    #endif // DEBUG_ENABLE
    for(int i = 1;i <= n;++i)
    {
        int it = std::lower_bound(lcp.begin(),lcp.end(),i) - lcp.begin();
        res.push_back((n - i + 1) - (n - it));
    }
    return res;
}
void test()
{
    std::string s;
    std::cin >> s;
    std::vector<int> suffixArray = suffixArrayConstruction(s);
    for(auto val : suffixArray)
        std::cout << val << "\n";
    std::vector<int> lcp = lcpConstruction(s,suffixArray);
}
int main()
{
#ifdef DEBUG_ENABLE
    test();
#endif // DEBUG_ENABLE
    std::string s;
    std::cin >> s;
    std::cout << answer(s);
    return 0;
