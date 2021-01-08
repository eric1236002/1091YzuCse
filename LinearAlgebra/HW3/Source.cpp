#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#define SIZE(c) int(c.size())
# define PI 3.14159265358979323846

using namespace std;

// reference: https://ppt.cc/f1yLAx

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

struct signal
{
    double real;
    double image;
};

void split(string& str); // 資料分割
void bitrp();            // 位反轉置換 Bit-reversal Permutation
void FFT();

vector<signal> signals;

int main(int argc, char* argv[])
{
    int Case = 0;
    ifstream inFile(argv[1]);
    string str;
    bool flag = false;
    while (getline(inFile, str))
    {
        if (flag) cout <<  '\n';
        signals.clear();
        split(str);
        FFT();

        cout << "Data " << ++Case << " :\n";
        for (auto& [r, i] : signals)
            cout << setprecision(4) << fixed << r << ' ' << i << '\n';
        flag = true;
    }
}

void split(string& str)
{
    stringstream ss(str);
    while (getline(ss, str, ',')) signals.push_back({ stod(str), 0 });
}

void bitrp()
{
    int p = 0;

    for (int i = 1; i < SIZE(signals); i *= 2) ++p;

    for (int i = 0; i < SIZE(signals); ++i)
    {
        int a = i, b = 0;
        for (int j = 0; j < p; ++j) b = b * 2 + a % 2, a /= 2;
        if (b > i) swap(signals[i], signals[b]);
    }
}

void FFT()
{
    vector<signal> w(SIZE(signals));

    bitrp();
    
    double arg = -2 * PI / SIZE(signals);
    double treal = cos(arg);
    double timage = sin(arg);
    w[0] = { 1.0, 0.0 };

    for (int i = 1; i < SIZE(signals) / 2; ++i)
    {
        w[i].real = w[i - 1].real * treal - w[i - 1].image * timage;
        w[i].image = w[i - 1].real * timage + w[i - 1].image * treal;
    }

    for (int m = 2; m <= SIZE(signals); m *= 2)
    {
        for (int k = 0; k < SIZE(signals); k += m)
        {
            for (int j = 0; j < m / 2; ++j)
            {
                int i1 = k + j;
                int i2 = i1 + m / 2;
                int t = SIZE(signals) * j / m;
                treal = w[t].real * signals[i2].real - w[t].image * signals[i2].image;
                timage = w[t].real * signals[i2].image + w[t].image * signals[i2].real;
                double ureal = signals[i1].real;
                double uimage = signals[i1].image;
                signals[i1] = { ureal + treal, uimage + timage };
                signals[i2] = { ureal - treal, uimage - timage };
            }
        }
    }
}