#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>

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
        int N, tmp, l = 0, r = 0, ret = -1;
        vector<int> v;
        unordered_set<int> s;
        cin >> N;
        while (N--)
        {
            cin >> tmp;
            while (s.count(tmp)) s.erase(v[l++]);
            s.insert(tmp);
            v.emplace_back(tmp);
            ret = max(r - l + 1, ret);
            ++r;
        }
        cout << ret << '\n';
    }
}