#include <bits/stdc++.h>

using namespace std;

class Grammar
{
public:
    vector<string> non_terminals;
    vector<string> terminals;
    unordered_map<string, vector<vector<string>>> productions;
    string start_symbol;

public:
    Grammar() {}

    Grammar(string file_name)
    {
        try
        {
            FILE *fp = fopen(file_name.c_str(), "r");
            string curr_str, curr_lhs;
            vector<string> curr_col_str;
            vector<vector<string>> curr_rhs;
            int segment_no = 0;
            while (!feof(fp))
            {
                char ch = getc(fp);
                switch (ch)
                {
                case '#':
                    curr_str.clear();
                    curr_lhs.clear();
                    curr_col_str.clear();
                    curr_rhs.clear();
                    segment_no++;
                    break;
                case '\n':
                    if (curr_str.empty())
                        continue;
                    if (segment_no == 1)
                        non_terminals.push_back(curr_str);
                    else if (segment_no == 2)
                        terminals.push_back(curr_str);
                    else if (segment_no == 3)
                    {
                        curr_col_str.push_back(curr_str);
                        curr_rhs.push_back(curr_col_str);
                        productions[curr_lhs] = curr_rhs;
                        curr_col_str.clear();
                        curr_rhs.clear();
                    }
                    else if (segment_no == 4)
                        start_symbol = curr_str;
                    curr_str.clear();
                    break;
                case '@':
                    if (segment_no == 3)
                    {
                        curr_lhs = curr_str;
                        curr_str.clear();
                    }
                    break;
                case ' ':
                    if (segment_no == 3)
                    {
                        curr_col_str.push_back(curr_str);
                        curr_str.clear();
                    }
                    break;
                case '|':
                    if (segment_no == 1)
                    {
                        non_terminals.push_back(curr_str);
                        curr_str.clear();
                    }
                    else if (segment_no == 2)
                    {
                        terminals.push_back(curr_str);
                        curr_str.clear();
                    }
                    if (segment_no == 3)
                    {
                        curr_col_str.push_back(curr_str);
                        curr_rhs.push_back(curr_col_str);
                        curr_str.clear();
                        curr_col_str.clear();
                    }
                    break;
                default:
                    curr_str.insert(curr_str.end(), ch);
                    break;
                }
            }
            fclose(fp);
        }
        catch (exception e)
        {
            cout << "Failed to build the grammar\n";
        }
    }

    void printGrammar()
    {
        cout << "The Grammar is -----\n";
    }

    bool isNonTerminal(string s)
    {
        for (string x : non_terminals)
        {
            if (x == s)
                return true;
        }
        return false;
    }

    bool isTerminal(string s)
    {
        for (string x : terminals)
        {
            if (x == s)
                return true;
        }
        return false;
    }

    friend class CLR1Parser;
};
