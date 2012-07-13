#include "PlayerInfoBox.h"
#include "../gameplay/GamePlay.h"
#include "gtkmm/textbuffer.h"
#include "gtkmm/textview.h"
#include <sstream>
#include <iostream>
using namespace std;

PlayerInfoBox::PlayerInfoBox(bool isHuman, int playerNum, GamePlay* gameplay) : 
    VBox(false, 2), mPlayerNumber(playerNum), mIsHuman(isHuman), 
    mScore(0), mGamePlay(gameplay), mButtonBox(false), mRageQuit("Rage Quit"), 
    mDiscard("Discard") {

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
}

void PlayerInfoBox::UpdateScore(int score) {
    // Update Display Scores
    stringstream scoreStream;
    scoreStream << mScore << endl;
    mScoreText->set_text(scoreStream.str().c_str());

    mScoreTextBox.set_buffer(mScoreText);
}

void PlayerInfoBox::HumanToComputer() {
    stringstream playerNumberStream;
    playerNumberStream << "Player " << mPlayerNumber << endl;
    playerNumberStream << "Status: Computer" << endl;
    mPlayerName = Gtk::TextBuffer::create();
    mPlayerName->set_text(playerNumberStream.str().c_str());

    // Disables Rage Quit and Discard button when computer
    mRageQuit.set_sensitive(false);
    mDiscard.set_sensitive(false);
}
