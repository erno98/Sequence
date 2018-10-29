//
// Created by Ernest Pokropek
// 293076
//

#ifndef SEQUENCE_SEQUENCE_H
#define SEQUENCE_SEQUENCE_H


#include <iostream>
#include <new>
#include <string.h>


template <typename Key, typename Info>
class Sequence {

private:
    template <typename aKey, typename aInfo>
    struct Node {
        aKey key;
        aInfo info;

        Node<aKey, aInfo> *next;

        //constructor for Node
        Node(const aKey &k, const aInfo &i){
            key = k;
            info = i;
            next = NULL;
        }
    };

    Node<Key, Info> *head;

    /***************************************************************************
    *  PRIVATE METHODS TO SUPPORT PUBLIC ONES
    ****************************************************************************/

    bool exists(const Key &key, const Info &info);
    // RETURNS:
    //    true, if the element exists in the sequence
    //    false, if the element doesn't exist in the sequence
    // PARAMETERS: key and info of sought node

    int howMany(const Key key, const Info info);
    // RETURNS:
    //   an integer number of how much elements of given
    //   key and info there are in the sequence
    // PARAMETERS: key and info of sought node

    Sequence<Key, Info> merge(const Sequence<Key, Info> &sequence ) const;
    // merges two sequences together, used in operator+ and +=
    // RETURNS:
    //    a merged Sequence<Key, Info> type object
    // PARAMETERS: Sequence<Key, Info> type object

public:


    /***************************************************************************
    *  MEMBER FUNCTIONS
    ****************************************************************************/

    // default constructor
    Sequence();

    // default destructor
    ~Sequence();

    // copy constructor
    Sequence(const Sequence<Key, Info> &sequence);

    // assignment operator
    Sequence<Key, Info> &operator=(const Sequence<Key, Info> &sequence);


    /***************************************************************************
    *  CAPACITY
    ****************************************************************************/

    bool isEmpty();
    // RETURNS:
    //    true, if the sequence has no elements
    //    false, if the sequence has at least 1 element

    unsigned int length() const;
    // RETURNS:
    //    number of nodes in the sequence


/***************************************************************************
*  DISPLAY
****************************************************************************/

    void print();
    // prints the sequence into the output stream

/***************************************************************************
*  MODIFIERS
****************************************************************************/

/***********************************************************************
 *  methods of adding to the sequence
************************************************************************/

    bool pushFront(const Key &newKey, const Info &newInfo);
    // inserts a new element at the beginning of the sequence
    // PARAMETERS: Key and Info of new node
    // RETURNS:
    //    true, if the insert was successful
    //    false, if the element hasn't been added

    bool pushBack(const Key &newKey, const Info &newInfo);
    // inserts a new element at the end of the sequence
    // PARAMETERS: Key and Info of new node
    // RETURNS:
    //    true, if the insert was successful
    //    false, if the element hasn't been added

    bool insertAfter(const Key &key, const Info &info, const Key &newKey, const Info &newInfo, int occurrence = 1);
    // inserts a new element after the given one
    // PARAMETERS: Key and Info of new node,
    //             Key and Info of the node before which the new one is added,
    //             number of node's occurrence*, defaultly 1
    // RETURNS:
    //    true, if the insert was successful
    //    false, if the element hasn't been added

    ///*consider a sequence 2 3 5 1 5. If we want to insert element after second 5, the occurrence value
    /// for the function will be equal to 2. If we won't specify it, element will be added after the first one.


    bool insertBefore(const Key &key, const Info &info, const Key &newKey, const Info &newInfo, int occurrence = 1);
    // inserts a new element before the given one
    // PARAMETERS: Key and Info of new node,
    //             Key and Info of the node before which the new one is added,
    //             number of node's occurrence, defaultly 1
    // RETURNS:
    //    true, if the insert was successful
    //    false, if the element hasn't been added


    /***********************************************************************
     *  methods of removing from the sequence
    ************************************************************************/

    bool remove(const Key &key, const Info &info, int occurrence = 1);
    // removes given element from the sequence
    // PARAMETERS: Key and Info of node to remove,
    //             number of node's occurrence, defaultly 1
    // RETURNS:
    //    true, if the removal was successful
    //    false, if the removal was not successful

    bool removeAllWhere(const Key &key, const Info &info);
    // removes every element from sequence of the given parameters
    // PARAMETERS: Key and Info of node(s) to remove
    // RETURNS:
    //    true, if the removal was successful
    //    false, if the removal was not successful

    bool clearSequence();
    // removes every element from the sequence
    // RETURNS:
    //    true, if the removal was successful
    //    false, if the removal was not successful

/***************************************************************************
*  OPERATIONS
****************************************************************************/


    Sequence<Key, Info> shuffle(const Sequence<Key, Info> &S1, unsigned int start1, unsigned int length1,
                                const Sequence<Key, Info> &S2, unsigned int start2, unsigned int length2,
                                unsigned int count);
    // shuffles the elements of two sequences
    // PARAMETERS:
    //    S1, S2 - given sequences
    //    start1, start2 - starting indexes (first elements) for the sequence shuffle
    //    length1, length2 - how many elements we take for each shuffle from S1 and S2
    //    count - how many shuffle cycles
    // RETURNS: a new, shuffled sequence
    // THROWS: lengthException in case of wrong input (start, count ount of bounds)
    /* EXAMPLE:
     *  s1: 1 2 3 4 5 6 7 8
     *  s2: 10 20 30 40 50 60 70 80 90 100
     *  s3 = shuffle(s1, 2, 2, s2, 0, 3, 4);
     *  s3: 3 4 10 20 30 5 6 40 50 60 7 8 70 80 90 100
     */


    /***************************************************************************
    *  OPERATORS
    ****************************************************************************/

    bool operator==(const Sequence<Key, Info> &sequence) const;
    // compares two sequences
    // PARAMETERS: constant reference to another sequence
    // RETURNS:
    //      true if the sequences are identical (order matters)
    //      false, if the sequences are different

    bool &operator!=(const Sequence<Key, Info> &sequence) const;
    // compares two sequences
    // PARAMETERS: constant reference to another sequence
    // RETURNS:
    //      true if the sequences are different (order matters)
    //      false, if the sequences are identical

    Sequence<Key, Info> operator+(const Sequence<Key, Info> &sequence) const;
    // adds the given sequence to the current one without modifying it
    // PARAMETERS: constant reference to another sequence
    // RETURNS: new merged sequence

    Sequence<Key, Info> &operator+=(const Sequence<Key, Info> &sequence);
    // adds the given sequence to the current one
    // PARAMETERS: constant reference to another sequence
    // RETURNS: current sequence with the given one merged to it




};


/***********************************************************************
*   IMPLEMENTATION
************************************************************************/



template<typename Key, typename Info>
bool Sequence<Key, Info>::exists(const Key &key, const Info &info) {

    Node<Key, Info> *travel = head;

    while(travel != NULL){
        if(travel->info == info && travel->key == key)
            return true;
        else travel = travel->next;
    }

    return false;

}


//--------------------------------------------------------------------------

template<typename Key, typename Info>
Sequence<Key, Info>::Sequence() {

    head = NULL;

}



//--------------------------------------------------------------------------

template<typename Key, typename Info>
Sequence<Key, Info>::~Sequence() {

    clearSequence();

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info> &sequence) {

    head = NULL;
    *this = sequence;

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
Sequence<Key, Info> &Sequence<Key, Info>::operator=(const Sequence<Key, Info> &sequence) {

    if (this == &sequence){
        return *this;
    }

    clearSequence();

    Node<Key, Info> *travel = sequence.head;
    while(travel != NULL){
        this->pushBack(travel->key, travel->info);
        travel = travel->next;
    }
    return *this;

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool Sequence<Key, Info>::pushFront(const Key &newKey, const Info &newInfo) {


    Node<Key, Info> *newNode;

    try {
        newNode = new Node<Key, Info>(newKey, newInfo);
    }
    catch (std::bad_alloc) {
        std::cerr << "Failed allocating memory for the new node" << std::endl;
        return false;
    }

    newNode->next = head;
    head = newNode;

    return true;


}



//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool Sequence<Key, Info>::pushBack(const Key &newKey, const Info &newInfo) {

    // list is empty, setting up the new element as first one
    if(head == NULL){
        pushFront(newKey, newInfo);
        return true;
    }

    // list not empty, finding the last element
    Node<Key, Info> *travel = head;
    while(travel->next != NULL){
        travel = travel->next;
    }

    // travel pointing at last element
    Node<Key, Info> *newNode;
    try {
        newNode = new Node<Key, Info>(newKey, newInfo);
    }
    catch (std::bad_alloc) {
        std::cerr << "Failed allocating memory for the new node" << std::endl;
        return false;
    }

    newNode->next = NULL;
    travel->next = newNode;


    return true;
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool Sequence<Key, Info>::insertAfter(const Key &key, const Info &info, const Key &newKey, const Info &newInfo,
                                      int occurrence) {


    //given element doesn't exists in the sequence
    if(!(this->exists(key, info))){
        std::cerr << "Couldn't find element: {" << key << ", " << info << "}" << std::endl;
        return false;
    }

    if(occurrence > this->howMany(key, info)){
        std::cerr << "Occurrence index out of bounds (" << occurrence << ")." << std::endl;
        return false;
    }


    //1 element sequence
    if (head->next == NULL){
        Node<Key, Info> *newNode;
        try{
            newNode = new Node<Key, Info>(newKey, newInfo);
        }
        catch(std::bad_alloc){
            std::cerr << "Failed allocating memory for the new node" << std::endl;
            return false;
        }

        head->next = newNode;
        newNode->next = NULL;
    }


    //given element exists at least once
    Node<Key, Info> *travel = head;
    while(travel != NULL){

        if(travel->key == key && travel->info == info){

            if(occurrence > 1){
                occurrence--;
                travel = travel->next;
            }

            else{
                Node<Key, Info> *newNode;
                try{
                    newNode = new Node<Key, Info>(newKey, newInfo);
                }
                catch(std::bad_alloc){
                    std::cerr << "Failed allocating memory for the new node" << std::endl;
                    return false;
                }



                newNode->next = travel->next;
                travel->next = newNode;

                return true;
            }
        }

        travel = travel -> next;
    }

    return false;
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool Sequence<Key, Info>::insertBefore(const Key &key, const Info &info, const Key &newKey, const Info &newInfo,
                                       int occurrence) {

    //given element doesn't exists in the sequence
    if(!(this->exists(key, info))){
        std::cerr << "Couldn't find element: {" << key << ", " << info <<  "}" << std::endl;
        return false;
    }

    if(occurrence > this->howMany(key, info)){
        std::cerr << "Occurrence index out of bounds (" << occurrence << ")." << std::endl;
        return false;
    }


    //1 element sequence
    if (head->next == NULL){
        Node<Key, Info> *newNode;
        try{
            newNode = new Node<Key, Info>(newKey, newInfo);
        }
        catch(std::bad_alloc){
            std::cerr << "Failed allocating memory for the new node" << std::endl;
            return false;
        }

        newNode->next = head;
        head = newNode;
    }

    //given element exists at least once
    Node<Key, Info> *travel = head;
    while(travel != NULL){

        if(travel->next->key == key && travel->next->info == info){

            if(occurrence > 1){
                occurrence--;
            }

            else{
                Node<Key, Info> *newNode;
                try{
                    newNode = new Node<Key, Info>(newKey, newInfo);
                }
                catch(std::bad_alloc){
                    std::cerr << "Failed allocating memory for the new node" << std::endl;
                    return false;
                }

                newNode->next = travel->next;
                travel->next = newNode;


                return true;
            }
        }

        travel = travel -> next;
    }

    return false;
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool Sequence<Key, Info>::remove(const Key &key, const Info &info, int occurrence) {

    //given element doesn't exists in the sequence
    if(!(this->exists(key, info))){
        std::cerr << "Couldn't find element: {" << key << ", " << info <<  "}" << std::endl;
        return false;
    }

    if(occurrence > this->howMany(key, info)){
        std::cerr << "Occurrence index out of bounds (" << occurrence << ")." << std::endl;
        return false;
    }


    //1 element list
    if(head->next == NULL && head->key == key && head->info == info && occurrence == 1){
        delete head;
        head = NULL;
        return true;
    }


    //non empty list
    Node<Key, Info> *travel = head;

    //sought element on the head of the sequence
    if(head->key == key && head->info == info) {
        if(occurrence == 1) {
            Node<Key, Info> *temp = head;
            head = travel->next;
            delete temp;

            return true;
        }
        else occurrence--;

    }

    //element not on the first place of the sequence
    while(travel != NULL){

      if(travel->next->key == key && travel->next->info == info){
        if(occurrence == 1) {
            Node<Key, Info> *temp = travel->next;
            travel->next = travel->next->next;
            delete temp;
            return true;
        }
        else occurrence--;

     }
         travel = travel->next;
    }

    return false;
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool Sequence<Key, Info>::removeAllWhere(const Key &key, const Info &info) {

    //given element doesn't exists in the sequence
    if(!(this->exists(key, info))){
        std::cerr << "Couldn't find elements: {" << key << ", " << info <<  "}" << std::endl;
        return false;
    }

    while(this->exists(key, info)){
        this->remove(key, info);
    }

    return true;
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool Sequence<Key, Info>::clearSequence() {


    Node<Key,Info> *travel = head;
    Node<Key,Info> *temp;
    while(travel != NULL){
        temp = travel;
        travel = travel->next;
        delete temp;
    }
    head = NULL;
    return true;
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool Sequence<Key, Info>::isEmpty() {

    return (head == NULL);
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
unsigned int Sequence<Key, Info>::length() const {

    Node<Key, Info> *travel = head;
    unsigned int count = 0;
    while(travel != NULL){
        count++;
        travel = travel->next;
    }

    return count;

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
void Sequence<Key, Info>::print() {

    Node<Key, Info> *travel = head;
    while(travel != NULL){
        std::cout << "{" << travel->key << ", " << travel->info << "} | ";
        travel = travel->next;
    }
    std::cout << std::endl;

}



//--------------------------------------------------------------------------

template<typename Key, typename Info>
Sequence<Key, Info>
Sequence<Key, Info>::shuffle(const Sequence<Key, Info> &S1, unsigned int start1, unsigned int length1,
                             const Sequence<Key, Info> &S2, unsigned int start2, unsigned int length2,
                             unsigned int count) {


    if(start1 > length1 || start2 > length2 || S1.length() < start1 || S2.length() < start2){
        std::string lengthException = "Start index out of bounds.";
        throw std::string(lengthException);
    }

    if(S1.length() < length1 ||  S2.length() < length2){
        std::string lengthException = "Length index out of bounds.";
        throw std::string(lengthException);
    }

    if(count == 0){
        std::string lengthException = "Count can't be equal to 0.";
        throw std::string(lengthException);
    }

    //no input errors

    Sequence<Key, Info> outputSequence;
    Node<Key, Info> *travel1 = S1.head;
    Node<Key, Info> *travel2 = S2.head;

    //move travels to the starting indexes
    for(int i = 0; i < start1; i++) {
        travel1 = travel1->next;
    }
    for(int i=0; i < start2; i++){
        travel2 = travel2->next;
    }


        for(int countNum = 0; countNum < count; countNum++){
            for(int len1 = 0; len1 < length1; len1++){
                if(travel1 == NULL) break;
                outputSequence.pushBack(travel1->key, travel1->info);
                travel1 = travel1->next;;
            }
            for(int len2 = 0; len2 < length2; len2++){
                if(travel2 == NULL) break;
                outputSequence.pushBack(travel2->key, travel2->info);
                travel2 = travel2->next;
            }
        }

    return outputSequence;
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator==(const Sequence<Key, Info> &sequence) const {


    if(this->head == NULL && sequence.head == NULL)
        return true;

    if(this->length() == sequence.length()){
        Node<Key, Info> *travel1 = this->head;
        Node<Key, Info> *travel2 = sequence.head;
        while(travel1 != NULL){

            if(travel1->info != travel2->info || travel1->key != travel2->key)
                return false;

            travel1 = travel1->next;
            travel2 = travel2->next;
        }
        return true;
    }

    return false;

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
bool &Sequence<Key, Info>::operator!=(const Sequence<Key, Info> &sequence) const{

    return !(this == sequence);

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::operator+(const Sequence<Key, Info> &sequence) const{


    return this->merge(sequence);


}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
Sequence<Key, Info> &Sequence<Key, Info>::operator+=(const Sequence<Key, Info> &sequence){

    *this = *this + sequence;
    return *this;

}


//--------------------------------------------------------------------------

template<typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::merge( const Sequence<Key, Info> &sequence ) const
{
    //Creating copies of sequences to merge
    Sequence<Key, Info> seq( *this );


    Node<Key, Info> *travel = sequence.head;
    while( travel != NULL )
    {
        seq.pushBack( travel->key, travel->info );
        travel = travel->next;
    }
    return seq;
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
int Sequence<Key, Info>::howMany(const Key key, const Info info) {

    if(head == NULL) return 0;

    int count = 0;
    Node<Key, Info> *travel = head;
    while(travel != NULL){

        if(travel->key == key && travel->info == info) count++;
        travel = travel->next;
    }

    return count;
}


#endif //SEQUENCE_SEQUENCE_H
