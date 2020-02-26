#include "MolData.h"

MolData::MolData()
{

}

std::vector<std::string> MolData::split(std::string const &input) {
    std::istringstream buffer(input);
    std::vector<std::string> ret((std::istream_iterator<std::string>(buffer)),
                                 std::istream_iterator<std::string>());
    return ret;
}


bool MolData::readOrcaLog(string fileName)
{
    vector <string> atomindex;
    vector <string> atomindexcoor;
    vector <tuple <string, double>> charge;
    vector <tuple <double, double, double>> coor;
    string result;
    int i_coor = 0;
    int i_charge = 0;
    int index = 0;
    bool coorFound = 0, chargeFound = 0;
    ifstream inFile(fileName);
    for (std::string line; getline(inFile,line);)
    {
        if (line.find("CARTESIAN COORDINATES (ANGSTROEM)") != string::npos)
        {
            i_coor = 1;
            coorFound = 1;
        }
        if (line.find("CARTESIAN COORDINATES (A.U.)") != string::npos)
        {
            i_coor = 0;
            index = 0;
        }
        if (line.find("HIRSHFELD ANALYSIS") != string::npos)
        {
            i_charge = 1;
            chargeFound = 1;
        }
        if (line.find("TIMINGS") != string::npos)
            i_charge = 0;
        if (i_coor == 1)
        {
            vector <string> temp = split(line);
            if (temp.size() == 4)
            {
                std::vector<string>::iterator it = std::find(atomindexcoor.begin(), atomindexcoor.end(), to_string(index));
                if (it == atomindexcoor.end())
                {
                   atomindexcoor.push_back(to_string(index));
                   coor.push_back(make_tuple(stof(temp[1]), stof(temp[2]), stof(temp[3])));
                }
                else
                {
                    int distance = std::distance(atomindexcoor.begin(),it);
                    coor.at(distance) = make_tuple(stof(temp[1]), stof(temp[2]), stof(temp[3]));
                }
                index++;
            }
        }
        if (i_charge == 1)
        {
            vector <string> temp = split(line);
            if (temp.size() == 4)
            {
                std::vector<string>::iterator it = std::find(atomindex.begin(), atomindex.end(), temp[0]);
                if (it == atomindex.end())
                {
                   atomindex.push_back(temp[0]);
                   charge.push_back(make_tuple(temp[1], stof(temp[2])));
                }
                else
                {
                    int distance = std::distance(atomindex.begin(),it);
                    charge.at(distance) = make_tuple(temp[1], stof(temp[2]));
                }
            }
        }
    }
    if (!coorFound)
    {
        cout << "atom coordinate is not found. please check your ORCA log file" << endl;
        return 0;
    }
    if (!chargeFound)
    {
        cout << "Hirshfeld charge is not found. Please add these lines to your ORCA input file and rerun simulation" << endl << endl;
        cout << "%output \n   Print[ P_Hirshfeld] 1 \nend" << endl;
        return 0;
    }
    int size = atomindex.size();
    for (int i = 0; i< size ; i++)
    {
        orcaData.push_back(make_tuple(stoi(atomindex[i]), get <0> (charge[i]), get <0> (coor[i]), get <1> (coor[i]), get <2> (coor[i]), get <1> (charge[i])));
    }
    return 1;
}

vector <tuple <int, string, double, double, double, double> > MolData::getOrcaData()
{
    return orcaData;
}

vector <double> MolData::getCoor(int idx)
{
    int size = orcaData.size();
    tuple <int, string, double, double, double, double> data;
    vector <double> result;
    for (int i = 0; i < size;i++)
    {
        data = orcaData.at(i);
        if (idx == get <0>(data) )
        {
            result.push_back(get <2>(data));
            result.push_back(get <3>(data));
            result.push_back(get <4>(data));
            return result;
        }
    }
}
double MolData::distance(int idx1, int idx2)
{
    double sum = 0.0;
    if (idx1 == idx2)
        return sum;
    vector <double> atom1, atom2;
    atom1 = getCoor(idx1);
    atom2 = getCoor(idx2);

    for (int i = 0; i < 3; i++)
    {
        double d = atom1.at(i)-atom2.at(i);
        sum += d*d;
    }
    return sqrt(sum);
}

double MolData::getCharge(int idx)
{
    int size = orcaData.size();
    tuple <int, string, double, double, double, double> data;
    vector <double> result;
    for (int i = 0; i < size;i++)
    {
        data = orcaData.at(i);
        if (idx == get <0>(data) )
        {
            return get <5>(data);
        }
    }
}
double MolData::getCM5Charge(int idx)
{
    double qCM5 = 0;
     qCM5 = getCharge(idx);
    int numatom = orcaData.size();
    string atomname1 = getAtomName(idx);
    for (int i = 0; i < numatom; i++)
    {
        if (idx != i)
        {
            string atomname2 = getAtomName(i);
            double Tkk = atomdata.getDeltaDValue(atomname1,atomname2);
            double Bkk = exp(-2.474 * (distance(idx, i) - atomdata.getRadius(atomname1) - atomdata.getRadius(atomname2)));
            qCM5 += Tkk * Bkk;
        }
    }
    return qCM5;
}

string MolData::getAtomName(int idx)
{
    return get <1> (orcaData.at(idx));
}

string MolData::printResult()
{
    string result;
    result += "######################################################################\n";
    result += "CM5UP is a program to calculate CM5 charge group from orca output file\n";
    result += "The Program is created by Khabib Khumaini, Department of Chemistry, \n Universitas Pertamina, Indonesia.";
    result += "The result also can be available in csv file";
    result += "\n";
    result += "The calculation is based on method in (Marenich, Jerome, Cramer, & Truhlar, 2012)\n";
    result += "\n";
    result += "It also produces 1.2*CM5 charge which was reported compatible\n with OPLS FF : (Vilseck, Tirado-Rives, & Jorgensen, 2014)\n";
    result += "\n It can freely downloaded and distributed for any purposes\n";
    result += "######################################################################\n";
    result += "##########################  THE RESULT  ##############################\n";
    result += "######################################################################\n";
    result += "index  element  x     y     z    Hirshfeld_Charge  cm5charge     1.2*CM5charge \n";
    int numatom = orcaData.size();
    double cm5;
    for  (int i = 0; i < numatom; i++)
    {
        cm5 = getCM5Charge(get <0> (orcaData[i]));
        result += to_string(get <0> (orcaData[i])) +  "    ";
        result += get <1> (orcaData[i]) +  "    ";
        result += to_string(get <2> (orcaData[i])) +  " ";
        result += to_string(get <3> (orcaData[i])) +  " ";
        result += to_string(get <4> (orcaData[i])) +  " ";
        result += to_string(get <5> (orcaData[i]))  +  " ";
        result += to_string(cm5) +  " ";
        result += to_string(cm5*1.2) + "\n";
    }
    return result;
}

void MolData::writeCsv(string fileNameOut)
{
    string result;
    int numatom = orcaData.size();
    double cm5;
    result = "index;element;x;y;z;Hirshfeld_Charge;cm5charge;1.2*CM5charge \n";
    for  (int i = 0; i < numatom;  i++)
    {

        cm5 = getCM5Charge(get <0> (orcaData[i]));
        result += to_string(get <0> (orcaData[i])) +  ";";
        result += get <1> (orcaData[i]) +  ";";
        result += to_string(get <2> (orcaData[i])) +  ";";
        result += to_string(get <3> (orcaData[i])) +  ";";
        result += to_string(get <4> (orcaData[i])) +  ";";
        result += to_string(get <5> (orcaData[i]))  +  ";";
        result += to_string(cm5) +  ";";
        result += to_string(cm5*1.2) + "\n";
    }

    ofstream out(fileNameOut);
    out << result;
    out.close();
}

string MolData::getBaseNameFile(string fileName)
{
    size_t lastindex = fileName.find_last_of(".");
    fileName.find_last_of(".");
    if (lastindex != -1)
        return fileName.substr(0, lastindex);
    else
        return fileName;
}

string MolData::writeXYZFile(string fileName)
{
    string result;
    int numatom = orcaData.size();
    result += to_string(numatom) + " \n\n";
    for  (int i = 0; i < numatom;  i++)
    {
        result += get <1> (orcaData[i]) +  "    ";
        result += to_string(get <2> (orcaData[i])) +  " ";
        result += to_string(get <3> (orcaData[i])) +  " ";
        result += to_string(get <4> (orcaData[i]));
        if (i != numatom -1)
            result += "\n";
    }
    ofstream out(fileName);
    out << result;
    out.close();
}
