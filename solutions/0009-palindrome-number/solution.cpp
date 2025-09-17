class Solution {
public:
    bool isPalindrome(int x) {
        int temp=x,ans=0,r;
        if(x==0){
            return 1;
        }
        if(x<0){
            return 0;
        }
        if(x%10==0){
            return 0;
        }
        
        while(x!=0){
            r=x%10;
            x=x/10;
            if((ans>INT_MAX/10)||(ans<INT_MIN/10)){
                return 0;
            }
            ans=ans*10+r;
            
        }
        if(ans==temp){
            return 1;
        }
        else{
            return 0;
        }
    }
};
