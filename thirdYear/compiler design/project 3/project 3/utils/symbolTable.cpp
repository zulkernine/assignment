//bhai idhar tum symbol table structure likhna

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

class Attr
{
    int lineno;
    int level;
    string data_type;
    char id_type;                        // 'f' - functions, 'v' - variable
    vector<pair<string, string>> params; // parameters if function
public:
    Attr()
    {
    }
    Attr(string dt, char it, vector<pair<string, string>> p)
    {
        data_type = dt;
        id_type = it;
        params = p;
    }
    friend class SymTab;
    friend class SymbolTableGenerator;
};

class SymTab
{
    vector<unordered_map<string, Attr>> hashmaps;
    int currLevel;
    string ofl;

    bool checkAtLevel(string idname, int level)
    {
        if (level <= currLevel)
        {
            return (hashmaps[level].find(idname) != hashmaps[level].end());
        }
        return false;
    }

public:
    SymTab(string filename = "output/symbolTable.txt")
    {
        currLevel = -1;
        ofl = filename;
        ofstream fout(ofl, ios::out);
        fout.close();
    }
    void entry()
    {
        ++currLevel;
        hashmaps.push_back(unordered_map<string, Attr>());
    }
    void exit()
    {
        if (currLevel >= 0)
        {
            ofstream fout(ofl, ios::app);
            --currLevel;
            fout << "\n--------Exiting a block: --------\n";
            fout << "Symbol Table for this block was: \n";
            for (auto itr : hashmaps[currLevel + 1])
            {
                fout << "Id : " << itr.first << " -> Data Type : " << itr.second.data_type << " -> Type : ";
                if (itr.second.id_type == 'f')
                {
                    fout << "Function -> Parameters : ";
                    for (auto p : itr.second.params)
                    {
                        fout << "<" << p.first << ", " << p.second << ">, ";
                    }
                    fout << "\n";
                }
                else
                {
                    fout << "Variable\n";
                }
            }
            fout.close();
            hashmaps.pop_back();
        }
    }
    pair<bool, Attr> lookup(string idname)
    {
        for (int level = currLevel; level >= 0; --level)
        {
            if (checkAtLevel(idname, level))
                return {true, hashmaps[level].find(idname)->second};
        }
        return {false, Attr()};
    }
    bool insert(string idname, string type, char idtype = 'v', vector<pair<string, string>> params = vector<pair<string, string>>())
    {
        if (checkAtLevel(idname, currLevel))
        {
            cerr << "[!] Multiple Declarations. " << idname << " is already declared.\n";
            return false;
        }
        else
        {
            hashmaps[currLevel][idname] = Attr(type, idtype, params);
            // for (auto itr : hashmaps[currLevel]) {
            //     cout << itr.first << "\n";
            // }
            return true;
        }
    }
};
