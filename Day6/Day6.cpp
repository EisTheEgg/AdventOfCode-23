#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;

int main()
{
    string line;

    int margin_of_error = 1;

    std::vector<string> race_lengths;
    std::vector<string> currrent_reconds;

    ifstream file("Day6Input.txt");

    getline(file, line);
    boost::split(race_lengths, line.substr(line.find_first_of("0123456789")), boost::is_any_of(" "), boost::token_compress_on);

    getline(file, line);
    boost::split(currrent_reconds, line.substr(line.find_first_of("0123456789")), boost::is_any_of(" "), boost::token_compress_on);

    for (int i = 0; i < race_lengths.size(); i++)
    {
        int length = stoi(race_lengths[i]);
        int record = stoi(currrent_reconds[i]);
        int records_beaten = 0;

        for (int button_hold = 0; button_hold < length; button_hold++)
        {
            int remaining_seconds = length - button_hold;
            int distance_traveled = remaining_seconds * button_hold;

            if (distance_traveled > record)
            {
                // we've beaten the record
                records_beaten++;
            }
        }

        margin_of_error *= records_beaten;
    }

    cout<<margin_of_error<<endl;
}