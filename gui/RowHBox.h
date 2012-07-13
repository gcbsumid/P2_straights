#ifndef ROW_HBOX
#define ROW_HBOX

#include <gtkmm/box.h>
#include "CardPics.h"

class CardPics;
class DeckGui;
class Card;
class GamePlay;

class RowHBox : public Gtk::HBox {
public:
    RowHBox(DeckGui*, GamePlay*, int, int);
    virtual ~RowHBox();
    void CardPlayed(Card* card);

protected:
    int mSuit;
    //Gtk::VBox* mCards[13];
    GamePlay* mGamePlay;
    DeckGui* mDeck;
    CardPics* mCards[13];
};

#endif
