class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=0,j=0,index=0;
        vector<int> nums(m);
        for(int x=0; x<m;x++){
            nums[x]=nums1[x];
        }
        while(i<m and j<n){
            if(nums[i]<nums2[j]){
                nums1[index]=nums[i];
                i++;
                index++;
            }
            else{
                nums1[index]=nums2[j];
                j++;
                index++;
            }
        }
        while(j<n){
            nums1[index]=nums2[j];
            j++;
            index++;
        }
        while(i<m){
            nums1[index]=nums[i];
            i++;
            index++;
        }
        
        
        
    }
};
