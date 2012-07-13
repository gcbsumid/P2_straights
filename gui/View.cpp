#include "View.h"
#include "../gameplay/GamePlay.h"
//#include "../gameplay/GameState.h"
//#include "subject.h" // Will figure out this one
//#include "../gui/DeckGui.h"
#include "TableVBox.h"
#include "RowHBox.h"
#include "DeckGui.h"
#include "PlayerInfoBox.h"
#include <gtkmm/messagedialog.h>

#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

// Creates the table
//View::View(GamePlay* c, GameState* m) : mGameState(m), mGamePlay(c) {
View::View(DeckGui* deck, GamePlay* gameplay) : Gtk::Window(), mGamePlay(gameplay), mDeck(deck), mTable(deck, gameplay), 
        mMenu(false, 10), mPanel(false, 0), mHand(), mPlayerInfoContainer(true, 5) {
    // Sets some properties in the window
    set_title("Straights");
    maximize();

    // Sets some attributes of the frame
    mTable.set_label("Cards on the Table:");
    mTable.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);
    mTable.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    // Adds the Panel;
    add(mPanel);


    /*****************************
    / THIS IS THE MENU
    *****************************/

    // Adds the menu at the top
    mPanel.add(mMenu);

    // Define the actions:
    mRefActionGroup = Gtk::ActionGroup::create();

    mRefActionGroup->add(Gtk::Action::create("MenuFile","_Game"));
    mRefActionGroup->add(Gtk::Action::create("New Game", "New Game"),
          sigc::mem_fun(*this, &View::onNewGame));
    mRefActionGroup->add(Gtk::Action::create("New Seed", "New Seed"),
          sigc::mem_fun(*this, &View::onNewSeed));
    mRefActionGroup->add(Gtk::Action::create("Quit", "Quit"),
          sigc::mem_fun(*this, &View::onQuit));

    // Define how the actions are presented in the menus and toolbars:
    Glib::RefPtr<Gtk::UIManager> mRefUIManager = Gtk::UIManager::create();
    mRefUIManager->insert_action_group(mRefActionGroup);
    add_accel_group(mRefUIManager->get_accel_group());

    Glib::ustring ui_info = 
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='MenuFile'>"
        "      <menuitem action='New Game' />"
        "      <menuitem action='New Seed' />"
        "      <separator/>"
        "      <menuitem action='Quit' />"
        "    </menu>"
        "  </menubar>"
        "</ui>";

    try {
        mRefUIManager->add_ui_from_string(ui_info);
    } catch (const Glib::Error& ex) {
        cerr << "building menus and toolbars failed: " << ex.what();
    } // catch

    Gtk::Widget* pMenuBar = mRefUIManager->get_widget("/MenuBar");

    /**********************
     * DONE THE MENU       
     ***********************/

    mTable.Display();
    mMenu.pack_start(*pMenuBar);
    mPanel.pack_start(mTable);

    mPanel.pack_start(mPlayerInfoContainer, Gtk::PACK_SHRINK);

    show_all_children();
}

View::~View() {}

void View::onNewGame() {
    // TODO: NEW GAME
    cout << "New Game" << endl;

    //mGamePlay->Quit();
    mGamePlay->PlayGame();
}

void View::onNewSeed() {
    // TODO: NEW GAME
    cout << "New Seed" << endl;
}
 
void View::onQuit() {
    // TODO: NEW GAME
    cout << "Quit" << endl;

    // Closes the main window to stop the Gtk::Main::run()
    hide();
}

// Implementations of the view external interface.
void View::AddPlayer(int player) {
    cout << "Got addplayer signal" << endl;
    stringstream s;
    s << "Is player " << player << " a human or a computer?";
    Gtk::Dialog dialog(s.str());
    dialog.add_button("Human", 1);
    dialog.add_button("Computer", 2);
    int resp = dialog.run();
    cout << "Got response " << resp << endl;
    if (resp == 1) {
        // Human player.
        mGamePlay->AddPlayer(true);
    } else {
        // Computer player.
        mGamePlay->AddPlayer(false);
    }
}


void View::HumanTurn(int player) {
    assert(player > 0 && player < 5);
    cout << "The view sees that it's a human's turn to play " << endl;
    vector<Card*> legalHand = mGamePlay->GetLegal(player);
    if (!legalHand.empty()) {
        cout << "We have legal cards to play" << endl;
        // We have legal cards to play
        mHand[player-1]->DisplayLegalCards(legalHand);
    } else {
        // No legal plays.
        mHand[player-1]->TurnHandToButton();
    }
}
void View::PlayerWon(int player) {}


// Observer pattern - notifications of state changes from model.

// creates an HBox for the hand to be displayed
// also creates a new player
void View::Model_PlayerAdded(bool IsHuman, int playerid) {
    cout << "Hey, apparently some player just got added lol. isHuman " << IsHuman << " id " << playerid << endl;
    assert(playerid > 0 && playerid < 5);
    if (IsHuman) {
        mHand[playerid-1] = new HandHBox(mDeck, mGamePlay, playerid);
        mPanel.add(*mHand[playerid-1]);
        // Displays the player information onto the screen
    } else {
        mHand[playerid-1] = NULL;
    }
    mPlayerInfo[playerid-1] = new PlayerInfoBox(IsHuman, playerid, mGamePlay);
    mPlayerInfoContainer.add(*mPlayerInfo[playerid-1]);
    mPlayerInfo[playerid-1]->show();
}

// Gives the list of cards to the mHand box to be displayed
void View::Model_CardsDealt(vector<vector<Card*> > playerCards) {
    cout << "Got some cards dealt" << endl;
    for (int i = 0; i < 4; i++) {
        if (!playerCards[i].empty()) {
            cout << "Got some human cards dealt" << endl;
            assert(mHand[i] != NULL);
            mHand[i]->AddCards(playerCards.at(i));
            mHand[i]->show();
        }
    }
}

void View::Model_PlayerRageQuitted(int player) {
    cout << "HUMAN is now a COMPUTER." << endl;
    mPlayerInfo[player-1]->HumanToComputer();
}
void View::Model_CardsCleared() {
    // TODO:: Clear table
    mTable.ClearTable();
}
void View::Model_ScoreUpdated(int player, int score) {
    // at the end of the round, this is their accumulative score.
    cout << "Updating Score." << endl;
    assert(player > 0 && player < 5);
    mPlayerInfo[player-1]->UpdateScore(score);
}
void View::Model_DiscardsCleared(int player) {}
void View::Model_CardPlayed(int player, Card* card) {
    assert(player > 0 && player < 5);
    cout << "Apparently, player " << player << " played card " << *card << endl;
    mTable.CardPlayed(card);
    if(mHand[player-1]){
        mHand[player-1]->CardPlayed(card);
        mHand[player-1]->TurnHandToStatic();
    }
}
void View::Model_CardDiscarded(int player, Card*) {}

