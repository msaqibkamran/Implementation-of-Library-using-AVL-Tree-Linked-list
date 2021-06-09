#include<iostream>
#include"dlist.h"
#include<vector>
#include<string>
using namespace std;

class book           // class of books
{
	int ISSN;
	vector<string> title;
	vector<string> authors;
	int no_ref_books;
	int no_issuable_books;
public:
	friend ostream& operator<<(ostream &, book &);
	friend class dnode<book>;
	friend class dlist<book>;
	friend class AVL<book>;
	book()												 // default constructor of book
	{
		ISSN = -1;
		no_ref_books = -1;
		no_issuable_books = -1;

	}
	book(int issn, vector<string> t, vector<string> a, int r_books, int iss_books)	// parametric constructor of book
	{
		ISSN = issn;
		title = t;
		authors = a;
		no_ref_books = r_books;
		no_issuable_books = iss_books;
	}

	void print_book()              // function to print a book
	{
		cout << "ISSN = " << ISSN << endl;
		cout << "Title = " << title[0] << endl;
		cout << "Authors:-  " << endl;
		for (int i = 0; i < authors.size(); i++)
			cout << i + 1 << ") " << authors[i] << " ";
		cout << endl;
		cout << "Number of Reference Books: " << no_ref_books << endl;
		cout << "Number of Issueable Books: " << no_issuable_books << endl;

	}

	book(const book &obj)   //deep copy constructor  w=t=v
	{
		ISSN = obj.ISSN;
		title = obj.title;
		authors = obj.authors;
		no_ref_books = obj.no_ref_books;
		no_issuable_books = obj.no_issuable_books;
	}
	book& operator=(const book &obj)   //   assignment operator
	{
		ISSN = obj.ISSN;
		title = obj.title;
		authors = obj.authors;
		no_ref_books = obj.no_ref_books;
		no_issuable_books = obj.no_issuable_books;
		return *this;
	}
	bool operator<(const book &obj)        // operator < for comparing two books
	{
		return(ISSN < obj.ISSN);
	}
	bool operator<=(const book &obj)        // operator < for comparing two books
	{
		return(ISSN <= obj.ISSN);
	}
	bool operator==(const book &obj)         // operator== for comparing two books
	{
		return (ISSN == obj.ISSN);
	}
	bool operator!=(const book &obj)          // operator =! for comparing two books
	{
		return (ISSN != obj.ISSN);
	}

};

ostream& operator<<(ostream &out, book &obj)         // operator << for printing book
{
	out << "ISSN = " << obj.ISSN << endl;
	out << "Title = " << obj.title[0] << endl;
	out << "Authors:-  " << endl;
	for (int i = 0; i < obj.authors.size(); i++)
		out << i + 1 << ") " << obj.authors[i] << " ";
	out << endl;
	out << "Number of Reference Books: " << obj.no_ref_books << endl;
	out << "Number of Issueable Books: " << obj.no_issuable_books << endl;
	return out;
}

dlist<book> book_list;

template<class T>
class AVL;

template <class T>
class tnode             // class of tnode
{
	tnode *left;
	tnode *right;
	int height;
	int issn;
	dnode<T>* address;
public:
	tnode(int i = -1, dnode<T>* a = 0, tnode * l = nullptr, tnode * r = nullptr, int h = 0)    // default constructor of tnode
	{
		left = l;
		right = r;
		height = h;
		issn = i;
		address = a;
	}
	void printTnodeData()        // prints data of tnode
	{
		cout << issn << endl;
		cout << address;
	}
	friend class AVL<T>;
};

template <class T>
class AVL              // class of binary search tree
{
	tnode<T> * root;
public:
	AVL()        // default constructor 
	{
		root = nullptr;
	}

	tnode<T>* search(int d)        // wrapper function for search function
	{
		return search(root, d);
	}

	tnode<T>* search(tnode<T> *r, int d)    // return the pointer of the node that contains d
											//if search is successful otherwise return null 
	{
		if (r == nullptr || r->issn == d)
			return r;
		else if (r->issn > d)
			return search(r->left, d);
		else
			return search(r->right, d);
	}

	~AVL()         //wrapper destructor of AVL 
	{
		destroy(root);
	}

	void destroy(tnode<T> * r)   // actual destructor of AVL
	{
		if (r != nullptr)
		{
			destroy(r->left);
			destroy(r->right);
			delete r;
		}
	}

	void rotate_Right(tnode<T> *& x)         // rotate right base factor is 2
											 // ( insertion is made in left subtree of left child of x)
	{
		tnode<T> *y = x->left;
		x->left = y->right;
		y->right = x;
		y->height = max_height(height(y->left), height(y->right)) + 1;
		x->height = max_height(height(x->left), height(x->right)) + 1;
		x = y;
	}

	void rotate_Left(tnode<T> *& x)         // rotate Left function base factor is -2
											// ( insertion is made in right subtree of right child of x)
	{
		tnode<T> *y = x->right;
		x->right = y->left;
		y->left = x;
		y->height = max_height(height(y->left), height(y->right)) + 1;
		x->height = max_height(height(x->left), height(x->right)) + 1;
		x = y;
	}

	void double_Rotate_Right(tnode<T> *& x)    // double rotate right base factor is 2
											   // ( insertion is made in right subtree of left child of x)
	{
		rotate_Left(x->left);
		rotate_Right(x);
	}

	void double_Rotate_Left(tnode<T> *& x)    // double rotate left base factor is -2
											  // ( insertion is made in left subtree of right child of x)
	{
		rotate_Right(x->right);
		rotate_Left(x);
	}

	void insert(dnode<T>* add, int d)                  // wrapper function for insert function
	{
		return insert(root, add, d);
	}

	void insert(tnode<T> *& r, dnode<T>* add, int d)            // for inserting data in AVL BST
	{
		if (r == nullptr)
		{
			r = new tnode<T>(d, add);
			return;
		}
		if (d < r->issn)        // data is smaller than root 
		{
			insert(r->left, add, d);
			if (height(r->left) - height(r->right) == 2)   // case 1 or 3
			{
				if (d < r->left->issn)
					rotate_Right(r);
				else
					double_Rotate_Right(r);
			}
		}
		else
		{
			insert(r->right, add, d);      // data is greater than root
			if (height(r->left) - height(r->right) == -2)   // case 2 or 4
			{
				if (d > r->right->issn)
					rotate_Left(r);
				else
					double_Rotate_Left(r);
			}
		}
		r->height = 1 + max_height(height(r->left), height(r->right));      // update height of changed root
	}

	tnode<T>*  insert_for_new_book(dnode<T>* add, int d)                  // wrapper function for insert function
	{
		tnode<T>* result = insert_for_new_book(root, add, d);
		return result;
	}

	tnode<T> * insert_for_new_book(tnode<T> *& r, dnode<T>* add, int d)            // for inserting new book in AVL BST
	{
		if (r == nullptr)
		{
			r = new tnode<T>(d, add);
			return nullptr;
		}
		if (d < r->issn)        // data is smaller than root 
		{
			tnode<T>* temp = insert_for_new_book(r->left, add, d);
			if (height(r->left) - height(r->right) == 2)   // case 1 or 3
			{
				if (d < r->left->issn)
					rotate_Right(r);
				else
					double_Rotate_Right(r);
			}
			if (r->left->left == nullptr && r->left->right == nullptr)     // return parent of inserted data
				return r;
			else
				return temp;
		}
		else
		{
			tnode<T>* temp = insert_for_new_book(r->right, add, d);       // data is smaller than root 
			if (height(r->left) - height(r->right) == -2)   // case 2 or 4
			{
				if (d > r->right->issn)
					rotate_Left(r);
				else
					double_Rotate_Left(r);
			}
			if (r->right->right == nullptr && r->right->left == nullptr)  // return parent of inserted data
				return r;
			else
				return temp;
		}
		r->height = 1 + max_height(height(r->left), height(r->right));        // update height of changed root
	}

	void review()       // function for reviweing a book
	{
		int issn;
		cout << "Enter ISSN of book to Review: " << endl;
		cin >> issn;
		if (search(issn))
		{
			tnode<T> * s = search(issn);
			dnode<T> * b = s->address;
			cout << b->data;       // print book data
		}
		else
			cout << " Book not Found with this ISSN !" << endl << endl;
	}

	void list_update(dnode<T> * address, book b)    // insert new book at the addresss
	{
		address->data = b;
	}

	void update()							 // making changes in the desired book 
	{
		int issn;
		cout << "Enter ISSN of book to Update: " << endl;
		cin >> issn;

		if (search(issn))
		{
			tnode<T> * s = search(issn);
			dnode<T> * b = s->address;

			vector<string> author;
			vector<string> title;
			string a1, t;
			int no_authors,new_issn,noi_books,nor_books;
			cout << "Enter new title: " << endl;            // new title 
			cin >> t;
			title.push_back(t);

			cout << "Enter new number of Authors: " << endl;   // new authors 
			cin >> no_authors;
			{
				for (int i = 0; i < no_authors; i++)
				{
					cout << "Enter Author " << i+1 << " : " << endl;
					cin >> a1;
					author.push_back(a1);
				}
			}

			cout <<"Enter new number of Issuable Books: " << endl;
			cin >> noi_books;
			cout <<"Enter new number of Reference Books: " << endl;
			cin >> nor_books;

			book c = b->data;
			new_issn = c.ISSN;
			book updated_book(new_issn, title, author, nor_books, noi_books);
			list_update(b, updated_book);        // make changes in the list as well   
		}
		else
			cout << " Book not Found with this ISSN !" << endl << endl;

	}

	void view_books()     // show book in the given range
	{
		int start, end;
		cout << "Enter Range to view Books: ";
		cin >> start;
		cin >> end;

		int found = 0;
		while (start <= end && found == 0)
		{
			if (search(start))
			{
				tnode<book> * s = search(start);
				dnode<T> * b = s->address;
				book_list.print_in_range(b, end);
				found = 1;
			}
			else
				start++;
		}
		if (found == 0)
			cout << "NO Book Found in this Range ! " << endl;
	}

	void new_book()        // add new book using issn
	{

		vector<string> author;
		vector<string> title;
		string a1, t;
		int new_book_issn,no_authors, new_issn, noi_books, nor_books;
		cout << "Enter new Book ISSN: " << endl;            // new title 
		cin >> new_book_issn;

		cout << "Enter new title: " << endl;            // new title 
		cin >> t;
		title.push_back(t);

		cout << "Enter new number of Authors: " << endl;   // new authors 
		cin >> no_authors;
		{
			for (int i = 0; i < no_authors; i++)
			{
				cout << "Enter Author " << i + 1 << " : " << endl;
				cin >> a1;
				author.push_back(a1);
			}
		}

		cout << "Enter new number of Issuable Books: " << endl;
		cin >> noi_books;
		cout << "Enter new number of Reference Books: " << endl;
		cin >> nor_books;

		book new_book(new_book_issn, title, author, nor_books, noi_books);
		
		tnode<T> * temp = insert_for_new_book(nullptr, new_book_issn);    // get address of parent
		dnode<T> * add;
		if (temp->issn< new_book_issn)      // at left of parent
		{
			add = book_list.insert_after(new_book, temp->address);        // get address in list
			temp->right->address = add;
		}
		else          // at right of parent
		{
			add = book_list.insert_before(new_book, temp->address);       // get address in list
			temp->left->address = add;
		}
	}

	int height(tnode<T> *n)      // gives height of given node
	{
		if (n == nullptr)
			return 0;
		return n->height;
	}

	int max_height(int h1, int h2)       // returns higher heigth between two heights
	{
		if (h1 > h2)
			return h1;
		return h2;
	}

	int balance_factor(tnode<T> *n)          // gives balance factor of a node
	{
		if (n == nullptr)
			return 0;
		return height(n->left) - height(n->right);
	}

	void remove_book(int key)     // wrapper function for removing book
	{
		return remove_book(root, key);
	}

	void remove_book(tnode<T> *& r, int key)        // remove book with given ISSN
	{

		if (root != nullptr)
		{
			if (key > r->issn)             // issn of book to be removed is greater from roots's issn
			{
				remove_book(r->right, key);
			}
			else if (key < r->issn)        // issn of book to be removed is less from roots's issn
			{
				remove_book(r->left, key);
			}
			else if (r->issn == key)       // book to be deleted
			{
				remove_node(r);
			}

		}
		balancenode(r);             // balance node after removing given book

	}

	void remove_node(tnode<T> *& r)      // removes given tnode from AVL
	{
		tnode<T>*  temp = r;
		if (r->left == nullptr)            // one child ( left is null )
		{
			r = r->right;
			delete temp;
		}
		else if (r->right == nullptr)       // one child ( right is null )
		{
			r = r->left;
			delete temp;
		}
		else                             // two childs
		{
			tnode<T> * d = findmin(r->right);          // find successor
			r->issn = d->issn;
			r->address = d->address;
			remove_book(r->right, d->issn);         // remove successor
		}
	}

	tnode<T> * findmin(tnode<T> * r)     // find minimum ( successor )
	{
		while (r->left != nullptr)
		{
			r = r->left;
		}
		return r;
	}

	void balancenode(tnode<T> *& r)                // balance AVL after deletion
	{
		if (r == nullptr)
		{
			return;
		}
		else
		{
			if (height(r->left) - height(r->right) > 1)       // right cases
			{
				if (height(r->left->left) - height(r->left->right) >= 0)          // rotate right
				{
					rotate_Right(r);
				}
				else if (height(r->left->left) - height(r->left->right) < 0)         // double-rotate right
				{
					double_Rotate_Right(r);
				}
			}
			else if (height(r->left) - height(r->right) < -1)      // left cases
			{
				if (height(r->right->left) - height(r->right->right) <= 0)             // rotate left
				{
					rotate_Left(r);
				}
				else if (height(r->right->left) - height(r->right->right) > 0)          // double-rotate left
				{
					double_Rotate_Left(r);
				}
			}
		}
		r->height = max_height(height(r->left), height(r->right)) + 1;               // update height after rotations
	}

	void removeBook()      // function to remove a book from index
	{
		int issn;
		cout << "Enter ISSN of book to Delete: " << endl;
		cin >> issn;

		if (search(issn))
		{
			tnode<T> * temp = search(issn);
			dnode<T> * add = temp->address;
			remove_book(issn);                       // remove from avl
			book_list.remove_book_list(add);       // remove from list
		}
		else
		{
			cout << "Book Not Found with this ISSN" << endl << endl;
		}
	}
};

int main()
{
	AVL<book> avl;

	vector<string> author;
	vector<string> title;
	string a1 = "Saqib";
	string a2 = "Kamran";
	string t = "Life of a Computer Science Student";
	author.push_back(a1);
	author.push_back(a2);
	title.push_back(t);
	vector<string> author2;
	vector<string> title2;
	string a3 = "Atif";
	string a4 = "Ahmed";
	author2.push_back(a3);
	author2.push_back(a4);
	string t2 = "Life at FAST";
	title2.push_back(t2);
	vector<string> author3;
	vector<string> title3;
	string a5 = "Khurrum";
	string a6 = "Niaz";
	string t3 = "Introduction to C++";
	author3.push_back(a5);
	author3.push_back(a6);
	title3.push_back(t3);

	book b(1, title, author, 2, 10);
	book b1(2, title2, author2, 4, 20);
	book b2(3, title3, author3, 6, 40);
	dnode<book> *  k = book_list.insertSorted(b1);
	dnode<book> *  k1 = book_list.insertSorted(b);
	dnode<book> *  k2 = book_list.insertSorted(b2);


	// Adding data in AVL Search Tree
	avl.insert(k, 2);
	avl.insert(k1, 1);
	avl.insert(k2, 3);
	cout << "1 = Review , 2 = Update , 3 = Create , 4 = delete , 5 = view, 0 = Exit" << endl;

	while (true)
	{
		int input;
		cin >> input;
		system("CLS");
		cout << "1 = Review , 2 = Update , 3 = Create , 4 = delete , 5 = view, 0 = Exit" << endl;
		
		if (input == 1)
		{
			avl.review();
		}
		else if (input == 2)
		{
			avl.update();
		}
		else if (input == 3)
		{
			avl.new_book();
		}
		else if (input == 4)
		{
			avl.removeBook();
		}
		else if (input == 5)
		{
			avl.view_books();
		}
		else if (input == 0)
		{
			break;
		}
	}

	return 0;
}