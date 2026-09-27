class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // int write=1;
        // if(nums.size()==0){
        //     return 0;
        // }
        // for(int read=1; read<nums.size(); read++){
        //     if(nums[read]!=nums[write-1]){
        //         nums[write]=nums[read];
        //         write++;
        //     }
        // }
        // return write;
        // int n=nums.size();
        // int i=0,j=1;
        // int count =1;
        // while(j<n){
        //     if(nums[j]==nums[i]){
        //         j++;
        //     }
        //     else{
        //         nums[count]=nums[j];
        //         i=j;
        //         j++;
        //         count++;
        //     }
        // }
        // return count;
        int n=nums.size();
        int officer=0;
        int cm=1;
        int unique=1;
        while(cm<n){
            if(nums[cm]==nums[cm-1]){
                cm++;
                continue;
            }
            else{
                nums[officer+1]=nums[cm];
                officer++;
                unique++;
                cm++;
            }
            
        }
        return unique;
    }
};
