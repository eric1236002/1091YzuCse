#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// fast IO
static auto __ = []()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int N, tmp, l = 0, r = 0, ret = 0;
        unordered_map<int, int> m;
        cin >> N;
        while (N--)
        {
            cin >> tmp;
            if (m.count(tmp)) l = max(l, m[tmp] + 1);
            ret = max(ret, r - l + 1);
            m[tmp] = r;
            ++r;
        }
        cout << ret << '\n';
    }
}