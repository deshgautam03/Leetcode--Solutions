class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        // int n=fruits.size(),j,c1=0,c2=0;
        // int len=0,longest_len=INT_MIN;
        // for(int i=0; i<n; i++){
        //     j=i+1;
        //     c1=1;
        //     if(j>i and (fruits[j]==fruits[j-1] or fruits[j]==fruits[i])){
        //         c1++;
        //         j++;
        //     }
        //     c2=1;
        //     if((fruits[j]==fruits[j-1]) or (fruits[j]==fruits[i])){
        //         c2++;
        //         j++;
        //     }
        //     len=c1+c2;
        //     if(len>longest_len){
        //         longest_len=len;
        //     }

        // }
        // return len;
        int n=fruits.size();
        int k=2,low=0,len=0,res=INT_MIN;
        unordered_map<int,int> freq;
        for(int high=0; high<n; high++){
            freq[fruits[high]]++;
        while(freq.size()>k){
            freq[fruits[low]]--;
            if(freq[fruits[low]]==0){
                freq.erase(fruits[low]);
            }
            low++;
        }
        res=max(res,high-low+1);
        
        // if(freq.size()==2){
        //     len=high-low+1;
        //     res=max(len,res);
        // }
        // else{
        //     res=high-low+1;
        // }
        
        }
        // if(res==INT_MIN){
        //     return 1;
        // }
        // else{
        //     return res;
        // }
        return res;


    }
};
