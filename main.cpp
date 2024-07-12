#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

#include "includes/airport/simulation.h"


using namespace std;

int main(int argv, char** argc) {
    bool debug = false;
    cout<<endl<<endl<<"======================================="<<endl<<endl;
    srand(time(0));
    for (int i=0; i<20; i++){
        cout << "---------------------- [" << i << "] ---------------------------" << endl;
        simulate_airport(debug);
    }
    cout <<endl<<endl<< "========== END SIMULATION ==================" << endl;
    return 0;
}