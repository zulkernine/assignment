#include <bits/stdc++.h>
#include "utils/lexicalAnalyser.cpp"
#include "utils/clrParser.cpp"
#include "utils/symbolTableGenerator.cpp"

using namespace std;

int main()
{
    CLR1Parser cp;
    try
    {
        cp = CLR1Parser("cfg.txt");
        cout << "Grammar read ... building item set" << endl;
        cout << "Item set built ... generating parsing table" << endl;
        cout << "Parsing table generated" << endl;
    }
    catch (exception e)
    {
        cout << "Oops! error occured\n";
        return 0;
    }

    LexicalAnalyser la;
    try
    {
        la = LexicalAnalyser("regex/lexicalRegex.txt");
        cout << "Lexical analyser built\n\n";
    }
    catch (exception e)
    {
        cout << "Oops! error occured\n";
        return 0;
    }

    string sourceFile;
    string lexicalOutpuFilename = "output/lexicalOutput.txt", semanticFileName = "output/semanticItermediateOutput.txt";
    cout << "Enter source file name: ";
    cin >> sourceFile;
    la.scan(sourceFile, lexicalOutpuFilename);
    cp.parse(lexicalOutpuFilename);
    bool success = cp.parse(lexicalOutpuFilename);
    if (success)
    {
        LexicalAnalyser sa = LexicalAnalyser("regex/semanticRegex.txt");
        sa.scan(sourceFile, semanticFileName);
        SymbolTableGenerator sal;
        sal.scan(semanticFileName);
    }
}
