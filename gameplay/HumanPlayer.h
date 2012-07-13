#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>
#include "ComputerPlayer.h"
#include "Player.h"

class GamePlay;
class GameState;
class Card;
class ViewInterface;

class HumanPlayer : public Player {
friend ComputerPlayer::ComputerPlayer(Player*);
public:
    HumanPlayer(GamePlay *gameplay, GameState* gamestate, ViewInterface* view, int id)
        : Player(gameplay, gamestate, view, id) {}
    virtual ~HumanPlayer() {}
    void TakeTurn();                    // Take Human Player's turn
    bool IsHuman() const;               // Returns true because this object is a human player
};

#endif
