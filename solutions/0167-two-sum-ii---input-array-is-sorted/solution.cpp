class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> arr(2);
        int n=numbers.size();
        int i=0,j=n-1;
        while(i<j){
            if((numbers[i]+numbers[j])==target){
                arr[0]=(i+1);
                arr[1]=(j+1);
                return arr;
            }
            else if((numbers[i]+numbers[j])<target){
                i++;
            }
            else{
                j--;
            }
            
        }
        return{};
    }
};
