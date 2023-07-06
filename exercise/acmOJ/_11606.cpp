// 纯在main函数里面操作了，虽然速度还可以，但是风格真的不太行
#include <iostream>
using namespace std;

// 寻找块
void index(int x, int y, int **gridNum, int unsure, int sure)
{
    gridNum[x][y] = sure;
    if (gridNum[x + 1][y] == unsure)
    {
        gridNum[x + 1][y] = sure;
        index(x + 1, y, gridNum, unsure, sure);
    }
    if (gridNum[x][y + 1] == unsure)
    {
        gridNum[x][y + 1] = sure;
        index(x, y + 1, gridNum, unsure, sure);
    }
    if (gridNum[x - 1][y] == unsure)
    {
        gridNum[x - 1][y] = sure;
        index(x - 1, y, gridNum, unsure, sure);
    }
    if (gridNum[x][y - 1] == unsure)
    {
        gridNum[x][y - 1] = sure;
        index(x, y - 1, gridNum, unsure, sure);
    }
    return;
}

int main()
{
    int x, y;
    int n, m;
    cin >> n >> m;
    int unknowm[5010];
    int unkNum = 0;
    char grid[n + 2][m + 2]{0};
    int **gridNum = new int *[n + 2];
    for (int i = 0; i < n + 2; ++i)
    {
        gridNum[i] = new int[m + 2];
        for (int j = 0; j < m + 2; ++j)
            gridNum[i][j] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> grid[i][j];
            if (grid[i][j] == '?')
            {
                gridNum[i][j] = 2;
            }
            if (grid[i][j] == '.')
            {
                gridNum[i][j] = 1;
                x = i;
                y = j;
            }
        }
    }

    // 处理‘？’为陆地或者湖泊
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            if (gridNum[i][j] == 2)
            {
                // 寻找‘？’块
                index(i, j, gridNum, 2, 3);
                bool flag = 0;
                // 判断‘？’块是否可能与陆地相连
                for (int s = 1; s < n + 1; s++)
                {
                    for (int t = 1; t < m + 1; t++)
                    {
                        if (gridNum[s][t] == 3)
                        {
                            if (gridNum[s + 1][t] == 1 || gridNum[s - 1][t] == 1 || gridNum[s][t - 1] == 1 || gridNum[s][t + 1] == 1)
                            {
                                flag = 1;
                                break;
                            }
                        }
                    }
                    if (flag)
                    {
                        break;
                    }
                }
                // 如果是，将其改为陆地
                if (flag)
                {
                    for (int s = 1; s < n + 1; s++)
                    {
                        for (int t = 1; t < m + 1; t++)
                        {
                            if (gridNum[s][t] == 3)
                            {
                                gridNum[s][t] = 1;
                                // 记下修改为陆地的‘？’
                                unknowm[unkNum * 2] = s;
                                unknowm[unkNum * 2 + 1] = t;
                                unkNum++;
                            }
                        }
                    }
                }
                // 如果否，改为湖泊
                else
                {
                    for (int s = 1; s < n + 1; s++)
                    {
                        for (int t = 1; t < m + 1; t++)
                        {
                            if (gridNum[s][t] == 3)
                            {
                                gridNum[s][t] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    // 复制一份新的地图
    int **gridNuman = new int *[n + 2];
    for (int i = 0; i < n + 2; i++)
    {
        gridNuman[i] = new int[m + 2];
        for (int j = 0; j < m + 2; j++)
            gridNuman[i][j] = gridNum[i][j];
    }
    // 寻找陆地块
    index(x, y, gridNuman, 1, 2);
    // 判断是否连通
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (gridNuman[i][j] == 1)
            {
                cout << "Impossible";
                return 0;
            }
        }
    }
    bool flag = 0;
    // 判断将某个改为陆地的‘？’改为海洋后是否连通
    for (int k = 0; k < unkNum; k++)
    {
        for (int i = 0; i < n + 2; i++)
        {
            for (int j = 0; j < m + 2; j++)
                gridNuman[i][j] = gridNum[i][j];
        }
        gridNuman[unknowm[2 * k]][unknowm[2 * k + 1]] = 0;
        index(x, y, gridNuman, 1, 2);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (gridNuman[i][j] == 1)
                {
                    flag = 1;
                }
            }
        }
        // 如果是，则多解
        if (!flag)
        {
            cout << "Ambiguous";
            return 0;
        }
        else
            flag = 0;
    }
    // 输出唯一解的地图
    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < m + 1; ++j)
        {
            if (gridNum[i][j] == 1)
            {
                cout << '.';
            }
            else
                cout << '#';
        }
        cout << endl;
    }
}
