#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include "Card.h"

class GamePlay;
class GameState;
class ViewInterface;
class Player {
friend class ComputerPlayer;
public:
    Player(GamePlay *, GameState*, ViewInterface*, int);
    virtual ~Player();
    
    // Functions called by the GamePlay.
    // Player's turn happens here
    virtual bool TakeTurn() = 0;

    // Returns whether or not the player is human
    virtual bool IsHuman() const = 0;

    // Returns ID
    int GetID() const;

    // Increment the player's score by the appropriate amount.
    void ClearDiscard();

    // Get the legal plays for the player.
    std::vector<Card*> GetLegalPlays();
    
protected:
    // Pointer to the gameplay object
    GamePlay* mGamePlay;

    // Pointer to the game state.
    GameState* mGameState;

    // Pointer to the view.
    ViewInterface* mView;

    // Player's ID
    int mID;
};

#endif
