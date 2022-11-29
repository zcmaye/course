#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 10010;
int cnt = 1, dp[N][N], q[N];
bool st[N];

void get_primes(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (st[i])  continue;
        else
        {
            q[cnt ++] = i;
            for (int j = i + i; j <= n; j += i )    st[j] = true;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    get_primes(n);
    for (int i = 0; i < cnt; i ++)  dp[i][0] = 1;
    
    for (int i = 1; i < cnt; i ++)
        for (int j = 2; j <= n; j ++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= q[i] && dp[i - 1][j - q[i]])  dp[i][j] = max(dp[i][j], dp[i - 1][j - q[i]] + 1);
        }
    
    int i = cnt - 1, j = n;
    int sum = 0;
    while (i && j) {
        if (dp[i][j] != dp[i - 1][j]) {
            cout << q[i] << " ";
            sum += q[i];
            j -= q[i];
        }
        i --;
    }
        
    cout << endl << dp[cnt - 1][n] - 1 << endl << sum;
    return 0;
}
