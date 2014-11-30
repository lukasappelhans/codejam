#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;


int main( int argc, const char* argv[] )
{
    std::ifstream infile("A-small-practice.in");
    string line;
    std::getline(infile, line);
    std::stringstream ss(line);
    int number;
    ss >> number;
    
    for (int i = 0; i != number; ++i) {
        getline(infile, line);
        stringstream nss(line);
        int n;
        nss >> n;
        
        std::vector<int> a;
        std::vector<int> b;
        
        for (int i = 0; i != n; ++i) {
            getline(infile, line);
            stringstream liness(line);
            int one, two;
            liness >> one;
            liness.ignore();//Space
            liness >> two;
            a.push_back(one);
            b.push_back(two);
        }
        
        int intersections = 0;
        for (int i = 0; i != a.size(); ++i) {
            for (int j = i + 1; j != b.size(); ++j) {
                intersections += (a[i] > a[j]) != (b[i] > b[j]);
            }
        }
        std::cout << "Case #" << (i + 1) << ": " << intersections << std::endl;
    }
}
