class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int small=INT_MAX,dis=0;
        // int c=0;
        for(int i=0; i<nums.size(); i++){
            if(nums[i]==target){
                // c++;
                dis=abs(i-start);
                // if(c==1){
                //     small=dis;
                // }
                if(dis<small){
                    small=dis;
                }
            }
            
            
        }
        return small;
    }
};
