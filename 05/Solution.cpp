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

using NewRange = pair<uint64_t, uint64_t>;
using NewRangeMap = tuple<uint64_t, uint64_t, uint64_t>;

vector<uint64_t> newSeeds;
vector<NewRangeMap> newRanges[7];
NewRange newRangeOut;
NewRange newRangeIn1;
NewRange newRangeIn2;

bool isNewInRange(uint64_t src, const NewRangeMap &newRange)
{
    return get<0>(newRange) <= src && get<0>(newRange) + get<2>(newRange) > src;
}

uint64_t newFindDestInRange(uint64_t src, int range)
{
    for (size_t i = 0; i < newRanges[range].size(); ++i)
    {
        if (isNewInRange(src, newRanges[range][i]))
            return get<1>(newRanges[range][i]) + (src - get<0>(newRanges[range][i]));
    }
    return src;
}

uint64_t newConvertSeedToLocation(uint64_t seed)
{
    for (int i = 0; i < 7; ++i)
        seed = newFindDestInRange(seed, i);
    return seed;
}

uint64_t dayFivePartOne()
{
    uint64_t res = INT_MAX;
    for (size_t i = 0; i < newSeeds.size(); ++i)
    {
        uint64_t location = newConvertSeedToLocation(newSeeds[i]);
        res = location < res ? location : res;
    }
    return res;
}

bool canGenerateNewRange(const NewRange &newRange, const NewRangeMap &newMap)
{
    return isNewInRange(newRange.first, newMap) ||
           isNewInRange(newRange.first + newRange.second, newMap) ||
           (newRange.first < get<0>(newMap) && newRange.first + newRange.second >= get<0>(newMap) + get<2>(newMap));
}

vector<NewRange> getNewPossibleRanges(const NewRange &newRange, int rangeMap)
{
    vector<NewRange> in = {newRange};
    vector<NewRange> out;

    for (size_t i = 0; i < newRanges[rangeMap].size(); ++i)
    {
        NewRangeMap newMap = newRanges[rangeMap][i];
        vector<NewRange> temp;

        for (size_t j = 0; j < in.size(); ++j)
        {
            NewRange range = in[j];

            if (canGenerateNewRange(range, newMap))
            {
                if (range.first < get<0>(newMap) && range.first + range.second < get<0>(newMap) + get<2>(newMap))
                {
                    newRangeOut.first = get<1>(newMap);
                    newRangeOut.second = (range.first + range.second) - get<0>(newMap);
                    newRangeIn1.first = range.first;
                    newRangeIn1.second = get<0>(newMap) - range.first;

                    if (newRangeIn1.second != 0)
                        temp.pb(newRangeIn1);
                }
                else if (range.first + range.second > get<0>(newMap) + get<2>(newMap) && range.first >= get<0>(newMap))
                {
                    newRangeOut.first = get<1>(newMap) + (range.first - get<0>(newMap));
                    newRangeOut.second = (get<0>(newMap) + get<2>(newMap)) - range.first;
                    newRangeIn1.first = get<0>(newMap) + get<2>(newMap);
                    newRangeIn1.second = (range.first + range.second) - (get<0>(newMap) + get<2>(newMap));

                    if (newRangeIn1.second != 0)
                        temp.pb(newRangeIn1);
                }
                else if (range.first <= get<0>(newMap) && range.first + range.second >= get<0>(newMap) + get<2>(newMap))
                {
                    newRangeOut.first = get<1>(newMap);
                    newRangeOut.second = get<2>(newMap);
                    newRangeIn1.first = range.first;
                    newRangeIn1.second = get<0>(newMap) - range.first;
                    newRangeIn2.first = get<0>(newMap) + get<2>(newMap);
                    newRangeIn2.second = (range.first + range.second) - (get<0>(newMap) + get<2>(newMap));

                    if (newRangeIn1.second != 0)
                        temp.pb(newRangeIn1);

                    if (newRangeIn2.second != 0)
                        temp.pb(newRangeIn2);
                }
                else
                {
                    newRangeOut.first = get<1>(newMap) + (range.first - get<0>(newMap));
                    newRangeOut.second = range.second;
                }

                out.pb(newRangeOut);
            }
            else
            {
                newRangeIn1.first = range.first;
                newRangeIn1.second = range.second;
                temp.pb(newRangeIn1);
            }
        }

        in = temp;
    }

    if (in.size() > 0)
        out.insert(out.end(), in.begin(), in.end());
    return out;
}

uint64_t dayFivePartTwo()
{
    uint64_t res = numeric_limits<uint64_t>::max();
    vector<NewRange> newRanges;
    vector<NewRange> swap;

    for (size_t i = 0; i < newSeeds.size(); i += 2)
    {
        NewRange newRange;
        newRange.first = newSeeds[i];
        newRange.second = newSeeds[i + 1];
        newRanges.pb(newRange);
    }

    for (int i = 0; i < 7; ++i)
    {
        swap.clear();
        for (size_t j = 0; j < newRanges.size(); ++j)
        {
            vector<NewRange> result = getNewPossibleRanges(newRanges[j], i);
            swap.insert(swap.end(), result.begin(), result.end());
        }
        newRanges = swap;
    }

    for (size_t i = 0; i < newRanges.size(); ++i)
    {
        if (newRanges[i].first < res)
            res = newRanges[i].first;
    }

    return res;
}

int main()
{
    fo;
    fi;
    ifstream file("input.txt");
    string line;

    //   int newNumber;
    char *newNumberSize;
    getline(file, line);
    line = line.substr(7);

    while (line.length() > 0)
    {
        newSeeds.pb(strtoll(line.c_str(), &newNumberSize, 10));
        line = line.substr(newNumberSize - line.c_str());
    }

    getline(file, line);
    getline(file, line);

    int newIndex = 0;
    while (getline(file, line))
    {
        if (line == "")
        {
            getline(file, line);
            ++newIndex;
            continue;
        }

        NewRangeMap newRange;

        get<1>(newRange) = strtoll(line.c_str(), &newNumberSize, 10);
        line = line.substr(newNumberSize - line.c_str());

        get<0>(newRange) = strtoll(line.c_str(), &newNumberSize, 10);
        line = line.substr(newNumberSize - line.c_str());

        get<2>(newRange) = strtoll(line.c_str(), &newNumberSize, 10);
        line = line.substr(newNumberSize - line.c_str());

        newRanges[newIndex].pb(newRange);
    }
    file.close();

    cout << "First solution: " << dayFivePartOne() << endl;
    cout << "Second solution: " << dayFivePartTwo() << endl;
    return 0;
}
