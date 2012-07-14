/************************************************
 * RowHBox.h                                    *
 * Author: Christian Sumido, Didier Smith       *
 ************************************************/

#ifndef ROW_HBOX
#define ROW_HBOX

// Includes Gtkmmm Libraries
#include <gtkmm/box.h>

// Includes our written code
#include "CardPics.h"

// Forward declares classes
class CardPics;
class DeckGui;
class Card;
class GamePlay;

class RowHBox : public Gtk::HBox {
public:
    RowHBox(DeckGui*, GamePlay*, int, int);
    virtual ~RowHBox();
    
    // Finds which card is being played and adds it to the table
    void CardPlayed(Card* card);

    // Resets all cards 
    void Reset();

protected:
    int mSuit;              // This is the suit of the cards
    GamePlay* mGamePlay;    // A pointer to the controller
    DeckGui* mDeck;         // A pointer to the deck of images
    CardPics* mCards[13];   // These are the cards being displayed
};

#endif
