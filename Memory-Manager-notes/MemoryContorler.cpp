#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        int dp[m][n];
        for(int i = m - 1; i >= 0; i--){
            for(int j = n - 1; j >= 0; j--){
                if(i == m - 1 && j == n - 1){
                    dp[i][j] = obstacleGrid[i][j] ? 0 : 1;
                    continue;
                }
                dp[i][j] = 0;
                if(i < m - 1 && obstacleGrid[i + 1][j] == 0){
                    dp[i][j] += dp[i + 1][j];
                }
                if(j < m - 1 && obstacleGrid[i][j + 1] == 0){
                    dp[i][j] += dp[i][j + 1];
                }
            }
        }
        return dp[0][0];
    }
};
int main(){
    vector<vector<int>> test{{0, 0}}; 
    cout << Solution().uniquePathsWithObstacles(test) << endl;
    return 0;
}