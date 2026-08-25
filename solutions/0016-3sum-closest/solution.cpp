class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int n=nums.size();
        int min_diff=INT_MAX,diff=0,sum=0,closest_sum=0;
        int j,k;
        for(int i=0; i<n-2; i++){
            j=i+1;
            k=n-1;
            while(j<k){
                sum=nums[i]+nums[j]+nums[k];
                diff=abs(sum-target);
                if(diff<min_diff){
                    min_diff=diff;
                    closest_sum=sum;
                }
                if(sum==target){
                    j++;
                    k--;
                }
                else if(sum<target){
                    j++;
                }
                else{
                    k--;
                }
            }
        }
        return closest_sum;
    }
};
