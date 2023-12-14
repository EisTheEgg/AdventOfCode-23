#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>

using namespace std;

int main()
{
    string line;

    ifstream file("Day4Input.txt");

    int sum = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            int card_worth = 1;
            int doubles = 0;

            size_t colon_index = line.find(":");
            //vector<string> game_results = custom_split(line.substr(colon_index + 2), "|", 1);

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
                    doubles += 1;
                }
            }

            if (doubles > 0)
            {
                for (int i = 0; i < doubles - 1; i++)
                {
                    card_worth *= 2;
                }
            }
            else
            {
                card_worth = 0;
            }

            sum += card_worth;
        }
    }

    cout<<sum<<endl;
}