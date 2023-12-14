#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

string cell_format(int row, int column)
{
    return to_string(row) + "," + to_string(column);
}

bool check_neighbours(vector<string>& grid, int row, int column, int length, string &out_cell_ref)
{
    for (int y = column - length; y < column; y++)
    {
        string cell_column = grid[row];

        // check surrounding cells
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int new_row = row + i;
                int new_column = y + j;

                // don't check if out of bounds
                if (new_row < 0 || new_row > grid.size() - 1) { continue; }
                if (new_column < 0 || new_column > cell_column.length() - 1) { continue; }

                char value = grid[new_row][new_column];

                if (value == '*')
                {
                    out_cell_ref = cell_format(new_row, new_column);
                    return true;
                }
            }
        }

    }

    return false;
}

int main()
{
    // create a 1-dimensional vector consisting of strings
    // strings should be the lines split
    // check the "cells" around the symbol

    cout<<"start"<<endl;

    string line;

    ifstream file("Day3Input.txt");

    vector<string> grid;

    int sum = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            grid.push_back(line);
        }
    }

    map<string, vector<int>> gear_ratios;

    for (int x = 0; x < grid.size(); x++)
    {
        string row = grid[x];
        string temp_concatenated_number = "";

        for (int y = 0; y < row.length(); y++)
        {
            char string_character = row[y];

            if (isdigit(string_character))
            {
                temp_concatenated_number += string_character;
            }
            else if (temp_concatenated_number.length() > 0)
            {
                string adjacent_cell;
                bool is_adjacent = check_neighbours(grid, x, y, temp_concatenated_number.length(), adjacent_cell);

                if (is_adjacent)
                {
                    if (gear_ratios.count(adjacent_cell) > 0)
                    {
                        gear_ratios[adjacent_cell].push_back(stoi(temp_concatenated_number));
                    }
                    else
                    {
                        vector<int> ratio_components;
                        ratio_components.push_back(stoi(temp_concatenated_number));
                        gear_ratios[adjacent_cell] = ratio_components;
                    }
                }

                temp_concatenated_number = "";
            }
        }
    }

    for (map<string, vector<int>>::iterator it = gear_ratios.begin(); it != gear_ratios.end(); it++)
    {
        vector<int> ratio_components = it->second;

        if (ratio_components.size() < 2)
        {
            continue;
        }

        int ratio_sum = 1;

        for (int i = 0; i < ratio_components.size(); i++)
        {
            ratio_sum *= ratio_components[i];
        }

        sum += ratio_sum;
    }

    cout<<sum<<endl;
}