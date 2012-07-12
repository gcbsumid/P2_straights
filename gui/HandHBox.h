#ifndef HAND_HBOX
#define HAND_HBOX
#include "RowHBox.h"
#include "../gameplay/Card.h"
#include <vector>

class CardPic;

class HandHBox : public RowHBox {
public:    
    HandHBox(DeckGui* deck, int player, int spacing = 5);
    ~HandHBox();
    void update();

    void AddCards(std::vector<Card*>);
private:
    void StaticToButton();
    void ButtonToStatic();
    int mPlayer;
};

#endif