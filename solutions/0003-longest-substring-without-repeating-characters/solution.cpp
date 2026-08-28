class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n=s.size();
        int low=0,res=INT_MIN;
        unordered_map<char,int> freq;
        for(int high=0; high<n; high++){
            freq[s[high]]++;
            while(freq.size()<(high-low+1)){
                freq[s[low]]--;
                if(freq[s[low]]==0){
                    freq.erase(s[low]);
                }
                low++;
            }
            if(freq.size()==(high-low+1)){
                res=max(res,high-low+1);
            }
        }
        if(n==0){
            return 0;
        }
        else{return res;}
        
    }
};
