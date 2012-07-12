#ifndef CARDPICS
#define CARDPICS
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include "DeckGui.h"
#include "../gameplay/Card.h"

class DeckGui;

class CardPics : public Gtk::HBox {
public:
    CardPics(bool isButton, DeckGui* deck, Rank f = RANK_COUNT, Suit s = SUIT_COUNT);
    ~CardPics();
    Rank GetRank();
    Suit GetSuit();
    bool IsValidCard();

private:
    DeckGui* mDeck;

    Rank mRank;
    Suit mSuit;
    // Member widgets:
    Gtk::Image* mCard;          // Images to display.
    Gtk::Button mButton;        // Button that will hold an image.
};

#endif 
