class Solution{
    public:
    int nextnode(int n){
        int ans=0;
        while(n>0){
            int r=n%10;
            ans+=(r*r);
            n=n/10;
        }
        return ans;
    }
    bool isHappy(int n){
        int slow=nextnode(n);
        int fast=nextnode(nextnode(n));
        while(slow!=fast){
            slow=nextnode(slow);
            fast=nextnode(nextnode(fast));
            if(slow==1 || fast==1){
                return true;
            }
            
        }
        return slow==1;
    }
};

