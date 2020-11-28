#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <list>

// reference : https://ppt.cc/fAS1wx

using namespace std;

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

struct node
{
    node() : islist() {}
    node(string key, string val) : key(key), val(val), islist() {}

    string key;
    string val;
    bool islist;
    list<shared_ptr<node>> l;
    vector<shared_ptr<node>> v;
};

string progStr(string str)
{
    // 移除前面及後面的空白
    while (!str.empty() && str.back() == ' ') str.pop_back();
    while (!str.empty() && str.front() == ' ') str.erase(str.begin());

    // 移除前後的雙引號
    if (!str.empty() && str.back() == '"') str.pop_back();
    if (!str.empty() && str.front() == '"') str.erase(str.begin());

    return str;
}

class parser
{
public:
    parser() { root = make_shared<node>(); }

    void read(vector<string>& v1, vector<string>& v2)
    {
        data = v1;
        search = v2;
        put();
    }

    void put()
    {
        bool stop = false;
        DQuotes = false;
        stack<shared_ptr<node>> nodes;
        nodes.push(root);

        string str;
        auto valtmp = make_shared<node>();
        shared_ptr<node> tmp;

        for (auto& v : data) for (auto& ch : v)
        {
            // 避免雙引號中出現關鍵字造成錯誤，如 "1[5" 或 "\"15"
            if (DQuotes && !(ch == '"' && str.back() != '\\'))
            {
                str.push_back(ch);
                continue;
            }
            switch (ch)
            {
            case '"':
                DQuotes ^= 1;
                str.push_back(ch);
                break;

            case '{':
                nodes.push(valtmp);
                valtmp = make_shared<node>();
                break;

            case '}':
                if (!str.empty())
                {
                    valtmp->val = progStr(str);
                    if (nodes.top()->islist) nodes.top()->l.push_back(valtmp);
                    else nodes.top()->v.push_back(valtmp);
                    valtmp = make_shared<node>();
                }

                tmp = nodes.top();
                nodes.pop();

                if (nodes.top()->islist) nodes.top()->l.push_back(tmp);
                else nodes.top()->v.push_back(tmp);

                str.clear();
                if (nodes.size() == 1) stop = true;
                break;

            case '[':
                valtmp->islist = true;
                nodes.push(valtmp);
                valtmp = make_shared<node>();
                break;

            case ']':
                if (!str.empty())
                {
                    valtmp->val = progStr(str);
                    if (nodes.top()->islist) nodes.top()->l.push_back(valtmp);
                    else nodes.top()->v.push_back(valtmp);
                    valtmp = make_shared<node>();
                }

                tmp = nodes.top();
                nodes.pop();

                if (nodes.top()->islist) nodes.top()->l.push_back(tmp);
                else nodes.top()->v.push_back(tmp);

                str.clear();
                break;

            case ':':
                valtmp->key = progStr(str);
                str.clear();
                break;

            case ',':
                if (!str.empty())
                {
                    valtmp->val = progStr(str);
                    if (nodes.top()->islist) nodes.top()->l.push_back(valtmp);
                    else nodes.top()->v.push_back(valtmp);
                    valtmp = make_shared<node>();
                }

                str.clear();
                break;

            default:
                str.push_back(ch);
                break;
            }

            if (stop) return;
        }
    }

    void print()
    {
        bool first = false;
        string str;
        for (auto& s : search)
        {
            out = false;
            vector<string> v;
            stringstream ss(s);
            while (getline(ss, str, '>')) v.emplace_back(str);
            if (first) cout << '\n'; // 若不為第一個測資則輸出一個空行
            _search(root, v, 0, vector<string>());
            first = true;
            if (!out) cout << '\n'; // 若找不到任何資料則輸出一個空行
        }
    }

    void _search(shared_ptr<node>& r, vector<string>& v, int cnt, vector<string> traversal)
    {
        // key 不為空就存入做檢索
        if(!r->key.empty()) traversal.push_back(r->key);

        if (r->key == v[cnt])
        {
            if (cnt == v.size() - 1)
            {
                int j = traversal.size() - 1;
                while (cnt >= 0 && v[cnt] == traversal[j]) --cnt, --j;
                if (cnt >= 0) return; // cnt 為 -1 才符合

                if (r->islist) listPrint(r);
                else if (!r->val.empty()) cout << r->val << '\n', out = true;
                return;
            }
            else ++cnt;
        }
        for (auto& p1 : r->v) _search(p1, v, cnt, traversal);
        for (auto& p1 : r->l) _search(p1, v, cnt, traversal);
    }

    void listPrint(shared_ptr<node>& r)
    {
        for (auto& n : r->l)
        {
            if (n->l.empty() && n->v.empty()) // n 為 leaf node
            {
                cout << n->val << '\n';
                out = true;
            }
        }
    }

private:
    vector<string> data;
    vector<string> search;
    shared_ptr<node> root;
    bool out; // 檢查是否有輸出資料
    bool DQuotes;
};

int main(int argc, char* argv[])
{
    string str;
    vector<string> v1, v2;
    //ifstream infile1("case.json");
    //ifstream infile2("search.txt");
    ifstream infile1(argv[1]);
    ifstream infile2(argv[2]);
    while (getline(infile1, str)) v1.emplace_back(str);
    while (getline(infile2, str)) v2.emplace_back(str);
    
    parser p;
    p.read(v1, v2);
    p.print();
}