#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
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
    map<string, int> max_values;
    max_values["red"] = 12;
    max_values["green"] = 13;
    max_values["blue"] = 14;

    int index_sum = 0;
    string line;

    ifstream file("Day2Input.txt");

    if (file.is_open())
    {
        while (getline(file, line))
        {
            bool is_legal = true;

            size_t colon_index = line.find(":");
            string game_results = line.substr(colon_index + 2);

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

                    map<string, int>::iterator max_value = max_values.find(colour);

                    if (amount > max_value->second)
                    {
                        is_legal = false;
                    }
                }
            }

            if (is_legal)
            {
                string game_info = line.substr(0, colon_index);
                int game_index = stoi(regex_replace(game_info, regex("[^0-9]*([0-9]+).*"), "$1"));
                index_sum += game_index;
            }
        }

        file.close();
    }    

    std::cout<<index_sum<<endl;
}