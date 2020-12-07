#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

// reference: https://ppt.cc/f4Hzex

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

struct edge
{
    int u;
    int v;
    double w; // 邊的權重 ( 兩城市之間的距離 )

    // 將所有邊根據距離由小到大排序
    bool operator<(const edge& r) { return w < r.w; }
};

// 計算兩城市的距離
double distance(pair<int, int>& c1, pair<int, int>& c2)
{
    auto& [x1, y1] = c1;
    auto& [x2, y2] = c2;
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// data
int Case = 0;
vector<edge> edges;
int parents[1001]; // 每個點的 parent
int ranks[1001];

void init(int n)
{
    edges.clear();
    // 一開始每個節點的 parent 都是自己，而 rank 皆為 0
    for (int i = 0; i < n; ++i) parents[i] = i, ranks[i] = 0;
}

int Find(int p) { return p == parents[p] ? p : parents[p] = Find(parents[p]); }

bool Union(int x, int y)
{
    int rx = Find(x), ry = Find(y);

    // 如果 x 跟 y 的 root 一樣，表示 x 和 y 接起會造成環
    if (rx == ry) return false;

    // 將 rank 較小的接到 rank 較大的樹下面，因為這樣後面 Find 時消耗較小
    if (ranks[rx] > ranks[ry]) parents[ry] = rx;
    else if (ranks[rx] < ranks[ry]) parents[rx] = ry;
    else parents[ry] = rx, ++ranks[rx];

    return true;
}

void kruskcal(int ts, int n)
{
    int cnt = 0;        // 州的數量
    double roadDis = 0; // 需要建造的公路長度
    double railDis = 0; // 需要建造的鐵路長度

    // 先根據權重 ( 城市與城市的距離 ) 排序
    sort(edges.begin(), edges.end());

    int j = 0; // 計算已經用了幾條邊，總共需要 n - 1 條
    for (auto& [c1, c2, dis] : edges)
    {
        if (j == n - 1) break;

        // 若 c1、c2 接起會造成環則不接
        if (!Union(c1, c2)) continue;

        // 若兩城市距離大於 ts 表示需要建鐵路，同時表示兩城市不在同一個州
        if (dis > ts) railDis += dis, ++cnt;
        else roadDis += dis;

        ++j;
    }

    // 最後需要將州的數量加一，因為州的數量等於 "長度大於 ts 的邊的數量" 加一
    ++cnt;
    // 兩者都四捨五入
    roadDis = (int)(roadDis + 0.5);
    railDis = (int)(railDis + 0.5);

    cout << "Case #" << ++Case << ": " << cnt << " " << roadDis << " " << railDis << '\n';
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int n, ts; // 閥值 threshold
        cin >> n >> ts;
        init(n);

        vector<pair<int, int>> cities(n); // 城市的座標
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            cities[i] = { x, y };
        }

        // 將所有城市兩兩相連，並計算距離
        for (int i = 0; i < n; ++i)
        {
            pair<int, int> c1 = { cities[i].first, cities[i].second };
            for (int j = i + 1; j < n; ++j)
            {
                pair<int, int> c2 = { cities[j].first, cities[j].second };
                edges.push_back({ i, j, distance(c1, c2) });
            }
        }

        kruskcal(ts, n);
    }
}