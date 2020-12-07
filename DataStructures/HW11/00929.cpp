#include <iostream>
#include <climits>
#include <queue>

using namespace std;

// reference: https://ppt.cc/fDEWex

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

struct Val
{
    int x;
    int y;
    int cost;

    bool operator>(const Val& r) const { return cost > r.cost; }
};

// data
int N, M;                     // matrix is N * M
int maze[1001][1001];
int value[1001][1001];        // 從起點走到每個點的最短路徑
int d[] = { 0, 1, 0, -1, 0 }; // 偏移量
bool visited[1001][1001];
priority_queue<Val, vector<Val>, greater<Val>> pq; // min heap

void init()
{
    // 一開始將距離都設為最大值
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) value[i][j] = INT_MAX;
    fill(visited[0], visited[0] + 1001 * 1001, false);
}

void dijkstra()
{
    pq.push({ 0, 0, value[0][0] = maze[0][0] });

    while (!pq.empty())
    {
        auto [x, y, val] = pq.top();
        visited[y][x] = true;
        pq.pop();

        for (int i = 0; i < 4; ++i)
        {
            int dx = x + d[i], dy = y + d[i + 1];

            // 如果超出範圍或是走過
            if (dx < 0 || dx >= M || dy < 0 || dy >= N || visited[dy][dx]) continue;

            int tmp = val + maze[dy][dx];
            if (value[dy][dx] > tmp) pq.push({ dx, dy, value[dy][dx] = tmp });
        }
    }

    cout << value[N - 1][M - 1] << '\n';
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cin >> N >> M;

        // 建圖
        for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j)
        {
            int val;
            cin >> val;
            maze[i][j] = val;
        }
            
        init();

        dijkstra();
    }
}