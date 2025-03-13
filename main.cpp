#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
struct pacient {
    string idproblema, specializare;
    int oraSosire, durata, prioritate;
    bool operator<(const pacient& p)const
    {
        if (oraSosire == p.oraSosire)
        {
            return prioritate > p.prioritate;
        }
        return oraSosire < p.oraSosire;
    }
};
int main()
{
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");
    set<pacient> pacienti;
    map<string, vector<string>>doctori;
    map<string, int> ora_curenta_doctor;
    map <string, vector<pair<string, int>>>pacienti_ajutati;
    int no_problems, no_doctors;
    string name, speciality;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        pacient p;
        inFile >> p.idproblema >> p.specializare >> p.oraSosire >> p.durata >> p.prioritate;
        pacienti.insert(p);

    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        int nr_specializari;
        inFile >> name>>nr_specializari;
        while (nr_specializari--)
        {
            inFile >> speciality;
            doctori[name].emplace_back(speciality);
        }
    }
    for (int i = 0; i < no_problems; i++)
    {
        pacient p = *pacienti.begin();
        pacienti.erase(pacienti.begin());
        for (auto& itr : doctori)
        {
            string nume_doctor = itr.first;
            if (find(doctori[nume_doctor].begin(), doctori[nume_doctor].end(), p.specializare) != doctori[nume_doctor].end())
            {
                if (ora_curenta_doctor[nume_doctor] <= p.oraSosire && ora_curenta_doctor[nume_doctor] + p.durata <= 17)
                {
                    ora_curenta_doctor[nume_doctor] = p.oraSosire + p.durata;
                    pacienti_ajutati[nume_doctor].emplace_back(make_pair(p.idproblema, p.oraSosire));
                    break;
                }
            }

        }
    }
    for (auto& itr : pacienti_ajutati)
    {
        string nume_doctor = itr.first;
        outFile << nume_doctor <<" " << itr.second.size()<<" ";
        for (auto& rezolvate : itr.second)
        {
            outFile << rezolvate.first << " " << rezolvate.second << " ";
        }
        outFile << "\n";
    }

    return 0;
}