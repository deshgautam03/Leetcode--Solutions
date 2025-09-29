class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n=nums.size();
        int res=0;
        int flag=0;
        for(int i=0; i<n; i++){
            if(nums[i]==1){
                flag++;
                if(flag>res){
                    res=flag;
                }
            }
            else{
                flag=0;
            }

        }
        return res;
    }
};
