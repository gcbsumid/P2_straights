#include "CardPics.h"
#include "DeckGui.h"
#include "../gameplay/Card.h"
#include "../gameplay/GamePlay.h"

#include <iostream>
using namespace std;

//DeckGui CardPics::deck;

CardPics::CardPics(bool isButton, DeckGui* deck, GamePlay* gameplay, Rank f, Suit s) 
        : HBox(false,0), mDeck(deck), mGamePlay(gameplay), mRank(f), mSuit(s) {
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
    if (IsImage()) {
        return;
    }
    cout << "removeing a buttonnnnnnnnnnnnnnnnnnnnnnnnn" << endl;
    
    remove(mButton);
    mCard->reparent(*this);
    //add(*mCard);
    show_all();
    mIsImage = true;
}

void CardPics::HandleButtonClick() {
    cout << "Handling a button click" << endl;
    if (mSuit == SUIT_COUNT || mRank == RANK_COUNT) {
        return;
    }
    mGamePlay->PlayCard(mSuit, mRank);
}

void CardPics::ImageToButton() {
    if (!IsImage()) {
        return;
    }
    cout << "ImageToButton called on " << mRank << " " << mSuit << endl;
    remove(*mCard);
    mButton.set_image(*mCard);
    mButton.signal_clicked().connect(sigc::mem_fun(*this, &CardPics::HandleButtonClick));
    add(mButton);
    mButton.show();
    mIsImage = false;
}

bool CardPics::IsImage() {
    return mIsImage;
}

void CardPics::UpdateCard(Rank rank, Suit suit) {
    mRank = rank;
    mSuit = suit;
    mCard->set(mDeck->image(rank, suit));
}

void CardPics::RemoveCard() {
    mRank = RANK_COUNT;
    mSuit = SUIT_COUNT;
    mCard->set(mDeck->null());
}
