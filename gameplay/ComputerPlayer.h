#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"

class GamePlay;
class GameState;
class ViewInterface;

class ComputerPlayer : public Player {
public:
    ComputerPlayer(GamePlay *gameplay, GameState* gamestate, ViewInterface* view, int id)
        : Player(gameplay, gamestate, view, id) {}

    ComputerPlayer(Player*);
    virtual ~ComputerPlayer() {}
    bool TakeTurn();                // The computer takes a turn. Returns false if the computer has nothing to do (ie. game over)
    bool IsHuman() const;           // returns false because it is a computer player object
};

#endif
