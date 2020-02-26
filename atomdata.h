#ifndef ATOMDATA_H
#define ATOMDATA_H
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
using namespace std;
class AtomData
{
public:
    AtomData();
    vector <tuple<string, int, double, double>> database;
    vector <pair <string, double>> pairwise_database;
    int getAtomicNumber(string atomname);
    double getRadius(string atomname);
    double getDvalue(string atomname);
    double getDeltaDValue(string atomname1, string atomname2);

};

#endif // ATOMDATA_H
