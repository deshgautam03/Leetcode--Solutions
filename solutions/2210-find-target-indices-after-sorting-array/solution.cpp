class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        vector<int> ans;
        int equal=0,smaller=0;
        for(auto & num:nums){
            if(num==target) equal++;
            else if(num<target) smaller++;
        }
        while(equal--){
            ans.push_back(smaller++);
        }
        return ans;
        



    }
};
