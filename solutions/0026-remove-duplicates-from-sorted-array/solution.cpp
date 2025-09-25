class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int write=1;
        if(nums.size()==0){
            return 0;
        }
        for(int read=1; read<nums.size(); read++){
            if(nums[read]!=nums[write-1]){
                nums[write]=nums[read];
                write++;
            }
        }
        return write;
        
    }
};
