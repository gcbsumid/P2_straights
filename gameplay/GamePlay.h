#ifndef _GAMEPLAY_
#define _GAMEPLAY_

#include <iostream>
#include <set>
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameState.h"


class Card;
class GameState;

class GamePlay {
friend class Player;
friend class HumanPlayer;
friend class ComputerPlayer;
public:
    GamePlay();                             // want an array of pointers to cards;
    ~GamePlay();
    
    // Functions called by the main game.
    void AddPlayer(bool human);             // Add a human/computer player to the game.
    bool PlayRound();                       // Each individual round happens in here. Return true if game over.
    
    // Functions called by players in the view.

    // The player plays the card with the given suit and rank. Returns false if invalid card.
    bool PlayCard(int player, Suit suit, Rank rank);
    // The player discards the card with the given suit and rank. Returns false if invalid card.
    bool DiscardCard(int player, Suit suit, Rank rank);

    void Quit();                            // Called by a human player when they want to quit. Ends the game.
    void RageQuit(int player);              // Converts indicated player from human to computer.
    void ResetSeed(int seed);               // Reset the seed to some other value.
    
    static int CARD_COUNT;
private:
    // Functions called by individual players.
    bool mQuit;

    GameState* mState;
};

#endif
