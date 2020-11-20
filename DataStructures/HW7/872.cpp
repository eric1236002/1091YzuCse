#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>

#define FOR(i, n) for(int i = 0; i < n; ++i)
#define diff(ch) (ch - 'A')
#define SIZE(c) int(c.size())

using namespace std;

// reference: https://ppt.cc/fqUhHx

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

auto print = [](string& str)
{
    cout << str[0];
    for (int i = 1; i < SIZE(str); ++i) cout << " " << str[i];
    cout << '\n';
};

int main()
{
    // Data
    int G[26][26];
    int visited[26];
    bool track;

    int T;
    string str, S;
    cin >> T;
    cin.ignore();

    function<void(string)> dfs = [&](string ret)
    {
        if (ret.length() == S.length()) { print(ret), track = true; return; }

        FOR(i, SIZE(S))
        {
            if (visited[diff(S[i])]) continue;
            
            int j = 0;
            for (; j < SIZE(ret); ++j) if (G[diff(S[i])][diff(ret[j])]) break;
            
            // 如果 j 不等於 ret 的長度表示 ret 裡面出現了必須要出現在 s[i] 後面的字元
            if (j != SIZE(ret)) continue;

            // back tracking
            visited[diff(S[i])] = 1;
            dfs(ret + S[i]);
            visited[diff(S[i])] = 0;
        }
    };

    while (T--)
    {
        getline(cin, str); // avoid space

        // init
        track = false;
        fill(G[0], G[0] + 676, 0);
        fill(visited, visited + 26, 0);
        S.clear();

        // 讀取英文字母
        getline(cin, str);
        stringstream ss(str);
        while (ss >> str) S += str;
        sort(begin(S), end(S));

        getline(cin, str);
        ss.clear();
        ss.str(str);
        // 紀錄不能出現在 str[0] 前面的字元
        while (ss >> str) G[diff(str[0])][diff(str[2])] = 1;

        dfs("");

        if (!track) cout << "NO\n";
        if (T) cout << '\n';
    }
}