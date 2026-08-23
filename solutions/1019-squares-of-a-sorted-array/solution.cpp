class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        //Brute force
        // int n=nums.size();
        // vector<int> arr(n);
        // for(int i=0; i<n; i++){
        //     arr[i]=(nums[i])*(nums[i]);
        // }
        // sort(arr.begin(),arr.end());
        // return arr;
        //Optimal
        int n=nums.size();
        int i=0,j=n-1,index=n-1;
        for(int i=0; i<n; i++){
            nums[i]=nums[i]*nums[i];
        }
        vector<int> arr(n);
        while(i<j or i==j){    
            if((nums[i]>nums[j]) ){
                arr[index]=nums[i];
                i++;
                index--;
            }
            else{
                arr[index]=nums[j];
                j--;
                index--;
            }
        }
        return arr;
    }
};
