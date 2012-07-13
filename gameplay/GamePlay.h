#ifndef _GAMEPLAY_
#define _GAMEPLAY_

#include <iostream>
#include <set>
#include <vector>
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameState.h"

/*
This is the main controller, and implements all of the game logic. 
It is assisted by the Player, HumanPlayer, and ComputerPlayer classes.

We implement the facade pattern here - the view only needs to interact with this class.
*/


class Card;
class GameState;
class ModelObserver;
class ViewInterface;

class GamePlay {
friend class Player;
friend class HumanPlayer;
friend class ComputerPlayer;
public:
    GamePlay();
    ~GamePlay();

    // Called by the main program to associate the controller with the view.
    void AddView(ViewInterface* v);

    // Also called by the main program. Associates the passed in observer with the model.
    // This is probably the same object as the parameter passed to AddView, just a different pointer type.
    // You can add as many observers as you like, but it's probably just one.
    void AddModelObserver(ModelObserver* m);
    
    // Functions called by the view when an event fires (the player wants to do something).

    // Main game loop. Initializes game and plays it out.
    void PlayGame();

    // Add a human/computer player to the game.
    void AddPlayer(bool human);

    // The player plays the card with the given suit and rank. Returns false if invalid card.
    // Note: To keep things simple for the view, if the player wishes to discard a card, they can also call this function.
    // It will figure out which player is currently playing, and whether the play is a discard or if it's a legal play.
    bool PlayCard(Suit suit, Rank rank);

    // The player discards the card with the given suit and rank. Returns false if invalid card.
    // If the view wishes to be more direct with its discarding, it has the option of calling this function.
    bool DiscardCard(int player, Suit suit, Rank rank);

    // Converts indicated player from human to computer.
    void RageQuit(int player);

    // Reset the seed to some other value.
    void ResetSeed(int seed);

    // Returns a player's discarded cards.
    std::vector<Card*> GetDiscards(int player) const;

    // Returns a vector of the player's legal plays.
    std::vector<Card*> GetLegal(int player) const;
    
    // Total number of cards in the deck.
    static const int CARD_COUNT;
private:
    // Helper functions that assist with the game flow.

    // Make the computer players take their turns, then break and prompt view when it's time for a human to play.
    void ContinueGame();

    // A round starts. Shuffle, deal, start the round.
    void StartRound();

    // A round ends. Tally scores, alert the view.
    void EndRound();

    // Called when the game is over, with the ID of the winning player. Alerts the model, which alerts the view.
    void EndGame(int winner);

    // Pointer to the model.
    GameState* mState;

    // Pointer to the view.
    ViewInterface* mView;
};

#endif
