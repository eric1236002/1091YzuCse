#include <iostream>
#include <algorithm>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define SIZE(c) int(c.size())

// reference: https://ppt.cc/fJFcMx

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

string orgin;
string target;
unordered_map<string, vector<string>> G;
unordered_set<string> visited;

int bfs()
{
    queue<string> q;
    q.push(orgin);
    visited.insert(orgin);

    int dis = 0;
    while (!q.empty())
    {
        int size = q.size();

        while (size--)
        {
            auto u = q.front();
            q.pop();

            if (u == target) return dis;

            for (auto& v : G[u]) if (!visited.count(v)) q.push(v), visited.insert(v);
        }
        ++dis;
    }
}

int main()
{
    int T;
    string str;

    cin >> T;
    cin.ignore();
    getline(cin, str); // avoid blank

    while (T--)
    {
        // init
        G.clear();

        // 讀取字典並儲存
        int cnt = 0;
        string tmp[200];
        while (getline(cin, str) && str != "*") tmp[cnt++] = str;

        // 每次找兩個字串比對，若只相差一個字元則建邊
        for (int i = 0; i < cnt; ++i) for (int j = i + 1; j < cnt; ++j)
        {
            // 若兩字串不等長就不做
            if (SIZE(tmp[i]) != SIZE(tmp[j])) continue;

            int dif = 0; // 兩字串相差的字元數
            for (int k = 0; k < SIZE(tmp[i]); ++k)
            {
                if (tmp[i][k] != tmp[j][k]) ++dif;
            }

            // 因為可互相轉換，所以建雙向
            if (dif == 1) G[tmp[i]].push_back(tmp[j]), G[tmp[j]].push_back(tmp[i]);
        }

        while (getline(cin, str) && !str.empty())
        {
            visited.clear();
            stringstream ss(str);
            ss >> orgin >> target;

            cout << orgin << ' ' << target << ' ';
            cout << bfs() << '\n';
        }

        if (T) cout << '\n';
    }
}