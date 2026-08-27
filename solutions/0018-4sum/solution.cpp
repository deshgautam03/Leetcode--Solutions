class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n=nums.size();
        long long sum=0;
        sort(nums.begin(),nums.end());
        vector<vector<int>> result;
        int j,k,l;
        for(int i=0; i<n-3; i++){
            if(i>0 and nums[i]==nums[i-1]){
                continue;
            }
            for(j=i+1; j<n-2; j++){
                if(j>i+1 and nums[j]==nums[j-1]){
                    continue;
                } 
                k=j+1;
                l=n-1;
                while(k<l){
                sum=(long long)nums[i]+nums[j]+nums[k]+nums[l];
                if(sum==target){
                    result.push_back({nums[i],nums[j],nums[k],nums[l]});
                    k++;
                    l--;
                    while(k<n and nums[k]==nums[k-1]){
                        k++;
                    }
                    while(l>=0 and nums[l]==nums[l+1]){
                        l--;
                    }
                }
                else if(sum<target){
                    k++;
                }
                else{
                    l--;
                }
            }
        }
        }
        return result;
    }
};
