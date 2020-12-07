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

struct reg
{
    int num;
    int period;
    int time;

    bool operator<(const reg& r) const
    {
        return (time > r.time || (time == r.time && num > r.num));
    }
};

int main()
{
    int num, time;
    string in;
    priority_queue<reg> pq;

    while (cin >> in && in != "#")
    {
        cin >> num >> time;
        pq.push({ num, time, time });
    }
    cin >> num;
    for (int i = 0; i < num; ++i)
    {
        auto tmp = pq.top();
        pq.pop();
        cout << tmp.num << '\n';
        pq.push({ tmp.num, tmp.period, tmp.time + tmp.period });
    }
}