//#include "observer.h"
#include "View.h"
//#include "../gameplay/GamePlay.h"
//#include "../gameplay/GameState.h"
//#include "subject.h" // Will figure out this one
//#include "../gui/DeckGui.h"
#include "TableVBox.h"
#include "RowHBox.h"
#include "DeckGui.h"
#include <iostream>
#include <cassert>
using namespace std;

// Creates the table
//View::View(GamePlay* c, GameState* m) : mGameState(m), mGamePlay(c) {
View::View(DeckGui* deck) : Gtk::Window(), mDeck(deck), mTable(deck), 
        mMenu(false, 10), mPanel(false, 0), mHand() {
    // Sets some properties in the window
    set_title("Straights");
    set_default_size(1000, 1000);

    // Sets some attributes of the frame
    mTable.set_label("Cards on the Table:");
    mTable.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);
    mTable.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    // Adds the Panel;
    add(mPanel);


    /*****************************
    / THIS IS THE MENU CRAP
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
        std::cerr << "building menus and toolbars failed: " << ex.what();
    } // catch

    Gtk::Widget* pMenuBar = mRefUIManager->get_widget("/MenuBar");

    /***********************/
    /* DONE THE MENU SHIT  */
    /***********************/

    mTable.Display();
    mMenu.pack_start(*pMenuBar, Gtk::PACK_SHRINK);
    mMenu.pack_start(mTable, Gtk::PACK_SHRINK);

    /***********************/
    /* ADDING THE PLAYERS  */
    /***********************/

    show_all_children();

    for (int i = 0; i < 4; i++) {
        mHand[i] = new HandHBox(i+1);
        add(mHand[i]);
    }

    //mPanel.add(mTable);
    //mTable.Display();
    // Adds the table to the window
    //mTable = new TableVBox(10);

    //add(*mTable);

    // The final step is to display the buttons (they display themselves)
    //show_all();

}

View::~View() {}

void View::update() {
    //mTable.update();
}

void View::onNewGame() {
    // TODO: NEW GAME
    cout << "New Game" << endl;
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

// gets a call from 
void View::Model_PlayerAdded(bool IsHuman, int playerid) {
    assert(playerid > 0 && playerid < 5);

}

void View::Model_CardsDealt(std::vector<std::std::vector<Card*> > playerCards) {
    assert(playerid > 0 && playerid < 5);
    for (int i = 0; i < 4; i++) {
        if(!playerCards.at(i).empty()){
            mHand[playerid-1]->AddCards(playerCards.at(i));
            mHand[playerid-1]->show();
        }
    }
}