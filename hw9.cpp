//
//  main.cpp
//  hw8part2
//
//  Created by Casey Taylor on 6/2/17.
//  Copyright © 2017 Casey Taylor. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class YogurtOrder{
    
public:
    //constructor
    YogurtOrder(int n);
    //declare public functions
    void addFlavor(string f);
    void printOrder();
    double getPrice();
    unsigned long getFlavorCount();
    void setSize(string s);
    void clearFlavors();
    
private:
    //member variables
    string size;
    vector <string> flavor;
    int flavorCounter;
    int orderNumber;
    
};

//member function definitions
YogurtOrder::YogurtOrder(int n){
    orderNumber = n;
    flavor.clear();
    flavor.resize(0);
}

/*This function sets the yogurt size, allowing it to be accessed by functions 
 @param string s represents the size of the yogurt
 @returns void
 */
 void YogurtOrder::setSize(string s){
    size = s;
}


/*This function adds inputted flavor to the vector flavor
 @param string f is the flavor being added
 */
void YogurtOrder::addFlavor(string f){
    flavor.push_back (f);
}

/*This function determines the price of the order depending on the selected size
 @param void
 @return double, the price of the order depending on size
 */
double YogurtOrder::getPrice(){
    //if yogurt size is small... price is 2.19
    if (size == "small"){
        cout << endl;
        return 2.19;
    }
    //if yogurt size is medium... price is 3.49
    if (size == "medium"){
        cout << endl;
        return 3.49;
    }
    //if yogurt size is large... price is 4.49
    if (size == "large"){
        cout << endl;
        return 4.49;
    }
    return 0;
}

/*This is a getter function for flavor count, which is associated with the size of the vector flavor (number of flavors)
 */
unsigned long YogurtOrder::getFlavorCount(){
    return flavor.size();
}

/* This function prints the order summary, including the size and the first four letters of each selected flavor
 @param void
 @return void
 */
void YogurtOrder::printOrder(){
    string ordername;
    int i = 0;
    //update the ordername with the first four letters of each inputted flavor, allowing up to 10 flavors
    while (i <= flavor.size()){
        ordername += (flavor[i].substr(0,4) + "-");
        i++;
    }
    //output the final order summary
    ordername = ordername.substr(0, ordername.size()-2);
    cout << "** Order " << orderNumber << ": " << size << " " << ordername << " **" << endl << endl;
    
    return ;
}

/*This functions clears and resizes the flavor vector to zero, eliminating any problems with the buffer and allowing for modifications to be made
 @param void
 @returns void
 */
void YogurtOrder::clearFlavors(){
    flavor.clear();
    flavor.resize(0);
}

//declare functions here
void printWelcomeMessage();
double getYogurtSize(string& yogurtSize);
void getYogurtFlavors(vector<string>&flavor, int flavorCounter);
void printOrder(const vector<string>&flavor, int orderNumber, const string& yogurtSize);
bool addAnotherOrderQ();
void printTotalCosts(double total);
double processOrder(YogurtOrder& Order);
bool modifyOrderQ();

int main() {
    
    
    // initialize the loop variables
    bool repeat = 1;
    int orderNumber = 1;
    bool modify = 1;
    vector <YogurtOrder> allOrders;
    
    // Variable for cost
    double total=0;
    
    // Print the welcome message
    printWelcomeMessage();
    
    // Continue to get orders until the user is done
    while(repeat == 1) {
        YogurtOrder Order(orderNumber);
        
        //processOrder function returns price of the order
        //update total price by adding price of individual order
        total+= processOrder(Order);
        allOrders.push_back(Order);
        
        // Determine whether or not to keep repeating.
        repeat = addAnotherOrderQ();
        orderNumber++;
        
    }
    //print out all orders saved in the vector
    for(int i=0; i < allOrders.size(); i++){
        allOrders[i].printOrder();
        
    }
    //asks the customer whether or not they would like to modify an order
    modify = modifyOrderQ();
    
    //while the user indicates that they would like to modify...
    while(modify == 1){
        int modifyOrderNum;
        //prompt user for the order number that they intend to modify
        cout << "Which order?: ";
        cin >> modifyOrderNum;
        cin.ignore();
        cout << endl;
        
        //if the indicated order number is not within bounds...
        if (modifyOrderNum > allOrders.size()){
            cout << "That is not a valid order number" << endl << endl;
        } else { //if the indicated order number is valid, proceed to modify it
            processOrder(allOrders[modifyOrderNum-1]);
        
        }
        //print out all orders saved in the vector
        for(int i=0; i < allOrders.size(); i++){
            allOrders[i].printOrder();
        }
        //ask the customer again if they would like to modify any orders
        modify = modifyOrderQ();
       
    }

    
    // Print out the tax, and total
    printTotalCosts(total);
    
    return 0;
}



/*This function prints a welcome message
 @param void
 @return void
 */
void printWelcomeMessage() {
    cout << "Welcome to My Frozen Yogurt!" << endl << endl;
    return ;
}


/*This function asks whether or not the customer wants to place another order
 @param void
 @returns bool, true or false value indicating whether the customer wants another order (true = yes, false = no)
 */
bool addAnotherOrderQ() {
    //prompts customers to answer whether they would like to add another order
    string response;
    cout << "Would you like to add another order?" << endl;
    cout << "Please enter yes or no: ";
    getline (cin, response);
    //if customers indicates that they want another order, return true
    if (response == "yes"){
        cout << endl;
        return true;
    }
    else{ //if customer does not want another order, return false
        cout << endl;
        return false;
    }
}
/* This function asks whether or not the customer wants to modify any previous orders
 @param void
 @returns bool, true or false value indicating whether they would like to modify (true = yes, false = no)
 */
bool modifyOrderQ() {
    string modify;
    cout << "Would you like to change any of these orders?" << endl;
    cout << "Please enter yes or no:";
    getline (cin, modify);
    //if customer indicates that they want to modify, return true
    if (modify == "yes"){
        cout << endl;
        return true;
    }
    else { //if customer does not want to modify, return false
        cout << endl;
        return false;
    }
}

/*This function calculates the sales tax and adds it to the total before printing out the total price
 @param is the total of the customers order
 @returns the total price of the order, incorporating sales tax
 */
void printTotalCosts(double total){
    double salesTax = 0.0875;
    //print out only two numbers after the decimal place
    cout << setprecision(2) << fixed;
    cout << "total: $" << total << endl;
    //calculate the sales tax by multiplying total by 0.875
    cout << "Tax (8.75%): $" << total * salesTax << endl;
    //calculate total price by adding sales tax to total
    cout << "Total: $" << total + (total * salesTax) << endl << endl;
    return ;
}

/*This function processes the order: it first takes input of yogurtSize, then prompts for the selection of up to 10 flavors, and then prints the order summary.
 @param orderNumber keeps track of the order number
 @returns double, the price of the order
 */
double processOrder(YogurtOrder& Order){
    string yogurtSize;
    
    //prompt customer to select size
    cout << "What size would you like?" << endl;
    cout << "Please enter small, medium, or large: ";
    getline (cin, yogurtSize);
    Order.setSize(yogurtSize);
    
    string yogurtFlavor;
    //initialize flavorCounter to 1
    int flavorCounter = 1;
   
    //make sure that flavor vector is clear
    Order.clearFlavors();
    
     //while inputted yogurt flavor does not equal "DONE" and the vector has not exceeded max size of 10, add the flavor to vector flavor
    while (yogurtFlavor != "DONE" && Order.getFlavorCount() <= 9){
        cout << "Enter flavor " << flavorCounter << ": ";
        getline (cin, yogurtFlavor);
        if (yogurtFlavor != "DONE") {
            Order.addFlavor(yogurtFlavor);
            ++flavorCounter;
        }
    }
    
    //returns the price of the order
    return Order.getPrice();
    
}


