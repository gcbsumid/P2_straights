#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include "Player.h"

class Gameplay;
class ComputerPlayer : public Player {
public:
    ComputerPlayer(Gameplay *gameplay, int id): Player(gameplay, id) {}

    ComputerPlayer(Player*);
    virtual ~ComputerPlayer() {}
    void TakeTurn();                // The computer takes a turn
    bool IsHuman() const;           // returns false because it is a computer player object
};

#endif
