
//
// Created by Ernest Pokropek
//


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

#ifndef SEQUENCE_SHUFFLE_H
#define SEQUENCE_SHUFFLE_H

#include "sequence.h"


template <typename Key, typename Info>
Sequence<Key, Info> shuffle(const Sequence<Key, Info> &S1, unsigned int start1, unsigned int length1,
                            const Sequence<Key, Info> &S2, unsigned int start2, unsigned int length2,
                            unsigned int count){


    if (start1 > length1 || start2 > length2 || S1.length() < start1 || S2.length() < start2) {
        std::string lengthException = "Start index out of bounds.";
        throw std::string(lengthException);
    }

    if (S1.length() < length1 || S2.length() < length2) {
        std::string lengthException = "Length index out of bounds.";
        throw std::string(lengthException);
    }

    if (count == 0) {
        std::string lengthException = "Count can't be equal to 0.";
        throw std::string(lengthException);
    }

    //correct input

    //sequence to return
    Sequence<Key, Info> outputSequence;

    //creating index1,2 to clarify code, and
    //size1 and size2 not to induce length() function
    //every iteration
    unsigned int index1 = start1, index2 = start2;
    unsigned int size1 = S1.length(), size2 = S2.length();

    //creating key and info to store values from getNode(...);
    Key aKey;
    Info aInfo;

    //number of shuffles loop
    for(int countNum = 0; countNum < count; countNum++){
        //put elements into sequence until there are no more to put
        //or the number of given length was fulfilled
        for(int i = 0; index1 < size1 && i < length1; i++){
            if(S1.getNode(index1, aKey, aInfo))
                outputSequence.pushBack(aKey, aInfo);
            index1++;
        }
        //put elements into sequence until there are no more to put
        //or the number of given length was fulfilled
        for(int i = 0; index2 < size2 && i < length2; i++){
            if(S2.getNode(index2, aKey, aInfo))
                outputSequence.pushBack(aKey, aInfo);
            index2++;
        }
    }

    return outputSequence;
}


#endif //SEQUENCE_SHUFFLE_H
