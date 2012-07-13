#ifndef MODEL_OBSERVER
#define MODEL_OBSERVER

#include <vector>
// Defines the interface which the view implements and the model calls.

class Card;

class ModelObserver {
public:
    // Receives a vector of size 4.
    // The value is either an empty vector for a computer player or a vector of 13 cards for a human.
    virtual void Model_CardsDealt(std::vector<std::vector<Card*> >) = 0;

    // A new round has begun - we are on round number roundNumber.
    virtual void Model_NewRound(int roundNumber) = 0;

    // Player of ID id has been added.
    virtual void Model_PlayerAdded(bool isHuman, int id) = 0;

    // player has ragequit and become a computer player.
    virtual void Model_PlayerRageQuitted(int player) = 0;

    // The cards have been cleared from the table. (Happens when round is complete).
    virtual void Model_CardsCleared() = 0;

    // player has a new score of score.
    virtual void Model_ScoreUpdated(int player, int score) = 0;

    // player has cleared their discard pile.
    virtual void Model_DiscardsCleared(int player) = 0;

    // player has played card.
    virtual void Model_CardPlayed(int player, Card*) = 0;

    // Player player has discarded Card.
    virtual void Model_CardDiscarded(int player, Card*) = 0;

    // The game is over and player has won.
    virtual void Model_EndGame(std::vector<int> players) = 0;
};

#endif
