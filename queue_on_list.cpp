#include <iostream>

struct CNode {
	int Data;
	CNode* Next;

	explicit CNode( int data ) : Data( data ), Next( 0 ) {}
};

class CQueue {
public:
	CQueue();
	~CQueue();

	// Вставка элемент.
	void Enqueue( int element );
	// Извлечение элемента. Если очередь пуста, то возвращает -1.
	int Dequeue();

private:
	CNode* head; // Указатель на голову очереди - первый элемент односвязного списка.
	CNode* tail; // Указатель на хвост очереди - последний элемент односвязного списка.
};

CQueue::CQueue() :
	head( 0 ),
	tail( 0 )
{
}

CQueue::~CQueue()
{
	for( CNode* current = head; current != 0; ) {
		CNode* next = current->Next;
		delete current;
		current = next;
	}
}

void CQueue::Enqueue( int element )
{
	CNode* newNode = new CNode( element );
	if( tail != 0 ) {
		tail->Next = newNode;
	} else {
		head = newNode;
	}
	tail = newNode;
}

int CQueue::Dequeue()
{
	if( head == 0 ) {
		return -1;
	}
	// Запоминаем результат и указатель на следующий.
	int result = head->Data;
	CNode* next = head->Next;

	// Удаляем элемент и двигаем head.
	delete head;
	head = next;

	// Если список оказался пуст, обновим tail.
	if( head == 0 ) {
		tail = 0;
	}

	return result;
}

int main()
{
	int commandsCount = 0;
	std::cin >> commandsCount;

	CQueue queue;
	for( int i = 0; i < commandsCount; ++i ) {
		int command = 0;
		std::cin >> command;
		int value = 0;
		std::cin >> value;
		switch( command ) {
			case 2:
			{
				int extractedElement = queue.Dequeue();
				if( value != extractedElement ) {
					std::cout << "NO";
					return 0;
				}
				break;
			}
			case 3:
				queue.Enqueue( value );
				break;
		}
	}
	std::cout << "YES";
	return 0;
}