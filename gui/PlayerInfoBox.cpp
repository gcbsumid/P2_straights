#include "PlayerInfoBox.h"
#include <sstream>
#include <iostream>

PlayerInfoBox::PlayerInfoBox(bool isHuman, int playerNum) : 
    HBox(false, 2), mPlayerNumber(playerNum), mIsHuman(isHuman), 
    mScore(0), mRageQuit("Rage Quit"), mDiscard("Discard"), 
    mScoreTextBox(false), mButtonBox(false) {

    // set sme properties of the box
    stringstream playerNumberStream, scoreStream; 
    playerNumberStream << "Player " << playerNum << endl;
    set_title(playerNumberStream.str().c_str());
    add(mPanel);

    scoreStream << mScore << endl;
    mScoreTextBox.set_title(scoreStream.str().c_str());
    add(mScoreTextBox);

    add(mButtonBox);

    mButtonBox.add(mRageQuit);
    mButtonBox.add(mDiscard);

    mRageQuit.signal_clicked().connect(sigc::mem_fun(*this, PlayerInfoBox::RageQuitButtonPressed));
    mDiscard.signal_clicked().connect(sigc::mem_fun(*this, PlayerInfoBox::DiscardButtonPressed));
    
    show_all();
}

PlayerInfoBox::~PlayerInfoBox() {}

void PlayerInfoBox::RageQuitButtonPressed() {
    // TODO: rage quit button.
    // Either GamePlay::RageQuit or View::RageQuit (the view goes to Gameplay)
}

void PlayerInfoBox::DiscardButtonPressed() {
    // TODO: Prompts for the discard pile from GamePlay
    //       and then displays a popup displaying all 
    //       discarded cards
}