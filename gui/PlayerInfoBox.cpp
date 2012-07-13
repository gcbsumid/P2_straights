#include "PlayerInfoBox.h"
#include "HandHBox.h" 
#include "DeckGui.h"
#include "../gameplay/GamePlay.h"
#include "gtkmm/textbuffer.h"
#include "gtkmm/textview.h"
#include <gtkmm/dialog.h>
#include <sstream>
#include <iostream>
using namespace std;

PlayerInfoBox::PlayerInfoBox(bool isHuman, int playerNum, GamePlay* gameplay, DeckGui* deck) : 
    VBox(false, 2), mPlayerNumber(playerNum), mIsHuman(isHuman), 
    mScore(0), mGamePlay(gameplay), mButtonBox(false), mRageQuit("Rage Quit"), 
    mDeck(deck), mDiscard("Discard"), mDiscardPile(deck, gameplay, playerNum, 5) {

    // set sme properties of the box
    stringstream playerNumberStream, scoreStream; 
    add(mPanel);

    playerNumberStream << "Player " << playerNum << endl;
    if (isHuman) {
        playerNumberStream << "Status: Human" << endl;
    } else {
        playerNumberStream << "Status: Computer" << endl;
    }
    mPlayerName = Gtk::TextBuffer::create();
    mPlayerName->set_text(playerNumberStream.str().c_str());

    mPlayerTextBox.set_buffer(mPlayerName);
    mPanel.add(mPlayerTextBox);

    // Displays the score
    scoreStream << mScore << endl;
    mScoreText = Gtk::TextBuffer::create();
    mScoreText->set_text(scoreStream.str().c_str());

    mScoreTextBox.set_buffer(mScoreText);
    mPanel.add(mScoreTextBox);

    //Add Button container
    add(mButtonBox);

    // If not human, buttons are disabled
    if (!isHuman) {
        mRageQuit.set_sensitive(false);
        mDiscard.set_sensitive(false);
    }
    // Adds the buttons 
    mButtonBox.add(mRageQuit);
    mButtonBox.add(mDiscard);

    // clicked functions assigned to buttons
    mRageQuit.signal_clicked().connect(sigc::mem_fun(*this, &PlayerInfoBox::RageQuitButtonPressed));
    mDiscard.signal_clicked().connect(sigc::mem_fun(*this, &PlayerInfoBox::DiscardButtonPressed));
    
    show_all();
}

PlayerInfoBox::~PlayerInfoBox() {}

void PlayerInfoBox::RageQuitButtonPressed() {
    // TODO: rage quit button.
    // Either GamePlay::RageQuit or View::RageQuit (the view goes to Gameplay)
    cout << "Someone pressed the rage quit button, time to do something about that" << endl;
    mGamePlay->RageQuit(mPlayerNumber);
}

void PlayerInfoBox::DiscardButtonPressed() {
    // TODO: Prompts for the discard pile from GamePlay
    //       and then displays a popup displaying all 
    //       discarded cards
    cout << "Displaying Discard Pile" << endl;
    Gtk::Dialog dialog("Discard Pile");
    Gtk::VBox* mDialogBox = dialog.get_vbox();
    mDialogBox->add(mDiscardPile);
    dialog.add_button("Okay", 1);
    dialog.run();
}

void PlayerInfoBox::UpdateScore(int score) {
    // Update Display Scores
    stringstream scoreStream;
    mScore = score;
    scoreStream << mScore << endl;
    mScoreText->set_text(scoreStream.str().c_str());

    mScoreTextBox.set_buffer(mScoreText);
}

void PlayerInfoBox::HumanToComputer() {
    stringstream playerNumberStream;
    cout << "FUCK THIS SHIT. I QUIT." << endl;
    playerNumberStream << "Player " << mPlayerNumber << endl;
    playerNumberStream << "Status: Computer" << endl;
    mPlayerName = Gtk::TextBuffer::create();
    mPlayerName->set_text(playerNumberStream.str().c_str());

    mPlayerTextBox.set_buffer(mPlayerName);
    // Disables Rage Quit and Discard button when computer
    mRageQuit.set_sensitive(false);
    mDiscard.set_sensitive(false);
}

void PlayerInfoBox::AddToDiscardPile(Rank r, Suit s) {
    cout << endl << "Moving to discard pile: " << r << s << endl << endl;
    mDiscardPile.AddCard(r, s);
}

void PlayerInfoBox::DeleteDiscardPile() {
    mDiscardPile.Reset();
}
