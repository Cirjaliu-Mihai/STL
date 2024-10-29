#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

int main()
{
    ifstream inFile("input.txt");

    int no_problems, no_doctors;
    string name, speciality;
    vector<string> names, specialities;
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        names.push_back(name);
        specialities.push_back(speciality);
        //cout << name << ' ' << speciality << '\n';
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        for (auto k=begin(specialities);k!=end(specialities);k++)
        {
            if (*k == speciality)
            {
                int d = distance(begin(specialities), k);
                specialities[d] = "Acceptat";
                cout << "s a gasit la poz " << d << endl;
            }
                
        }
        //cout << name << ' ' << speciality << '\n';
    }
    for (auto i = begin(specialities); i != end(specialities); i++)
    {
        int d = distance(begin(specialities), i);
        if (*i == "Acceptat")
        {
            cout << names[d] << " " << *i << "\n";
        }
        else
        {
            cout << names[d] << " Respins\n";
        }
    }
    return 0;
}