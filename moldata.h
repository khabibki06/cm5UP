#ifndef MolData_H
#define MolData_H
#include <iostream>
#include <regex>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <atomdata.h>
#include <math.h>
using namespace std;

class MolData
{
public:

    MolData();
    vector <tuple <int, string, double, double, double, double> > orcaData;
    std::vector<std::string> split(std::string const &input);
    bool readOrcaLog(string fileName);
    vector <tuple <int, string, double, double, double, double> > getOrcaData();
    double distance(int idx1, int idx2);
    vector <double> getCoor(int idx);
    double getCM5Charge(int idx);
    double getCharge(int idx);
    string getAtomName(int idx);
    string printResult();
    void writeCsv(string fileNameOut);
    string getBaseNameFile(string fileName);
    string writeXYZFile(string fileName);
private:
    AtomData atomdata;
};

#endif // MolData_H
