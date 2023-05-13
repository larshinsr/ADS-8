// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
    Cage* newCage = new Cage;
    newCage->light = light;
    newCage->next = nullptr;

    if (first == nullptr) {
        newCage->next = newCage;
        newCage->prev = newCage;
        first = newCage;
    } else {
        newCage->next = first;
        newCage->prev = first->prev;
        first->prev->next = newCage;
        first->prev = newCage;
    }
}

/*
*****************************
    the main idea of the algorithm
    1) we start in first cage

    2) than we go to the next cage
    until we meet the cage
    with the lamp on
    than backtrack

    3.1) if light in first cage on
    loop starts again
    3.2) if light off in first cage
    break loop and return count of cages
******************************
    steps in this algorithm
    1. go to the 1st cage
    1.1 switch light on
    1.2 set count to 1
/////////////////////////////////
    2. start an infinity loop
    2.1 go next
/////////////////////////////////
    3. different cases of
    light in cages
    3.1 if light is off
    3.1.1 count of cage++
        (count++)
    3.1.2 coont of operation++
        (countOp++)
////////////////////////////////
    3.2 if light is on
    3.2.1 count of operation++
    3.2.2 switch light off
    3.2.3 go to first cage
        by using count(count of cages)
        countOp++
////////////////////////////////
    4. if light was switched off in first cage
        means that we went t
        hrough the whole train
    5. loop starts again
*/
int Train::getLength() {
    if (first == nullptr) return 0;
    Cage* current = first;  // 1
    current->light = 1;     // 1.1
    int count = 1;          // 1.2
    // 2
    while (true) {
        current = current->next;  // 2.1
        // 3
        if (current->light == 0) {             // 3.1
            ++count;                           // 3.1.1
            ++countOp;                         // 3.1.2
        } else {                               // 3.2
            ++countOp;                         // 3.2.1
            current->light = 0;                // 3.2.2
            for (int i = count; i > 0; i--) {  // 3.2.3
                countOp++;
                current = current->prev;
            }
            if (current->light == 0) return count;  // 4
            count = 1;                              // 5
        }
    }
}
int Train::getOpCount() { return countOp; }
