#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int generate_random_number() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    uniform_int_distribution<int> distribution(1, 1000);

    int roll = distribution(generator);

    // cout << "The answer is " << roll << ".\n";
    return roll;
}

int get_number() {
    int n = 0;
    cout << "Enter an integer in the range of 1 to 1000.\n";
    cin >> n;

    while (n < 1 || n > 1000) {
        // If ostream& operator>>(ostream& , T&) fails the extraction of
        // formatted data (such as integer, double, float, ...),
        // stream.fail() will be true and thus
        // !stream will evaluate to true too.
        if(!cin) {
            cout << "You entered value with wrong type.\n";
        }
        else {
            cout << "The number you entered is out of range.\n";
        }

        cout << "Enter an integer in the range of 1 to 1000.\n";
        cin.clear(); // unset fail bit
        // It is important to ignore the rest of the line,
        // since operator>> won't extract any data from the stream anymore
        // as it is in a wrong format.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> n;
    }

    cout << "You entered " << n << ".\n";
    return n;

}

int main() {
    int target_number = generate_random_number();
    int number_entered = get_number();

    while(number_entered != target_number) {
        if(number_entered < target_number) {
            cout << "The number is bigger than you guessed.\n";
        }
        else if(number_entered > target_number) {
            cout << "The number is smaller than you guessed.\n";
        }
        number_entered = get_number();
    }

    cout << "Bingo! The answer is " << target_number << "." << endl;
    return 0;
}
