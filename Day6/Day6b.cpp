#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <regex>

using namespace std;

long long isolate_numbers(string line)
{
    string numbers_temp = "";

    for (int i = 0; i < line.length(); i++)
    {
        if (isdigit(line[i]))
        {
            numbers_temp += line[i];
        }
    }

    return stoll(numbers_temp);
}

int main()
{
    string line;

    ifstream file("Day6Input.txt");

    getline(file, line);
    long long length = isolate_numbers(line);
    getline(file, line);
    long long record = isolate_numbers(line);

    long long records_beaten = 0;

    for (long long button_hold = 0; button_hold < length; button_hold++)
    {
        long long remaining_seconds = length - button_hold;
        long long distance_traveled = remaining_seconds * button_hold;

        if (distance_traveled > record)
        {
            // we've beaten the record
            records_beaten++;
        }
    }

    cout<<records_beaten<<endl;
}