#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
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
    while (!str.empty() && str.back() == ' ') str.pop_back();
    stringstream ss(str);
    string tmp, tmp1;
    ss >> tmp;
    while (!ss.eof()) ss >> tmp1, tmp += " " + tmp1;
    if (tmp.empty()) return tmp;
    while (!tmp.empty() && (tmp.front() == '"' || tmp.front() == ' ')) tmp.erase(tmp.begin());
    while (!tmp.empty() && (tmp.back() == '"' || tmp.back() == ' ')) tmp.pop_back();
    return tmp;
}

class paser
{
public:
    paser() { root = make_shared<node>(); }

    void read(vector<string>& v1, vector<string>& v2)
    {
        data = v1;
        search = v2;
        put();
    }

    void put()
    {
        bool stop = false;
        stack<shared_ptr<node>> nodes;

        stack<bool> islist;

        nodes.push(root);
        islist.push(false);

        string str;
        auto valtmp = make_shared<node>();
        shared_ptr<node> tmp;

        for (auto& v : data) for (auto& ch : v)
        {
            switch (ch)
            {
            case '{':
                nodes.push(valtmp);
                islist.push(false);
                valtmp = make_shared<node>();
                break;

            case '}':
                if (!valtmp->key.empty())
                {
                    valtmp->val = progStr(str);
                    if (islist.top()) nodes.top()->l.push_back(valtmp);
                    else nodes.top()->v.push_back(valtmp);
                    valtmp = make_shared<node>();
                }

                tmp = nodes.top();
                nodes.pop();
                islist.pop();

                if (islist.top()) nodes.top()->l.push_back(tmp);
                else nodes.top()->v.push_back(tmp);

                str.clear();
                if (nodes.size() == 1) stop = true;
                break;

            case '[':
                valtmp->islist = true;
                nodes.push(valtmp);
                islist.push(true);
                valtmp = make_shared<node>();
                break;

            case ']':
                if (!valtmp->key.empty())
                {
                    valtmp->val = progStr(str);
                    if (nodes.top()->islist) nodes.top()->l.push_back(valtmp);
                    else nodes.top()->v.push_back(valtmp);
                    valtmp = make_shared<node>();
                }

                tmp = nodes.top();
                nodes.pop();
                islist.pop();

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
            if (first) cout << endl;
            _search(v);
            first = true;
            if (!out) cout << endl;
        }
    }

    void _search(vector<string>& v)
    {
        if (v.empty()) return;
        if (v.size() == 1) dfs1(root, v.front());
        else dfs2(root, v, 0);
    }

    void dfs1(shared_ptr<node> r, string& str)
    {
        if (r->key == str && r->islist)
        {
            for (auto& p1 : r->l) print2(p1);
            out = true;
        }
        else
        {
            if (r->key == str)
            {
                cout << r->val << endl;
                out = true;
            }
            for (auto& p1 : r->v) dfs1(p1, str);
            for (auto& p1 : r->l) dfs1(p1, str);
        }
    }

    void print2(shared_ptr<node>r)
    {
        if (r->key.empty())
        {
            cout << r->val << endl;
            out = true;
        }
        else
        {
            for (auto& p1 : r->l) print2(p1);
            for (auto& p1 : r->v) print2(p1);
        }
    }

    void dfs2(shared_ptr<node>r, vector<string>& v, int cnt)
    {
        if (r->key == v[cnt])
        {
            if (cnt == v.size() - 1)
            {
                if (r->islist) for (auto& p1 : r->l) print2(p1);
                else cout << r->val << endl;
                out = true;
            }
            else
            {
                for (auto& p1 : r->v) dfs2(p1, v, cnt + 1);
                for (auto& p1 : r->l) dfs2(p1, v, cnt + 1);
            }
        }
        else
        {
            for (auto& p1 : r->v) dfs2(p1, v, cnt);
            for (auto& p1 : r->l) dfs2(p1, v, cnt);
        }
    }

private:
    vector<string> data;
    vector<string> search;
    shared_ptr<node> root;
    bool out;
};

int main(int argc, char* argv[])
{
    string str;
    vector<string> v1, v2;
    ifstream infile1("case.json");
    ifstream infile2("search.txt");
    /*ifstream infile1(argv[1]);
    ifstream infile2(argv[2]);*/
    while (getline(infile1, str)) v1.emplace_back(str);
    while (getline(infile2, str)) v2.emplace_back(str);
    
    paser p;
    p.read(v1, v2);
    p.print();
}