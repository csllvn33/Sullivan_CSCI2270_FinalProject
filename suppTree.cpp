#include <iostream>
#include "suppTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <json/json.h>

using namespace std;

/*
Function prototype:
SuppTree();

Function description:
This constructor method initializes the private variables for the class

Example:
will not be called

Precondition: variables found in the constructor must be in the "private" portion of the class
Post condition: variables are initialized.
*/
SuppTree::SuppTree()
{
    root = NULL;
    opCount = 1;
    ProjectOutput = json_object_new_object();
}


/*
Function prototype:
virtual ~SuppTree();

Function description:
This destructor method will be called when the user wants to exit the program and deletes the nodes in the BST

Example:
automatically called when the program ends.
Will delete nodes upon user input "6"

Precondition: root must be defined in order for the deletion to be successful
Post condition: tree deleted node-by-node through the "deleteAll(node)" function.
*/
SuppTree::~SuppTree()
{
    DeleteAll(root);

    // Clean up json object
    json_object_put(ProjectOutput);
}


/*
Function prototype:
void deleteMovie(string)

Function description:
This method calculates takes a node, the root, as a parameter and deletes each node through recursive calls. The 
deletion is executed through a post-order tree traversal.

Example:
DeleteAll(root);

Precondition: node passed in must be the root in order to complete a successfull tree deletion
Post condition: DeleteAll method will result in an empty tree if executed correctly
*/
/* Used to delete all nodes in the tree */
void SuppTree::DeleteAll(SuppNode * node)
{
    // clean to the left
    if (node->leftChild != NULL)
        DeleteAll(node->leftChild);
    // clean to the right
    if (node->rightChild != NULL)
        DeleteAll(node->rightChild);
    // delete this node
    delete node;

    return;
}


/*
Function prototype:
void initJson()

Function description:
This method initializes the json code output to one specific variable to access throughout the class

Example:
function serves as a constructor, will not be called

Precondition: include Json library and use Json formatting in code
Post condition: Project output can be used to store the json operations.
*/
void SuppTree::initJson()
{
    ProjectOutput = json_object_new_object();
}


/*
Function prototype:
void printInOrder()

Function description:
This method does not take any parameters. The purpose of this function is to call the private function
"printInOrder(node, traverselog)". Calling this function is cleaner than producing the print statements
in the other function.

Example:
printInOrder();

Precondition: Must include the private function printInOrder(node, traverseLog) to properly work
Post condition: Supplements are printed in order, which in this case, prints the supplements in alphabetical order.
/* Helper for the printMovieInventory recursive function */
void SuppTree::printInOrder()
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    printInOrder(root,travLog);

    // Update our json object
    json_object *jsonOperation = json_object_new_string("traverse");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(ProjectOutput,to_string(opCount).c_str(),newJSON);

    opCount++;

    return;
}


/*
Function prototype:
void printInOrder();

Function description:
This method is a private version of the previous method. The recursive calls enables the tree to be printed
in alphabetical order.

Example:
printInOrder(root, traverseLog);

Precondition: For a successfuly BST print, the root should be passed in as the node parameter.
Post condition: BST printed in alphabetical order.
*/
/* Prints the inventory(in order traversal) */
void SuppTree::printInOrder(SuppNode * node, json_object * traverseLog)
{
   
    // Left Node
    if(node->leftChild!=NULL)
        printInOrder(node->leftChild,traverseLog);

    // Value
    cout<<"Supplement: "<<node->name<< endl;

    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->name.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=NULL)
        printInOrder(node->rightChild,traverseLog);

    return;
}

/*
Function prototype:
void addSupp(name, rating, description);

Function description:
This method adds the contents from "supplements.txt" into a BST. The contents are separated in Driver.cpp
and when called, names are compared and sorted as a normal BST.

Example:
addSupp("Nutrex OUTRAGE", 90, "pre-workout"); (This information would be found in the .txt file)

Precondition: Proper use of the getline method in Diver.cpp is necessary for code. names must be strings, ratings ints 
and descriptions strings.
Post condition: Contents passed in are stored into a node which is also added into the BST in proper order.
*/
void SuppTree::addSupp(string name, int rating, string description, int stock)
{
    int index = 0;

    //cout << "entered!\n";
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    // Create a log for the traversal
    json_object * travLog = json_object_new_array();

    // Create the node we will be inserting
    SuppNode * newSupp = new SuppNode(name, rating, description, stock);
    SuppNode * x = root;
    SuppNode * y = NULL;

   // cout << x->name << endl;
    // Do we have an empty tree?
     if (root == NULL){
            root = newSupp;
           suppArray[index] = newSupp;
            }   

        // If the tree is not empty
        else
        {
            suppArray[index] = newSupp;

            // Get to the end of the tree, where we need to add this node.
            while (x != NULL)
            {
                // Add the current node to the traversal log before moving to next.
                json_object *curTitle = json_object_new_string(x->name.c_str());
                json_object_array_add(travLog, curTitle);

                y = x;
                
                if(newSupp->name.compare(x->name) < 0){
                   
                    x = x->leftChild;
                
                }   
                else{
                  
                    x = x->rightChild;
                    
                    }
                }

            // set the parent of this node to be the previous node.
            newSupp->parent = y;

            // Determine which child to this previous node we are at.
            if (newSupp->name.compare(y->name) < 0)
                y->leftChild = newSupp;
            else
                y->rightChild = newSupp;
    }




    // Update our json object
    json_object *jsonOperation = json_object_new_string("add");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonTitle = json_object_new_string(name.c_str());
    json_object_object_add(newJSON,"parameter",jsonTitle);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(ProjectOutput,to_string(opCount).c_str(),newJSON);
    opCount++;


    return;

}


/*
Function prototype:
void findSupp(string name);

Function description:
This method simply calls searchSuppTree(node, name, traverselog). This particular method is passed in
the name of a supplement to search for. Although this method does not actual search, the print statements are 
found in this method.

Example:
findSupp("RSP Nutrition CLA");

Precondition: Name must be typed in exactly when passed in as a parameter or will not be found.
Post condition: Method prints contents of the supplement the user wanted to find
*/
/* used to find movie information, provides info or says supp can't be found */
void SuppTree::findSupp(std::string name)
{
    // Create a traversal log
    json_object * travLog = json_object_new_array();
    // Find the movie
    SuppNode * foundSupp = searchSuppTree(root,name, travLog);
    if (foundSupp != NULL)
    {
        cout << "Supplement Info:" << endl;
        cout << "===========" << endl;
        cout << "Rating: " << foundSupp->rating << endl;
        cout << "Name: " << foundSupp->name << endl;
        cout << "Type: " << foundSupp->description << endl;
        cout << "Stock: " << foundSupp->stock << endl;
        //cout << "Quantity:" << foundSupp->quantity << endl;
        
    }
    else
        cout << "Supplement not found." << endl;

    return;
}


/*
Function prototype:
SuppNde* searchSuppTree(SuppNode * node, string name, json_object traverseLog);

Function description:
Method will kepp searching for the name passed in via recursive calls. If that name does not exist then
the user is notified.

Example:
searchSuppTree(root, "RSP Nutrition CLA", traverseLog);

Precondition: Node passed in should be root to successfully search entire tree. Also, name must be exact - including capital
letters.
Post condition: Node containing the name passed in is returned. This returned node can be used in other methods.
*/
SuppNode* SuppTree::searchSuppTree(SuppNode * node, string name, json_object * traverseLog)
{
    // Add the current node to the traverse log
    if (node != NULL)
    {
        json_object *curTitle = json_object_new_string(node->name.c_str());
        json_object_array_add(traverseLog, curTitle);
    }

    // If the node is NULL, we just return. Failed to find node.
    if (node == NULL)
        return NULL;
    // Return this node if it is the one we are searching for
    else if (node->name == name)
        return node;

    // Else return the correct recursive call.
    else
    {
        if(name.compare(node->name) < 0)
            return searchSuppTree(node->leftChild, name,traverseLog);

        else
            return searchSuppTree(node->rightChild, name, traverseLog);
    }
}



/*
Function prototype:
void buySupp(string name);

Function description:
This method decrements the stock of a certain supplement when user buys it. Uses the searchSuppTree function
to find the name passed in.

Example:
buySupp("RSP Nutrition CLA");

Precondition: Supplement Should have >= 1 in stock to buy.
Post condition: If bought, supplement stock is decremented. When stock = 0, supplement is deleted via the
deleteSupp method.
*/

void SuppTree::buySupp(std::string name)
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    int stockOutput = 0;

    json_object * travLog = json_object_new_array();
    SuppNode * foundSupp = searchSuppTree(root, name,travLog);

    // If the Supplement exists.
    if (foundSupp != NULL)
    {
        // If it's in stock.
        if (foundSupp->stock > 0)
        {
            cout << "Supplement has been bought." << endl;
            foundSupp->stock--;
            stockOutput = foundSupp->stock;

            // Update our json object
            json_object *jsonOperation = json_object_new_string("buy");
            json_object_object_add(newJSON,"operation",jsonOperation);
            json_object *jsonTitle = json_object_new_string(name.c_str());
            json_object_object_add(newJSON,"parameter",jsonTitle);
            json_object *jsonOutput = json_object_new_string(to_string(stockOutput).c_str());
            json_object_object_add(newJSON,"output",jsonOutput);
            json_object_object_add(ProjectOutput,to_string(opCount).c_str(),newJSON);

            opCount++;

            //change this to print information
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Rating:" << foundSupp->rating << endl;
            cout << "Name:" << foundSupp->name << endl;
            cout << "Type:" << foundSupp->description << endl;
            cout << "Stock:" << foundSupp->stock << endl;
            // If the stock is 0 delete the movie
            if (foundSupp->stock == 0)
                deleteSupp(foundSupp->name);

        }
        // If it's not in stock.
        else
            cout << "Supplement out of stock." << endl;

    }
    // If it doesn't exist.
    else
        cout << "Supplement not found." << endl;

}



/*
Function prototype:
void deleteSupp(string name);

Function description:
Method is passed in a name, which is then passed into searchSuppTree. Once node is found, it resets
parents and children, then deletes the node.

Example:
deleteSupp("RSP Nutrtion CLA");

Precondition: Name must be exact, node must exist, and seachSuppTree must work properly.
Post condition: Supplement desired to be deleted will be deleted without cutting off any branches of the tree.
*/
void SuppTree::deleteSupp(std::string name)
{

    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    json_object * travLog = json_object_new_array();
    SuppNode * foundSupp = searchSuppTree(root, name,travLog);

    // If the movie exists
    if (foundSupp != NULL)
    {
        // If it has no children
        if (foundSupp->leftChild == NULL && foundSupp->rightChild == NULL)
        {
            // If this node is the left child, set the parents left child to NULL
            if (foundSupp->parent->leftChild == foundSupp)
                foundSupp->parent->leftChild = NULL;
            // Else, this node is the right child, set that to NULL
            else
                foundSupp->parent->rightChild = NULL;
            // Delete the node
            delete foundSupp;

        }
        // If it only has a left child
        else if (foundSupp->rightChild == NULL)
        {
            if (foundSupp->parent->leftChild == foundSupp)
                foundSupp->parent->leftChild = foundSupp->leftChild;
            else
                 foundSupp->parent->rightChild = foundSupp->leftChild;

            delete foundSupp;

        }
        // If it only has a right child
        else if (foundSupp->leftChild == NULL)
        {
            if (foundSupp->parent->leftChild == foundSupp)
                foundSupp->parent->leftChild = foundSupp->rightChild;
            else
                 foundSupp->parent->rightChild = foundSupp->rightChild;

            delete foundSupp;
        }

        // Node has two children, we need the smallest node from the right child
        else
        {
            // Start on the right sub-tree
            SuppNode * replacementNode = foundSupp->rightChild;

            // search for the smallest left child
            while (replacementNode->leftChild != NULL)
            {
                replacementNode = replacementNode->leftChild;
            }

            // Swap in all the info from the replacement to this node we are "deleting"
            foundSupp->name = replacementNode->name;
            foundSupp->rating = replacementNode->rating;
            foundSupp->description = replacementNode->description;
            


            // If the replacement node has a right child, update the parent
            if (replacementNode->rightChild != NULL)
                replacementNode->rightChild->parent = replacementNode->parent;

            // If the replacement node is a left child
            if (replacementNode->parent->leftChild == replacementNode)
                replacementNode->parent->leftChild = replacementNode->rightChild;
            // If it is a right child
            else
                replacementNode->parent->rightChild = replacementNode->rightChild;

            // Delete the node
            delete replacementNode;
        }

        // Update our json object
        json_object *jsonOperation = json_object_new_string("delete");
        json_object_object_add(newJSON,"operation",jsonOperation);
        json_object *jsonTitle = json_object_new_string(name.c_str());
        json_object_object_add(newJSON,"parameter",jsonTitle);
        json_object_object_add(newJSON,"output",travLog);
        json_object_object_add(ProjectOutput,to_string(opCount).c_str(),newJSON);
        opCount++;

    }
    // If it doesn't exist
    else
        cout << "Supplement not found." << endl;



}


/*
Function prototype:
int countSupps();

Function description:
Method calls the private function countSupps(SuppNode *node). This function returns the number produced
when countSupps(SuppNode *node) is called.

Example:
countSupps(); No parameters needed.

Precondition: Private function to count nodes must exist and be called in order for this function to work.
Post condition: Number of Supplements (nodes) are counted and returned.
*/
int SuppTree::countSupps()
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    // Determine the count
    int count = countSupps(root);

    // Update our json object
    json_object *jsonOperation = json_object_new_string("count");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonOutput = json_object_new_string(to_string(count).c_str());
    json_object_object_add(newJSON,"output",jsonOutput);
    json_object_object_add(ProjectOutput,to_string(opCount).c_str(),newJSON);
    opCount++;

    return count;
}

/*
Function prototype:
int countSupps(SuppNode *node);

Function description:
Method counts the number of nodes through recursive calls. 
Example:
countSupps(root);

Precondition: To count all of the nodes in the BST, root should be passed in as a parameter.
Post condition: Method returns the number of nodes in the BST.
*/
int SuppTree::countSupps(SuppNode *node)
{
    if (node == NULL)
        return 0;
    return countSupps(node->leftChild) + countSupps(node->rightChild) + 1;
}



/* getter method for json operations*/
json_object* SuppTree::getJsonObject()
{
    return ProjectOutput;
}

/*
Function prototype:
void printSorted();

Function description:
This method calls the bubble sort method and prints the ratings in ascending order.

Example:
printSorted(); no parameters needed

Precondition:bubble sort method must sort the ratings correctly.
Post condition: ratings are printed in ascending (low to high) order.
*/

void SuppTree::printSorted()
{
    for(int i =0; i < 51; i++)
    {
        bubbleSort(suppArray, 52);
    }
}



/*
Function prototype:
void bubbleSort(int *array, int n);

Function description:
This method sorts the ratings in suppArray through a bubble sort. Method will be called in printSorted()
to show results.

Example:
bubbleSort(suppArray[]->rating, 52); There are 52 items in the array

Precondition: Items in the array must be integers in order to be sorted. In this case, the ratings are being sorted
Post condition: When finished srting, the method produces a sorted array from low rating to high rating.

*/
void SuppTree::bubbleSort(SuppNode *array [52], int n)
{ //n is the size of the array
    int swap;
    for(int c = 0; c < n - 1; c++){
        for(int d = 0; d < n - c - 1; d++){
            if(array[d]->rating > array[d+1]->rating){
                swap = array[d]->rating;
                array[d]->rating = array[d+1]->rating;
                array[d+1]->rating = swap;
            }
        }
    }
    cout<<"sorted list, ascending order:"<<endl;
    for(int c = 0; c < n; c++){
       cout<<array[c]->rating<<endl;
   }
}