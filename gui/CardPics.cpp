#include "CardPics.h"
#include "DeckGui.h"
#include "../gameplay/Card.h"

//DeckGui CardPics::deck;

CardPics::CardPics(bool isButton, DeckGui* deck, Rank f, Suit s) 
        : HBox(false,0), mDeck(deck), mRank(f), mSuit(s) {
    Glib::RefPtr<Gdk::Pixbuf> card;

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

CardPics::~CardPics() {
    delete mCard;
}

Rank CardPics::GetRank() {
    return mRank;
}

Suit CardPics::GetSuit() {
    return mSuit;
}

bool CardPics::IsValidCard() {
    if(mRank != RANK_COUNT || mSuit != SUIT_COUNT){
        return true;
    }
    return false;
}

void CardPics::ButtonToImage() {
    remove(mButton);
    add(*mCard);
    show_all();
    mIsImage = true;
}

void CardPics::ImageToButton() {
    remove(*mCard);
    mButton.set_image(*mCard);
    add(mButton);
    show_all();
    mIsImage = false;
}

bool CardPics::IsImage() {
    return mIsImage;
}

void CardPics::UpdateCard(Rank rank, Suit suit) {
    mCard->set(mDeck->image(rank, suit));
}
