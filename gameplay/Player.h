#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include "Card.h"

class GamePlay;
class GameState;
class Player {
friend class ComputerPlayer;
public:
    Player(GamePlay *, GameState*, int);
    virtual ~Player();
    
    // Functions called by the GamePlay.
    virtual void TakeTurn() = 0;            // Player's turn happens here
    virtual bool IsHuman() const = 0;       // Returns whether or not the player is human
    int GetID() const;                      // Returns ID
    void ClearDiscard();                    // Prints discarded cards and increments the score by the appropriate amount.
    std::vector<Card*> GetLegalPlays();
    
protected:
    GamePlay* mGamePlay;                    // Pointer to the gameplay object
    GameState* mGameState;                  // Pointer to the game state.
    int mID;                                // Player's ID
};

#endif
