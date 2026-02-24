#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) {
    int sum = 0;

    if (argc == 1) {
        cout << "Please input numbers to find average.\n";
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        sum += atoi(argv[i]);
    }
    cout << "---------------------------------\n";
    cout << "Average of " << argc - 1 << " numbers = "
         << sum / (argc - 1) << endl;
    cout << "---------------------------------";
    return 0;
}
