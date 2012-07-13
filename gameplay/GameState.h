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
    void AddObserver(ModelObserver*);

    void ResetSeed(int seed);

    // Make sure things are ready before the start of a game.
    void Initialize();

    // Functions for interaction from the GamePlay controller.
    void AddHumanPlayer(ViewInterface* v);      // Add a Player to the game. 
    void AddComputerPlayer(ViewInterface* v);   // Add a Player to the game.
    void Shuffle();                             // Shuffle the cards.
    void DealCards();                           // Deal the cards between the players.
    void ClearCardsOnTable();
    bool IsLegal(Card* card) const;
    int PlayerWithSevenOfSpades() const;        // Returns the ID of whichever player has thet 7 of spades.
    Player* NextPlayer();                       // Returns whoever's supposed to play next. Cycles through.
    Player* CurrentPlayer();                       // Returns whoever's supposed to play right now.
    void ResetNextPlayer(int player);           // If instead of cycling through the players, we need to reset the next player. Takes the player ID.
    Player* HumanToComputer(HumanPlayer* human); // Call when a human player ragequits, returns pointer to new computer player.

    // Functions for interaction from players.
    Player* PlayerWithID(int player) const;     // Returns the player with given ID.
    void UpdateScore(int player, int score);    // Update the score of player with given ID to given score.
    int GetScore(int player) const;
    void ClearDiscard(int player);                  // Clear the discards of the given player.
    Card* CardInHand(int player, Card* card) const;    // Return pointer to card in player's hand if given card matches suit/rank, null otherwise.
    int CardsInHand(int player) const;          // Returns the number of cards left in player's hand.
    void DiscardCard(int player, Card* card);   // Discards given card from player's hand.
    void PlayCard(int player, Card* card);
    bool PlayerHas(int player, Card* card) const;
    std::vector<Card*> GetDiscards(int player) const; // Get the vector of discarded cards for a player.
    std::vector<Card*> GetHand(int player) const;   // Get the legal plays for the player.
    void EndGame(int winner);                   // The game has ended, player winner won.

private:
    std::vector<ModelObserver*> mObservers;

    Card* mCardsArray[52];                      // Shuffled pointers
    Card* mArrangedCards[52];                   // cards arranged in order
    std::set<Card*> mCardsOnTable;              // arranged in order Clubs, Diamonds, Hearts, Spades, from Ace to King

    // Player vectors - the outer vectors all have size 4.
    std::vector<Player*> mPlayers;              // The players in the game.
    std::vector<int> mScores;                   // Players' scores.
    std::vector<std::vector<Card*> > mHands;    // Players' hands, one vector per player.
    std::vector<std::vector<Card*> > mDiscards; // Players' discards, one vector per player.

    GamePlay* mGamePlay;
    int mCurrentPlayer;
    int mSeed;
};

#endif
