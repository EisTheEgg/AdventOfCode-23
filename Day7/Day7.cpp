#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>

using namespace std;

class Hand {
private: 
    string hand;
    int bid;
    int value;
    map<char, int> hand_card_amounts;

    int get_max()
    {
        int current_max = 0;

        for (map<char, int>::iterator it = hand_card_amounts.begin(); it != hand_card_amounts.end(); it++)
        {
            current_max = max(current_max, it->second);
        }

        return current_max;
    }

    int get_min()
    {
        int current_min = 10000000000;

        for (map<char, int>::iterator it = hand_card_amounts.begin(); it != hand_card_amounts.end(); it++)
        {
            current_min = min(current_min, it->second);
        }

        return current_min; 
    }

    int get_pair_amount()
    {
        int amount = 0;

        for (map<char, int>::iterator it = hand_card_amounts.begin(); it != hand_card_amounts.end(); it++)
        {
            if (it->second == 2)
            {
                amount++;
            }
        }

        return amount;
    }

    void calculate_value()
    {
        for (int i = 0; i < hand.length(); i++)
        {
            hand_card_amounts[hand[i]] += 1;
        }

        // first ordering
        if (hand_card_amounts.begin()->second == 5) { value = 6; }
        else if (get_max() == 4) { value = 5; }
        else if (get_max() == 3 && get_min() == 2) { value = 4; }
        else if (get_max() == 3) { value = 3; }
        else { value = get_pair_amount(); }
    }

public:
    Hand(string hand_input, int bid_input)
    {
        hand = hand_input;
        bid = bid_input;
        calculate_value();
    }

    int get_value()
    {
        return value;
    }

    int get_bid()
    {
        return bid;
    }

    string get_hand_string()
    {
        return hand;
    }
};

bool second_ordering(Hand h1, Hand h2)
{
    vector<char> card_order = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

    for (int i = 0; i < h1.get_hand_string().length(); i++)
    {
        char h1_letter = h1.get_hand_string()[i];
        char h2_letter = h2.get_hand_string()[i];

        if (h1_letter == h2_letter) 
        { 
            continue;
        }

        int h1_index = find(card_order.begin(), card_order.end(), h1_letter) - card_order.begin();
        int h2_index = find(card_order.begin(), card_order.end(), h2_letter) - card_order.begin();

        return h1_index > h2_index;
    }

    // if we reach here, it's the exact same string
    // this shouldn't happen, but let's just return false
    // to make the compiler happy
    return false;
}

bool compare_hand(Hand h1, Hand h2)
{
    if (h1.get_value() == h2.get_value())
    {
        return second_ordering(h1, h2);
    }

    return (h1.get_value() < h2.get_value());
}

int main()
{
    string line;

    ifstream file("Day7Input.txt");

    vector<Hand> hands;

    while(getline(file, line))
    {
        std::vector<string> entry;
        boost::split(entry, line, boost::is_any_of(" "));

        Hand entry_hand(entry[0], stoi(entry[1]));
        hands.push_back(entry_hand);
    }

    sort(hands.begin(), hands.end(), compare_hand);

    long long winnings = 0;

    for (int i = 0; i < hands.size(); i++)
    {
        winnings += hands[i].get_bid() * (i + 1);
    }

    cout<<winnings<<endl;
}