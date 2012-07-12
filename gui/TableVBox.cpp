#include "TableVBox.h"
#include "RowHBox.h"
#include <iostream>
using namespace std;

// Constructor - it creates the 4 suits in a Hbox each
TableVBox::TableVBox() : mPanel(false, 5) {

}

void TableVBox::Display() {
    // Sets some paramters
        //set_border_width(10);

    // Set the look of the panel;
    add(mPanel);

    for (int i = 0; i < 4; i++) {
        mSuits[i] = new RowHBox(5, i);
        mPanel.pack_start(*mSuits[i], Gtk::PACK_SHRINK);
        cout << "this should be adding hbox " << i << endl;
    }

    // The final step is to display the buttons (they display themselves)
    show_all_children();
}

// Deletes the suit hboxes
TableVBox::~TableVBox(){
    for (int i = 0; i < 4; i++) {
        delete mSuits[i];
    }
}

void TableVBox::update(){
    for (int i = 0; i < 4; i++) {
        mSuits[i]->update();
    }
}