#ifndef _GAMEPLAY_
#define _GAMEPLAY_

#include <iostream>
#include <set>
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"


class Card;

class Gameplay {
friend class Player;
friend class HumanPlayer;
friend class ComputerPlayer;
public:
    Gameplay();                             // want an array of pointers to cards;
    ~Gameplay();
    
    // Functions called by the main game.
    void PlayRound();                       // Each individual round happens in here. 
    bool IsGameOver();                      // If the game has been quit, or if the game has completed.

    
private:
    // Functions called by individual players.
    void PrintCardsOnTable() const;         // Prints cards that are on the table
    void AddCardToTable(Card*);             // Called by a player when they play a card.
    bool IsLegal(Card*) const;              // Determines if a card is a legal play or not.
    void PrintAllCards() const;             // Debug function to print the deck.
    void Quit();                            // Called by a human player when they want to quit. Ends the game.

    // Helper functions.
    static void shuffle(Card**);            // Shuffles the provided array of 52 cards.
    void DealCards();                       // Distribute the shuffled deck of cards to the four players.
    int PlayerWithSevenOfSpades() const;    // Returns the player number with the seven of spades;

    static int CARD_COUNT;
    bool mQuit;

    Player* mPlayers[4];
    Card* mCardsArray[52];       // Shuffled pointers
    Card* mArrangedCards[52];   // cards arranged in order
    std::set<Card*> mCardsOnTable;           // arranged in order Clubs, Diamonds, Hearts, Spades, from Ace to King
};

#endif
