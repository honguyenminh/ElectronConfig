//C++11
//TODO: add exceptions about relative rule
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

//I'll be using ushort, 11562 is the max anyway right?
using ushort = unsigned short int;

struct ElectronContainer {
    //static uint count;
    vector<char> subShell;
    vector<ushort> shell, subShellElec;

    //ElectronContainer() {
    //    count = 0;
    //}

    ushort size() {
        return shell.size();
    }
};

bool IsDigit(const string &str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}
//Function to handle the calculating from peak of line.
ElectronContainer subCalculate(ushort i, ushort j, ushort& n, ElectronContainer container) {
    //List of subshell, but it's a string
    string jAlias = "spdfghiklmnoqrtuvwxyz";
    while (j >= 1) {
        //Add the subshell name (1s, 3d, 6d,...) to the output first
        container.shell.insert(container.shell.end(), i);
        container.subShell.insert(container.subShell.end(), jAlias[j-1]);
        //Maximum electron held by a subshell (s,p,d,...) is 4j - 2
        ushort max = 4 * j - 2;
        //If n is bigger than the subshell's max electron, add max to that shell
        if (n > max) {
            n = n - max;
            container.subShellElec.insert(container.subShellElec.end(), max);
        } else {
            //Else, when n = or < than max electron, add just n, makes it 0, then return.
            container.subShellElec.insert(container.subShellElec.end(), n);
            n = 0;
            return container;
        }
        // Put the TEMPORARY layer "cursor" down to the left.
        i++; j--;
    }

    return container;
}


int main(int argc, char *argv[]) {
    bool isSorted = true;   //True = will sort the result; false = won't, just push everything to stdout

    //Arguments handler. Really basic one.
    if (argc == 1) {
        cout << "No argument provided.\nUse --help or -h for more information.\n";
        return -1;
    }
    else if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0)) {
        cout << "ElectronConfig - A command line utilities for calculating electron config of a given element\n";
        cout << "Usage: " << argv[0] << " <number of electron>\n";
        cout << "Whereas <number of electron> is... self-explanatory.\n";
        cout << "The range of <number of electron> is n > 0 and n < 12704.\nWhy? Because the English alphabets stop at z.\n\n";
        cout << "I wasted 2 hours on this, so hope you enjoy it as much as I didn't making this algorithm\n";
        cout << "GitHub: Did I forgot to put the link here again?\n"; //TODO: add the github link
        return 0;
    }
    else if ((strcmp(argv[1], "-e") == 0) || (strcmp(argv[1], "--energy-sorted") == 0)) {
        isSorted = false;
        argv[1] = argv[2];
    }
    //If argument is number only, default behaviour: Sorted output

    //Check if argument inputted is a number
    if ( (argv[1] == nullptr) || !( IsDigit(argv[1]) ) ) {
        cout << "Error: Invalid input\n";
        return 1;
    }
    //Get the n value (number of electrons) from argv
    ushort n = stoi(argv[1]);
    //Check for upper boundary. 11562 is the maximum with the subshell being z
    if ((n > 11562) || (n < 1)) {
        cout << "Error: Invalid input or non-existence element\n";
        return 0;
    }

    //Main algorithm
    ElectronContainer container;
    //i represents the shell (1, 2, 3, 4,...) and j represents the subshell (s, p, d, f,...)
    ushort i = 1, j = 1;

    while (n > 0) {
        //If the start of line is the outermost, call the calculate func then increase the shell count
        if (j == i) {
            container = subCalculate(i, j, n, container);
            i++;
        } else {
            //Else increase the subshell count instead
            container = subCalculate(i, j, n, container);
            j++;
        }
    }

    //If -e switch is used, sort the thing
    //TODO
    if (isSorted) {
    }

    //Return stuff
    for (ushort f = 0; f < container.size(); f++) {
        cout << container.shell[f] << container.subShell[f] << container.subShellElec[f] << " ";
    }
    cout << endl; return 0;
}