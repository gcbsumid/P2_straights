// Include our written code
#include "gui/View.h"
#include "gameplay/GamePlay.h"

// Include C++ Libraries
#include <string>
#include <iostream>
#include <stdlib.h>

// Include Gtkmm Libraries
#include <gtkmm/main.h>

using namespace std;

int main(int argc, char** argv) {
    cout << "Started main" << endl;
    
    // Create a gameplay object that will be passed down to the view
    GamePlay* gameplay = new GamePlay();

    // Initialize gtkmm with the command line arguments, as appropriate.
    Gtk::Main kit(argc, argv);
    cout << "Initialized gtkmm" << endl;

    // Creating the Deck of images and the View Object
    DeckGui deck;
    View view(&deck, gameplay);
    gameplay->AddView(&view);
    gameplay->AddModelObserver(&view);
    
    // Show the window and return when it is closed.
    Gtk::Main::run(view);               
    
    delete gameplay;
    return 0;
}
