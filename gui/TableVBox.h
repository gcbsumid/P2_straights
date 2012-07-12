#ifndef TABLE_VBOX
#define TABLE_VBOX

#include <gtkmm/frame.h>
#include "RowHBox.h"

class RowHBox;

class TableVBox : public Gtk::Frame {
public:
    TableVBox();
    ~TableVBox();
    void update();
    void Display();
private:
    Gtk::VBox mPanel;
    RowHBox* mSuits[4];
};

#endif