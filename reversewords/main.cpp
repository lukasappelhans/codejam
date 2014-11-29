#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits.h>
#include <utility>
#include <list>
#include <algorithm>

using namespace std;

int main( int argc, const char* argv[] )
{
    std::ifstream infile("B-large-practice.in");
    string line;
    std::getline(infile, line);
    std::stringstream iss(line);
    int n;
    iss >> n;
    
    for (int i = 0; i != n; ++i) {
        std::getline(infile, line);
        std::list<std::string> list;
        std::istringstream buf(line);
        for (std::string token; getline(buf, token, ' '); )
            list.push_back(token);
        
        std::string output;
        auto it = list.rbegin();
        auto end = list.rend();
        for (; it != end; ++it)
            output = output + " " + (*it);
        
        std::cout << "Case #" << (i + 1) << ":" << output << std::endl;
    }
}
