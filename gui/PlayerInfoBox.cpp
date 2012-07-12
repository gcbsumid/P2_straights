#include "PlayerInfoBox.h"
#include <sstream>
#include <iostream>
using namespace std;

PlayerInfoBox::PlayerInfoBox(bool isHuman, int playerNum) : 
    VBox(false, 2), mPlayerNumber(playerNum), mIsHuman(isHuman), 
    mScore(0), mButtonBox(false), mScoreTextBox(false),
    mRageQuit("Rage Quit"), mDiscard("Discard") {

    // set sme properties of the box
    stringstream playerNumberStream, scoreStream; 
    playerNumberStream << "Player " << playerNum << endl;
    set_name(playerNumberStream.str().c_str());
    add(mPanel);

    // Displays the score
    scoreStream << mScore << endl;
    mScoreTextBox.set_name(scoreStream.str().c_str());
    add(mScoreTextBox);

    //Add Button container
    add(mButtonBox);

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
}

void PlayerInfoBox::DiscardButtonPressed() {
    // TODO: Prompts for the discard pile from GamePlay
    //       and then displays a popup displaying all 
    //       discarded cards
}