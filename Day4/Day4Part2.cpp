#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <regex>

using namespace std;

int main()
{
    string line;
    ifstream file("Day4Input.txt");

    int sum = 0; 
    map<int, int> card_copies;

    if (file.is_open())
    {
        int index = 0;

        while (getline(file, line))
        {
            card_copies[index] = 1;
            index++;
        }

        file.clear();
        file.seekg(0);

        while (getline(file, line))
        {
            int matches = 0;

            size_t colon_index = line.find(":");
            string card_info = line.substr(0, colon_index);
            int card_index = stoi(regex_replace(card_info, regex("[^0-9]*([0-9]+).*"), "$1")) - 1;

            std::vector<std::string> card_results;
            boost::split(card_results, line.substr(colon_index + 2), boost::is_any_of("|"));
            
            string winning_numbers_str = card_results[0];
            string own_numbers_str = card_results[1];
            // trim the start spacing off
            boost::trim(winning_numbers_str);
            boost::trim(own_numbers_str);

            std::vector<std::string> own_numbers;
            // token_compress_on is necessary, as we don't want two spaces in a row
            // (before numbers with only 1 digit) to affect the result.
            boost::split(own_numbers, own_numbers_str, boost::is_any_of(" "), boost::token_compress_on);

            std::vector<std::string> winning_numbers;
            boost::split(winning_numbers, winning_numbers_str, boost::is_any_of(" "), boost::token_compress_on);

            for (int i = 0; i < own_numbers.size(); i++)
            {
                if (std::find(winning_numbers.begin(), winning_numbers.end(), own_numbers[i]) != winning_numbers.end())
                {
                    matches += 1;
                }
            }

            for (int i = 1; i <= matches; i++)
            {
                int next_line_index = i + card_index;  

                card_copies[next_line_index] += card_copies[card_index];
            }

        }

        file.close();
    }

    for (map<int, int>::iterator it = card_copies.begin(); it != card_copies.end(); it++)
    {
        sum += it->second;
    }

    cout<<sum<<endl;
}