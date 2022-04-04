#include <iostream>
#include <vector>

using namespace std;
using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    int current = 0;
    int i = 0;
    int num = 0;
    stops.push_back(dist);

    /*for (auto x : stops) {
        cout << x << endl;
    }*/

    while (current != dist) {
        while (stops.at(i)-current <= tank) {
            if (i < stops.size()-1) {
                i++;
            }
            else {
                return num;
            }
        }
        current = stops.at(i-1);
        i--;
        num++;
        //cout << "Car currently at " << stops.at(i) << endl;
    }
    return 0;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    int return_val = 0;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> stops.at(i);
        if (i >= 1) {
            if (stops.at(i)-stops.at(i-1) > m) {
                return_val = -1;
            }
        }
    }
    if (d - stops.at(stops.size()-1) > m) {
        return_val = -1;
    }

    if (d < m) {
        cout << 0;
        return 0;
    }

    if (return_val != -1) {
        cout << compute_min_refills(d, m, stops) << "\n";
    }
    else {
        cout << -1;
    }

    return 0;
}
