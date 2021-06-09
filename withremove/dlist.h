#include<iostream>
using namespace std;
#include<vector>

class book;            // defining classes which will be used later
template<class T>
class dlist;
template<class T>
class AVL;
template<class T>
class dnode     // class of node
{
	T data;
	dnode<T> * next;
	dnode<T> * prev;
public:

	dnode() { next = prev = nullptr; }   // default constructor of dnode

	dnode(T d, dnode* n = nullptr)      // constructor with parimeters of dnode
	{
		data = d;
		next = n;
		prev = nullptr;
	}
	friend class dlist<T>;
	friend class AVL<T>;
};

// class of list
template <class T>
class dlist
{
	dnode<T> head;												// dummy head

public:
	friend class AVL<T>;
	dlist()										 // constructor of list
	{
		head.next = nullptr;
	}

	~dlist()								// destructor of list
	{
		if (head.next != nullptr) {
			dnode<T> *t = head.next;
			while (t != nullptr) {
				t = head.next->next;
				delete head.next;
				head.next = t;
			}
		}
	}

	dnode<T>* insertatstart(T d)				 // inserts data at start of list
	{
		dnode<T> * temp = new dnode<T>(d);
		temp->next = head.next;
		temp->prev = nullptr;
		if (head.next != nullptr)
			head.next->prev = temp;
		head.next = temp;

		return temp;
	}

	dnode<T> * insertSorted(T d)     // inserts data in list in a sorted order
	{
		if (head.next != nullptr)
		{
			dnode<T> * temp = new dnode<T>(d);
			dnode<T> *prev, *curr;
			curr = head.next;
			prev = curr->prev;
			if (curr->data < d)
			{
				while (curr->next != nullptr && curr->next->data < d)
				{
					prev = curr;
					curr = curr->next;
				}
				if (curr->next == nullptr)    // insertion at end of list
				{
					temp->next = nullptr;
					curr->next = temp;
					temp->prev = curr;
				}
				else                     // insertion at middle of list
				{
					temp->next = curr->next;
					temp->prev = curr;
					curr->next = temp;
					//temp->next->prev = temp;  
				}
				return temp;
			}
			else         // insertion at start of list
			{
				dnode<T> * t = new dnode<T>(d);
				t->next = head.next;
				t->prev = nullptr;
				if (head.next != nullptr)
					head.next->prev = t;
				head.next = t;
				return t;
			}

		}
		else
		{
			dnode<T>*  j = insertatstart(d);
			return j;
		}

	}

	void remove(T d)          // removes given data from list
	{
		if (head.next != nullptr)
		{
			dnode<T> *curr, *prev;
			curr = head.next;
			prev = curr->prev;
			while (curr->next != nullptr && curr->data < d)
			{
				prev = curr;
				curr = curr->next;
			}
			if (curr != nullptr && curr->data == d)
			{
				if (curr == head.next)        // first element
					head.next = head.next->next;
				else
					prev->next = curr->next;
			}
			delete curr;
		}
	}

	bool isEmpty()   // returns true if list is empty
	{
		return head.next == nullptr;
	}

	bool search(T d)   // search given data from list
	{
		dnode<T> *curr = head.next;
		while (curr != nullptr)
		{
			if (curr->data == d)
				return true;
			else
				curr = curr->next;
		}
		return false;
	}

	void printList()   // prints data of list
	{
		dnode<T> *curr = head.next;
		while (curr != nullptr)
		{
			cout << curr->data << endl;
			curr = curr->next;
		}
		cout << endl << endl;
	}

	dnode<T>* getHead()     // return pointer of first element
	{
		return head.next;
	}

     dnode<T>* insert_after(book b, dnode<T> * add)     // inserts data after the address of given node
	{
		dnode<T>* temp = new dnode<T>(b);
		temp->next = add->next;
		temp->prev = add;
		add->next = temp;
		return temp;
	}

    dnode<T>* insert_before(book b, dnode<T> * add)         // inserts data before the address of given node
	{
		dnode<T>* temp = new dnode<T>(b);
		temp->prev = add->prev;
		temp->next = add;
		add->prev = temp;
		return temp;
	}

    void remove_book_list(dnode<T> *add)                // removes given node from list
	{
		dnode<T> * prev = add->prev;
		if (add == head.next)        // first element
		{
			head.next = head.next->next;
			head.next->prev = nullptr;
		}
		else if (add->next == nullptr)    //  last element
		{
			prev->next = nullptr;
		}
		else           //  middle element
		{
			prev->next = add->next;
			add->next->prev = prev;
		}
		delete add;
		add = nullptr;
	}

	void print_in_range(dnode<T> *add, int end)
	{
		dnode<T> *curr = add;
		while (curr != nullptr && curr->data.ISSN <= end)
		{
			cout << curr->data;
			curr = curr->next;
		}
	}

};


