class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n=nums.size();        
        int mid,start=0,end=n-1,first=-1,last=-1;
        //first occurence
        while(start<=end){
            mid=start+(end-start)/2;
            if(nums[mid]==target){
               first=mid;
               end=mid-1;
            }
            else if(target>nums[mid]){
                start=mid+1;
            }
            else{
                end=mid-1;
            }
        }
        //finding last occurence
        start=0;
        end=n-1;
        while(start<=end){
            mid=start+(end-start)/2;
            if(nums[mid]==target){
               last=mid;
               start=mid+1;
            }
            else if(target>nums[mid]){
                start=mid+1;
            }
            else{
                end=mid-1;
            }
        }
        return {first,last};
    }
};
