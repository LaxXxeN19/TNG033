#include "set.hpp"
#include <algorithm>  //std::swap

/*
* std::size_t is defined in the C++ standard library
* std::size_t is an unsigned integer type that can store the maximum size of any possible object
* sizes are non-negative integers -- i.e. unsigned integer type
*/

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ************************************ */
// Default constructor
Set::Set() : head{new Node{}}, counter{0} {  // create the dummy node
}

// Constructor for creating a singleton {x}
Set::Set(int x) : Set() {
    // ADD CODE
    
    insert(head, x); //Inserts x at the node after the one pointed at by pointer head.
}

// Constructor: create a set with elements
// elements is not sorted and values in it may not be unique
Set::Set(const std::vector<int>& elements) : Set() {
    /*
    * Sorting a vector cannot used here
    * std::sort and std::unique cannot be used
    */
    // ADD CODE
    //for (int i : elements)
    for (int i = 0; i < std::ssize(elements); i ++){
        sort(elements[i]);//adds the value off element i to the sort func, which checks if it's in the set and places it corectly in the set.
    }
}

// copy constructor
Set::Set(const Set& rhs) : Set() {
    // ADD CODE
    Node* ptr1 = rhs.head->next; //Pointer that points to the first node of Set rhs.
    Node* ptr2 = head; //Pointer that points to the head of the second set.
    while ( ptr1 != nullptr){ //As long as there are more nodes in rhs 
        ptr2->next = new Node(ptr1->value, nullptr); //Create a new node in the second Set that has the value of the node pointed at by ptr1 one and points at nullptr. 
        ptr1 = ptr1->next; //Points to the next node of Set rhs
        ptr2 = ptr2->next; //Points at the newly created node of he new Set.
    }
    counter = rhs.counter; //Set the new counter to the same value as in rhs.
}

// Assignment operator: use copy-and-swap idiom
Set& Set::operator=(Set rhs) { //call by value creates copy of rhs.
    // ADD CODE
    std::swap(head, rhs.head); //Makes pointer *this point at the head of the copy of rhs.
    std::swap(counter, rhs.counter); //Swap the counter of the Set pointed at by *this with counter of copy of rhs.

    return *this; 
}

// Destructor: deallocate all nodes
Set::~Set() {
    // ADD CODE

   //points at head 
    Node* p = head;

    // removes the first elements as long as p isnt pointng at nullptr 
    while (p != nullptr){//loops if not in end of linkt list
        head = p->next; //moves head ptr to the next pointer in linkt list
        delete(p); //allocate memory
        p = head; //ptr is asigned to head
        --counter;
    }

}

// Return number of elements in the set
std::size_t Set::cardinality() const {
    // ADD CODE
    return counter;  //return number off nodes
}

// Test if set is empty
bool Set::empty() const {
    // ADD CODE
    return (counter == 0); //if conter 0 return true else false
     
}

// Test if x is an element of the set
bool Set::member(int x) const {
    // ADD CODE
    Node* ptr = head; //Points at dummy node of Set pointed at by *this.
    while((ptr != nullptr) && (ptr->value != x)){ //as long as we haven't reached the end of Set and the value of a node is not the same as the int x itterate to the next node.
        ptr = ptr->next;
    }
    if(ptr == nullptr){ //If we reach the end of the Set without finding x return false.
        return false;
    }
    else{
        return true;
    }
}

// Return true, if *this is a subset of Set b
// Otherwise, false is returned
bool Set::is_subset(const Set& b) const {
    // ADD CODE
    Node* ptr = head; //Points at dummy node of the Set pointed at by *this.
    while (ptr != nullptr){ //Iterates over all nodes in Set pointed at by *this.
        if(b.member(ptr->value)){ //Checks if the value of the node in the Set pointed at by *this is a member of Set b.
            ptr = ptr->next; //Iterates as long as this is true.
        }
        else {
            return false; //Breaks as soon as a node in b is not in the Set pointed at by *this.
        }
    }
    return true; //Returns true as long as all values in the nodes of Set b is in the Set pointed at by *this.
}

// Return a new Set representing the union of Sets *this and b
// Repeated values are not allowed
// Implement an algorithm similar to the one in exercise 3/Set 1, but don't use vectors
Set Set::set_union(const Set& b) const {
    // ADD CODE
    Node* ptr = head->next; //Points at *this first node.
    Set c; //Creates new Set for the result.
    while(ptr != nullptr){ //Loops over the nodes in Set that *this points at.
        c.sort(ptr->value); //Inserts unique values by order of magnitude from Set pointed at by *this into Set c.
        ptr = ptr->next; //Iterates over nodes pointed at by *this.
    }
    ptr = b.head->next; //Changes pointer ptr to point at the first node o Set b.
    while(ptr != nullptr){ //Loops over nodes in Set b.
        c.sort(ptr->value); //Inserts unique values by order of magnitude from Set b into Set c.
        ptr = ptr->next; //Iterates over nodes in Set b.
    }
    return c; //Returns the union of Set pointed at by *this and Set b.
}

// Return a new Set representing the intersection of Sets *this and b
Set Set::set_intersection(const Set& b) const {
    // ADD CODE
    Node* ptr = head->next; //Points at *this first node.
    Set c; //Creates new Set for the result.
    while (ptr != nullptr) { //Loops over the nodes in Set that *this points at.
        if (b.member(ptr->value)) { //Checks if the value in the Set *this points at is a member of Set b.
            c.sort(ptr->value); //If the value of the node in the Set pointed at by *this is a member of Set b insert unique numbers into Set c.
            ptr = ptr->next;//If it is just itterate to the next node in Set pointed at by *this.
        }
        ptr = ptr->next; //Iterates to the next node of Set pointed at by *this. 
    }
	return c; //Returns the intersection of Set pointed at by *this and Set b.
}

// Return a new Set representing the difference between Set *this and Set b
Set Set::set_difference(const Set& b) const {
    // ADD CODE
    Node* ptr = head->next; //Points at *this first node.
    Set c; //Creates new Set for the result.
    while (ptr != nullptr) { //Loops over the nodes in Set that *this points at.
        if (b.member(ptr->value)) { //Checks if the value in the Set *this points at is a member of Set b.
            ptr = ptr->next; //If it is just itterate to the next node in Set pointed at by *this.
        }
        else {
            c.sort(ptr->value); //If the value of the node in the Set pointed at by *this is not a member of Set b insert unique numbers into Set c.
            ptr = ptr->next; //Iterates to the next node of Set pointed at by *this. 
        }
    }
    return c; //Returns the difference between Set pointed at by *this and Set b.
}
//got from aida like this
std::ostream& operator<<(std::ostream& os, const Set& rhs) {
    if (rhs.empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* ptr = rhs.head->next;
        os << "{ ";

        while (ptr != nullptr) {
            os << ptr->value << " ";
            ptr = ptr->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/
void Set::insert(Node *p, int v){ //inserts one node with value v after the node pointed at by p.  
        // why work diff
        Node* newNode = new Node; //Creates a new node pointed at by the pointer newNode.
        newNode->value = v; //Set the value of the new node to v.
        newNode->next = p->next; //Points the pointer of the new node to the node pointed at by pointer p.
        p->next = newNode; //Set pointer p to point at the new node.
        //*/
        //Node* newNode = new Node(v, p->next);
        //p->next = newNode;
        ++counter;
        
}
//if insert is only a value
/*
void Set::insert(int value) {
    Node* ptr = head;
    while ((ptr -> next != nullptr) && (ptr->next->value < value))//executs if ptr dos not point too an emty ptr and the value of pointet head is more than i
    {
        ptr = ptr->next;
    }
    if((ptr->next == nullptr) || (ptr->next->value != value)){
        insert(ptr, value);
    }
}
*/
void Set::sort(int n) //sorts values and checks for occurance in Set. Only insert values that does not occur in Set.
{
    Node* ptr = head; //Points at the dummy node of Set pointed to by *this.
    while ((ptr->next != nullptr) && (ptr->next->value < n)) {  //As long as we havent reached the end of the Set and the value of the next node in the set is lower than n
        ptr = ptr->next; //Iterate over the Set
    }
    if (!member(n)) { //Checks that n is not aleady in the Set
        insert(ptr, n); //If the value n is larger than the value of the earlier node and is not already in the list insert into the Set as a new node.
    }
}