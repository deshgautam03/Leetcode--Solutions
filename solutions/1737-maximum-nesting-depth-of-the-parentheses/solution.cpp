class Solution {
public:
    int maxDepth(string s) {
        stack <char> st;
        int ans=0;
        for(auto ch:s){
            if(ch=='('){
                st.push(ch);
                int count=st.size();
                ans=max(ans,count);
            }
            else if(ch==')'){
                st.pop();
            }
            else{
                continue;
            }
        }
        return ans;
    }
};
