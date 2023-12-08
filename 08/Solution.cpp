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
        input.pb(line);
    return input;
}

ll lcm(ll a, ll b)
{
    return a / __gcd(a, b) * b;
}

ll dayEightPartOne(const vs &input)
{
    string rules = input[0];

    map<string, pair<string, string>> network;

    size_t i = 2;
    while (i < input.size())
    {
        stringstream ss(input[i]);
        string node, equal, left, right;

        ss >> node >> equal >> left >> right;

        left.erase(left.begin());
        left.erase(left.end() - 1);
        right.erase(right.end() - 1);

        network[node] = {left, right};
        ++i;
    }

    string node = "AAA";
    ll steps = 0;
    size_t idx = 0;

    while (node != "ZZZ")
    {
        ++steps;
        char direction = rules[idx];
        if (direction == 'L')
            node = network[node].first;
        else if (direction == 'R')
            node = network[node].second;

        ++idx;
        if (idx >= rules.size())
            idx = 0;
    }

    return steps;
}

ll dayEightPartTwo(const vs &input)
{
    string rules = input[0];

    map<string, pair<string, string>> network;

    size_t i = 2;
    while (i < input.size())
    {
        stringstream ss(input[i]);
        string node, equal, left, right;

        ss >> node >> equal >> left >> right;

        left.erase(left.begin());
        left.erase(left.end() - 1);
        right.erase(right.end() - 1);

        network[node] = {left, right};
        ++i;
    }

    vs startingNodes;
    for (const auto &n : network)
        if (n.first[n.first.size() - 1] == 'A')
            startingNodes.pb(n.first);

    ll res = 1;

    for (const auto &n : startingNodes)
    {
        string node = n;
        ll steps = 0;
        size_t idx = 0;

        while (node[node.size() - 1] != 'Z')
        {
            ++steps;
            char direction = rules[idx];
            if (direction == 'L')
                node = network[node].first;
            else if (direction == 'R')
                node = network[node].second;

            ++idx;
            if (idx >= rules.size())
                idx = 0;
        }

        res = lcm(res, steps);
    }
    return res;
}

int main()
{
    fo;
    fi;
    freopen("input.txt", "r", stdin);
    vs input = getInput();

    cout << "First solution: " << dayEightPartOne(input) << endl;
    cout << "Second solution: " << dayEightPartTwo(input) << endl;

    return 0;
}
