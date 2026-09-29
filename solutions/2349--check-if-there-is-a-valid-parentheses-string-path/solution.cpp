class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m=grid.size(),n=grid[0].size();
        if((m+n-1)%2!=0) return false;
        if(grid[0][0]==')'||grid[m-1][n-1]=='(') return false;
        int maxBal=m+n;
        vector<vector<vector<bool>>> dp(
            m, vector<vector<bool>>(n, vector<bool>(maxBal, false))
        );
        dp[0][0][1] = true; // grid[0][0] is '(', so balance starts at 1

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                int delta = (grid[i][j] == '(') ? 1 : -1;

                for (int b = 0; b < maxBal; b++) {
                    bool reachable = false;
                    if (i > 0 && b - delta >= 0 && b - delta < maxBal)
                        reachable |= dp[i-1][j][b - delta];
                    if (j > 0 && b - delta >= 0 && b - delta < maxBal)
                        reachable |= dp[i][j-1][b - delta];
                    dp[i][j][b] = reachable;
                }
            }
        }

        return dp[m-1][n-1][0];
    }
};
