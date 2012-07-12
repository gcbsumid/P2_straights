#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>
#include "ComputerPlayer.h"
#include "Player.h"

class GamePlay;
class GameState;
class Card;

class HumanPlayer : public Player {
friend ComputerPlayer::ComputerPlayer(Player*);
public:
    HumanPlayer(GamePlay *gameplay, GameState* gamestate, int id) : Player(gameplay, gamestate, id) {}
    virtual ~HumanPlayer() {}
    void TakeTurn();                    // Take Human Player's turn
    bool IsRageQuitted() const;         // Player rage quits and is replaced by a computer
    void RageQuit();
    bool IsHuman() const;               // Returns true because this object is a human player
    
private: 
    bool mRageQuit;
};

#endif
