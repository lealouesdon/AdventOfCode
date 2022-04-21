#include "../source_code/day_two.cpp"
#include <stdlib.h>
#include <iostream>
#include <ratio>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream testFile("../source_code/inputs/day_two.txt");    
    string line;

    Length completeSize;
    while(getline(testFile, line)){
        Present p;
        replace(line.begin(), line.end(), 'x', ' ');
        stringstream ss(line);
        ss >> p.height >> p.length >> p.width;
        std::cout << p.wrapping_paper_calculator() << std::endl;
        completeSize += p.wrapping_paper_calculator();
        std::cout << "New size " << completeSize << std::endl;
    }
    
    std::cout << "Needed size : "<< completeSize << std::endl;
}