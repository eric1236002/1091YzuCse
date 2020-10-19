#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <stack>

using namespace std;

// fast IO
static auto __ = []()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

auto isleap = [](auto& y) { return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0); };

int date[] = { 0, 31 , 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct node
{
    node* prev;
    node* next;

    string ID;
    string ICD;
    int Days;
};

class MyList
{
public:
    MyList() : mySize() { myHead = new node; myHead->prev = myHead->next = myHead; }

    ~MyList() { while (mySize) pop_back(); delete myHead; }

    void printall()
    {
        auto p = myHead->next;
        while (p != myHead) cout << p->ID << "," << p->ICD << "," << p->Days << '\n', p = p->next;
    }

    void putIn(vector<string>& v)
    {
        // {ID, {ICD, {admit, discharge}}}
        // sort priority : ID > ICD > admit > discharge
        map<string, map<string, priority_queue<pair<string, string>>>> m;

        for (auto& str : v)
        {
            auto tmp = convert(str);
            // sort data
            for (size_t i = 3; i < tmp.size(); ++i) if (!tmp[i].empty())
                m[tmp[0]][tmp[i]].push({ tmp[1], tmp[2] });
        }

        // store data
        for (auto& [ID, _m] : m) for (auto& [ICD, pq] : _m)
        {
            // {admit, discharge}
            stack<pair<string, string>> s;
            while (pq.size() > 1) s.push({ pq.top().first, pq.top().second }), pq.pop();

            while (!s.empty())
            {   // because sort by admit, if second period's admit earlier than first period's discharge
                // means two time periods contain or across
                if (s.top().first <= pq.top().second)
                {   // if two periods across
                    if (s.top().second > pq.top().second)
                    {
                        auto tmp = pq.top().first;
                        pq.pop();
                        pq.push({ tmp, s.top().second });
                    }
                }
                else pq.push({ s.top().first, s.top().second });

                s.pop();
            }

            int cnt = 0;
            while (!pq.empty()) cnt += daysdiff(pq.top().first, pq.top().second), pq.pop();

            push_back(ID, ICD, cnt);
        }
    }

    void push_back(const string& id, const string& icd, const int& days)
    {
        myHead->prev->next = new node{ myHead->prev, myHead , id, icd, days };
        myHead->prev = myHead->prev->next;
        ++mySize;
    }

    void pop_back()
    {
        if (mySize)
        {
            myHead->prev = myHead->prev->prev;
            delete myHead->prev->next;
            myHead->prev->next = myHead;
            --mySize;
        }
    }

    // return {ID, admit, discharge, ICD1, ICD2, ICD3}
    // if ICD doesn't exist, replace by empty string
    vector<string> convert(string val)
    {
        vector<string> v;
        size_t idx;

        // split string and get data
        while ((idx = val.find(',')) != -1)
        {   // if idx = 0 means two commas adjacent
            v.push_back(idx ? val.substr(0, idx) : "");
            val.erase(0, idx + 1);
        }
        v.push_back(val.empty() ? "" : val);

        // if the discharge is empty
        if (v[2].empty())
        {
            int y = atoi(v[1].substr(0, 4).c_str());
            int mon = atoi(v[1].substr(4, 2).c_str());
            date[2] = isleap(y) ? 29 : 28;
            v[2] = v[1].substr(0, 6) + to_string(date[mon]);
        }

        return v;
    }

    int daysdiff(const string& d1, const string& d2)
    {
        int d1Y = atoi(d1.substr(0, 4).c_str());
        int d1M = atoi(d1.substr(4, 2).c_str());
        int d1D = atoi(d1.substr(6, 2).c_str());

        int d2Y = atoi(d2.substr(0, 4).c_str());
        int d2M = atoi(d2.substr(4, 2).c_str());
        int d2D = atoi(d2.substr(6, 2).c_str());

        int cnt = 0; // count days

        // if the year isn't the same
        while (d1Y < d2Y)
        {
            date[2] = isleap(d1Y) ? 29 : 28;
            cnt += date[d1M++] - d1D;
            while (d1M <= 12) cnt += date[d1M++];
            d1D = 0, d1M -= 12, ++d1Y;
        }

        // the year should be the same
        date[2] = isleap(d1Y) ? 29 : 28;
        while (d2M > d1M) d2D += date[--d2M];
        cnt += d2D - d1D + 1;

        return cnt;
    }

private:
    node* myHead;
    size_t mySize;
};

int main(int argc, char* argv[])
{
    if (argc < 2) return 0;
    string str;
    vector<string> v;
    //ifstream infile("Case.csv");
    ifstream infile(argv[1]);
    while (getline(infile, str)) v.push_back(str);

    MyList l;
    
    l.putIn(v);
    l.printall();
}