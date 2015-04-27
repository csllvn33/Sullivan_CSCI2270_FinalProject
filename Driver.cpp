#include <iostream>
#include "suppTree.h"
#include <fstream>  //allows istream/ostream
#include <string>
#include <json/json.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Supplement{
    string name;
    string rating;
    string description;
    //string stock;
    Supplement(){};

    Supplement(string in_name, string in_rating, string in_description)
    {
        name = in_name;
        rating = in_rating;
        description = in_description;
    }
};
Supplement *suppArray[52];
void displayMenu();
int getFileSize(char * fileName);
void readFileIntoTree(SuppTree * ST, char * fileName);

int main(int argc, char*argv[])
{
    int input;
    // Determine the size of the text file.
    //int fileSize = getFileSize(argv[1]);
    //cout << "about to create object\n";
    // Create a new communication network
    SuppTree *ST = new SuppTree();

    // Read each line and add it to tree
    readFileIntoTree(ST, argv[1]);

    // Flag used for exiting menu
    bool quit = false;

    // Used for input
    string name;

    while(quit != true)
    {
        displayMenu();
        cin >> input;

        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input)
        {
            // Find a movie
            /*
            case 1:
                cout << "Enter title:" << endl;
                getline(cin,title);
                mt->findMovie(title);
                break;
            */
            // Rent a movie
            case 1:
                cout << "Enter Name:" << endl;
                getline(cin,name);
                ST->buySupp(name);
                break;
            // Print the inventory
            case 2:
                ST->printInOrder();
               // ST->printSorted();
                break;

            // Delete Node
            case 3:
                cout << "Enter Name:" << endl;
                getline(cin,name);
                ST->deleteSupp(name);
                break;
            // Count Tree
            case 4:
                cout << "Tree contains: " << ST->countSupps() << " Supplements." << endl;
                break;
            case 5:
                cout << "Enter exact name: " << endl;
                getline(cin,name);
                ST->findSupp(name);
                break;
            case 6:
                
               // ST->printSorted();
            // Quit
            case 7:
                cout << "Goodbye!" << endl;
                quit = true;
                break;
            // invalid input
            default:
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                break;
        }
    }

    // Write our JSON object to a file
    ofstream myfile;
    myfile.open("supplementsOutput.txt");
    myfile << json_object_to_json_string_ext(ST->getJsonObject(), JSON_C_TO_STRING_PRETTY);
    myfile.close();


    // Free memory and return
    delete ST;

    return 0;
}

/*displays a menu with options to enqueue and dequeue a message and transmit the entire message and quit*/
void displayMenu()
{
    cout << "======Main Menu=====" << endl;
    //cout << "1. Find a movie" << endl;
    cout << "1. Buy a Supplement" << endl;
    cout << "2. Print the inventory" << endl;
    cout << "3. Delete a supplement" << endl;
    cout << "4. Count the supplements" << endl;
    cout << "5. Search for a supplement" << endl;
    cout << "6. See supplement ratings in order" << endl;
    cout << "7. Quit" << endl;
    return;
}

/*grabs the number of words in a file */
int getFileSize(char * fileName)
{
    ifstream in_stream;
    in_stream.open(fileName);
    int count = 0;
    string word;

    while (!in_stream.eof())
    {
        getline(in_stream,word);
        count++;
    }

    in_stream.close();

    return count;
}

/* reads file into tree */
void readFileIntoTree(SuppTree * ST, char * fileName)
{
    //cout << "reading file" << endl;
    ifstream in_stream;
    cout << fileName << endl;
    in_stream.open(fileName);
   // cout << "opened" << endl;
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }
    string name;
    string rating;
    string description;
    string stock;
    //string stock;
for(int i = 0; i < 51; i++){
    while (!in_stream.eof())
    {  // cout << "inside while loop" << endl;
        name ="";
        getline(in_stream, name, ',');
        getline(in_stream, rating, ',');
        getline(in_stream, description, ',');
        getline(in_stream, stock);
       // getline(in_stream, quantity); // "\n" is the default delimiter
        
        if (name != "")
        {
          //  cout << " inside if statement" << endl;
            //cout << "Adding: " << name << endl;
            ST->addSupp(name, atoi(rating.c_str()), description, atoi(stock.c_str()));
           // suppArray[i] = 

        }

        }
    }
}
