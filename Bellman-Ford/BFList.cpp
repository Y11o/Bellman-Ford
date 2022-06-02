#include <iostream>

using namespace std;

template <typename dataType>

class BFList
{
private:
	size_t size;
	class Node
	{
	public:
		Node *pNext, *pPrevious;
		dataType data;
		Node(dataType data, Node *pNext = NULL, Node *pPrevious = NULL)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrevious = pPrevious;
		}
	};
	Node* head;
	Node* tail; 
public:
	BFList()
	{
		head = tail = NULL;
		size = 0;
	};

	BFList(dataType data)
	{

		Node* newNode = new Node(data);
		head = tail = newNode;
		size = 1;

	};

	~BFList()
	{
		clear();
	};

	void clear()
	{ 
		Node* temp = head;
		while (head != NULL)
		{
			Node* temp = head->pNext;
			delete head;
			head = temp;
		}
		tail = head = NULL;
		size = 0;
	};

	size_t get_size() 
	{
		return size;
	}

	dataType at(size_t elem)      
	{
		if (elem < get_size())
		{
			Node* temp = head;
			for (int i = 0; i < elem; i++) {
				temp = temp->pNext;
			}
			return temp->data;
		}
		else {
			throw out_of_range("Out of range");
		}
	}

	void push_back(dataType data) 
	{
		Node* newNode = new Node(data);

		if (isEmpty())
		{                      
			head = tail = newNode;
		}
		else
		{ 
			newNode->pPrevious = tail;
			tail->pNext = newNode;
			tail = newNode;

		}
		size++;
	};

	void push_front(dataType data)              
	{
		Node* temp = new Node(data);
		if (head != NULL)                          
		{
			temp->pNext = head;
			head->pPrevious = temp;
			head = temp;
			size++;
		}
		else                                      
		{
			head = tail = temp;
			size++;
		}
	}

	bool isEmpty()   
	{
		if (head == NULL)
			return true;
		else
			return false;
	}

	void insert(dataType data, size_t index)                           
	{
		if (index > get_size() - 1)
			throw out_of_range("Out of range");
		else
		{
			if ((index == 0) || (index = get_size() - 1))                      
			{
				if (index == 0)
					push_front(data);
				if (index = get_size() - 1)
					push_back(data);
			}
			else                                                    
			{
				Node* temp = head, *nextNode;
				for (int i = 0; i < index - 1; i++)
					temp = temp->pNext;
				Node* newNode = new Node(data, NULL, NULL);
				newNode->data = data;
				nextNode = temp->pNext;
				temp->pNext;
				temp->pNext = newNode;
				newNode->pNext = nextNode;
				size++;
			}

		}
	}

	int isInList(dataType data)
	{
		int position = INT_MAX;
		Node* temp = head;
		for (int i = 0; i < size; i++)
		{
			if (temp->data == data)
			{
				position = i;
				break;
			}
			temp = temp->pNext;

		}
		return position;
	}

	friend std::ostream& operator << (std::ostream& out, BFList& list) 
	{
		size_t listSize = list.get_size();
		for (size_t i = 0; i < listSize; i++)
		{
			cout << list.at(i) << endl;
		}
		return out;
	}
};