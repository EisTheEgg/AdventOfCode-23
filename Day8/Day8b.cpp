#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <map>
#include <vector>

using namespace std;

typedef long long int ll;

struct Node
{
    string index;
    string left;
    string right;
};

ll find_lcm(ll a, ll b)
{
    ll max_value = max(a,b);
    ll min_value = min(a,b);

    for (ll i = max_value; ; i+=max_value)
    {
        if(i%min_value==0)
        {
            return i;
        }
    }
}

ll find_total_lcm(vector<ll> input)
{
    ll current_lcm = find_lcm(input[0], input[1]);

    for (int i = 2; i < input.size(); i++)
    {
        current_lcm = find_lcm(current_lcm, input[i]);
    }

    return current_lcm;
}

int main()
{
    int c = find_lcm(24,32);

    string line;

    ifstream file("Day8Input.txt");
    getline(file, line);
    string instructions = line;
    getline(file, line);

    map<string, Node> network;
    vector<Node> current_nodes;

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

        Node new_node = Node { index, coords[0], coords[1] };
        network[index] = new_node;

        if (index[index.size() - 1] == 'A')
        {
            current_nodes.push_back(new_node);
        }
    }

    vector<ll> min_steps;

    for (int node_i = 0; node_i < current_nodes.size(); node_i++)
    {
        ll steps = 0;
        int i = 0;

        Node current_node = current_nodes[node_i];

        while (current_node.index.back() != 'Z')
        {
            if (i >= instructions.size()) { i = 0; }

            char instruction = instructions[i];
            string next_node_index;

            if (instruction == 'R') { next_node_index = current_node.right; }
            if (instruction == 'L') { next_node_index = current_node.left; }

            current_node = network.at(next_node_index);

            steps++;
            i++;
        }

        min_steps.push_back(steps);
    }

    cout<<find_total_lcm(min_steps)<<endl;

}