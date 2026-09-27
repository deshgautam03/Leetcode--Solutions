class Solution {
public:
    bool isPowerOfFour(int n) {
        if(n<1){
            return false;
        }
        else{
            int count=0;
            while(n!=1){
                if(n%2==1){
                    return false;
                }
                n/=2;
                count++;
            }
            if(count%2==0){
                return true;
            }
            else{
                return false;
            }
        }
    }
};
