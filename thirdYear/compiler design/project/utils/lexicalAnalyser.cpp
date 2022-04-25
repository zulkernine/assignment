#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

class LexicalAnalyser
{
public:
    vector<pair<string, string>> regex_patterns;

public:
    LexicalAnalyser()
    {
        //Do nothing
    }

    LexicalAnalyser(string rif)
    {
        FILE* fp = fopen(rif.c_str(), "r");
        if (fp == NULL)
        {
            cout << "Couldn't open file : " << rif << " \n";
            return;
        }

        string curr_str;
        pair<string, string> curr_pair;
        bool is_lhs = true;
        while (!feof(fp))
        {
            char ch = getc(fp);
            switch (ch)
            {
            case ':':
                curr_pair.first = curr_str;
                is_lhs = false;
                curr_str.clear();
                break;
            case ' ':
                break;
            case '\n':
                if (is_lhs)
                {
                    if (curr_str.empty())
                        break;
                    curr_pair.first = curr_str;
                    curr_pair.second = " $0 ";
                    regex_patterns.push_back(curr_pair);
                }
                else if (!is_lhs)
                {
                    if (curr_str.empty())
                    {
                        curr_pair.second = " $0 ";
                        regex_patterns.push_back(curr_pair);
                    }
                    else
                    {
                        curr_pair.second = curr_str;
                        regex_patterns.push_back(curr_pair);
                    }
                }
                is_lhs = true;
                curr_str.clear();
                break;
            default:
                curr_str.insert(curr_str.end(), ch);
            }
        }

        fclose(fp);
    }

    bool scan(string ifl, string ofl)
    {
        ifstream fin(ifl);
        if (!fin.is_open())
        {
            cerr << "Could not open the file - \'" << ifl << "\'\n";
            return false;
        }
        ofstream fout(ofl);
        if (!fout.is_open())
        {
            cerr << "Could not open the file - \'" << ofl << "\'\n";
            return false;
        }

        for (pair<string, string> rg : regex_patterns)
        {
            // cout << "Regex : " << rg.first << "    output : " << rg.second << "\n";
        }

        // Regex Part
        vector<pair<regex, string>> all_regex;
        for (pair<string, string> rg : regex_patterns)
        {
            all_regex.push_back(pair<regex, string>(regex(rg.first), " " + rg.second + " "));
        }

        regex re_space("[\\s]+");

        // File Reading Line by Line
        string line;
        string output = "";
        while (getline(fin, line))
        {
            for (pair<regex, string> curr : all_regex)
            {
                line = regex_replace(line, curr.first, curr.second);
            }
            output += line;
        }
        output = regex_replace(output, re_space, " ");
        fout << output;

        fin.close();
        fout.close();

        return true;
    }
};
