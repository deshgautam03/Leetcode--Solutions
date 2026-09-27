class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n=nums.size();
        vector<vector<int>> result;
        int sum=0,i=0,j,k;
        sort(nums.begin(),nums.end());
       
        while(i<n-2){
            j=i+1;
            k=n-1;
            int s=-1*nums[i];
            if(i>0 and nums[i]==nums[i-1]){
                i++;
                continue;
            }
            while(j<k){
                sum=nums[j]+nums[k];
                if(sum==s){
                    result.push_back({nums[i],nums[j],nums[k]});
                    j++;
                    k--;
                
                
                while(j<k and nums[j]==nums[j-1]){
                    j++;
                }
                while(k>=0 and nums[k]==nums[k+1]){
                    k--;
                }
                }
                else if(sum<s){
                    j++;
                }
                else{
                    k--;
                }
            }
        i++;
        }
        return result;
    }
};
