#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() 
{
    const string numbers = "1234567890";
    int sum = 0;

    string line;

    ifstream file("Day1Input.txt");

    if (file.is_open()) 
    {
        while(getline(file, line)) 
        {
            size_t first = line.find_first_of(numbers);
            size_t last = line.find_last_of(numbers);

            string combination = string(1, line[first]) + string(1, line[last]);
            
            sum += stoi(combination);
        }

        file.close();
    }

    return 0;
}