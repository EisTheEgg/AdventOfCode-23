#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

bool check_neighbours(vector<string>& grid, int row, int column, int length)
{
    string symbols = "%&$#*+/@=-";

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

                if (symbols.find(value) != string::npos)
                {
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
                bool is_adjacent = check_neighbours(grid, x, y, temp_concatenated_number.length());

                if (is_adjacent)
                {
                    sum += stoi(temp_concatenated_number);
                }

                temp_concatenated_number = "";
            }
        }
    }

    cout<<sum<<endl;
}