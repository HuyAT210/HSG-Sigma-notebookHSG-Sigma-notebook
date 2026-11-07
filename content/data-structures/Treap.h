#include<bits/stdc++.h>
#define newl '\n'
 
const int MaxN = 1e5 + 10;
const int MaxV = 1e7 + 10;
const long long Inf = 1e18;
const long long Mod = 1e9 + 7;
 
std::mt19937_64 rng(std::chrono::high_resolution_clock().now().time_since_epoch().count());
 
long long Rand(long long lo = 1,long long hi = 1e9){
    return std::uniform_int_distribution<long long>(lo,hi)(rng);
}
struct Node{
    Node *l,*r;
    long long val,sum;
    int cnt;
    bool rev;
    long long w;
    Node(int val) : l(nullptr),r(nullptr),val(val),sum(0),cnt(0),rev(false),w(Rand()){
 
    }
};
typedef Node* pNode;
 
struct Treap{
private:
    int cnt(pNode t){
        return (t ? t->cnt : 0);
    }
    long long sum(pNode t){
        return (t ? t->sum : 0);
    }
    void update(pNode t){
        if(!t){
            return;
        }
        t->cnt = cnt(t->l) + cnt(t->r) + 1;
        t->sum = sum(t->l) + sum(t->r) + t->val;
    }
    void push(pNode it){
        if(it && it->rev){
            it->rev = false;
            std::swap(it->l,it->r);
            if(it->l){
                it->l->rev ^= true;
            }
            if(it->r){
                it->r->rev ^= true;
            }
        }
    }
    void merg(pNode &t,pNode l,pNode r){
        push(l);
        push(r);
        if(!l || !r){
            t = (l ? l : r);
        }else if(l->w > r->w){
            merg(l->r,l->r,r);
            t = l;
        }else{
            merg(r->l,l,r->l);
            t = r;
        }
        update(t);
    }
    void split(pNode t,pNode &l,pNode &r,int pos){
        push(t);
        if(!t){
            l = r = t;
        }else if(pos >= cnt(t->l) + 1){
            split(t->r,t->r,r,pos - (cnt(t->l) + 1));
            l = t;
        }else{
            split(t->l,l,t->l,pos);
            r = t;
        }
        update(t);
    }
    void print_ans(pNode t){
        if(!t){
            return;
        }
        push(t);
        print_ans(t->l);
        std::cout << t->sum;
        print_ans(t->r);
    }
public:
    pNode root;
    Treap() :root(nullptr){
 
    }
    void add(int val){
        merg(root,root,new Node(val));
    }
    void rev(int l,int r){
        pNode a,b;
        split(root,root,a,l - 1);
        split(a,a,b,r - l + 1);
        a->rev ^= true;
        merg(root,root,a);
        merg(root,root,b);
    }
    long long get_sum(int l,int r){
        long long ans = 0;
        pNode a,b;
        split(root,root,a,l - 1);
        split(a,a,b,r - l + 1);
        ans = a->sum;
        merg(root,root,a);
        merg(root,root,b);
        return ans;
    }
    void print_ans(){
        print_ans(root);
    }
};
 
 
int n,m;
void solve(){
    Treap tree;
    std::cin >> n >> m;
    for(int i = 1;i <= n;++i){
        int val;
        std::cin >> val;
        tree.add(val);
    }
    for(int i = 1;i <= m;++i){
        int t,l,r;
        std::cin >> t >> l >> r;
        if(t & 1){
            tree.rev(l,r);
        }else{
            std::cout << tree.get_sum(l,r) << newl;
        }
    }
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);std::cout.tie(nullptr);
    solve();
    return 0;
}