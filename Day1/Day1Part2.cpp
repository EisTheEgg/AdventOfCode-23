#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

size_t get_first_position(string password, string searches[2])
{
    size_t first_pos = string::npos;

    for (int i = 0; i <= searches->length(); i++)
    {
        string Search = searches[i];
        size_t pos = password.find(Search);

        if (pos < first_pos || first_pos == string::npos)
        {
            first_pos = pos;
        }
    }

    return first_pos;
}

size_t get_last_position(string password, string searches[2])
{
    // This is necessary as there might be duplicates of the same letter / number
    // in the same string. If we simply used .find(), it would only
    // find the first value.

    size_t last_pos = string::npos;

    for (int i = 0; i <= searches->length(); i++)
    {
        string Search = searches[i];
        size_t pos = password.find(Search);

        while (pos != string::npos)
        {
            if (pos > last_pos || last_pos == string::npos)
            {
                last_pos = pos;
            }
            
            pos = password.find(Search, pos+1);
        }
    }
    
    return last_pos;
}

int main() 
{
    const string numbers = "1234567890";
    const string corresponding_strings[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int sum = 0;
    string line;

    ifstream file("Day1Part2Input.txt");

    if (file.is_open())
    {
        while (getline(file, line))
        {
            int first_index = 10000;
            int first_index_number;

            int last_index = 0;
            int last_index_number;

            for (int index = 1; index < 10; index++)
            {
                string number_string = to_string(index);
                string number_spelling = corresponding_strings[index - 1];

                string searches[2] = {number_string, number_spelling};
                size_t first_number_index = get_first_position(line, searches);
                size_t last_number_index = get_last_position(line, searches);

                if (first_number_index != string::npos && first_number_index < first_index)
                {
                    first_index = first_number_index;
                    first_index_number = index;
                }

                if (last_number_index != string::npos && last_number_index >= last_index)
                {
                    last_index = last_number_index;
                    last_index_number = index;
                }
            }

            string combination = to_string(first_index_number) + to_string(last_index_number);
            sum += stoi(combination);
        }
    }

    cout<<sum<<endl;     
}