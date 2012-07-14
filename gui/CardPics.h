/************************************************
 * CardPics.h                                   *
 * Author: Christian Sumido, Didier Smith       * 
 ************************************************/

#ifndef CARDPICS
#define CARDPICS

// Include Gtkmm Libraries
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>

// Include our own libraries
#include "DeckGui.h"
#include "../gameplay/Card.h"

class DeckGui;
class GamePlay;

class CardPics : public Gtk::HBox {
public:
    CardPics(bool isButton, DeckGui* deck, GamePlay* gameplay, Rank f = RANK_COUNT, Suit s = SUIT_COUNT);
    ~CardPics();

    // Returns the rank of a card
    Rank GetRank();

    // Returns the suit of a card
    Suit GetSuit();

    // Returns whether the image is that of a valid card or a null image
    bool IsValidCard();

    // Turns the button into an image
    void ButtonToImage();

    // handles the button click
    void HandleButtonClick();

    // Turns an image into a button
    void ImageToButton();

    // Returns whether the object is displaying an image or a button
    bool IsImage();

    // Replaces the current image with a null image and sets the rank
    // and suit to RANK_COUNT and SUIT_COUNT
    void RemoveCard();

    // Changes the image to the image of a certain card 
    void UpdateCard(Rank rank, Suit suit);

private:
    DeckGui* mDeck;             // Pointer to deck of images
    GamePlay* mGamePlay;        // Pointer to Controller

    Rank mRank;                 // Rank of card in image
    Suit mSuit;                 // Suit of card in image
    bool mIsImage;              // stores whether the Image or Button is being displayed
    
    // Member widgets:
    Gtk::Image* mCard;          // Images to display.
    Gtk::Button mButton;        // Button that will hold an image.
};

#endif 
