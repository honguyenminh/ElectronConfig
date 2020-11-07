//TODO: BIG ONE. MAKE AN OPTION TO REARRANGE THE WHOLE RESULT INTO ORDER. MAKE. AN. OPTION. ONLY.
#include <iostream>
#include <string>
#include <cstring>

// I'll be using ushort, 12704 is the max anyway right?
using ushort = unsigned short int;

// A void function to handle the calculating from peak of line. Read the main func first
void subCalculate(ushort i, ushort j, ushort& n) {
    //List of inner layer, but it's a string
    std::string jAlias = "spdfghiklmnoqrtuvwxyz";
    while (j >= 1) {
        //Add the layer name (1s, 3d, 6d,...) to the output first
        std::cout << i << jAlias[j-1];
        //Maximum electron held by an inner layer (s,p,d,...) is 4j - 2
        ushort max = 4 * j - 2;
        //If n is bigger than inner layer's max electron, add max to that layer
        if (n > max) {
            n = n - max;
            std::cout << max << " ";
        } else {
            //Else, when n = or < than max electron, add just n, makes it 0, then return.
            std::cout << n; n = 0;
            return;
        }
        // Put the TEMPORARY layer "cursor" down to the left.
        i++; j--;
    }
}

int main(int argc, char *argv[]) {
    //Arguments handler. Really basic one.
    if (argc == 1) std::cout << "No argument provided.\nUse --help or -h for more information.\n";
    else if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0)) {
        std::cout << "ElectronConfig - A command line utilities for calculating electron config of a given element\n";
        std::cout << "Usage: <ElectronConfig> <number of electron>\n";
        std::cout << "Whereas <ElectronConfig> is the name of the executable and\n<number of electron> is self-explanatory.\n";
        std::cout << "The range of <number of electron> is n > 0 and n < 12704. Why? Because the English alphabets stop at z.\n\n";
        std::cout << "Well, to be honest, I don't think this will be useful, to anyone, but meh it's just a proof of concept.\n";
        std::cout << "I wasted 2 hours on this, so hope you enjoy it as much as I didn't making this algorithm\n";
        std::cout << "GitHub: Did I forgot to put the link here again?\n"; //TODO: add the github link here
    }
    //The actual main code
    else {
        //Get the n value (number of electrons) from argv
        ushort n = std::stoi(argv[1]);
        //Check for upper boundary. 12704 is the maximum with inner layer being z
        //TODO: add actual error handler here.
        if (n > 12704) {
            std::cout << "That element... just doesn't exist... Yet? :)\n";
            return 0;
        }
        //i represents the layer (1, 2, 3, 4,...) and j represents the inner layer (s, p, d, f,...)
        ushort i = 1, j = 1;

        while (n > 0) {
            //If the start of cross line is the outermost, call the calculate func then increase the layer count
            if (j == i) {
                subCalculate(i, j, n);
                i++;
            } else {
                //Else increase the inner layer count instead
                subCalculate(i, j, n);
                j++;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
