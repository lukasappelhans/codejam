#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <list>

using namespace std;

int main( int argc, const char* argv[] )
{
    std::ifstream infile("D-large-practice.in");
    string line;
    std::getline(infile, line);
    std::stringstream ss(line);
    int number;
    ss >> number;
    
    for (int i = 0; i != number; ++i) { 
        getline(infile, line);
        std::stringstream mss(line);
        int m;
        mss >> m;
        const int DIM = 8;
        char figures[DIM][DIM];
        memset(figures, 'Z', sizeof(figures[0][0]) * DIM * DIM);
        for (int i = 0; i != m; ++i) {
            getline(infile, line);
            char dimone = line[0];
            char dimtwo = line[1];
            char type = line[3];
        
            int dimoneNumber = dimone - 'A';
            int dimtwoNumber = dimtwo - '0' - 1;
            figures[dimtwoNumber][dimoneNumber] = type;
            
            //std::cout << dimoneNumber << "/" << dimtwoNumber << ": " << type << std::endl;
        }

        long long total = 0;
        for (int i = 0; i != DIM; ++i) {
            for (int j = 0; j != DIM; ++j) {
                char type = figures[i][j];
                long long totalOld = total;
                //Only the K and P parts are working and tested
                switch (type) {
                case 'K':
                    total += (i + 1 < DIM) && figures[i + 1][j] != 'Z';
                    total += (i + 1 < DIM) && (j + 1 < DIM) && figures[i + 1][j + 1] != 'Z';
                    total += (j + 1 < DIM) && figures[i][j + 1] != 'Z';
                    total += (i - 1 >= 0) && (j + 1 < DIM) && figures[i - 1][j + 1] != 'Z';
                    total += (i - 1 >= 0) && figures[i - 1][j] != 'Z';
                    total += (i - 1 >= 0) && (j - 1 >= 0) && figures[i - 1][j - 1] != 'Z';
                    total += (j - 1 >= 0) && figures[i][j - 1] != 'Z';
                    total += (j - 1 >= 0) && (i + 1 < DIM) && figures[i + 1][j - 1] != 'Z';
                    break;
                case 'Q':
                    //Test straight X line
                    for (int k = 0; k != DIM; ++k) {
                        if (k == i)
                            continue;
                        if (figures[k][j] != 'Z') {
                            total++;
                            if (k < i)
                                k = i;
                            else
                                break;
                        }
                    }
                    for (int k = 0, l = 0; k != DIM; ++k, ++l) {
                        if (k == i)
                            continue;
                        if (figures[k][l] != 'Z') {
                            total++;
                            if (k < i) {
                                k = i;
                                l = j;
                            } else
                                break;
                        }
                    }              
                    for (int l = 0; l != DIM; ++l) {
                        if (l == j)
                            continue;
                        if (figures[i][l] != 'Z') {
                            total++;
                            if (l < j)
                                l = j;
                            else
                                break;
                        }
                    }
                    for (int k = 0, l = DIM - 1; k != DIM; ++k, --l) {
                        if (k == i)
                            continue;
                        if (figures[k][l] != 'Z') {
                            total++;
                            if (k < i) {
                                k = i;
                                l = j;
                            } else
                                break;
                        }
                    }   
                    break;
                case 'R':
                    for (int k = 0; k != DIM; ++k) {
                        if (k == i)
                            continue;
                        if (figures[k][j] != 'Z') {
                            total++;
                            if (k < i)
                                k = i;
                            else
                                break;
                        }
                    }
                    for (int l = 0; l != DIM; ++l) {
                        if (l == j)
                            continue;
                        if (figures[i][l] != 'Z') {
                            total++;
                            if (l < j)
                                l = j;
                            else
                                break;
                        }
                    }
                    break;
                case 'B':
                    for (int k = 0, l = 0; k != DIM; ++k, ++l) {
                        if (k == i)
                            continue;
                        if (figures[k][l] != 'Z') {
                            total++;
                            if (k < i) {
                                k = i;
                                l = j;
                            } else
                                break;
                        }
                    }                     
                    for (int k = 0, l = DIM - 1; k != DIM; ++k, --l) {
                        if (k == i)
                            continue;
                        if (figures[k][l] != 'Z') {
                            total++;
                            if (k < i) {
                                k = i;
                                l = j;
                            } else
                                break;
                        }
                    }   
                    break;
                case 'N': 
                    total += (i - 2 >= 0) && (j - 1 >= 0) && figures[i - 2][j - 1] != 'Z'; 
                    total += (i - 2 >= 0) && (j + 1 < DIM) && figures[i - 2][j + 1] != 'Z'; 
                    total += (i + 2 < DIM) && (j - 1 >= 0) && figures[i + 2][j - 1] != 'Z'; 
                    total += (i + 2 < DIM) && (j + 1 < DIM) && figures[i + 2][j + 1] != 'Z'; 
                    total += (i - 1 >= 0) && (j - 2 >= 0) && figures[i - 1][j - 2] != 'Z';
                    total += (i - 1 >= 0) && (j + 2 < DIM) && figures[i - 1][j + 2] != 'Z';
                    total += (i + 1 < DIM) && (j - 2 >= 0) && figures[i + 1][j - 2] != 'Z';
                    total += (i + 1 < DIM) && (j + 2 < DIM) && figures[i + 1][j + 2] != 'Z';
                    break;
                case 'P':
                    total += (i + 1 < DIM) && (j + 1 < DIM) && figures[i + 1][j + 1] != 'Z'; 
                    total += (i - 1 >= 0) && (j + 1 < DIM) && figures[i - 1][j + 1] != 'Z'; 
                    break;
                };
                //if (total - totalOld > 0)
                //    std::cout << i << "/" << j << " kills " << total - totalOld << std::endl;
            }
        }
        std::cout << "Case #" << (i + 1) << ": " << total << std::endl;
    }
}


