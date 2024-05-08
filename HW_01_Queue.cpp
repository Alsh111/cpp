#include <iostream>
using namespace std;
class Node
{
	int field;
	class Node *ptr;
	friend class Queue;
};

class Queue
{
	Node *head, *tail;
	int count = 0;
	Node* Prev(Node *); // Переход к предыдущему узлу (не интерфейсный метод)
public:
	Queue() { head = NULL; tail = NULL; } // Инициализация списка
	int getCount() { return count; } // Получение количества узлов списка
	bool isEmpty() { return head == NULL; }  // Проверка, пуст ли список
	int getValue(Node* p) { return p->field; } // Получение значения узла списка
	void setValue(Node *p, int val) { p->field = val; } // Установка значения узла списка
	Node* getFirst() { return head; } // Получение корневого узла списка
	Node* getLast() { return tail; };			// Получение последнего узла списка
	void Clear();				// Очистка списка
	Node* Next(Node *);			// Переход к следующему узлу
	Node* Push(int, Node*);		// Добавление узла списка
	Node* Pop();		// Удаление узла списка
	void Print();				// Вывод значений узлов списка
	void Swap(Node*, Node*);	// Взаимообмен двух узлов
};

Node* Queue::Push(int num, Node* node = NULL) 
{
	Node *elem = new Node();
	elem->field = num;
	count++;
	if (head == NULL) {
		elem->ptr = NULL;
		head = elem;
		tail = elem;
	}
	else {
		elem->ptr = node;
		tail = elem;
	}
	return elem;
}

Node* Queue::Pop() 
{
	if (head == NULL) { return NULL; } // В списке нет узлов
	count--;
    Node *node = head;
    
	head = Prev(head);
	delete node;
	return head;
}

void Queue::Print()
{
	if (isEmpty()) { cout << "Очередь пуста" << endl; return; }
	Node *p = tail;
	do {
		cout << getValue(p) << " ";
		p = p->ptr;
	} while (p != NULL);
	cout << endl;
}

void Queue::Clear()
{
	class Node *p = tail;
	if (p == NULL) return;
	do {
		Node *d = p;
		p = p->ptr;
		delete d;
	} while (p != NULL);
	count = 0;
	head = NULL;
}

Node* Queue::Next(Node* node)
{
	if (isEmpty()) return NULL;
	return node->ptr;
}

Node* Queue::Prev(Node* node)
{
	if (isEmpty()) return NULL;
	if (node == tail) return NULL;
	Node *p = tail;
	while (p->ptr != node)
		p = p->ptr;
	return p;
}

void Queue::Swap(Node* node1, Node* node2)
{
	if (node1 == NULL || node2 == NULL) return;
	if (node1 == node2) return;
	if (node2->ptr == node1)
	{
		Node *p = node1;
		node1 = node2;
		node2 = p;
	}
	Node *prev1 = Prev(node1);
	Node *prev2 = Prev(node2);
	Node *next1 = Next(node1);
	Node *next2 = Next(node2);
	if (next1 == node2)
	{
		if (prev1 != NULL)
			prev1->ptr = node2;
		else
			head = node2;
		node2->ptr = node1;
		node1->ptr = next2;
		return;
	}
	if (prev1 != NULL)
		prev1->ptr = node2;
	else
		head = node2;
	if (prev2 != NULL)
		prev2->ptr = node1;
	else
		head = node1;
	node2->ptr = next1;
	node1->ptr = next2;
}
int main()
{
	system("clear");
	Queue q;
	q.Print();
	cout << "Введите элементы по очереди" << endl;
	Node *s = q.getLast();
	for (int i = 0; i < 10; i++) {
		int z;
		cout << ">> ";
		cin >> z;
		s = q.Push(z, s);
	}
	q.Print();
	cout << "Последний элемент: " << q.getValue(q.getLast()) << endl;
	
	q.Print();
	cout << "В очереди " << q.getCount() << " элементов" << endl;
	q.Swap(q.getFirst(), q.getLast());
	q.Print();
	q.Clear();
	q.Print();
	cout << "В очереди " << q.getCount() << " элементов" << endl;
	cin.get(); cin.get();
	return 0;
}

