class Solution {
public:
    void sortColors(vector<int>& nums) {
        // sort(nums.begin(),nums.end());
        // int zero=0,one=0,two=0;
        // int n=nums.size();
        // for(int i=0; i<n; i++){
        //     if(nums[i]==0){
        //         zero++;
        //     }
        //     else if(nums[i]==1){
        //         one++;
        //     }
        //     else{
        //         two++;
        //     }
        // }
        // int j=0;
        // while(zero!=0){
        //     nums[j]=0;
        //     zero--;
        //     j++;
        // }
        // while(one!=0){
        //     nums[j]=1;
        //     one--;
        //     j++;
        // }
        // while(two!=0){
        //     nums[j]=2;
        //     two--;
        //     j++;
        // }
        int n=nums.size();
        int low=0, mid=0, high=n-1;
        while(mid<=high){
            if(nums[mid]==0){
                swap(nums[low],nums[mid]);
                low++;
                mid++;
            }
            else if(nums[mid]==1){
                mid++;
            }
            else{
                swap(nums[high],nums[mid]);
                high--;
                // mid++;(we dont have to do it as high can give us anything where as low can not give is anything as we only considerign mid and high)
            }
        }
    }
};
