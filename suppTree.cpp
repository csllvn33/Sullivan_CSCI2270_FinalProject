#include <iostream>
#include "suppTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <json/json.h>

using namespace std;

SuppTree::SuppTree()
{
    root = NULL;
    opCount = 1;
    ProjectOutput = json_object_new_object();
}

SuppTree::~SuppTree()
{
    DeleteAll(root);

    // Clean up json object
    json_object_put(ProjectOutput);
}

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

void SuppTree::initJson()
{
    ProjectOutput = json_object_new_object();
}

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

/* Prints the inventory(in order traversal) */
void SuppTree::printInOrder(SuppNode * node, json_object * traverseLog)
{
   
    // Left Node
    if(node->leftChild!=NULL)
        printInOrder(node->leftChild,traverseLog);

    // Value
    cout<<"Movie: "<<node->name<< endl;

    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->name.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=NULL)
        printInOrder(node->rightChild,traverseLog);

    return;
}


void SuppTree::addSupp(string name, int rating, string description)
{
    int index = 0;

    //cout << "entered!\n";
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    // Create a log for the traversal
    json_object * travLog = json_object_new_array();

    // Create the node we will be inserting
    SuppNode * newSupp = new SuppNode(name, rating, description);
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

/* used to find movie information, provides info or says movie can't be found */
void SuppTree::findSupp(std::string name)
{
    // Create a traversal log
    json_object * travLog = json_object_new_array();
    // Find the movie
    SuppNode * foundSupp = searchSuppTree(root,name, travLog);
    if (foundSupp != NULL)
    {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        /*cout << "Ranking:" << foundSupp->ranking << endl;
        cout << "Title:" << foundMovie->title << endl;
        cout << "Year:" << foundMovie->year << endl;
        cout << "Quantity:" << foundMovie->quantity << endl;
        */
    }
    else
        cout << "Movie not found." << endl;

    return;
}

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
void SuppTree::buySupp(std::string name)
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    int stockOutput = 0;

    json_object * travLog = json_object_new_array();
    SuppNode * foundSupp = searchSuppTree(root, name, rating,travLog);

    // If the movie exists.
    if (foundSupp != NULL)
    {
        // If it's in stock.
        if (foundSupp->quantity > 0)
        {
            cout << "Movie has been rented." << endl;
            foundSupp->quantity--;
            stockOutput = foundSupp->quantity;

            // Update our json object
            json_object *jsonOperation = json_object_new_string("rent");
            json_object_object_add(newJSON,"operation",jsonOperation);
            json_object *jsonTitle = json_object_new_string(title.c_str());
            json_object_object_add(newJSON,"parameter",jsonTitle);
            json_object *jsonOutput = json_object_new_string(to_string(stockOutput).c_str());
            json_object_object_add(newJSON,"output",jsonOutput);
            json_object_object_add(ProjectOutput,to_string(opCount).c_str(),newJSON);

            opCount++;

            //change this to print information
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << foundMovie->ranking << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout << "Year:" << foundMovie->year << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
            // If the stock is 0 delete the movie
            if (foundMovie->quantity == 0)
                deleteMovieNode(foundMovie->title);

        }
        // If it's not in stock.
        else
            cout << "Movie out of stock." << endl;

    }
    // If it doesn't exist.
    else
        cout << "Movie not found." << endl;

}
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
        cout << "Movie not found." << endl;



}

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

int SuppTree::countSupps(SuppNode *node)
{
    if (node == NULL)
        return 0;
    return countSupps(node->leftChild) + countSupps(node->rightChild) + 1;
}


json_object* SuppTree::getJsonObject()
{
    return ProjectOutput;
}