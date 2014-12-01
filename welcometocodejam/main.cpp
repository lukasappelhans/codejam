#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cstring>

const int BASE = 10000;

using namespace std;

//Map starting point, number of characters left => number of occurrences
long long ways[510][30];

long long findOccurrences(int searchIndex, int stlength, const std::string &sT, int startIndex, int linelength, const std::string &line)
{
    if (searchIndex == stlength)
        return 1;
    long long result = 0;
    for (int i = startIndex; i != linelength; ++i) {
        if (ways[i][stlength - searchIndex - 1] != -1) {
            result += ways[i][stlength - searchIndex - 1];
        } else if (line[i] == sT[searchIndex]) {
            long long returned = findOccurrences(searchIndex + 1, stlength, sT, i + 1, linelength, line);
            ways[i][stlength - searchIndex - 1] = returned;
            result += returned;
        }
    }
    return result%BASE;
}

int main( int argc, const char* argv[] )
{
    std::ifstream infile("C-large-practice.in");
    string line;
    std::getline(infile, line);
    std::stringstream ss(line);
    int number;
    ss >> number;
    
    const std::string searchTerm = "welcome to code jam";
    for (int i = 0; i != number; ++i) {
        getline(infile, line);
        
        memset(ways, -1, sizeof(ways[0][0]) * 500 * 30);
    
        long long counts = findOccurrences(0, searchTerm.length(), searchTerm, 0, line.length(), line);
        
        std::cout << "Case #" << (i + 1) << ": " << (counts % 10000) / 1000 << (counts % 1000) / 100 << (counts % 100) / 10 << (counts % 10) << std::endl;
    }
}
