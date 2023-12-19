#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <map>
#include <vector>

using namespace std;

struct Node
{
    string index;
    string left;
    string right;
};

int main()
{
    string line;

    ifstream file("Day8Input.txt");
    getline(file, line);
    string instructions = line;
    getline(file, line);

    map<string, Node> network;

    while (getline(file, line))
    {
        vector<string> node_properties;
        boost::split(node_properties, line, boost::is_any_of("="));

        string index = node_properties[0];
        boost::trim(index);

        string coords_string = node_properties[1];
        vector<string> coords;
        boost::split(coords, coords_string.substr(coords_string.find("(") + 1, 8), boost::is_any_of(","));
        boost::trim(coords[1]);

        network[index] = Node { index, coords[0], coords[1] };
    }

    Node current_node = network.at("AAA");
    int steps = 0;

    while (current_node.index != "ZZZ")
    {
        for (int i = 0; i < instructions.length(); i++)
        {
            char instruction = instructions[i];
            string next_node_index;

            if (instruction == 'R') { next_node_index = current_node.right; }
            if (instruction == 'L') { next_node_index = current_node.left; }

            current_node = network.at(next_node_index);
            steps++;

            if (next_node_index == "ZZZ") { break; }
        }
    }

    cout<<steps<<endl;
}