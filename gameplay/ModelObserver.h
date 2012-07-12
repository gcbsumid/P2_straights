#ifndef MODEL_OBSERVER
#define MODEL_OBSERVER

// Defines the interface which the view implements and the model calls.

class Card;

class ModelObserver {
public:
    void Model_CardsDealt(std::vector<std::vector<Card*> >);
    void Model_PlayerAdded(bool isHuman, int id);
    void Model_PlayerRageQuitted(int player);
    void Model_CardsCleared();
    void Model_ScoreUpdated(int player, int score);
    void Model_DiscardsCleared(int player);
    void Model_CardPlayed(int player, Card*);
    void Model_CardDiscarded(int player, Card*);
};

#endif
