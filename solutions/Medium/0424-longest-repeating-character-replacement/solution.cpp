class Solution {
public:
    int characterReplacement(string s, int k) {
        int freq[256]={0};
        int maxfreq=0,len=0,res=INT_MIN,low=0;
        int n=s.size();
        for(int high=0 ; high <n; high++){
            freq[s[high]]++;
            for(int j=0; j<256; j++){
                if(freq[j]>maxfreq){
                    maxfreq=freq[j];
                }
            }
            len=high-low+1;
            int diff=len-maxfreq;
            while(diff>k){
                freq[s[low]]--;
                low++;
            for(int j=0; j<256; j++){
                if(freq[j]>maxfreq){
                    maxfreq=freq[j];
                }
            }
            len=high-low+1;
            diff=len-maxfreq;
            }
            if(diff<k or diff==k){
                res=max(res,len);
            }
            
        }
        return res;
    }
};
