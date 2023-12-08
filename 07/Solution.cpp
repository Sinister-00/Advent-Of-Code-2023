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

class CardHand
{
private:
    string hand;
    ll bidValue;

public:
    CardHand(string hand, ll bidValue) : hand{hand}, bidValue{bidValue} {};

    string getHand() const { return hand; }
    ll getBidValue() const { return bidValue; }
};

enum StrengthType
{
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind
};

bool isFind(vi vec, int target)
{
    auto it = vec.begin();
    while (it != vec.end())
    {
        if (*it == target)
            return true;
        ++it;
    }
    return false;
}

namespace Part1
{
    map<char, int> convertToRelativeStrength{
        {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8}, {'T', 9}, {'J', 10}, {'Q', 11}, {'K', 12}, {'A', 13}};

    StrengthType getStrengthType(string hand)
    {
        vi occurrence;

        map<char, int> countOccurrence;
        for (char c : hand)
        {
            ++countOccurrence[c];
        }
        auto p = countOccurrence.begin();
        while (p != countOccurrence.end())
        {
            occurrence.pb(p->second);
            ++p;
        }

        if (isFind(occurrence, 5))
        {
            return FiveOfAKind;
        }
        else if (isFind(occurrence, 4))
        {
            return FourOfAKind;
        }
        else if (isFind(occurrence, 3) && isFind(occurrence, 2))
        {
            return FullHouse;
        }
        else if (isFind(occurrence, 3))
        {
            return ThreeOfAKind;
        }
        else if (count(occurrence.begin(), occurrence.end(), 2) == 2)
        {
            return TwoPair;
        }
        else if (isFind(occurrence, 2))
        {
            return OnePair;
        }
        else
        {
            return HighCard;
        }
    }

    bool compare(const CardHand &c1, const CardHand &c2)
    {
        string c1Hand = c1.getHand();
        string c2Hand = c2.getHand();

        if (getStrengthType(c1Hand) != getStrengthType(c2Hand))
            return getStrengthType(c1Hand) < getStrengthType(c2Hand);
        else
        {
            int i = 0;
            while (i < 5)
            {
                if (c1Hand[i] != c2Hand[i])
                    return convertToRelativeStrength[c1Hand[i]] < convertToRelativeStrength[c2Hand[i]];
                ++i;
            }
            return false;
        }
    }
}

namespace Part2
{
    string allCardFace = "23456789TQKA";

    map<char, int> convertToRelativeStrength{
        {'J', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'Q', 11}, {'K', 12}, {'A', 13}};

    StrengthType getStrengthType(string hand)
    {
        StrengthType maxStrengthOfHand = HighCard;
        auto face = allCardFace.begin();
        while (face != allCardFace.end())
        {
            string possibleHand = hand;
            replace(possibleHand.begin(), possibleHand.end(), 'J', *face);

            StrengthType handStrength;

            vi occurrence;

            map<char, int> countOccurrence;
            auto c = possibleHand.begin();
            while (c != possibleHand.end())
            {
                ++countOccurrence[*c];
                ++c;
            }

            auto p = countOccurrence.begin();
            while (p != countOccurrence.end())
            {
                occurrence.pb(p->second);
                ++p;
            }

            if (isFind(occurrence, 5))
            {
                handStrength = FiveOfAKind;
            }
            else if (isFind(occurrence, 4))
            {
                handStrength = FourOfAKind;
            }
            else if (isFind(occurrence, 3) && isFind(occurrence, 2))
            {
                handStrength = FullHouse;
            }
            else if (isFind(occurrence, 3))
            {
                handStrength = ThreeOfAKind;
            }
            else if (count(occurrence.begin(), occurrence.end(), 2) == 2)
            {
                handStrength = TwoPair;
            }
            else if (isFind(occurrence, 2))
            {
                handStrength = OnePair;
            }
            else
            {
                handStrength = HighCard;
            }
            maxStrengthOfHand = max(maxStrengthOfHand, handStrength);
            ++face;
        }
        return maxStrengthOfHand;
    }

    bool compare(const CardHand &c1, const CardHand &c2)
    {
        string c1Hand = c1.getHand();
        string c2Hand = c2.getHand();

        if (getStrengthType(c1Hand) != getStrengthType(c2Hand))
            return getStrengthType(c1Hand) < getStrengthType(c2Hand);
        else
        {
            int i = 0;
            while (i < 5)
            {
                if (c1Hand[i] != c2Hand[i])
                    return convertToRelativeStrength[c1Hand[i]] < convertToRelativeStrength[c2Hand[i]];
                ++i;
            }
            return false;
        }
    }
}

vs processInput()
{
    string line;
    vs input;
    while (getline(cin, line))
    {
        input.pb(line);
    }
    return input;
}

ll solve(vs &input, bool usePart2)
{
    vector<CardHand> cardsHand;

    auto cardHand = input.begin();
    while (cardHand != input.end())
    {
        stringstream ss(*cardHand);

        string hand;
        ss >> hand;
        string bidStr;
        ss >> bidStr;
        ll bid = stoll(bidStr);
        cardsHand.pb({hand, bid});
        ++cardHand;
    }

    if (usePart2)
        sort(cardsHand.begin(), cardsHand.end(), Part2::compare);
    else
        sort(cardsHand.begin(), cardsHand.end(), Part1::compare);

    ll res = 0;
    size_t i = 0;
    while (i < cardsHand.size())
    {
        res += (i + 1) * cardsHand[i].getBidValue();
        ++i;
    }

    return res;
}

int main()
{
    fo;
    fi;
    freopen("input.txt", "r", stdin);
    vs input = processInput();

    cout << "First solution: " << solve(input, false) << endl;
    cout << "Second solution: " << solve(input, true) << endl;
    return 0;
}
