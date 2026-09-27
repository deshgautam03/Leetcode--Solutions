class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n=nums.size();
        int low=0,high=0,sum=0,res=INT_MAX,len=0;
        while(high<n){
            sum=sum+nums[high];
            while(sum>=target){
                len=high-low+1;
                res=min(res,len);
                sum=sum-nums[low];
                low++;
            }
            high++;
        }
        if(res==INT_MAX){
            return 0;
        }
        else{
            return res;
        }
        
    }
};
