#include <iostream>

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
    cout << ((argc > 1 && atoi(argv[1]) > 0 && atoi(argv[1]) < 65535) ? (1 + atoll(argv[1])) * atoll(argv[1]) / 2 : 0);
}