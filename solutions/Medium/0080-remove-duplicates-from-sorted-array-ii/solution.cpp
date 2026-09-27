class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // int n=nums.size();
        // int i=0,j=1,count=1,c=1;
        // while(j<n){
        //     if(nums[j]==nums[i]){
        //         c++;
        //         if(c<=2){
        //             nums[count]=nums[j];
        //             i++;
        //             count++;
        //             j++;
        //         }
        //         else{
        //             j++;
        //         }
        //     }
        //     else{
        //         nums[count]=nums[j];
        //         i++;
        //         j++;
        //         c=1;
        //         count++;
        //     }
        // }
        // return count ;
        int n=nums.size();
        int i=0,j=1,c=1,count=1;
        while(j<n){
            if(nums[j]==nums[i]){
                if(c<2){
                    nums[i+1]=nums[j];
                    i++;
                    j++;
                    c++;
                    count++;
                }
                else{
                    j++;
                }
            }
            else{
                nums[i+1]=nums[j];
                i++;
                j++;
                c=1;
                count++;
            }
        }
        return count;
    }
};
