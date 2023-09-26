//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
// Lucas Ellenberger
// lmellenb
// pa6
//-----------------------------------------------------------------------------
#include "List.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char** argv) {
    // Test for constructor
    List* my_list = new List();

    // Test for length()
    cout << "Expected length: 0" << endl;
    cout << "Actual length: " << my_list->length() << endl;

    // Test for insertAfter() and moveNext()
    for(int i = 0; i < 10; i++) {
        my_list->insertAfter(i);
        my_list->moveNext();
    }

    // Test for moveBack()
    my_list->moveBack();
    
    // Test for position()
    cout << "Expected cursor: 10" << endl;
    cout << "Actual cursor: " << my_list->position() << endl;

    my_list->movePrev();
    // Test for insertBefore()
    my_list->insertBefore(404);

    // Test for position()
    cout << "Expected cursor: 10" << endl;
    cout << "Actual cursor: " << my_list->position() << endl;

    // Test for peekPrev()
    cout << "Expected val: 404" << endl;
    cout << "Actual val: " << my_list->peekPrev() << endl;

    // Test for moveFront()
    my_list->moveFront();
    my_list->moveNext();
    my_list->insertAfter(333);
    
    // Test for peekAfter()
    cout << "Expected val: 333" << endl;
    cout << "Actual val: " << my_list->peekNext() << endl;

    for (int i = 0; i < 4; i++) {
        my_list->moveNext();
    }
    // Now at position 4

    // Test for overloaded << operator and to_string()
    cout << "Expected: (0,333,1,2,3,4,5,6,7,8,404,9)" << endl;
    cout << "Actual: " << my_list->to_string() << endl;

    // Test for front() and back()
    cout << "Expected front: 0" << endl;
    cout << "Actual front: " << my_list->front() << endl;
    cout << "Expected back: 9" << endl;
    cout << "Actual back: " << my_list->back() << endl;

    // Test for length()
    cout << "Expected length: 12" << endl;
    cout << "Actual length: " << my_list->length() << endl;

    // Test for copy constructor
    List* copy_list = new List(*my_list);
    cout << "Expected: (0,333,1,2,3,4,5,6,7,8,404,9)" << endl;
    cout << "Actual: " << copy_list->to_string() << endl;

    // Test for equals()
    cout << "Expected: true" << endl;
    cout << std::boolalpha << "Actual: " << (*my_list).equals(*copy_list) << endl;

    copy_list->moveFront();
    copy_list->moveNext();

    // Test for eraseBefore()
    copy_list->eraseBefore();
    for (int i = 0; i < 3; i++) {
        copy_list->moveNext();
    }

    // Test for eraseAfter()
    copy_list->eraseAfter();
    cout << "Expected: (333,1,2,4,5,6,7,8,404,9)" << endl;
    cout << "Actual: " << copy_list->to_string() << endl;

    // Test for setAfter()
    copy_list->setAfter(15);
    copy_list->movePrev();

    // Test for setBefore()
    copy_list->setBefore(44);

    cout << "Expected: (333,44,2,15,5,6,7,8,404,9)" << endl;
    cout << "Actual: " << copy_list->to_string() << endl;

    // Test for equality
    cout << "Expected: false" << endl;
    bool win = (*my_list)==(*copy_list);
    cout << std::boolalpha << "Actual: " << win << endl;
    
    // Test for concat()
    List concat_list = my_list->concat(*copy_list);
    List * copy_concat = new List(concat_list);

    cout << "Expected: (0,333,1,2,3,4,5,6,7,8,404,9,333,44,2,15,5,6,7,8,404,9)" << endl;
    cout << "Actual: " << copy_concat->to_string() << endl;

    // Test for FindNext()
    copy_concat->moveFront();
    copy_concat->moveNext();
    int found = copy_concat->findNext(404);
    cout << "Expected: 11" << endl;
    cout << "Actual: " << found << endl;
    found = copy_concat->findNext(8);
    cout << "Expected: 20" << endl;
    cout << "Actual: " << found << endl;
    found = copy_concat->findNext(1);
    cout << "Expected: -1" << endl;
    cout << "Actual: " << found << endl;

    // Test for FindPrev()
    found = copy_concat->findPrev(404);
    cout << "Expected: 20" << endl;
    cout << "Actual: " << found << endl;
    found = copy_concat->findPrev(99999);
    cout << "Expected: -1" << endl;
    cout << "Actual: " << found << endl;

    // Test for cleanup()
    copy_concat->moveFront();
    for (int i = 0; i < 13; i++) {
        copy_concat->moveNext();
    }
    cout << "Before Cleanup: " << copy_concat->to_string() << endl;
    cout << "Cursor Expected: 13" << endl; // Figure out cursor logic
    cout << "Cursor Actual: " << copy_concat->position() << endl;
    copy_concat->cleanup();
    cout << "After Cleanup: " << copy_concat->to_string() << endl;
    cout << "Cursor Expected: 12" << endl;
    cout << "Cursor Actual: " << copy_concat->position() << endl;

    // Test for destructor
    delete copy_list;
    delete my_list;
    delete copy_concat;
    return 0;
}
