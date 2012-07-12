#ifndef GAME_STATE
#define GAME_STATE

#include <vector>

class Player;
class Card;
class GamePlay;
class HumanPlayer;
class GameState {
public:
    GameState(GamePlay* gameplay);
    ~GameState();

    // Functions for interaction from the GamePlay controller.
    void AddHumanPlayer();                      // Add a Player to the game. 
    void AddComputerPlayer();                      // Add a Player to the game.
    void Shuffle();                             // Shuffle the cards.
    void DealCards();                           // Deal the cards between the players.
    void ClearCardsOnTable();
    void AddCardToTable(Card* card);
    bool IsLegal(Card* card) const;
    int PlayerWithSevenOfSpades() const;        // Returns the ID of whichever player has thet 7 of spades.
    Player* NextPlayer();                       // Returns whoever's supposed to play next. Cycles through.
    void ResetNextPlayer(int player);           // If instead of cycling through the players, we need to reset the next player. Takes the player ID.
    Player* HumanToComputer(HumanPlayer* human); // Call when a human player ragequits, returns pointer to new computer player.

    // Functions for interaction from players.
    void DiscardCard(int player, Card* card);   // Discards given card from player's hand.
    Player* PlayerWithID(int player) const;     // Returns the player with given ID.
    void UpdateScore(int player, int score);    // Update the score of player with given ID to given score.
    int GetScore(int player);
    void ClearDiscard(int player);                  // Clear the discards of the given player.
    void RemoveFromHand(int player, Card* card);    // Remove the given card from the hand of the player with given ID.
    Card* CardInHand(int player, Card* card);    // Return pointer to card in player's hand if given card matches suit/rank, null otherwise.
    void PlayCard(int player, Card* card);
    bool PlayerHas(int player, Card* card) const;
    const std::vector<Card*> GetDiscards(int player); // Get the vector of discarded cards for a player.
    std::vector<Card*> GetHand(int player);   // Get the legal plays for the player.

private:
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
};


#endif
