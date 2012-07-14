/************************************************
 * CardPics.cpp                                 *
 * Author: Christian Sumido, Didier Smith       * 
 ************************************************/
// Include our own libraries
#include "CardPics.h"
#include "DeckGui.h"
#include "../gameplay/Card.h"
#include "../gameplay/GamePlay.h"

#include <iostream>
using namespace std;

//DeckGui CardPics::deck;

CardPics::CardPics(bool isButton, DeckGui* deck, GamePlay* gameplay, Rank f, Suit s) 
        : HBox(false,0), mDeck(deck), mGamePlay(gameplay), mRank(f), mSuit(s) {
    
    // Temporary holder of the image
    Glib::RefPtr<Gdk::Pixbuf> card;

    // Wire up mButton to the button event handler.
    mButton.signal_clicked().connect(sigc::mem_fun(*this, &CardPics::HandleButtonClick));

    // Sets the image to be displayed
    if (f == RANK_COUNT || s == SUIT_COUNT) {
        card = mDeck->null();
    } else {
        card = mDeck->image(f, s);
    }
    mCard = new Gtk::Image(card);

    // If its a button, then I add it to the Hbox, else, I just add 
    // it as a static image
    if (isButton) {
        mIsImage = false;
        mButton.set_image(*mCard);
        add(mButton);
    } else {
        mIsImage = true;
        add(*mCard);
    }

    // display the widget
    show_all();
}

// Destructor - deletes the image 
CardPics::~CardPics() {
    delete mCard;
}

// Returns the rank of a card in the image
Rank CardPics::GetRank() {
    return mRank;
}

// Returns the suit of a card in the image
Suit CardPics::GetSuit() {
    return mSuit;
}

// Returns whether the image is an actual card or a null image
bool CardPics::IsValidCard() {
    if(mRank != RANK_COUNT || mSuit != SUIT_COUNT){
        return true;
    }
    return false;
}

// Removes the button and adds the image
void CardPics::ButtonToImage() {
    if (IsImage()) {
        // If its already an image, return
        return;
    }
    
    // Removes the button
    remove(mButton);

    // Changes the parent of the image from mButton to the object widget
    mCard->reparent(*this);

    // display the card
    show_all();
    mIsImage = true;
}

// Handles the button click 
void CardPics::HandleButtonClick() {
    if (!IsValidCard()) {
        // The current card should never be a invalid, but if it does, 
        // just return it.
        return;
    }

    // If its a valid card, it is played.
    mGamePlay->PlayCard(mSuit, mRank);
}

// Turns the object from an image to a button
void CardPics::ImageToButton() {
    if (!IsImage()) {
        return;
    }
    // remove the card image from this widget
    remove(*mCard);

    // Sets the button image to the card image
    mButton.set_image(*mCard);

    // add it to the widget  and show it
    add(mButton);
    mButton.show();
    mIsImage = false;
}

// returns if the current widget contains an image or a button
bool CardPics::IsImage() {
    return mIsImage;
}

// Changes the picture to the desired card
// also sets the suit and rank
void CardPics::UpdateCard(Rank rank, Suit suit) {
    mRank = rank;
    mSuit = suit;
    mCard->set(mDeck->image(rank, suit));
}

// Resets the picture to the null image
// also sets the suit and rank to invalid values
void CardPics::RemoveCard() {
    mRank = RANK_COUNT;
    mSuit = SUIT_COUNT;
    mCard->set(mDeck->null());
}
