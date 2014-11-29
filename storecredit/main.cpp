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
        int credit;
        iss >> credit;
        
        std::getline(infile, line);
        std::stringstream mss(line);
        int m;
        mss >> m;
        
        std::vector<int> x;
        
        std::getline(infile, line);
        std::stringstream xss(line);
        for (int i = 0; i != m; ++i) {
            int tmp;
            xss >> tmp;
            x.push_back(tmp);
            if (xss.peek() == ' ')
                xss.ignore();
        }
        
        int result1 = 0, result2 = 0;
        for (int i = 0; i != m; ++i) {
            for (int j = 0; j != m; ++j) {
                if (i == j)
                    continue;
                if (credit == x[i] + x[j]) {
                    result1 = min(i, j) == i ? i : j;
                    result2 = result1 == i ? j : i;
                    result1++;
                    result2++;
                    break;
                }
            }
        }
        //std::cout << "Credit: " << credit << std::endl;
        //            std::cout << "Choice is: " << x[result1-1] << " and " << x[result2-1] << std::endl;
        std::cout << "Case #" << (i + 1) << ": " << result1 << " " << result2 << std::endl;
    }
}
