#include <iostream>
#include <stack>
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
    int n, cmd, val;
    while (cin >> n)
    {
        bool S = true, Q = true, PQ = true;
        stack<int> s;
        queue<int> q;
        priority_queue<int> pq;
        while (n--)
        {
            cin >> cmd >> val;
            switch (cmd)
            {
            case 1:
                s.push(val), q.push(val), pq.push(val);
                break;
            case 2:
                if (S)
                {
                    if (!s.empty() && s.top() == val) s.pop();
                    else S = false;
                }
                if (Q)
                {
                    if (!q.empty() && q.front() == val) q.pop();
                    else Q = false;
                }
                if (PQ)
                {
                    if (!pq.empty() && pq.top() == val) pq.pop();
                    else PQ = false;
                }
                break;
            }
        }
        if ((S && Q) || (S && PQ) || (Q && PQ)) cout << "not sure\n";
        else if (S) cout << "stack\n";
        else if (Q) cout << "queue\n";
        else if (PQ) cout << "priority queue\n";
        else cout << "impossible\n";
    }
}