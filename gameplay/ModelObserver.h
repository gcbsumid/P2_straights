#ifndef MODEL_OBSERVER
#define MODEL_OBSERVER

// Defines the interface which the view implements and the model calls.

class Card;

class ModelObserver {
public:
    // Receives a vector of size 4.
    // The value is either an empty vector for a computer player or a vector of 13 cards for a human.
    virtual void Model_CardsDealt(std::vector<std::vector<Card*> >) = 0;
    virtual void Model_PlayerAdded(bool isHuman, int id) = 0;
    virtual void Model_PlayerRageQuitted(int player) = 0;
    virtual void Model_CardsCleared() = 0;
    virtual void Model_ScoreUpdated(int player, int score) = 0;
    virtual void Model_DiscardsCleared(int player) = 0;
    virtual void Model_CardPlayed(int player, Card*) = 0;
    virtual void Model_CardDiscarded(int player, Card*) = 0;
};

#endif
