#ifndef _GAMEPLAY_
#define _GAMEPLAY_

#include <iostream>
#include <set>
#include <vector>
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameState.h"


class Card;
class GameState;
class ModelObserver;
class ViewInterface;

class GamePlay {
friend class Player;
friend class HumanPlayer;
friend class ComputerPlayer;
public:
    GamePlay();                             // want an array of pointers to cards;
    ~GamePlay();
    void AddView(ViewInterface* v);
    void AddModelObserver(ModelObserver* m);
    
    // Functions called by the main game.
    void PlayGame();                        // Main game loop. Initializes game and plays it out.
    void AddPlayer(bool human);             // Add a human/computer player to the game.
    
    // Functions called by players in the view.

    // The player plays the card with the given suit and rank. Returns false if invalid card.
    bool PlayCard(Suit suit, Rank rank);
    // The player discards the card with the given suit and rank. Returns false if invalid card.
    bool DiscardCard(int player, Suit suit, Rank rank);

    void RageQuit(int player);              // Converts indicated player from human to computer.
    void ResetSeed(int seed);               // Reset the seed to some other value.
    std::vector<Card*> GetDiscards(int player) const;    // Returns a player's discarded cards.
    std::vector<Card*> GetLegal(int player) const;    // Returns a player's discarded cards.
    
    static int CARD_COUNT;
private:
    // Functions called by individual players.
    void ContinueGame();
    void EndGame(int winner);
    void EndRound();
    void StartRound();
    bool mQuit;

    GameState* mState;
    ViewInterface* mView;
};

#endif
