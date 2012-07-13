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
    HandHBox(DeckGui* deck, GamePlay* gameplay, int player, int spacing = 5);
    virtual ~HandHBox();
    void update();

    void AddCards(std::vector<Card*>);
    void AddCard(Rank r, Suit s);
    void ReturnLegalCardsToImage();
    void DisplayLegalCards(vector<Card*> legalCards);
    void TurnHandToButton();
    void TurnHandToStatic();
    void CardPlayed(Card* card);
    void Reset();
private:
    DeckGui* mDeck;

    int mPlayer;
    GamePlay* mGamePlay;
    CardPics* mCards[13];
};

#endif
