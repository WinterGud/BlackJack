#pragma once
#include <sstream>
#include <string>

enum class Suit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

enum class Rank
{
    Ace = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
};

inline std::string generateTexturePath(Suit suit, Rank rank) {
    std::ostringstream pathStream;
    pathStream << "..\\..\\..\\BlackJack\\Sources\\Main\\assets\\";

    // Append suit prefix to the path
    switch (suit) {
    case Suit::Hearts: pathStream << "hearts_"; break;
    case Suit::Diamonds: pathStream << "diamonds_"; break;
    case Suit::Clubs: pathStream << "clubs_"; break;
    case Suit::Spades: pathStream << "spades_"; break;
    }

    // Append rank suffix to the path
    if (rank == Rank::Ace) pathStream << "ace";
    else if (rank == Rank::Two) pathStream << "2";
    else if (rank == Rank::Three) pathStream << "3";
    else if (rank == Rank::Four) pathStream << "4";
    else if (rank == Rank::Five) pathStream << "5";
    else if (rank == Rank::Six) pathStream << "6";
    else if (rank == Rank::Seven) pathStream << "7";
    else if (rank == Rank::Eight) pathStream << "8";
    else if (rank == Rank::Nine) pathStream << "9";
    else if (rank == Rank::Ten) pathStream << "10";
    else if (rank == Rank::Jack) pathStream << "jack";
    else if (rank == Rank::Queen) pathStream << "queen";
    else if (rank == Rank::King) pathStream << "king";

    pathStream << ".png";
    return pathStream.str();
}

inline int toInt(Rank rank) {
    switch (rank) {
    case Rank::Ace: return 1;
    case Rank::Two: return 2;
    case Rank::Three: return 3;
    case Rank::Four: return 4;
    case Rank::Five: return 5;
    case Rank::Six: return 6;
    case Rank::Seven: return 7;
    case Rank::Eight: return 8;
    case Rank::Nine: return 9;
    case Rank::Ten: 
    case Rank::Jack: 
    case Rank::Queen: 
    case Rank::King: return 10;
    default: return 0;
    }
}
