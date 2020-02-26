#include "atomdata.h"

AtomData::AtomData()
{   // Dx is from (Marenich, Jerome, Cramer, & Truhlar, 2012)
    // covalent radii is from CRC Handbook of Chemistry and Physics, 94th Edition

    //atom-wise
    //format: element, atomic_number, covalent_radii, Dx
    database.push_back(make_tuple("H",1,0.32,0.0056));
    database.push_back(make_tuple("He",2,0.37,-0.1543));
    database.push_back(make_tuple("Li",3,1.30,0));
    database.push_back(make_tuple("Be",4,0.99,0.0333));
    database.push_back(make_tuple("B",5,0.84,-0.1030));
    database.push_back(make_tuple("C",6,0.75,-0.0446));
    database.push_back(make_tuple("N",7,0.71,-0.1072));
    database.push_back(make_tuple("O",8,0.64,-0.0802));
    database.push_back(make_tuple("F",9,0.84,-0.0629));
    database.push_back(make_tuple("Ne",10,0.62,-0.1088));
    database.push_back(make_tuple("Na",11,1.60,0.00184));
    database.push_back(make_tuple("Mg",12,1.40,0));
    database.push_back(make_tuple("Al",13,1.24,-0.0726));
    database.push_back(make_tuple("Si",14,1.14,-0.0790));
    database.push_back(make_tuple("P",15,1.09,-0.0756));
    database.push_back(make_tuple("S",16,1.04,-0.0565));
    database.push_back(make_tuple("Cl",17,1.00,-0.0444));
    database.push_back(make_tuple("Ar",18,1.01,-0.0767));
    database.push_back(make_tuple("K",19,2.00,0.0130));
    database.push_back(make_tuple("Ca",20,1.74,0));
    database.push_back(make_tuple("Zn",30,1.20,0));
    database.push_back(make_tuple("Ge",32,1.20,-0.0557));
    database.push_back(make_tuple("As",33,1.20,-0.0533));
    database.push_back(make_tuple("Se",34,1.18,-0.0399));
    database.push_back(make_tuple("Br",35,0.84,-0.0313));
    database.push_back(make_tuple("I",53,1.36,-0.0220));

    //atom-wise
    //format: pair, Dx
    pairwise_database.push_back(make_pair("H-C",0.0502));
    pairwise_database.push_back(make_pair("C-H",-0.0502));
    pairwise_database.push_back(make_pair("H-N",0.1747));
    pairwise_database.push_back(make_pair("N-H",-0.1747));
    pairwise_database.push_back(make_pair("H-O",0.1671));
    pairwise_database.push_back(make_pair("O-H",-0.1671));
    pairwise_database.push_back(make_pair("C-N",0.0556));
    pairwise_database.push_back(make_pair("N-C",-0.0556));
    pairwise_database.push_back(make_pair("C-O",0.0234));
    pairwise_database.push_back(make_pair("O-C",-0.0234));
    pairwise_database.push_back(make_pair("N-O",-0.0346));
    pairwise_database.push_back(make_pair("O-N",0.0346));
}

int AtomData::getAtomicNumber(string atomname)
{
    int size = database.size();
    tuple<string, int, double, double> data;
    for (int i = 0; i < size;i++)
    {
        data = database.at(i);
        if (atomname == get <0>(data) )
        {
            return get <1>(data);
        }
    }
}
double AtomData::getRadius(string atomname)
{
    int size = database.size();
    tuple<string, int, double, double> data;
    for (int i = 0; i < size;i++)
    {
        data = database.at(i);
        if (atomname == get <0>(data) )
        {
            return get <2>(data);
        }
    }
}
double AtomData::getDvalue(string atomname)
{
    int size = database.size();
    tuple<string, int, double, double> data;
    for (int i = 0; i < size;i++)
    {
        data = database.at(i);
        if (atomname == get <0>(data) )
        {
            return get <3>(data);
        }
    }
}

double AtomData::getDeltaDValue(string atomname1, string atomname2)
{
    string pairwise = atomname1 + "-" + atomname2;
    int pairwisedatabase_size = pairwise_database.size();
    for (int i = 0; i < pairwisedatabase_size; ++i) {
        if (pairwise == pairwise_database.at(i).first)
        {
         //   cout << "it's a pair wise" << endl;
            return pairwise_database.at(i).second;
        }
    }
    // not found in pair wise database
    return getDvalue(atomname1) - getDvalue(atomname2);
}
