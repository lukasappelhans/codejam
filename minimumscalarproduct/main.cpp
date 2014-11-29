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
    std::ifstream infile("A-large-practice.in");
    string line;
    std::getline(infile, line);
    std::stringstream iss(line);
    int n;
    iss >> n;
    
    for (int i = 0; i != n; ++i) {
        std::getline(infile, line);
        std::stringstream iss(line);
        int m;
        iss >> m;
        
        std::list<long long> x;
        std::list<long long> y;
        
        std::getline(infile, line);
        std::stringstream xss(line);
        for (int i = 0; i != m; ++i) {
            long long tmp;
            xss >> tmp;
            x.push_back(tmp);
            if (xss.peek() == ' ')
                xss.ignore();
        }
        
        std::getline(infile, line);
        std::stringstream yss(line);
        for (int i = 0; i != m; ++i) {
            int tmp;
            yss >> tmp;
            y.push_back(tmp);
            if (yss.peek() == ' ')
                yss.ignore();
        }
        
        x.sort();
        y.sort(greater<long long>());
        
        long long result = 0;
        auto xit = x.begin();
        auto yit = y.begin();
        auto xend = x.end();
        for (; xit != xend; ++xit, ++yit) {
            result += (*xit) * (*yit);
        }
        
        std::cout << "Case #" << (i + 1) << ": " << result << std::endl;
    }
}
