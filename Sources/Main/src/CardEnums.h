#pragma once

enum class Suit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

enum class Rank
{
    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9,
    Ten = 10,
    Jack = 10,
    Queen = 10,
    King = 10,
    Ace = 11
};



inline const char* toString(const Suit e)
{
    switch (e)
    {
    case Suit::Hearts: return "Hearts";
    case Suit::Diamonds: return "Diamonds";
    case Suit::Clubs: return "Clubs";
    case Suit::Spades: return "Spades";
    default: return "unknown";
    }
}

inline const char* toString(Rank e)
{
    switch (e)
    {
    case Rank::Two: return "Two";
    case Rank::Three: return "Three";
    case Rank::Four: return "Four";
    case Rank::Five: return "Five";
    case Rank::Six: return "Six";
    case Rank::Seven: return "Seven";
    case Rank::Eight: return "Eight";
    case Rank::Nine: return "Nine";
    case Rank::Ten: return "Ten";
    case Rank::Jack: return "Jack";
    case Rank::Queen: return "Queen";
    case Rank::King: return "King";
    case Rank::Ace: return "Ace";
    default: return "unknown";
    }
}

