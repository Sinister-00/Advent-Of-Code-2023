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

vector<vc> helper(ifstream &inputFile)
{
    string line;
    vector<vc> mtx;
    while (getline(inputFile, line))
    {
        vc row(line.begin(), line.end());
        mtx.pb(row);
    }
    return mtx;
}

void dayThreeFirst(vector<vc> mtx)
{
    long res = 0;

    for (vector<vc>::size_type row = 1, high = 0, low = 2; row < mtx.size() - 1; ++row, ++high, ++low)
    {
        for (vc::size_type col = 0; col < mtx[row].size(); ++col)
        {
            if (mtx[row][col] != '.' && !isdigit(mtx[row][col]))
            {
                for (vc::size_type r = high; r <= low; ++r)
                {
                    for (vc::size_type c = col - 1; c <= col + 1; ++c)
                    {
                        if (isdigit(mtx[r][c]))
                        {
                            int num = 0;
                            int startPos = c;
                            int endPos = c;
                            while (startPos >= 0 && isdigit(mtx[r][startPos]))
                            {
                                startPos--;
                            }
                            while (endPos < static_cast<int>(mtx[r].size()) && isdigit(mtx[r][endPos]))
                            {
                                endPos++;
                            }
                            for (int p = startPos + 1; p < endPos; ++p)
                            {
                                num = num * 10 + (mtx[r][p] - '0');
                                mtx[r][p] = '.';
                            }
                            res += num;
                        }
                    }
                }
            }
        }
    }
    cout << "First solution: " << res << endl;
}

void dayThreeSecond(vector<vc> mtx)
{
    long res = 0;
    int temp = 0;

    for (vector<vc>::size_type row = 1, high = 0, low = 2; row < mtx.size() - 1; ++row, ++high, ++low)
    {
        for (vc::size_type col = 0; col < mtx[row].size(); ++col)
        {
            if (mtx[row][col] == '*' && !isdigit(mtx[row][col]))
            {
                bool first = true;
                for (vc::size_type r = high; r <= low; ++r)
                {
                    for (vc::size_type c = col - 1; c <= col + 1; ++c)
                    {
                        if (isdigit(mtx[r][c]))
                        {
                            int num = 0;
                            int startPos = c;
                            int endPos = c;
                            while (startPos >= 0 && isdigit(mtx[r][startPos]))
                            {
                                startPos--;
                            }
                            while (endPos < static_cast<int>(mtx[r].size()) && isdigit(mtx[r][endPos]))
                            {
                                endPos++;
                            }
                            for (int p = startPos + 1; p < endPos; ++p)
                            {
                                num = num * 10 + (mtx[r][p] - '0');
                                mtx[r][p] = '.';
                            }
                            first ? temp = num : res += (num * temp);
                            first = false;
                        }
                    }
                }
            }
        }
    }

    cout << "Second solution: " << res << endl;
}

// Driver function
int main()
{
    fo;
    fi;
    ifstream inputFile("input.txt", ios::in);
    vector<vc> mtx = helper(inputFile);
    dayThreeFirst(mtx);
    dayThreeSecond(mtx);

    return 0;
}
