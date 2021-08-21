//
// implement required test program here:
// ...

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;
#include <stdlib.h>

#include "solver.h"

/* Typedef templates to avoid typing long lines */
typedef vector<int> vint;
typedef vint::iterator vintiter;
typedef pair<int, int> pint;

int parseoutint(ifstream &ifs) {
    int ret = 0; // Init parsed int value to error
    string buff; // Using string class as a buffer may be slower than char[], but I don't have to make any assumptions about line/buffer length 
    if(getline(ifs, buff)) {
        ret = atoi(buff.c_str()); // I could use stringstream to parse out data, but it's only one int per line, so atoi will do it more efficiently
    } else {
        cerr << __FILE__ << ':' << __LINE__ << " -> Error: failed to read line at " << ifs.tellg() << " position" << endl;
    }
    return ret; 
}

int main(int argc, char **argv) {
    vint viratings;
    pint pistops;
    int err = 1, /* Init err to error */
        routes, stops, rating, i, j;
    if(argc != 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
    } else {
	const char * const cfn = argv[1];
        ifstream ifs(cfn); 
        if(ifs.is_open()) {
            routes = parseoutint(ifs);
            if(routes > 0) {
                for(i = 1; i <= routes; ++i) {
                    stops = parseoutint(ifs);
                    if(stops > 0) {
                        viratings.clear();
                        viratings.reserve(stops - 1);
                        for(j = 1; j < stops; ++j) {
                            rating = parseoutint(ifs);
                            if(rating) {
                                viratings.push_back(rating);
                            } else {
                                cerr << __FILE__ << ':' << __LINE__ << " -> Error: " << cfn
                                    << " input file contains zero rating for a part of route "
                                    << i << ", between bus stops " << j << " and " << j + 1 << endl;
                                break; // since data is corrupted break out from inner loop
                            }
                        }
                        if(j == stops) { // don't run solver if inner loop ended prematurely
                            solver<vintiter, vint::value_type>(viratings.begin(), viratings.end(), pistops);
                            cout << "route " << i << ": ";
                            if(pistops.first != pistops.second) {
                                cout << "cycle between stops " << pistops.first << " and " << pistops.second; 
                            } else {
                                cout << "no cycling";
                            }
                            cout << endl;
                        } else {
                            break; // since data is corrupted break out from outer loop also
                        }
                    } else {
                        cerr << __FILE__ << ':' << __LINE__ << " -> Error: " << cfn << " input file contains " << stops
                            << " stops for route " << i << ", positive non-zero number of stops was expected" << endl;
                        break;
                    }
                    if(j == stops && i - 1 == routes) {
                        err = 0; // since neither of the loops ended prematurely set err to success
                    }
                }
            } else {
                cerr << __FILE__ << ':' << __LINE__ << " -> Error: " << cfn << " input file contains " << routes
                    << " routes, while positive non-zero number of routes was expected" << endl;
            }
            ifs.close();
        } else {
            cerr << __FILE__ << ':' << __LINE__ << " -> Error: Can't open " << cfn << " input file" << endl;
        }
    }
    return err;
}
