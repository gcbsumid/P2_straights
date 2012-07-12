#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"

class GamePlay;
class GameState;
class ComputerPlayer : public Player {
public:
    ComputerPlayer(GamePlay *gameplay, GameState* gamestate, int id): Player(gameplay, gamestate, id) {}

    ComputerPlayer(Player*);
    virtual ~ComputerPlayer() {}
    void TakeTurn();                // The computer takes a turn
    bool IsHuman() const;           // returns false because it is a computer player object
};

#endif
