//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for the List ADT
// Lucas Ellenberger
// lmellenb
// pa6
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>

#include"List.h"

using std::cout;
using std::endl;

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x) {
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List(){
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy constructor.
List::List(const List& L) { // THIS IS PROBABLY TERRIBLY WRONG!!!
   // make this an empty Queue
   this->frontDummy = new Node(-1);
   this->backDummy = new Node(-1);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;

   // load elements of L into this List
   Node* N = L.frontDummy->next;
   while (N->next != nullptr) {
      this->insertAfter(N->data);
      this->moveNext();
      N = N->next;
   }
}

// Destructor
List::~List() {
   this->moveFront();
   while (this->length() > 0) {
      this->eraseAfter();
   }
   delete(this->frontDummy);
   delete(this->backDummy);
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
   return(this->num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
   if (this->num_elements == 0) {
      throw std::length_error("List: front(): empty List");
   }
   return(this->frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
   if (this->num_elements == 0) {
      throw std::length_error("List: front(): empty List");
   }
   return(this->backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
   return(this->pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
   if (this->pos_cursor >= this->num_elements) {
      throw std::domain_error("List: peekNext(): invalid position");
   }
   return(this->afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
   if (this->pos_cursor <= 0) {
      throw std::domain_error("List: peekPrev(): invalid position");
   }
   return(this->beforeCursor->data);
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
   this->moveFront();
   while (this->length() > 0) {
      this->eraseAfter();
   }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
   this->pos_cursor = 0;
   this->beforeCursor = this->frontDummy;
   this->afterCursor = this->frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
   this->pos_cursor = this->num_elements;
   this->beforeCursor = this->backDummy->prev;
   this->afterCursor = this->backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
   if (this->pos_cursor >= this->num_elements) {
      throw std::domain_error("List: moveNext(): invalid position");
   }
   this->pos_cursor++;
   this->beforeCursor = this->afterCursor;
   this->afterCursor = this->beforeCursor->next; // DOUBLE CHECK THIS
   return this->beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
   if (this->pos_cursor <= 0) {
      throw std::domain_error("List: movePrev(): invalid position");
   }
   this->pos_cursor--;
   this->afterCursor = this->beforeCursor;
   this->beforeCursor = this->afterCursor->prev;
   return this->afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
   Node * newNode = new List::Node(x);
   newNode->prev = this->beforeCursor;
   newNode->next = this->afterCursor;
   this->afterCursor->prev = newNode;
   this->beforeCursor->next = newNode;
   this->afterCursor = newNode;
   this->num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
   Node * newNode = new List::Node(x);
   newNode->prev = this->beforeCursor;
   newNode->next = this->afterCursor;
   this->afterCursor->prev = newNode;
   this->beforeCursor->next = newNode;
   this->beforeCursor = newNode;
   this->num_elements++;
   this->pos_cursor++; // Maybe check with someone?
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
   if (this->pos_cursor >= this->num_elements) {
      throw std::domain_error("List: setAfter(): invalid position");
   }
   this->afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
   if (this->pos_cursor <= 0) {
      throw std::domain_error("List: setBefore(): invalid position");
   }
   this->beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
   if (this->pos_cursor >= this->num_elements) {
      throw std::domain_error("List: eraseAfter(): invalid position");
   }
   Node * freethis = this->afterCursor;
   this->afterCursor->next->prev = this->beforeCursor;
   this->beforeCursor->next = this->afterCursor->next;
   this->afterCursor = this->afterCursor->next;
   delete(freethis);
   this->num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
   if (this->pos_cursor <= 0) {
      throw std::domain_error("List: setBefore(): invalid position");
   }
   Node * freethis = this->beforeCursor;
   this->beforeCursor->prev->next = this->afterCursor;
   this->afterCursor->prev = this->beforeCursor->prev;
   this->beforeCursor = this->beforeCursor->prev;
   delete(freethis);
   this->num_elements--;
   this->pos_cursor--;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
   while(this->pos_cursor < this->num_elements) {
      int check = this->moveNext();
      if (check == x) {
         return pos_cursor;
      }
   }
   return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
   while(this->pos_cursor > 0) {
      int check = this->movePrev();
      if (check == x) {
         return pos_cursor;
      }
   }
   return -1;  
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
   int num_loops = 0;
   int num_unique_before_cursor = 0;
   int datas[this->num_elements];
   int num_in_datas = 0;
   bool changed = false;
   Node * curr = this->frontDummy->next;
   while (curr->next != nullptr) {
      if (num_loops == this->pos_cursor) {
         // Sets the number of unique values we found before hitting the original cursor
         num_unique_before_cursor = num_in_datas;
      }
      for (int i = 0; i < num_in_datas; i++) {
         if (curr->data == datas[i]) {
            // cout << "We are deleting: " << curr->data << " from the list" << endl;
            Node * freethis = curr;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            curr = curr->next;
            this->num_elements--;
            delete freethis;
            changed = true;
            break;
         }
      }
      if (!changed) {
         // cout << "We added: " << curr->data << " to the list of seen data" << endl;
         datas[num_in_datas] = curr->data;
         num_in_datas++;
         curr = curr->next;
      }
      changed = false;
      num_loops++;
   }
   if (num_loops == this->pos_cursor) { // To check if the cursor was at the back position
      // Sets the number of unique values we found before hitting the original cursor
      num_unique_before_cursor = num_in_datas;
   }
   // After deleting the elements from the list, we need to move the cursor to where it should be
   this->moveFront();
   for (int i = 0; i < num_unique_before_cursor; i++) {
      this->moveNext();
   }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
   List newList;
   Node * curr = this->frontDummy->next;
   while (curr->next != nullptr) {
      newList.insertAfter(curr->data);
      newList.moveNext();
      curr = curr->next;
   }
   curr = L.frontDummy->next;
   while (curr->next != nullptr) {
      newList.insertAfter(curr->data);
      newList.moveNext();
      curr = curr->next;
   }
   newList.pos_cursor = 0;
   newList.beforeCursor = newList.frontDummy;
   newList.afterCursor = newList.frontDummy->next;
   return newList;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
   if (this->length() == 0) {
      return "()";
   }
   std::string rep = "(";
   Node * curr = this->frontDummy->next;
   rep += std::to_string(curr->data);
   curr = curr->next;
   for (int i = 1; i < this->num_elements; i++) {
      rep += ",";
      rep += std::to_string(curr->data);
      curr = curr->next;
   }
   rep += ")";
   return rep;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
   if (this->num_elements != R.num_elements) {
      return false;
   }
   Node * curr_this = this->frontDummy->next;
   Node * curr_r = R.frontDummy->next;
   for (int i = 0; i < this->num_elements; i++) {
      if (curr_this->data != curr_r->data) {
         return false;
      }
   }
   return true;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
   return stream << L.List::to_string() << std::endl;
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
   return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
   if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(this->frontDummy, temp.frontDummy);
      std::swap(this->backDummy, temp.backDummy);
      std::swap(this->num_elements, temp.num_elements);
   }
   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}
