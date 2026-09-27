class Solution {
public:
    int countIntersectingIntervals(vector<vector<int>>& intervals) {
        int n=intervals.size();
        int count=0;
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                int a=intervals[i][0],b=intervals[i][1];
                int c=intervals[j][0],d=intervals[j][1];
                if(a<=d and c<=b){
                    count++;
                }
            }
        }
        return count;
    }
};
