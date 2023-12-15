#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std;

int main()
{
    string line;
    ifstream file("Day5Input.txt");

    // get the seeds values
    std::getline(file, line);

    size_t colon = line.find(':') + 1;
    line = line.substr(colon);
    boost::trim(line);

    std::vector<std::string> seeds;
    boost::split(seeds, line, boost::is_any_of(" "), boost::token_compress_on);

    long long lowest_location = 10000000000;

    for (int i = 0; i < seeds.size(); i++)
    {
        long long seed = stoll(seeds[i]);
        long long source = seed;
        bool should_continue = false;

        while (std::getline(file, line))
        {
            // skip the spacing, to just get the map values
            if (line.empty())
            {
                should_continue = false;
                std::getline(file, line);
                std::getline(file, line);
            }

            // skip the rest of the entries in the map
            // if a value has already been found.
            // resets when line is empty (new map).
            if (should_continue) { continue; }

            vector<string> line_properties;
            boost::split(line_properties, line, boost::is_any_of(" "));

            long long dest = stoll(line_properties[0]);
            long long source_start = stoll(line_properties[1]);
            long long range = stoll(line_properties[2]);

            if (source <= source_start + range && source >= source_start)
            {
                long long difference = dest - source_start;
                source += difference;

                should_continue = true;
            }
        }

        file.clear();
        file.seekg(0);
        std::getline(file, line);

        lowest_location = min(lowest_location, source);
    }

    cout<<lowest_location<<endl;
}