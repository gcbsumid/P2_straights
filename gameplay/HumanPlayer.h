#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <vector>
#include "ComputerPlayer.h"
#include "Player.h"

class Gameplay;
class Card;

class HumanPlayer : public Player {
friend ComputerPlayer::ComputerPlayer(Player*);
public:
    HumanPlayer(Gameplay *gameplay, int id) : Player(gameplay, id) {}
    virtual ~HumanPlayer() {}
    void TakeTurn();                    // Take Human Player's turn
    void PrintHand() const;             // Prints Player's Hand     
    void PrintLegal();            // Prints Player's Legal moves
    bool IsRageQuitted() const;         // Player rage quits and is replaced by a computer
    bool IsHuman() const;               // Returns true because this object is a human player
    // Translates the pointer to a card created by command to the pointer to that equivalent card in our hand.
    Card* CardInHand(Card*) const;
    
private: 
    bool mRageQuit;
    bool mHasLegal;
};

#endif
