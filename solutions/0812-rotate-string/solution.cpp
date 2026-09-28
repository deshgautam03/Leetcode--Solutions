class Solution {
public:
    bool rotateString(string s, string goal) {
        //*********Using inbuilt functions*********
        // if(goal.length()<s.length()) return false;
        // string ne=s+s;
        // if(ne.find(goal)!= string::npos) return true;
        // else{return false;}4

        //********* NOT Using inbuilt functions*********
        string ne=s+s;
        int n=goal.length();
        int m=s.length();
        if(goal.length()<s.length()) return false;
        for(int i=0; i<(2*m)-n; i++){
            if((ne.substr(i,n))==goal) return true;
        }
        return false;
      

    }
    
};
