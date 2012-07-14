/************************************************
 * HandHBox.h                                     *
 * Author: Christian Sumido, Didier Smith       * 
 ************************************************/

#ifndef HAND_HBOX
#define HAND_HBOX

// Include our written code
#include "../gameplay/Card.h"
#include "DeckGui.h"
#include "CardPics.h"

// Include Gtkmm Libraries
#include <gtkmm/box.h>
#include <gtkmm/label.h>

// Include C++ Libraries
#include <vector>
#include <string>

class CardPic;
class DeckGui;

class HandHBox : public Gtk::HBox {
public:    
    HandHBox(DeckGui* deck, GamePlay* gameplay, int player, int spacing = 5);
    virtual ~HandHBox();

    // Adds a vector of cards to the hand
    void AddCards(std::vector<Card*>);

    // Adds a card to the hand
    void AddCard(Rank r, Suit s);

    // Change all legal cards to back to Images
    void ReturnLegalCardsToImage();

    // Change all legal cards to buttons in the HBox
    void DisplayLegalCards(vector<Card*> legalCards);

    // Turn entire Hand into buttons
    void TurnHandToButton();

    // Turn entire Hand to static Images
    void TurnHandToStatic();

    // Sets a card to a null image once it has been played
    void CardPlayed(Card* card);

    // Resets the entire hand to null static images
    void Reset();
private:
    DeckGui* mDeck;             // Deck of Images

    int mPlayer;                // Player Number
    Gtk::Label::Label* mName;   // Label of the name of the character
    GamePlay* mGamePlay;        // Pointer to controller
    CardPics* mCards[13];       // pointer to 13 cards in hand
};

#endif
