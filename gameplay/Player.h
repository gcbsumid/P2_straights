#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include "Card.h"

class Gameplay;
class Player {
friend class ComputerPlayer;
public:
    Player(Gameplay *, int);
    virtual ~Player();
    
    // Functions called by the Gameplay.
    virtual void TakeTurn() = 0;            // Player's turn happens here
    virtual bool IsHuman() const = 0;       // Returns whether or not the player is human
    void ReceiveCards(std::vector<Card*>);  // Receives your hand from gameplay
    int GetScore() const;                   // Returns Score
    int GetID() const;                      // Returns ID
    bool PlayerHas(Card*) const;            // Returns whether the player has the specific card
    void PrintDiscard();                    // Prints discarded cards and increments the score by the appropriate amount.
    
protected:
    // Helper Functions
    void RemoveFromHand(Card*);             // Remove a card from the player's hand
    void PlayCardInHand(Card*);               // Plays the card in the hand;
    
    Gameplay* mGameplay;                    // Pointer to the gameplay object
    std::vector<Card*> mHand;               // Player's Hand
    std::vector<Card*> mDiscard;            // Player's Discard pile
    int mScore;                             // Player's current score
    int mID;                                // Player's ID
};

#endif
