#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

using namespace std;

vector<string> custom_split(string str, string tokenizer, int spacing)
{
    vector<string> split_strings;

    int start_index = 0;
    size_t last_index = 0;

    while (last_index != string::npos)
    {
        last_index = str.find(tokenizer, start_index);
        string round_results = str.substr(start_index, last_index - start_index);
        split_strings.push_back(round_results);

        start_index = last_index + spacing;
    }

    return split_strings;
}

int main() 
{
    int power_sum = 0;
    string line;

    ifstream file("Day2Input.txt");

    if (file.is_open())
    {
        while (getline(file, line))
        {
            map<string, int> smallest_values_possible;
            smallest_values_possible["red"] = 0;
            smallest_values_possible["green"] = 0;
            smallest_values_possible["blue"] = 0;

            size_t column_index = line.find(":");
            string game_results = line.substr(column_index + 2);

            vector<string> rounds = custom_split(game_results, ";", 2);

            for (int i = 0; i < rounds.size(); i++)
            {
                string round = rounds[i];

                vector<string> throws = custom_split(round, ",", 2);

                for (int j = 0; j < throws.size(); j++)
                {
                    vector<string> properties = custom_split(throws[j], " ", 1);
                    int amount = stoi(properties[0]);
                    string colour = properties[1];

                    if (smallest_values_possible[colour] < amount)
                    {
                        smallest_values_possible[colour] = amount;
                    }
                }
            }

            int power = smallest_values_possible["red"] * smallest_values_possible["green"] * smallest_values_possible["blue"];
            power_sum += power;
        }

        file.close();
    }    

    std::cout<<power_sum<<endl;
}