#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "grammar.cpp"
#include "itemsetbuilder.cpp"

using namespace std;

class TableItem
{
public:
    string op_type;
    int new_state_no;
    pair<string, vector<string>> reducing_rule;

public:
    TableItem() {}

    TableItem(string op, int n, pair<string, vector<string>> rr)
    {
        op_type = op;
        new_state_no = n;
        reducing_rule = rr;
    }

    TableItem(string op, int n)
    {
        op_type = op;
        new_state_no = n;
    }

    TableItem(string op, pair<string, vector<string>> rr)
    {
        op_type = op;
        reducing_rule = rr;
    }
};

class CLR1Parser
{
    Grammar G;
    ItemSet item_set;
    vector<unordered_map<string, TableItem>> parsing_table;

public:
    CLR1Parser() {}

    CLR1Parser(string file_name)
    {
        G = Grammar(file_name);
        item_set = ItemSet(G);
        parsing_table = vector<unordered_map<string, TableItem>>(item_set.items.size());

        for (EdgeInfo ei : item_set.edge_list)
        {
            if (G.isNonTerminal(ei.symbol))
                parsing_table[ei.from].insert(pair<string, TableItem>(ei.symbol, TableItem("goto", ei.to)));
            else
                parsing_table[ei.from].insert(pair<string, TableItem>(ei.symbol, TableItem("shift", ei.to)));
        }

        for (Item item : item_set.items)
        {
            for (ProductionLookahead pl : item.prods)
            {
                if (pl.index == pl.rhs.size())
                {
                    for (string la : pl.look_ahead)
                    {
                        parsing_table[item.node].insert(pair<string, TableItem>(la, TableItem("reduce", pair<string, vector<string>>(pl.lhs, pl.rhs))));
                    }
                }
            }
        }

        print_parsing_table("output/parsingTable.txt");
    }

    void print_parsing_table(string file_name)
    {
        ofstream of(file_name);
        if (!of.is_open())
        {
            cout << "Couldn't open file : " << file_name << "\n";
            return;
        }
        int index = 0;
        for (unordered_map<string, TableItem> temp : parsing_table)
        {
            of << "\n\nTable entry for Item " << index << " -----\n";
            of << "GOTO Entries\n";
            for (string t : G.terminals)
            {
                if (temp.find(t) != temp.end())
                {
                    TableItem te = temp[t];
                    of << "On symbol : " << t << " ";
                    of << "Op name : " << te.op_type;
                    if (te.op_type == "shift")
                    {
                        of << " goto : " << te.new_state_no;
                    }
                    else if (te.op_type == "reduce")
                    {
                        of << " Reduce : " << te.reducing_rule.first << " -> ";
                        for (string s : te.reducing_rule.second)
                        {
                            of << s << " ";
                        }
                    }
                    of << "\n";
                }
            }

            of << "ACTION Entries\n";
            for (string t : G.non_terminals)
            {
                if (temp.find(t) != temp.end())
                {
                    TableItem te = temp[t];
                    of << "On symbol : " << t << " ";
                    of << "Op name : " << te.op_type;
                    if (te.op_type == "goto")
                    {
                        of << " goto : " << te.new_state_no;
                    }
                    of << "\n";
                }
            }
            index++;
        }

        of.close();
    }

    bool parse(string file_name)
    {
        ifstream inp_file(file_name);
        vector<string> tokens;
        string token;
        stack<int> state_stack;
        stack<string> pruning_stack;
        state_stack.push(0);
        bool flag = false;

        while (getline(inp_file, token, ' '))
        {
            if (!token.empty())
                tokens.push_back(token);
        }
        tokens.push_back("$");

        stack<pair<string, vector<string>>> applied_rules;
        int curr_index = 0;
        while (curr_index < tokens.size())
        {
            if (!pruning_stack.empty() && pruning_stack.top() == item_set.augmented_start_symbol && tokens[curr_index] == "$")
            {
                flag = true;
                break;
            }

            if (parsing_table[state_stack.top()].find(tokens[curr_index]) == parsing_table[state_stack.top()].end())
            {
                cout << "Top : " << state_stack.top() << " Current token : " << tokens[curr_index] << " Can't find stack top symbol for current token\n";
                break;
            }
            else
            {
                TableItem te = parsing_table[state_stack.top()][tokens[curr_index]];
                if (te.op_type == "shift")
                {
                    state_stack.push(te.new_state_no);
                    pruning_stack.push(tokens[curr_index]);
                    curr_index++;
                }
                else if (te.op_type == "reduce")
                {
                    applied_rules.push(te.reducing_rule);

                    int size = te.reducing_rule.second.size();
                    for (int i = 0; i < size; i++)
                    {
                        pruning_stack.pop();
                        state_stack.pop();
                    }
                    pruning_stack.push(te.reducing_rule.first);
                    if (te.reducing_rule.first == item_set.augmented_start_symbol)
                        continue;

                    if (parsing_table[state_stack.top()].find(pruning_stack.top()) == parsing_table[state_stack.top()].end())
                    {
                        break;
                    }
                    else
                    {
                        state_stack.push(parsing_table[state_stack.top()][pruning_stack.top()].new_state_no);
                    }
                }
            }
        }

        if (flag)
        {
            cout << "\nInput is syntactically correct and belongs to this language\n\n";
            print_derivation("output/derivation.txt", applied_rules);
        }
        else
        {
            cout << "nInput is syntactically not correct and also does not nbelongs to this language\n\n";
        }
        return flag;
    }

    void print_derivation(string file_name, stack<pair<string, vector<string>>> applied_rules)
    {
        ofstream of(file_name);
        if (!of.is_open())
        {
            cout << "Couldn't open file : " << file_name << "\n";
            return;
        }

        of << "Derivation steps for input file-----\n\n";

        pair<string, vector<string>> curr_rule = applied_rules.top();
        of << curr_rule.first;
        vector<string> rhs = curr_rule.second;
        print_rhs(of, rhs);
        pair<string, vector<string>> prev_rule = curr_rule;
        applied_rules.pop();
        while (!applied_rules.empty())
        {
            of << "     ";
            curr_rule = applied_rules.top();
            vector<string> new_rhs;
            int index = rhs.size() - 1;
            while (index >= 0)
            {
                if (rhs[index] == curr_rule.first)
                    break;
                index--;
            }
            for (int i = 0; i < index; i++)
            {
                new_rhs.push_back(rhs[i]);
            }
            for (string curr : curr_rule.second)
            {
                new_rhs.push_back(curr);
            }
            for (int i = index + 1; i < rhs.size(); i++)
            {
                new_rhs.push_back(rhs[i]);
            }
            rhs = new_rhs;
            print_rhs(of, rhs);
            applied_rules.pop();
        }
    }

    void print_rhs(ofstream &of, vector<string> rhs)
    {
        of << " => ";
        for (string curr : rhs)
        {
            of << curr << " ";
        }
        of << "\n";
    }
};
