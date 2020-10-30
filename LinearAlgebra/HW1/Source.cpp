#include <iostream>
#include <fstream>

using namespace std;

// fast IO
static auto __ = []()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

int main(int argc, char* argv[])
{
    if (argc < 2) return 0; // no file path

    ifstream file(argv[1], ios::binary);
    file.seekg(54, ios::beg); // avoid header

    // read file and print
    int cnt = 0;
    char ch, tmp = 0;
    while (file.get(ch).get(ch).get(ch)) // B, G, R
    {
        ++cnt;
        tmp = (tmp << 1) + ch + 1; // ch == -1 -> white = 0, ch == 0 -> black = 1
        if (cnt == 8)
        {
            if (tmp < 32 || tmp > 126) break;
            cout << tmp;
            cnt = tmp = 0;
        }
    }
}