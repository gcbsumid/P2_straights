/*
 *  Deck.cc
 *  
 *
 *  Created by Caroline Kierstead on 25/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */
#include "DeckGui.h"
#include <algorithm>
#include <iterator>
#include <string>
using std::string;
using std::transform;

// Sets up an array of the Portable Network Graphics (PNG) file names that contain the necessary card images.
// The deck will load the contents into pixel buffers for later use.
const char * image_names[] = {   
    // Set up ACE of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_0.png", "img/1_0.png", "img/2_0.png", "img/3_0.png",
    // Set up TWO of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_1.png", "img/1_1.png", "img/2_1.png", "img/3_1.png",
    // Set up THREE of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_2.png", "img/1_2.png", "img/2_2.png", "img/3_2.png",
    // Set up FOUR of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_3.png", "img/1_3.png", "img/2_3.png", "img/3_3.png",
    // Set up FIVE of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_4.png", "img/1_4.png", "img/2_4.png", "img/3_4.png",
    // Set up SIX of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_5.png", "img/1_5.png", "img/2_5.png", "img/3_5.png",
    // Set up SEVEN of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_6.png", "img/1_6.png", "img/2_6.png", "img/3_6.png",
    // Set up EIGHT of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_7.png", "img/1_7.png", "img/2_7.png", "img/3_7.png",
    // Set up NINE of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_8.png", "img/1_8.png", "img/2_8.png", "img/3_8.png",
    // Set up TEN of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_9.png", "img/1_9.png", "img/2_9.png", "img/3_9.png",
    // Set up ELEVEN of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_10.png", "img/1_10.png", "img/2_10.png", "img/3_10.png",
    // Set up QUEEN of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_11.png", "img/1_11.png", "img/2_11.png", "img/3_11.png",
    // Set up KING of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_12.png", "img/1_12.png", "img/2_12.png", "img/3_12.png",
    // Set up the back of a card for a place holder/null card
    "img/back_1.png"
}; 

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
    return Gdk::Pixbuf::create_from_file( name );
} // createPixbuf

DeckGui::DeckGui()  {
    // Images can only be loaded once the main window has been initialized, so cannot be done as a static
    // constant array. Instead, use the STL transform algorithm to apply the method createPixbuf to every
    // element in the array of image names, starting with first and ending with the last. New elements are
    // added to the back of deck.
    transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], 
               std::back_inserter(deck), &createPixbuf );
} // DeckGui::DeckGui

DeckGui::~DeckGui() {
} // DeckGui::~DeckGui

// Returns the image for the specified card.
Glib::RefPtr<Gdk::Pixbuf> DeckGui::image( Rank f, Suit s ) {
    int index = ((int) f)*4 + ((int) s );
    return deck[ index ];
} // DeckGui::getCardImage 

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckGui::null() {
    int size = deck.size();
    return deck[ size-1 ];
} // DeckGui::getNullCardImage
