#include <bits/stdc++.h>

using namespace std;

class FirstSetBuilder
{
public:
    unordered_map<string, unordered_set<string>> firstSet;
    unordered_map<string, bool> firstSetBuilt;

public:
    FirstSetBuilder(Grammar G)
    {
        for (string terminal : G.terminals)
        {
            firstSet[terminal].insert(terminal);
        }
        firstSet["ε"].insert("ε");
        firstSetBuilt["ε"] = true;

        firstSet["$"].insert("$");
        firstSetBuilt["$"] = true;

        for (string nonterminal : G.non_terminals)
        {
            buildFirstSet(G, nonterminal);
        }
        displayFirstSet("output/firstSet.txt");
    }

    void buildFirstSet(Grammar G, string nonterminal)
    {
        if (G.productions.find(nonterminal) == G.productions.end())
            return;
        for (vector<string> prod : G.productions[nonterminal])
        {
            if (prod[0] == nonterminal)
            {
                continue;
            }

            for (string token : prod)
            {
                if (!firstSetBuilt[token])
                    buildFirstSet(G, token);
                for (string rhs : firstSet[token])
                {
                    firstSet[nonterminal].insert(rhs);
                }
                if (firstSet[token].find("ε") == firstSet[token].end())
                {
                    firstSet[nonterminal].erase("ε");
                    break;
                }
            }
        }
        firstSetBuilt[nonterminal] = true;
    }

    void displayFirstSet(string file_name)
    {
        ofstream of(file_name);
        if (!of.is_open())
        {
            cout << "Couldn't open file : " << file_name << "\n";
            return;
        }

        of << "First Set of terminals and non-terminals------\n";
        for (auto itr : firstSet)
        {
            of << itr.first << " : ";
            for (string s : itr.second)
            {
                of << s << ", ";
            }
            of << "\n";
        }
    }

    unordered_set<string> getFirstOf(Grammar G, vector<string> alpha)
    {
        unordered_set<string> result = unordered_set<string>();
        for (int i = 0; i < alpha.size(); i++)
        {
            if (!firstSetBuilt[alpha[i]])
                buildFirstSet(G, alpha[i]);
            for (string rhs : firstSet[alpha[i]])
            {
                result.insert(rhs);
            }
            if (firstSet[alpha[i]].find("ε") == firstSet[alpha[i]].end())
            {
                result.erase("ε");
                break;
            }
        }
        return result;
    }
};