#include <bits/stdc++.h>
#include "firstsetbuilder.cpp"

using namespace std;

class EdgeInfo
{
public:
    int from;
    int to;
    string symbol;

public:
    EdgeInfo() {}

    EdgeInfo(int f, int t, string s)
    {
        from = f;
        to = t;
        symbol = s;
    }
};

class ProductionLookahead
{
public:
    string lhs;
    vector<string> rhs;
    int index;
    unordered_set<string> look_ahead;

public:
    ProductionLookahead()
    {
        index = 0;
    }

    ProductionLookahead(string nt, vector<string> prod, int ix, unordered_set<string> la)
    {
        lhs = nt; //lhs of production
        rhs = prod; //rhs of production
        index = ix; // position of dot
        look_ahead = la;
    }

    // compares two production rules with lookaheads
    bool is_equal(ProductionLookahead pl2)
    {
        if (lhs != pl2.lhs)
            return false;
        for (int i = 0; i < rhs.size(); i++)
        {
            if (rhs[i] != pl2.rhs[i])
                return false;
        }
        if (index != pl2.index)
            return false;

        for (string curr : look_ahead)
        {
            if (pl2.look_ahead.find(curr) == pl2.look_ahead.end())
                return false;
        }
        return true;
    }

    // compares two production rules not considering lookaheads
    bool core_equal(ProductionLookahead pl2)
    {
        if (lhs != pl2.lhs)
            return false;
        for (int i = 0; i < rhs.size(); i++)
        {
            if (rhs[i] != pl2.rhs[i])
                return false;
        }
        if (index != pl2.index)
            return false;
        return true;
    }

    // appending to the lookahead unordered set
    void add_look_ahead(unordered_set<string> la)
    {
        for (string curr : la)
        {
            look_ahead.insert(curr);
        }
    }

    // compares two lookaheads
    bool inclusive_look_ahead(ProductionLookahead pl2)
    {
        for (string curr : pl2.look_ahead)
        {
            if (look_ahead.find(curr) == look_ahead.end())
                return false;
        }
        return true;
    }
};

class Item
{
public:
    int node; // item number
    vector<ProductionLookahead> prods; //stores the production rules in an item

public:
    Item()
    {
        node = 0;
    }

    Item(int n, vector<ProductionLookahead> pl, Grammar g)
    {
        node = n;
        FirstSetBuilder fsb = FirstSetBuilder(g);

        // insert all the productions with lookaheads into the item
        for (ProductionLookahead curr : pl)
        {
            prods.push_back(curr);
        }
        int curr_index = 0;

        // Closure set building
        while (curr_index < prods.size())
        {
            string curr_pointed_nt;
            if (prods[curr_index].index < prods[curr_index].rhs.size()) // if not yet final item
                curr_pointed_nt = prods[curr_index].rhs[prods[curr_index].index];
            else
            {
                curr_index++;
                continue;
            }

            vector<string> alpha = vector<string>(); // stores the rhs of dot
            
            for (int i = prods[curr_index].index + 1; i < prods[curr_index].rhs.size(); i++)
            {
                alpha.push_back(prods[curr_index].rhs[i]);
            }
            unordered_set<string> first_set = prods[curr_index].look_ahead;

            for (vector<string> rhs : g.productions[curr_pointed_nt])
            {
                unordered_set<string> first_set_curr;
                if (!alpha.empty())
                {
                    first_set_curr = fsb.getFirstOf(g, alpha);
                }

                if ((first_set_curr.find("ε") != first_set_curr.end()) || alpha.empty())
                {
                    for (string curr : first_set)
                    {
                        first_set_curr.insert(curr);
                        first_set_curr.erase("ε");
                    }
                }
                ProductionLookahead temp = ProductionLookahead(curr_pointed_nt, rhs, 0, first_set_curr);
                bool flag = false;
                for (ProductionLookahead pl : prods)
                {
                    if (pl.core_equal(temp) && pl.inclusive_look_ahead(temp))
                    {
                        flag = true;
                        break;
                    }
                }
                if (!flag)
                    prods.push_back(temp);
            }
            curr_index++;
        }
        vector<ProductionLookahead> dummy_prod = vector<ProductionLookahead>();
        for (ProductionLookahead pl1 : prods)
        {
            ProductionLookahead temp = pl1;
            for (ProductionLookahead pl2 : prods)
            {
                if (pl1.core_equal(pl2))
                {
                    temp.add_look_ahead(pl2.look_ahead);
                }
            }
            bool flag = false;
            for (ProductionLookahead pl3 : dummy_prod)
            {
                if (pl3.is_equal(temp))
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                dummy_prod.push_back(temp);
            }
        }
        prods = dummy_prod;
    }

    void print_item(ofstream &of)
    {
        of << "Item No. : " << node << " -----\n";
        for (ProductionLookahead pl : prods)
        {
            of << pl.lhs << " -> ";
            for (int i = 0; i < pl.rhs.size(); i++)
            {
                if (i == pl.index)
                    of << ". ";
                of << pl.rhs[i] << " ";
            }
            of << "\tlookahead : ";
            for (string curr : pl.look_ahead)
            {
                of << curr << " ";
            }
            of << "\n";
        }
    }

    bool is_equal(Item i2)
    {
        if (prods.size() != i2.prods.size())
            return false;
        for (ProductionLookahead pl1 : prods)
        {
            ProductionLookahead temp = pl1;
            bool flag = false;
            for (ProductionLookahead pl2 : i2.prods)
            {
                if (pl1.is_equal(pl2))
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                return false;
            }
        }
        return true;
    }

    bool go_to(vector<ProductionLookahead> &result, string x)
    {
        bool flag = false;
        for (ProductionLookahead pl : prods)
        {
            ProductionLookahead temp = pl;
            if (pl.index < pl.rhs.size() && pl.rhs[pl.index] == x)
            {
                flag = true;
                temp.index += 1;
                result.push_back(temp);
            }
        }
        return flag;
    }
};

class ItemSet
{
public:
    vector<Item> items;
    vector<EdgeInfo> edge_list;
    string augmented_start_symbol;

public:
    ItemSet() {}

    bool contain_item(Item i2)
    {
        for (Item curr : items)
        {
            if (curr.is_equal(i2))
                return true;
        }
        return false;
    }

    int find_index(Item i2)
    {
        int index = -1;
        for (Item curr : items)
        {
            index++;
            if (curr.is_equal(i2))
                return index;
        }
        return index;
    }

    ItemSet(Grammar g)
    {
        unordered_set<string> la;
        la.insert("$");
        vector<string> prod;
        prod.push_back(g.start_symbol);
        augmented_start_symbol = g.start_symbol + "\'";
        ProductionLookahead pl = ProductionLookahead(augmented_start_symbol, prod, 0, la);
        vector<ProductionLookahead> pl_list;
        pl_list.push_back(pl);

        int item_no = 0;
        Item curr = Item(item_no, pl_list, g);
        item_no++;
        items.push_back(curr);
        int curr_index = 0;
        while (curr_index < items.size())
        {
            for (string nt : g.non_terminals)
            {
                vector<ProductionLookahead> result;
                if (items[curr_index].go_to(result, nt))
                {
                    Item temp = Item(item_no, result, g);
                    if (!contain_item(temp))
                    {
                        items.push_back(temp);
                        edge_list.push_back(EdgeInfo(items[curr_index].node, item_no, nt));
                        item_no++;
                    }
                    else
                    {
                        edge_list.push_back(EdgeInfo(items[curr_index].node, find_index(temp), nt));
                    }
                }
            }

            for (string t : g.terminals)
            {
                vector<ProductionLookahead> result;
                if (items[curr_index].go_to(result, t))
                {
                    Item temp = Item(item_no, result, g);
                    if (!contain_item(temp))
                    {
                        items.push_back(temp);
                        edge_list.push_back(EdgeInfo(items[curr_index].node, item_no, t));
                        item_no++;
                    }
                    else
                    {
                        edge_list.push_back(EdgeInfo(items[curr_index].node, find_index(temp), t));
                    }
                }
            }

            curr_index++;
        }

        print_item_set("output/itemSet.txt");
    }

    void print_item_set(string file_name)
    {
        ofstream of(file_name);
        if (!of.is_open())
        {
            cout << "Couldn't open file : " << file_name << "\n";
            return;
        }
        for (Item curr : items)
        {
            of << "\n";
            curr.print_item(of);
        }

        of << "\nEdge List -----\n";
        of << "\t"
           << "From"
           << "\t"
           << "To"
           << "\t"
           << "On symbol"
           << "\n";
        for (EdgeInfo ei : edge_list)
        {
            of << "\t" << ei.from << "\t" << ei.to << "\t" << ei.symbol << "\n";
        }

        of.close();
    }
};
