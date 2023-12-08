#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 <folder_name>"
  exit 1
fi

folder_name="$1"
mkdir "$folder_name"

makefile_content=$(cat <<EOL
CXX = g++
CXXFLAGS = -Wall -std=c++17 -g
TARGET = $folder_name
SRC = Solution.cpp
OBJ = \$(SRC:.cpp=.o)

all: \$(TARGET)

\$(TARGET): \$(OBJ)
	\$(CXX) \$(CXXFLAGS) -o \$@ \$^

%.o: %.cpp
	\$(CXX) \$(CXXFLAGS) -c -o \$@ \$<

clean:
	rm -f \$(TARGET) \$(OBJ)

.PHONY: all clean
EOL
)

echo "$makefile_content" > "$folder_name/Makefile"

cpp_content=$(cat <<EOL
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
int main(){
fo;fi;
return 0;}
EOL
)

echo "$cpp_content" > "$folder_name/Solution.cpp"

touch "$folder_name/input.txt"

echo "Folder '$folder_name' created with Makefile, Solution.cpp, and input.txt."
