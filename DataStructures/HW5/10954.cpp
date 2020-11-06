#include <iostream>
#include <queue>

using namespace std;

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

int main()
{
    int n, tmp;
    priority_queue<int, vector<int>, greater<int>> pq;
    while (cin >> n && n)
    {
        int ret = 0;
        while (n--) cin >> tmp, pq.push(tmp);
        while (pq.size() > 1)
        {
            int n1 = pq.top(); pq.pop();
            n1 += pq.top(), pq.pop();
            ret += n1;
            pq.push(n1);
        }
        cout << ret << '\n';
        pq.pop();
    }
}