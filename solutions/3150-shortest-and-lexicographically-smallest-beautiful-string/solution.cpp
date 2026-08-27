class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        // int n = s.size();
        
        // // Step 1: collect indices where '1' occurs
        // vector<int> onesIdx;
        // for (int i = 0; i < n; i++) {
        //     if (s[i] == '1') {
        //         onesIdx.push_back(i);
        //     }
        // }
        
        // int m = onesIdx.size();
        // string best = "";
        
        // // Step 2: slide a window of size k over onesIdx
        // for (int j = 0; j + k - 1 < m; j++) {
        //     int start = onesIdx[j];
        //     int end = onesIdx[j + k - 1];
        //     string candidate = s.substr(start, end - start + 1);
            
        //     if (best == "" || candidate.size() < best.size() ||
        //        (candidate.size() == best.size() && candidate < best)) {
        //         best = candidate;
        //     }
        // }
        
        // return best;
        int n=s.size();
        vector<int> ones;
        for(int i=0; i<n; i++){
            if(s[i]=='1'){
                ones.push_back(i);
            }
        }
        int n2=ones.size();
        int low=0,high=k-1,len=0,smallest_len=INT_MAX,best_start=-1;
        string result="";
        while(high<n2){
            len=ones[high]-ones[low]+1;
            if(len<smallest_len){
                smallest_len=len;
                best_start=ones[low];
            }
            else if(len==smallest_len){
                if(s.substr(ones[low],len)<s.substr(best_start,smallest_len)){
                    best_start=ones[low];
                }

            }
            
            low++;
            high++;
        }
    if(best_start==-1){
        return "";
    }
    else{
    result=s.substr(best_start,smallest_len);
    return result;
    }
    }
    
};
