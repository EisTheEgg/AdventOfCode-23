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

struct Mapping 
{
    long long start;
    long long end;
    long long dest_start;
};

int main()
{
    string line;

    ifstream file("Day5Input.txt");

    if (file.is_open())
    {
        getline(file, line);

        vector<string> seed_data;
        boost::split(seed_data, line.substr(line.find(':') + 2), boost::is_any_of(" "));

        vector<vector<Mapping>> mappings;
        vector<Mapping> current_mappings;
        vector<Mapping> seeds;

        for (int i = 0; i < seed_data.size(); i+=2)
        {
            long long source = stoll(seed_data[i]);
            long long range = stoll(seed_data[i + 1]);

            Mapping seed_mapping;
            seed_mapping.start = source;
            seed_mapping.end = source + range;

            seeds.push_back(seed_mapping);
        }

        getline(file, line); // skip whitespace
        getline(file, line); // skip whitespace

        while (getline(file, line))
        {
            if (line.empty())
            {
                mappings.push_back(current_mappings);
                current_mappings.clear();

                getline(file, line);
                continue;
            }

            vector<string> entry_properties;
            boost::split(entry_properties, line, boost::is_any_of(" "));

            Mapping entry;
            entry.dest_start = stoll(entry_properties[0]);
            entry.start = stoll(entry_properties[1]);
            entry.end = entry.start + stoll(entry_properties[2]);

            current_mappings.push_back(entry);
        }

        mappings.push_back(current_mappings); // insert last set of maps

        for (int map_index = 0; map_index < mappings.size(); map_index++)
        {
            vector<Mapping> entries = mappings[map_index];
            vector<Mapping> new_seeds;

            for (int seed_index = 0; seed_index < seeds.size(); seed_index++)
            {
                Mapping seed = seeds[seed_index];
                bool found_new = false;

                for (int entry_index = 0; entry_index < entries.size(); entry_index++)
                {
                    Mapping entry = entries[entry_index];

                    long long max_start = max(entry.start, seed.start);
                    long long min_end = min(entry.end, seed.end);

                    if (min_end > max_start)
                    {
                        long long difference = entry.dest_start - entry.start;

                        Mapping new_mapping;
                        new_mapping.start = max_start + difference;
                        new_mapping.end = min_end + difference;

                        new_seeds.push_back(new_mapping);
                        found_new = true;

                        // should also create a new range from seed start - entry start
                        if (seed.start < max_start)
                        {
                            seeds.push_back(Mapping { seed.start, max_start });
                        }

                        // and from the end of range to the end of seed
                        if (min_end < seed.end)
                        {
                            seeds.push_back(Mapping { min_end, seed.end });
                        }

                        break;
                    }
                }

                if (!found_new)
                {
                    new_seeds.push_back(seed);
                }
            }

            seeds = new_seeds;
        }

        long long lowest_loc = 100000000000000;

        for (int i = 0; i < seeds.size(); i++)
        {
            lowest_loc = min(lowest_loc, seeds[i].start);
        }

        cout<<lowest_loc<<endl;
    }
}