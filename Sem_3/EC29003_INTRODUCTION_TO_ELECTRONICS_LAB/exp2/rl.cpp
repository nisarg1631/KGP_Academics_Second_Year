#include <bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
int main()
{
    double r, l;
    cout << "Enter R: ";
    cin >> r;
    cout << "Enter L: ";
    cin >> l;
    double w[8] = {50, 150, 450, 1300, 3800, 6500, 11500, 25000};
    cout << "Low pass:" << endl;
    for (int i = 0; i < 8; i++)
    {
        w[i]*=2*pi;
        cout << 20 * log10(r / sqrt((r * r) + (w[i] * w[i] * l * l))) << endl;
    }
    cout << "High pass:" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << 20 * log10(w[i] * l / sqrt(r * r + w[i] * w[i] * l * l)) << endl;
    }
    return 0;
}