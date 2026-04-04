#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main()
{
    string inputFileName;
    // string outputFileName;

    cout << "Enter input file name: ";
    cin >> inputFileName;

    // cout << "Enter output file name: ";
    // cin >> outputFileName;

    ifstream fin(inputFileName);
    // ofstream fout(outputFileName);

    if (!fin)
    {
        cout << "Error: could not open input file." << endl;
        return 1;
    }

     // make output file and write to it
    string base = inputFileName;
    size_t pos = base.find_last_of("/\\");
    if (pos != string::npos)
    {
        base = base.substr(pos + 1);
    }

    string outputFileName = "Output_" + base;
    ofstream fout(outputFileName);

    if (!fout)
    {
        cout << "Error: could not create output file." << endl;
        return 1;
    }

    bool printRules = true;   // switch to turn production rule printing on/off

    Lexer lexer(fin);
    Parser parser(lexer, fout, printRules);

    parser.parse();

    fin.close();
    fout.close();

    cout << "Parsing complete. Check output file: " << outputFileName << endl;

    return 0;
}
