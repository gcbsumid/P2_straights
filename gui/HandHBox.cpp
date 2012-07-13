#include "HandHBox.h"
#include "CardPics.h"
#include "../gameplay/Card.h"
#include "DeckGui.h"
#include <gtkmm/box.h>
#include <iostream>
#include <vector>
using namespace std;

class GamePlay;

// Constructor - it creates the 4 suits in a Hbox each
HandHBox::HandHBox(DeckGui* deck, GamePlay* gameplay, int player, int spacing) : 
                Gtk::HBox(true, spacing), mDeck(deck), mPlayer(player), 
                mGamePlay(gameplay) {
    // The final step is to display the buttons (they display themselves)

}

// Deletes the each card object
HandHBox::~HandHBox() {
    for (int i = 0; i < 13; i++) {
        if(mCards[i]) {
            cout <<"I'm deleting cards in human hand" << endl;
            delete mCards[i];
        }
    }
}

void HandHBox::update(){
    // TODO: something/
}

void HandHBox::TurnHandToButton() {
    // When no legal plays, every card turns into a discard
    // option, therefore we turn them into buttons
    for (int i = 0; i < 13; i++) {
        if (mCards[i]->IsValidCard()) {
            mCards[i]->ImageToButton();
        }
    }

}

void HandHBox::TurnHandToStatic() {
    // When the discard turn is done, return everything back
    // into imagesons
    for (int i = 0; i < 13; i++) {
        if (mCards[i]->IsValidCard()) {
            mCards[i]->ButtonToImage();
        }
    }
}

void HandHBox::DisplayLegalCards(vector<Card*> legalCards) {
    // Makes all the Legal cards into buttons
    //cout << "Trying to display legal cards - we have " << legalCards.size() << " of them" << endl;
    for (int i = 0; i < 13; i++) {
        //cout << "Trying card " << mCards[i]->GetRank() << " of " << mCards[i]->GetSuit() << endl;
        for(int j = 0; j < legalCards.size(); j++) {
            if (!mCards[i]->IsValidCard()) {
                cout << "Card number " << i << " has already been played" << endl;
                break;
            }
            if (mCards[i]->GetRank() == legalCards[j]->getRank()) {
                //cout << "Rank matches " << *legalCards[j] << endl;
                if (mCards[i]->GetSuit() == legalCards[j]->getSuit()) {
                    cout << "Found legal card " << *legalCards[j] << endl;
                    mCards[i]->ImageToButton();
                    break;
                }
            }
        }
    }

}

void HandHBox::ReturnLegalCardsToImage() {
    // DISCARD
    // TODO: delete buttons and replace them as static images
    for (int i = 0; i < 13; i++) {
        if (!mCards[i]->IsImage()) {
            mCards[i]->ButtonToImage();
        }
    }
}

void HandHBox::AddCards(std::vector<Card*> cards) {
    // Display all the cards
    for (int i = 0; i < 13; i++) {
        Card* card = cards.at(i);
        mCards[i] = new CardPics(false, mDeck, mGamePlay, card->getRank(), card->getSuit());
        cout << "I'm adding the cards dealt to me." << endl;
        add(*mCards[i]);
    }
    show_all_children();  // Not sure if needed
}

void HandHBox::CardPlayed(Card* card) {
    for (int i = 0; i < 13; i++) {
        cout << "Card Rank: " << card->getRank() << endl;
        cout << "Card Suit: " << card->getSuit() << endl;
        cout << "mCard[" << i << "] Rank: " << mCards[i]->GetRank() << endl;
        cout << "mCard[" << i << "] Suit: " << mCards[i]->GetSuit() << endl;
        if (mCards[i]->GetRank() == card->getRank() 
            && mCards[i]->GetSuit() == card->getSuit()) {
            mCards[i]->RemoveCard();
        }
    }
}
