//C++11
//TODO: add exceptions about relative rule
//TODO: add elements dictionary
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
using ushort = unsigned short int;


struct ElectronContainer {
    vector<char> subshell;
    vector<ushort> shell, subshellElec;
    ushort shellCount = 0;
    char lastSubShell = ' ';

    void erase(ushort i) {
        shell.erase(shell.begin() + i);
        subshell.erase(subshell.begin() + i);
        subshellElec.erase(subshellElec.begin() + i);
    }
};

bool IsDigit(const string &str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

//Function to handle the calculating from peak of line
ElectronContainer subCalculate(ushort i, ushort j, ushort& n, ElectronContainer container) {
    string jAlias = "spdfghiklmnoqrtuvwxyz"; //List of subshells
    while (j >= 1) {
        //Add the subshell name (1s, 3d, 6d,...) to the output first
        container.shell.push_back(i);
        container.subshell.push_back(jAlias[j - 1]);
        ushort max = 4 * j - 2; //Max electron in a subshell

        if (n > max) {
            n = n - max;
            container.subshellElec.push_back(max);
        } else {
            container.subshellElec.push_back(n);
            n = 0; container.lastSubShell = jAlias[j - 1];
            return container;
        }
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

    ushort n = stoi(argv[1]);
    //Check for upper boundary. 11562 is the maximum with the subshell being z
    if ((n > 11562) || (n < 1)) {
        cout << "Error: Invalid input or non-existence element\n";
        return 0;
    }

    //Main algorithm
    ElectronContainer container;
    {
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
    }

    //TODO
    if (isSorted) {
        ElectronContainer tempContainer; tempContainer.shellCount = 1;
        tempContainer.lastSubShell = container.lastSubShell;

        while (!container.shell.empty()) {
            for (ushort i = 0; i < (ushort)container.shell.size(); i++) {
                if (container.shell[i] == tempContainer.shellCount) {
                    //Clean code incoming :)
                    tempContainer.shell.push_back(container.shell[i]);
                    tempContainer.subshell.push_back(container.subshell[i]);
                    tempContainer.subshellElec.push_back(container.subshellElec[i]);
                    container.erase(i);
                    i--;
                }
            }

            tempContainer.shellCount++;
        }

        container = tempContainer;
    } else {
        for (ushort i = 0; i < (ushort)container.shell.size(); i++) {
            if (container.shell[i] > container.shellCount) {
                container.shellCount = container.shell[i];
            }
        }
    }

    //Return stuff
    for (ushort i = 0; i < (ushort)container.shell.size(); i++) {
        cout << container.shell[i] << container.subshell[i] << container.subshellElec[i] << " ";
    }
    cout << endl << "Last subshell is " << container.lastSubShell << endl;
    cout << "Shell count is " << container.shellCount << endl;
    return 0;
}