#ifndef HAND_HBOX
#define HAND_HBOX
#include "../gameplay/Card.h"
#include "DeckGui.h"
#include "CardPics.h"
#include <gtkmm/box.h>
#include <vector>

class CardPic;
class DeckGui;

class HandHBox : public Gtk::HBox {
public:    
    HandHBox(DeckGui* deck, int player, int spacing = 5);
    virtual ~HandHBox();
    void update();

    void AddCards(std::vector<Card*>);
private:
    DeckGui* mDeck;

    void StaticToButton();
    void ButtonToStatic();
    int mPlayer;
    CardPics* mCards[13];
};

#endif