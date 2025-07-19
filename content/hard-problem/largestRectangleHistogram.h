/**
 * Author: Cellul4r
 * Description: None
 */

int largestRectangleArea(vector<int>& heights) {
    
    stack<pair<int,int>> st;
    int n = heights.size();
    int maxArea = 0;
    for(int i=0;i<n;++i) {
        int idx = i, h = heights[i];
        while(!st.empty() && st.top().second >= h) {
            int j = st.top().first, k = st.top().second;
            st.pop();
            maxArea = max(maxArea, k * (i - j));
            idx = j;
        }
        st.push(make_pair(idx,h));
    }

    while(!st.empty()) {
        int j = st.top().first, h = st.top().second;
        st.pop();
        maxArea = max(maxArea, h * (n - j));
    }

    return maxArea;
}
