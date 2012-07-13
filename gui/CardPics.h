#ifndef CARDPICS
#define CARDPICS
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include "DeckGui.h"
#include "../gameplay/Card.h"

class DeckGui;
class GamePlay;

class CardPics : public Gtk::HBox {
public:
    CardPics(bool isButton, DeckGui* deck, GamePlay* gameplay, Rank f = RANK_COUNT, Suit s = SUIT_COUNT);
    ~CardPics();
    Rank GetRank();
    Suit GetSuit();
    bool IsValidCard();
    void ButtonToImage();
    void HandleButtonClick();
    void ImageToButton();
    bool IsImage();
    void RemoveCard();
    void UpdateCard(Rank rank, Suit suit);
private:
    DeckGui* mDeck;
    GamePlay* mGamePlay;

    Rank mRank;
    Suit mSuit;
    bool mIsImage;
    // Member widgets:
    Gtk::Image* mCard;          // Images to display.
    Gtk::Button mButton;        // Button that will hold an image.
};

#endif 
