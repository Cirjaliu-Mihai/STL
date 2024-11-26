#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
struct doctor {
    string nume;
    string specializare;
    int nr_probleme;
    vector<string> probleme_rezolvate;
    int ore;
    doctor()
    {
        ore = 8;
        nr_probleme = 0;
    };
};
struct pacient {
    string problema;
    string specializare;
    int durata;
    int prioritate;
    bool operator<(const pacient& p)const
    {
        return this->prioritate < p.prioritate;
    }
};
int main()
{
    ifstream inFile("input3.txt");
    ofstream outFile("output3.txt");
    priority_queue<pacient> pacienti;
    int no_problems, no_doctors;
    string name, speciality;
    inFile >> no_problems;
    for (int i = 0; i < no_problems; i++)
    {
        pacient p;
        inFile >> p.problema >> p.specializare >> p.durata >> p.prioritate;
        pacienti.push(p);
    }

    inFile >> no_doctors;
    vector<doctor> doctori;
    for (int i = 0; i < no_doctors; i++)
    {
        doctor d;
        inFile >> d.nume >> d.specializare;
        doctori.push_back(d);
    }
    for (int i = 0; i < no_problems; i++)
    {
        pacient p;
        p = pacienti.top();
        //cout << p.problema<<" "<<p.specializare<<"\n";
        bool gasit = 0;
        int index = 0;
        while (index<no_doctors)
        {
            if (doctori[index].specializare == p.specializare && p.durata <= doctori[index].ore)
            {
                gasit = 1;
                doctori[index].nr_probleme++;
                //cout << doctori[index].nr_probleme;
                doctori[index].ore -= p.durata;
                doctori[index].probleme_rezolvate.emplace_back(p.problema);
                break;
            }
            index++;
        }
        pacienti.pop();
    }
    for (auto itr:doctori)
    {
        if (itr.nr_probleme != 0)
        {
            outFile << itr.nume << " " << itr.nr_probleme << " ";
            for (auto itr2 : itr.probleme_rezolvate)
            {
                outFile << itr2<<" ";
            }
            outFile << "\n";
        }
    }

    return 0;
}