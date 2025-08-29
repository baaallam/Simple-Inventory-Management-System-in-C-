#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Structure to hold inventory items
struct Item {
    string name;
    int quantity;
    double price;
};

vector<Item> inventory;

// Widgets
Fl_Input *nameInput, *quantityInput, *priceInput;
Fl_Multiline_Output *output;

// Helper function to refresh inventory display
void refreshDisplay() {
    stringstream ss;
    if (inventory.empty()) {
        ss << "Inventory is empty.\n";
    } else {
        ss << "Current Inventory:\n";
        for (const auto &item : inventory) {
            ss << "Name: " << item.name
               << ", Quantity: " << item.quantity
               << ", Price: $" << item.price << "\n";
        }
    }
    output->value(ss.str().c_str());
}

// Callback to add item
void addItemCallback(Fl_Widget*, void*) {
    Item newItem;
    newItem.name = nameInput->value();
    newItem.quantity = atoi(quantityInput->value());
    newItem.price = atof(priceInput->value());
    inventory.push_back(newItem);
    refreshDisplay();
}

// Callback to remove item
void removeItemCallback(Fl_Widget*, void*) {
    string name = nameInput->value();
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == name) {
            inventory.erase(it);
            break;
        }
    }
    refreshDisplay();
}

// Main function
int main() {
    Fl_Window *window = new Fl_Window(600, 400, "Inventory System");

    nameInput = new Fl_Input(100, 20, 200, 25, "Name:");
    quantityInput = new Fl_Input(100, 60, 200, 25, "Quantity:");
    priceInput = new Fl_Input(100, 100, 200, 25, "Price:");

    Fl_Button *addButton = new Fl_Button(320, 20, 100, 25, "Add Item");
    addButton->callback(addItemCallback);

    Fl_Button *removeButton = new Fl_Button(320, 60, 100, 25, "Remove Item");
    removeButton->callback(removeItemCallback);

    output = new Fl_Multiline_Output(50, 150, 500, 200);
    refreshDisplay();

    window->end();
    window->show();
    return Fl::run();
}
