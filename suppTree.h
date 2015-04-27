#ifndef SUPPTREE_H
#define SUPPTREE_H
#include <string>
#include <json/json.h>


struct SuppNode{
    std::string name;
    int rating;
    std::string description;
    SuppNode *parent;
    SuppNode *leftChild;
    SuppNode *rightChild;

    SuppNode(){};

    SuppNode(std::string in_name, int in_rating, std ::string in_description)
    {
        name = in_name;
        rating = in_rating;
        description = in_description;
    }

};

class SuppTree
{

    int opCount;
    public:
        SuppTree();
        virtual ~SuppTree();
        void printInOrder();
        void printHighFirst();
        void printLowFirst();
        int countSupps();
        void addToArray(std::string name, int rating, std::string description);
        void deleteSupp(std::string name);
        void addSupp(std::string name, int rating, std::string description);
        SuppNode* searchSuppTree(SuppNode * node, std::string name, json_object * traverseLog);
        void findSupp(std::string name);
        void buySupp(std::string name);
        void bubbleSort(SuppNode *array [52], int n);
       void printSorted();
        //void helpDelete(SuppNode *node);
        void initJson();
        void rateSupp(int rating);
        json_object* getJsonObject();

    protected:
    private:
        void DeleteAll(SuppNode * node); //use this for the post-order traversal deletion of the tree
        void printInOrder(SuppNode * node, json_object * traverseLog);
        void printHighFirst(SuppNode *node, json_object * traverseLog);
        void printLowFirst(SuppNode *node, json_object * traverseLog);
        int countSupps(SuppNode *node);

        SuppNode* searchSuppTree(SuppNode * node, std::string name, int rating, json_object * traverseLog);
        SuppNode *root;
        json_object * ProjectOutput;
        SuppNode* suppArray[52];


};

#endif // SUPPTREE_H
