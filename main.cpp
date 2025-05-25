#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <random>
#include <chrono>

void splitDeck(const std::vector<int> &deck, std::vector<int> &cards, std::vector<int> &cards2)
{
    if (deck.size() < 2)
        return;

    size_t half = deck.size() / 2;

    cards.insert(cards.begin(), deck.begin(), deck.begin() + half);
    cards2.insert(cards2.begin(), deck.begin() + half, deck.end());
}

int main()
{
    int player1{};
    int player2{};
    int card{2};
    std::string name, name2{};

    std::cout << "Enter names of the players: " << '\n';
    std::cin >> name >> name2;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<int> deck;
    while (deck.size() < 52)
    {
        int count = std::count(deck.begin(), deck.end(), card);

        if (count < 4)
        {
            deck.push_back(card);
        }
        else
        {
            card = card + 1;
            continue;
        }
    };

    for (auto i : deck)
        std::cout << i << " ";

    std::cout << '\n';
    std::cout << "Deck size: " << deck.size() << '\n';

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

    std::cout << "RANDOM deck size: " << deck.size() << '\n';

    for (auto i : deck)
        std::cout << i << " ";

    std::vector<int> cards, cards2;
    splitDeck(deck, cards, cards2);

    while (!cards.empty() && !cards2.empty())
    {
        player1 = cards.front();
        std::cout << name << ": " << player1 << '\n';
        cards.erase(cards.begin());

        player2 = cards2.front();
        std::cout << name2 << ": " << player2 << '\n';
        cards2.erase(cards2.begin());
        if (player1 == player2)
        {

            std::cout << "IT IS A DRAW" << '\n';
            std::vector<int> draw_cards{};
            if (cards.size() < 6)
            {
                while (cards.size() > 0)
                {
                    draw_cards.push_back(cards.front());
                    cards.erase(cards.begin());
                    draw_cards.push_back(cards2.front());
                    cards2.erase(cards2.begin());
                }
            }
            else if (cards2.size() < 6)
            {
                while (cards2.size() > 0)
                {
                    draw_cards.push_back(cards.front());
                    cards.erase(cards.begin());
                    draw_cards.push_back(cards2.front());
                    cards2.erase(cards2.begin());
                }
            }
            else
            {
                while (draw_cards.size() < 5)
                {
                    draw_cards.push_back(cards.front());
                    cards.erase(cards.begin());
                    draw_cards.push_back(cards2.front());
                    cards2.erase(cards2.begin());
                }

                std::cout << "DRAWN CARDS" << '\n';

                for (auto i : draw_cards)
                    std::cout << i << " ";

                std::cout << '\n';
                int player1_draw, player2_draw{};

                player1_draw = cards.front();
                std::cout << name << ": " << player1_draw << '\n';
                cards.erase(cards.begin());

                player2_draw = cards2.front();
                std::cout << name2 << ": " << player2_draw << '\n';
                cards2.erase(cards2.begin());
                if (player1_draw > player2_draw)
                {
                    std::cout << name << " wins this round!" << '\n';
                    cards.push_back(player1);
                    cards.push_back(player2);
                    cards.push_back(player1_draw);
                    cards.push_back(player2_draw);
                    for (auto i : draw_cards)
                        cards.push_back(i);
                }
                else
                {
                    std::cout << name2 << " wins this round!" << '\n';
                    cards2.push_back(player1);
                    cards2.push_back(player2);
                    cards2.push_back(player1_draw);
                    cards2.push_back(player2_draw);
                    for (auto i : draw_cards)
                        cards2.push_back(i);
                }
            }
        }
        else if (player1 > player2)
        {
            std::cout << name << " wins this round!" << '\n';
            cards.push_back(player1);
            cards.push_back(player2);
        }
        else
        {
            std::cout << name2 << " wins this round!" << '\n';
            cards2.push_back(player1);
            cards2.push_back(player2);
        }
        std::cout << name << " cards: ";
        for (auto i : cards)
            std::cout << i << " ";

        std::cout << '\n'
                  << name
                  << " card count: " << cards.size() << '\n';
        std::cout << '\n';

        std::cout << name2 << " cards: ";
        for (auto i : cards2)
            std::cout << i << " ";
        std::cout << '\n'
                  << name2
                  << " 2 card count: " << cards2.size();
        std::cout << '\n';

        std::cin.get();
    }

    std::string winner{};

    if (cards.empty())
    {
        winner = name2;
    }
    else if (cards2.empty())
    {
        winner = name;
    };

    std::cout << "War winner and absoulte champion is " << winner << '\n';

    return 0;
}