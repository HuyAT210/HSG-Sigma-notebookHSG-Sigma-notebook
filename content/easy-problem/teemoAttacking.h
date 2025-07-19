/**
 * Author: Cellul4r
 * Description: None
 */

int findPoisonedDuration(vector<int>& timeSeries, int duration) {
    int lastPoison = 0;
    int ans = 0;
    for(int& x : timeSeries) {
        int nxt = x + duration - 1;
        ans += max(0, nxt - max(lastPoison, x) + 1);
        lastPoison = nxt + 1;
    }    
    return ans;
}
