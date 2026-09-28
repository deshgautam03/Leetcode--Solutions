class Solution {
public:
    int rotatedDigits(int n) {
        int count=0;
        for(int i=1; i<=n; i++){
            if(isGood(i)) count++;
        }
        return count;
    }
private:
    bool isGood(int x){
        int d;
        bool ans=false;
        while(x>0){
            d=x%10;
            if(d==3||d==4||d==7) return false;
            if(d==2||d==5||d==6||d==9) ans=true;
            x/=10;
        }
        return ans;
    }
};
