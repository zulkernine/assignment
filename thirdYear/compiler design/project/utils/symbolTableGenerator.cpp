#include <iostream>
#include "symbolTable.cpp"
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace std;

class SymbolTableGenerator
{
    SymTab S;
    vector<string> tokens;

public:
    void tokenize(string str)
    {
        string token;
        istringstream ss(str);
        while (ss >> token)
        {
            tokens.push_back(token);
        }
    }

    void scan(string filename)
    {
        ifstream fin(filename);
        if (!fin.is_open())
        {
            cerr << "Could not open the file - \'" << filename << "\'\n";
            return;
        }
        string str;
        getline(fin, str);
        // cout << str << "\n";
        tokenize(str);
        bool isForLoopBlockStarted = false;

        unordered_set<string> keywords = {"void", "int", "float", "(", ")", "{", "}", "main", "id", "$", ",", ";", "+", "-", "string", "<", ">", "=", "return", "\"", "<=", ">=", "==", "+=", "++", "for"};
        unordered_set<string> data_type = {"int", "float", "string"};
        unordered_set<string> bin_op = {"+", "-", "<", ">", "<=", ">=", "==", "++", "+="};

        int sz = tokens.size(), i = 0;

        // for (int i = 0; i < sz; ++i) {
        //     cout << i << " " << tokens[i] << "\n";
        // }

        cout << "Starting Semantic Analysis.\n\n";
        S.entry();
        while (i < sz)
        {

            if (tokens[i] == "int" || tokens[i] == "float" || tokens[i] == "string")
            {
                string type = tokens[i];
                if (i + 2 < sz && (tokens[i + 2] == "="))
                { // declaration
                    i++;

                    //Multiple declaration
                    while (tokens[i] != ";")
                    {
                        // insert the variable
                        S.insert(tokens[i], type);
                        i += 1;
                        if (tokens[i] != "=")
                        {
                            cout << "Not permitted symbol: " << tokens[i];
                            exit(1);
                        }
                        else
                            i++;

                        //parse the assigned value, it may be an expression
                        while (tokens[i] != "," && tokens[i] != ";")
                        {
                            // parse the literal / constant
                            if (tokens[i] == "\"")
                            { // rhs is string, parse it
                                string str = "";
                                i++;
                                while (tokens[i] != "\"")
                                {
                                    str += tokens[i++];
                                }
                                S.insert(str, "STRING_CONSTANT");
                                i++;
                            }
                            else if (isdigit(tokens[i][0]))
                            { // rhs is a number
                                S.insert(tokens[i], "NUMBER_CONSTANT");
                                i++;
                            }
                            else if (keywords.find(tokens[i]) == keywords.end())
                            { // rhs is variable
                                pair<bool, Attr> val = S.lookup(tokens[i]);
                                if (val.first == false)
                                {
                                    cerr << "[!] Undeclared identifier " << tokens[i++] << " used.\n";
                                }
                                else
                                    i++;
                            }
                            else if (bin_op.find(tokens[i]) != bin_op.end())
                            {
                                i++;
                            }
                            else
                            {
                                cout << "unecpexted symbol found: " << tokens[i] << endl;
                                exit(1);
                            }
                        }
                        if (tokens[i] == ",")
                            i++;
                    }
                    i++;
                }
                else
                    i++;
            }
            else if (tokens[i] == "for")
            {
                S.entry();
                isForLoopBlockStarted = true;
                i += 2;
            }
            else if (tokens[i] == "{")
            {
                if (isForLoopBlockStarted)
                {
                    isForLoopBlockStarted = false;
                }
                else
                {
                    S.entry();
                }
                ++i;
            }
            else if (tokens[i] == "}")
            {
                S.exit();
                ++i;
            }
            else
            {
                if (tokens[i] == "\"")
                { // rhs is string, parse it
                    string str = "";
                    i++;
                    while (tokens[i] != "\"")
                    {
                        str += tokens[i++];
                    }
                    S.insert(str, "STRING_CONSTANT");
                    i++;
                }
                else if (isdigit(tokens[i][0]))
                { // rhs is a number
                    S.insert(tokens[i], "NUMBER_CONSTANT");
                    i++;
                }
                else if (keywords.find(tokens[i]) == keywords.end())
                { // rhs is variable
                    pair<bool, Attr> val = S.lookup(tokens[i]);
                    if (val.first == false)
                    {
                        cerr << "[!] Undeclared identifier " << tokens[i++] << " used.\n";
                    }
                    else
                        i++;
                }
                else if (keywords.find(tokens[i]) != keywords.end())
                {
                    i++;
                }
                else
                {
                    cout << "unecpexted symbol found: " << tokens[i] << endl;
                    exit(1);
                }

                // pair<bool, Attr> val = S.lookup(tokens[i]);
                // if (val.first == false) {
                //     // cerr << i << "\n";
                //     cerr << "[!] Undeclared identifier " << tokens[i] << " used.\n";
                // }
                // else if (val.second.id_type == 'f') {
                //     string func_name = tokens[i];
                //     if (functionCallCheck(i, val.second, keywords) == false) {
                //         cerr << "[!] Incorrect call of function " << func_name << " .\n";
                //     }
                // }
                // ++i;
            }
        }
        S.exit();
        cout << "\nFinished Semantic Analysis.\n\n";
    }
};