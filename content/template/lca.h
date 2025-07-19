/**
 * Author: Theerada Siri
 * Description: 
 *
 * 
 * Time: O()
 */

#define N 100010
#define L 20
 
int dep[N], par[N][L];
vector<int> tree[N];
 
void dfs(int i, int p) {
    dep[i] = dep[p] + 1;
    par[i][0] = p;
    for(int l = 1; l < L; ++l)
    	par[i][l] = par[par[i][l - 1]][l - 1];
    for(int j : tree[i])
    	if(j != p)
    		dfs(j, i);
}
 
int lca(int a, int b) {
    if(dep[a] < dep[b])
    	swap(a, b);
    for(int l = L - 1; l >= 0; --l)
    	if((dep[a] - dep[b]) >> l)
    		a = par[a][l];
    if(a == b)
    	return a;
    for(int l = L - 1; l >= 0; --l)
    	if(par[a][l] != par[b][l]) {
    		a = par[a][l];
    		b = par[b][l];
    	}
    return par[a][0];
}
// dfs(1,1)
