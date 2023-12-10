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

vs readInputLines()
{
    string inputLine;
    vs inputLines;
    while (getline(cin, inputLine))
    {
        inputLines.pb(inputLine);
    }
    return inputLines;
}

bool isNumberString(string str)
{
    for (auto character : str)
    {
        if (character == '-')
            continue;
        if (character < '0' || character > '9')
        {
            return false;
        }
    }
    return true;
}

vector<ll> extractIntegers(string line)
{
    vector<ll> integerList;
    stringstream ss(line);
    string token;
    while (ss >> token)
    {
        if (!token.empty() && isNumberString(token))
        {
            integerList.pb(stoll(token));
        }
    }
    return integerList;
}

ll dayNinePartOne(const vs &inputLines)
{
    ll res = 0;

    for (string inputLine : inputLines)
    {
        if (inputLine.empty())
            continue;
        vector<vector<ll>> sequences;
        vector<ll> history = extractIntegers(inputLine);
        sequences.pb(history);

        ll seqIdx = 0;
        while (true)
        {
            bool hasOnlyZeros = true;
            vector<ll> seq;
            int seqSize = sequences[seqIdx].size();
            for (int i = 1; i < seqSize; ++i)
            {
                ll newNumber = sequences[seqIdx][i] - sequences[seqIdx][i - 1];
                seq.pb(newNumber);
                if (newNumber != 0)
                    hasOnlyZeros = false;
            }
            sequences.pb(seq);

            if (hasOnlyZeros)
                break;

            ++seqIdx;
        }
        for (const auto &seq : sequences)
        {
            res += seq[seq.size() - 1];
        }
    }
    return res;
}

ll dayNinePartTwo(const vs &inputLines)
{
    ll res = 0;

    for (string inputLine : inputLines)
    {
        ll val = 0;
        if (inputLine.empty())
            continue;
        vector<vector<ll>> sequences;
        vector<ll> history = extractIntegers(inputLine);
        sequences.pb(history);
        ll seqIdx = 0;
        while (true)
        {
            bool hasOnlyZeros = true;
            vector<ll> seq;
            int seqSize = sequences[seqIdx].size();
            for (int i = 1; i < seqSize; ++i)
            {
                ll newNumber = sequences[seqIdx][i] - sequences[seqIdx][i - 1];
                seq.pb(newNumber);
                if (newNumber != 0)
                    hasOnlyZeros = false;
            }
            sequences.pb(seq);

            if (hasOnlyZeros)
                break;

            ++seqIdx;
        }
        reverse(sequences.begin(), sequences.end());

        for (auto seq : sequences)
        {
            val = seq[0] - val;
        }
        res += val;
    }
    return res;
}

int main()
{
    fo;
    fi;
    freopen("input.txt", "r", stdin);
    vs input = readInputLines();

    cout << "First solution: " << dayNinePartOne(input) << endl;
    cout << "Second solution: " << dayNinePartTwo(input) << endl;

    return 0;
}
