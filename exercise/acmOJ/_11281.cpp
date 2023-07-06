#include <iostream>
#include <queue>
using namespace std;

int jumpToDestination(int startx, int starty, int endx, int endy, int m1, int m2, int **grid, int **isEverT, int M, int N)
{
    int x1, y1;
    queue<int> q;
    while (1)
    {
        x1 = startx + m1;
        y1 = starty + m2;
        if (x1 == endx && y1 == endy)
        {
            return isEverT[startx][starty] + 1;
        }
        if (x1 <= M && y1 <= N && grid[x1][y1] == 1 && !isEverT[x1][y1])
        {
            isEverT[x1][y1] = isEverT[startx][starty] + 1;
            q.push(x1);
            q.push(y1);
        }
        x1 = startx - m1;
        y1 = starty + m2;
        if (x1 == endx && y1 == endy)
        {
            return isEverT[startx][starty] + 1;
        }
        if (x1 > 0 && y1 <= N && grid[x1][y1] == 1 && !isEverT[x1][y1])
        {
            isEverT[x1][y1] = isEverT[startx][starty] + 1;
            q.push(x1);
            q.push(y1);
        }
        x1 = startx + m1;
        y1 = starty - m2;
        if (x1 == endx && y1 == endy)
        {
            return isEverT[startx][starty] + 1;
        }
        if (x1 <= M && y1 > 0 && grid[x1][y1] == 1 && !isEverT[x1][y1])
        {
            isEverT[x1][y1] = isEverT[startx][starty] + 1;
            q.push(x1);
            q.push(y1);
        }
        x1 = startx - m1;
        y1 = starty - m2;
        if (x1 == endx && y1 == endy)
        {
            return isEverT[startx][starty] + 1;
        }
        if (x1 > 0 && y1 > 0 && grid[x1][y1] == 1 && !isEverT[x1][y1])
        {
            isEverT[x1][y1] = isEverT[startx][starty] + 1;
            q.push(x1);
            q.push(y1);
        }
        x1 = startx + m2;
        y1 = starty + m1;
        if (x1 == endx && y1 == endy)
        {
            return isEverT[startx][starty] + 1;
        }
        if (x1 <= M && y1 <= N && grid[x1][y1] == 1 && !isEverT[x1][y1])
        {
            isEverT[x1][y1] = isEverT[startx][starty] + 1;
            q.push(x1);
            q.push(y1);
        }
        x1 = startx - m2;
        y1 = starty + m1;
        if (x1 == endx && y1 == endy)
        {
            return isEverT[startx][starty] + 1;
        }
        if (x1 > 0 && y1 <= N && grid[x1][y1] == 1 && !isEverT[x1][y1])
        {
            isEverT[x1][y1] = isEverT[startx][starty] + 1;
            q.push(x1);
            q.push(y1);
        }
        x1 = startx + m2;
        y1 = starty - m1;
        if (x1 == endx && y1 == endy)
        {
            return isEverT[startx][starty] + 1;
        }
        if (x1 <= M && y1 > 0 && grid[x1][y1] == 1 && !isEverT[x1][y1])
        {
            isEverT[x1][y1] = isEverT[startx][starty] + 1;
            q.push(x1);
            q.push(y1);
        }
        x1 = startx - m2;
        y1 = starty - m1;
        if (x1 == endx && y1 == endy)
        {
            return isEverT[startx][starty] + 1;
        }
        if (x1 > 0 && y1 > 0 && grid[x1][y1] == 1 && !isEverT[x1][y1])
        {
            isEverT[x1][y1] = isEverT[startx][starty] + 1;
            q.push(x1);
            q.push(y1);
        }
        startx = q.front();
        q.pop();
        starty = q.front();
        q.pop();
    }
}

int main()
{
    int M, N, m1, m2;
    cin >> M >> N >> m1 >> m2;
    int **grid = new int *[M + 2];
    int **iseverT = new int *[M + 2];
    for (int i = 1; i < M + 1; i++)
    {
        grid[i] = new int[N + 2];
        iseverT[i] = new int[N + 2];
        for (int j = 1; j < N + 1; ++j)
        {
            cin >> grid[i][j];
            iseverT[i][j] = 0;
        }
    }
    int startx, starty, endx, endy;
    for (int i = 1; i < M + 1; i++)
    {
        for (int j = 1; j < N + 1; j++)
        {
            if (grid[i][j] == 3)
            {
                startx = i;
                starty = j;
            }
            if (grid[i][j] == 4)
            {
                endx = i;
                endy = j;
            }
        }
    }
    int shortRoad = jumpToDestination(startx, starty, endx, endy, m1, m2, grid, iseverT, M, N);
    cout << shortRoad;
    return 0;
}