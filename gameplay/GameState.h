#ifndef GAME_STATE
#define GAME_STATE

#include <vector>
#include <set>

class Player;
class Card;
class GamePlay;
class HumanPlayer;
class ViewInterface;
class ModelObserver;

class GameState {
public:
    GameState(GamePlay* gameplay);
    ~GameState();

    //----- Functions that should be called that alter the fundamental operation of this class.
    void AddObserver(ModelObserver*);

    // Reset the seed used for shuffling the next game.
    void ResetSeed(int seed);

    // Make sure things are ready before the start of a game.
    void Initialize();

    //----- Functions for interaction from the GamePlay controller, used for setting up and ending games/rounds.
    // Add a Player to the game. 
    void AddPlayer(bool IsHuman, ViewInterface* v);

    // Shuffle the cards.
    void Shuffle();

    // Deal the cards between the players.
    void DealCards();

    void NewRound();

    // Remove the cards from the table and let the observers know about this.
    void ClearCardsOnTable();

    // The game has ended, player winner won.
    void EndGame(std::vector<int> winner);

    //----- Functions for treating the game as a state machine - advance to the next player, reset the next player, return current player.
    // Returns whoever's supposed to play next. Cycles through.
    Player* NextPlayer();

    // Returns whoever's supposed to play right now.
    Player* CurrentPlayer();

    // If instead of cycling through the players, we need to reset the next player. Takes the player ID.
    void ResetNextPlayer(int player);

    //----- Functions used in the middle of gameplay to accomplish things.

    // Call when a human player ragequits, returns pointer to new computer player.
    Player* HumanToComputer(HumanPlayer* human);

    // Update the score of player with given ID to given score.
    void UpdateScore(int player, int score);

    // Clear the discards of the given player.
    void ClearDiscard(int player);

    // Discards given card from player's hand.
    void DiscardCard(int player, Card* card);

    // Play the given card.
    void PlayCard(int player, Card* card);

    //----- Utilitity functions.

    // Returns true if a card can legally be played (neighbour of a card on the table, or seven).
    bool IsLegal(Card* card) const;

    // Returns the ID of whichever player has thet 7 of spades.
    int PlayerWithSevenOfSpades() const;

    // Returns the player with given ID.
    Player* PlayerWithID(int player) const;

    // Return pointer to card in player's hand if given card matches suit/rank, null otherwise.
    Card* CardInHand(int player, Card* card) const;

    // Returns the number of cards left in player's hand.
    int CardsInHand(int player) const;

    // Return true if the player has a matching card in their hand, false otherwise.
    bool PlayerHas(int player, Card* card) const;

    // Get the vector of discarded cards for a player.
    std::vector<Card*> GetDiscards(int player) const;

    // Get the legal plays for the player.
    std::vector<Card*> GetHand(int player) const;

    // Return the score of the current player. Used for determining when the game is over.
    int GetScore(int player) const;

private:
    
    // Helper function to remove a card from a player's hand. The Card* must be the same Card* as the card in the hand.
    void RemoveFromHand(int player, Card* card);

    // List of observers to update on state changes.
    std::vector<ModelObserver*> mObservers;

    // Shuffled pointers to cards.
    Card* mCardsArray[52];

    // cards arranged in order
    // arranged in order Clubs, Diamonds, Hearts, Spades, from Ace to King
    Card* mArrangedCards[52];

    // The cards that have been played.
    std::set<Card*> mCardsOnTable;

    // Player vectors - the outer vectors all have size 4.
    // The players in the game.
    std::vector<Player*> mPlayers;

    // Players' scores.
    std::vector<int> mScores;

    // Players' hands, one vector per player.
    std::vector<std::vector<Card*> > mHands;

    // Players' discards, one vector per player.
    std::vector<std::vector<Card*> > mDiscards;

    // The controller.
    GamePlay* mGamePlay;

    // Zero-index of the current player.
    int mCurrentPlayer;

    // Seed to use for next game.
    int mSeed;

    // The number of our current round.
    int mRound;
};

#endif
