class Solution {
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals) {
        // sort(intervals.begin(),intervals.end());
        // int count=0;
        // int n=intervals.size();
        // int start=0,end=n-1;
        // while(start<=end){
        //     int a=intervals[start][0],b=intervals[start][1];
        //     int c=intervals[end][0],d=intervals[end][1];
        //     if(a<=d and c<=b){
        //         count++;
        //     }
        //     start++;
        // }
        
        // return count;
        int n=intervals.size();
        vector<int> starts(n);
        for(int i=0; i<n; i++){
            starts[i]=intervals[i][0];
        }
        sort(starts.begin(),starts.end());
        long long total=(long long)n*(n-1)/2;
        long long non_overlap=0;
        for(int i=0; i<n; i++){
            int end=intervals[i][1];
            int index=upper_bound(starts.begin(),starts.end(),end)-starts.begin();
            non_overlap+=n-index;
        }
        return total-non_overlap;
    }
};
