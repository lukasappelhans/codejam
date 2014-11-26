#include <iostream>
#include <fstream>
#include <unordered_map>
#include <math.h>

using namespace std;

long long calculate(const string &input)
{
    unordered_map<char, unsigned int> map;
    
    unordered_map<char, unsigned int>::iterator end = map.end();
    
    unsigned int base = 0;
    for (int i = 0; i != input.length(); ++i) {
        if (map.find(input[i]) == end) {
            map[input[i]] = base;
            base++;
        }
    }
    if (base < 2)
        base = 2;
    
    long long result = 0;
    for (int i = 0; i != input.length(); ++i) {
        unsigned int replace = map[input[i]];
        if (replace == 1)
            replace = 0;
        else if (replace == 0)
            replace = 1;
        //result += replace * pow(base, (input.length() - i - 1));
        result = result*base + replace;
    }
    return result;
}

int main( int argc, const char* argv[] )
{
    std::ifstream infile("A-large-practice.in");
    int number;
    infile >> number;
    
    int caseNr = 1;
    string input;
    while (infile >> input)
    {
        long long result = calculate(input);
        std::cout << "Case #" << caseNr << ": " << result << std::endl;
        caseNr++;
    }
}
