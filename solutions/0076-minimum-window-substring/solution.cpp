class Solution {
public:
    string minWindow(string s, string t) {
       int n=t.size();
       int m=s.size();
       if(n==0 or m<n) return "";
       int low=0,best_start=0,best_len=INT_MAX,matched=0;
       unordered_map<char,int> need;
       unordered_map<char,int> freq;

       for(char ch:t) need[ch]++;
       for(int high=0; high<m; high++){
        freq[s[high]]++;
        if(need.count(s[high]) and freq[s[high]]==need[s[high]]){
            matched++;
        }
        while(matched==need.size()){
            if(high-low+1<best_len){
                best_len=high-low+1;
                best_start=low;
            }
            
            freq[s[low]]--;
            if(need.count(s[low]) and freq[s[low]]<need[s[low]]){
                matched--;
            }
            low++;
        }
       }
       if(best_len==INT_MAX) return "";
       else return s.substr(best_start,best_len);
    }
};
