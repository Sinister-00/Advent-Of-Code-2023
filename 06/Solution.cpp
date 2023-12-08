#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vvi vector<vi>
#define vc vector<char>
#define vs vector<string>
#define pb push_back
#define test  \
    ll t;     \
    cin >> t; \
    while (t--)
#define mod 1000000007
#define fo ios_base::sync_with_stdio(false);
#define fi cin.tie(NULL);

vs getInput()
{
    string line;
    vs input;
    while (getline(cin, line))
    {
        input.pb(line);
    }
    return input;
}

bool isNumber(string str)
{
    for (char c : str)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }
    return true;
}

vector<ll> getIntList(string line)
{
    vector<ll> res;
    stringstream ss(line);
    string token;
    while (ss >> token)
    {
        if (!token.empty() && isNumber(token))
        {
            res.pb(stoll(token));
        }
    }
    return res;
}

ll getIntSkipSpace(string line)
{
    string n;
    stringstream ss(line);
    string token;
    while (ss >> token)
    {
        if (!token.empty() && isNumber(token))
        {
            n += token;
        }
    }
    return stoll(n);
}

bool isDoubleInt(double d)
{
    ll i = static_cast<ll>(d);
    return i == d;
}

ll daySixPartOne(const vs &input)
{
    ll res = 1;
    vector<ll> times = getIntList(input[0]);
    vector<ll> distances = getIntList(input[1]);

    for (size_t i = 0; i < times.size(); ++i)
    {
        ll time = times[i];
        ll distance = distances[i];

        double delta = sqrt(time * time - 4 * distance);

        double a = (time - delta) / 2;
        double b = (time + delta) / 2;

        if (isDoubleInt(a))
            ++a;
        if (isDoubleInt(b))
            --b;
        ll numOfWin = floor(b) - ceil(a) + 1;

        res *= numOfWin;
    }
    return res;
}

ll daySixPartTwo(const vs &input)
{
    ll res = 1;

    ll time = getIntSkipSpace(input[0]);
    ll distance = getIntSkipSpace(input[1]);

    double delta = sqrt(time * time - 4 * distance);

    double a = (time - delta) / 2;
    double b = (time + delta) / 2;

    if (isDoubleInt(a))
        ++a;
    if (isDoubleInt(b))
        --b;
    ll numOfWin = floor(b) - ceil(a) + 1;

    res *= numOfWin;
    return res;
}

int main()
{
    freopen("input.txt", "r", stdin);

    vs input = getInput();
    cout << "First solution: " << daySixPartOne(input) << endl;
    cout << "Second solution: " << daySixPartTwo(input) << endl;
    return 0;
}
