#include <string>
#include <iostream>
#include <stdlib.h>
#include <gtkmm/main.h>
//#include "model.h"
//#include "controller.h"
#include "view/View.h"

#include "gameplay/GamePlay.h"

using namespace std;

int main(int argc, char* argv[]) {
    //if (argc == 2) {
        // Seed the random number generator.
    //    int seed = atoi(argv[1]);
    //    srand48(seed);
    //}

    //GamePlay* gameplay = new GamePlay();
    // Play the game, round by round.
    //while(gameplay->PlayRound()) {}


    //delete gameplay;

    Gtk::Main  kit( argc, argv );         // Initialize gtkmm with the command line arguments, as appropriate.
    //Model model;                          // Create model
    //    Controller controller( &model );  // Create controller
    //View view( &controller, &model );     // Create the view -- is passed handle to controller and model
    View view;
    Gtk::Main::run( view );               // Show the window and return when it is closed.
    return 0;
}
