class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int count=0; 
        for(int i=0; i<nums.size(); i++){
            int ele=nums[i];
            for(int j=0; j<nums.size(); j++){
                if(ele==nums[j]){
                    count++;
                }
            }
            if(count<2){
                return ele;
            }
            count=0;
        }
        return 0;
    }
};
