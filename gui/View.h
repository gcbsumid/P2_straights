#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/actiongroup.h>
#include "TableVBox.h"
//#include "gameplay/GamePlay.h"
//#include "gameplay/GameState.h"

//class GamePlay; // Controller
//class GameState; // Model

class DeckGui;  // Images of cards.

class View : public Gtk::Window {
    //, public ControllerObserver, public ModelObserver
public:
    View(DeckGui* deck);
    //View(Controller*, Model*);
    virtual ~View();
    virtual void update(); 
    // Observer Pattern: concrete update() method

private:
    // Observer Pattern: to access Model accessors without having to downcast subject
    //GameState* mGameState;
    
    // Strategy Pattern member (plus signal handlers)
    //GamePlay* mGamePlay;

    // Card Images
    DeckGui* mDeck;

    // Signal Handlers
    virtual void onNewGame();
    virtual void onNewSeed();
    virtual void onQuit();

    // Member Widgets;
    TableVBox mTable;       // This is where all the cards on table is shown
    Gtk::VBox mMenu;
    Gtk::VBox mPanel;       // This is the container for all objects

    Glib::RefPtr<Gtk::UIManager> mRefUIManager;
    Glib::RefPtr<Gtk::ActionGroup> mRefActionGroup;
};

#endif
