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
#include <moldata.h>

using namespace std;

int main(int argc, char **argv)
{
    AtomData atomdata;
    MolData moldata;
    vector <tuple <int, string, double, double, double, double> > orcaCharge;
    string option;
    string filenameIn;
    string filenameOut;
    char *program_name= argv[0];
    if (argc < 2)
    {
        cout << "Syntax: cm5UP -i orcaoutputfilename -o outputname" << endl;
        cout << "-i orcaoutputfilename : (mandatory) orca log file" << endl;
        cout << "-o outfilename : (optional)  base name the output csv and xyz file" << endl;
        cout << "                  If it is not given. The basename will be extracted from orcaoutputfilename" << endl;
        cout << "The source code and manual: https://github.com/khabibki06/cm5UP " << endl;
        return 1;
    }
    for (int i = 1; i < argc;i++)
    {
        option = argv[i];
        if ((option == "-i") && (argc > (i+1)))
        {
            filenameIn = argv[i+1];
        }
        if ((option == "-o") && (argc > (i+1)))
        {
            filenameOut = argv[i+1];
        }
    }
    if (filenameIn.empty())
    {
        cout << "This program requires orca log file as input" << endl;
        cout << "Syntax: cm5UP -i orcaoutputfilename -o outputname" << endl;
        cout << "-i orcaoutputfilename : (mandatory) orca log file" << endl;
        cout << "-o outfilename : (optional)  base name the output csv and xyz file" << endl;
        cout << "                  If it is not given. The basename will be extracted from orcaoutputfilename" << endl;
        cout << "The source code and manual: https://github.com/khabibki06/cm5UP " << endl;
        return 1;
    }
    if (filenameOut.empty())
        filenameOut = moldata.getBaseNameFile(filenameIn) + ".csv";
    if (!moldata.readOrcaLog(filenameIn))
        return 1;
    cout << moldata.printResult();
    cout << endl << "Write csv output file" << endl;
    moldata.writeCsv(filenameOut);
    cout << endl << "Write XYZ File " << endl;
    moldata.writeXYZFile(moldata.getBaseNameFile(filenameOut) + ".xyz");
    return 0;
}

