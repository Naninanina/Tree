#include <iostream>
#include <locale.h>
#include <queue>
#include <string>
using namespace std;


class Node
{
public:
	Node(int data = int(), Node *pLeft = nullptr, Node *pRight = nullptr)
	{
		this->data = data;
		this->pLeft = pLeft;
		this->pRight = pRight;
	}

	int data;
	Node *pLeft, *pRight;
};

Node* insert(int data, Node *node)
{
	if (node == nullptr)
	{
		Node *temp = new Node(data);
		return temp;
	}

	if (data < node->data)
	{
		node->pLeft = insert(data, node->pLeft);
	}
	else if (data > node->data)
	{
		node->pRight = insert(data, node->pRight);
	}

	return node;
}

void preorder(Node *node)
{
	if (node != nullptr)
	{
		cout << node->data << " ";
		preorder(node->pLeft);
		preorder(node->pRight);
	}
}

void inorder(Node *node)
{
	if (node != nullptr)
	{
		inorder(node->pLeft);
		cout << node->data << " ";
		inorder(node->pRight);
	}
}

void postorder(Node *node)
{
	if (node != nullptr)
	{
		postorder(node->pLeft);
		postorder(node->pRight);
		cout << node->data << " ";
	}
}

void bfs(Node *node)
{
	if (node != nullptr)
	{
		queue <Node*> q;
		q.push(node);

		while (q.empty() == false)
		{
			Node *temp = q.front();
			cout << " " << temp->data;
			q.pop();

			if (temp->pLeft != nullptr)
				q.push(temp->pLeft);

			if (temp->pRight != nullptr)
				q.push(temp->pRight);
		}
	}
	cout << endl;
}

void min(Node *node)
{
	Node *temp = node;
	while (temp->pLeft != nullptr)
	{
		temp = temp->pLeft;
	}
	cout << temp->data << endl;
}

void max(Node *node)
{
	Node *temp = node;
	while (temp->pRight != nullptr)
	{
		temp = temp->pRight;
	}
	cout << temp->data << endl;
}

void find(Node *node, int data)
{
	if (node == nullptr)
	{
		cout << "Я искал, но в дереве пусто, выросла капуста..." << endl;
		return;
	}
	if (node->data == data)
	{
		cout << "Я нашел " << data << "! Ссылка: " << node << endl;
		return;
	}
	else if (node->data > data) find(node->pLeft, data);
	else if (node->data < data) find(node->pRight, data);
}

void remove(Node *node, int data, Node *pPrev = nullptr)
{
	if (node == nullptr)
	{
		cout << "Ничего не пришлось удалять." << endl;
		return;
	}
	if (node->data == data)
	{
		if (node->pLeft == nullptr && node->pRight == nullptr)
		{
			if(pPrev->data < data)
			{
				pPrev->pRight = nullptr;
				delete node;
			}
			else
			{
				pPrev->pLeft = nullptr;
				delete node;
			}
		}
		else if (node->pLeft != nullptr && node->pRight == nullptr)
		{
			node->data = node->pLeft->data;
			node->pRight = node->pLeft->pRight;
			Node *temp = node->pLeft;
			node->pLeft = node->pLeft->pLeft;
			delete temp;
		}
		else if (node->pLeft == nullptr && node->pRight != nullptr)
		{
			node->data = node->pRight->data;
			node->pLeft = node->pRight->pLeft;
			Node *temp = node->pRight;
			node->pRight = node->pRight->pRight;
			delete temp;
		}
		else if (node->pLeft != nullptr && node->pRight != nullptr)
		{
			if (node->pRight->pLeft == nullptr) //Если левый узел правого поддерева отсутствует
			{
				node->data = node->pRight->data;
				node->pRight = node->pRight->pRight;
			}
			else
			{
				Node *temp = node->pRight;
				while (temp->pLeft != nullptr)
				{
					temp = temp->pLeft;
				}
				node->data = temp->data;
				remove(node, data, pPrev);
			}
		}
	}
	else if (node->data > data) remove(node->pLeft, data, node);
	else if (node->data < data) remove(node->pRight, data, node);
}

void printRight(Node *node, int level = 0);
void printLeft(Node *node, int level = 0);

void printRight(Node *node, int level)
{
	if (node->pRight != nullptr) printRight(node->pRight, level + 1);
	system("color 03");				//С наступающим Новым годом!
	for (int i = 0; i < level - 1; i++)
		cout << "    ";
	if (level)
		cout << "/```";
	cout << node->data << endl;
	if (node->pLeft != nullptr) printLeft(node->pLeft, level + 1);
}

void printLeft(Node *node, int level)
{
	if (node->pRight != nullptr) printRight(node->pRight, level + 1);
	system("color 02");
	for (int i = 0; i < level - 1; i++)
		cout << "    ";
	if (level)
		cout << "\\...";
	cout << node->data << endl;
	if (node->pLeft != nullptr) printLeft(node->pLeft, level + 1);
}

void print(Node *node, int level = 0)
{
	Node *temp = node;
	while (temp->pLeft != nullptr || temp->pRight != nullptr)
	{
		if (node->pRight != nullptr)
		{
			//print(temp->pRight, level + 1);
			printRight(temp->pRight, level + 1);
		}
		/*for (int i = 0; i < level-1; i++)
				cout << "    ";
		if (level)
			cout << "\\---";*/
		cout << temp->data << endl;
		if (temp->pLeft != nullptr)
		{
			//print(temp->pRight, level + 1);
			printLeft(temp->pLeft, level + 1);
		}
		cout << endl;
		system("color 07");
		return;
	}
}


/*Node::~Node()
{
	if (this != nullptr)
	{
		remove(this->pLeft);
		remove(this->pRight);
		delete this;
	}
}*/

void print_menu()
{
	//system("cls");
	cout << "Что вы хотите сделать с этим деревом?" << endl;
	cout << "1. Добавить элемент" << endl;
	cout << "2. Удалить элемент" << endl;
	cout << "3. Найти минимальный элемент" << endl;
	cout << "4. Найти максимальный элемент" << endl;
	cout << "5. Найти определенный элемент" << endl;
	cout << "6. Произвести прямой обход по дереву" << endl;
	cout << "7. Произвести центрированный обход по дереву" << endl;
	cout << "8. Произвести обратный обход по дереву" << endl;
	cout << "9. Обойти в ширину" << endl;
	cout << "10. Напечатать дерево" << endl;
	cout << "11. Выйти" << endl;
	cout << ">";
}

int intValidation()
{
	while (true)
	{
		int val;
		cin >> val;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Вы ввели неверное значение, попробуйте еще раз: ";
		}
		else
		{
			cin.ignore(32767, '\n');
			return val;
		}
	}
}

int checkForExistence(int numOne, int numTwo, string message)
{
	int choice;
	cin >> choice;
	if (choice >= numOne && choice <= numTwo)
	{
		return choice;
	}
	else
	{
		do
		{
			cout << message << endl;
			choice = intValidation();
		} while (!(choice >= numOne && choice <= numTwo));
		return choice;
	}
}


int main() {
	setlocale(LC_ALL, "ru");

	Node *tree = nullptr;
	tree = insert(9, tree);
	tree = insert(4, tree);
	tree = insert(10, tree);
	tree = insert(25, tree);
	tree = insert(2, tree);
	tree = insert(3, tree);
	tree = insert(18, tree);
	tree = insert(1, tree);
	tree = insert(19, tree);
	tree = insert(26, tree);
	tree = insert(5, tree);
	tree = insert(100, tree);
	tree = insert(70, tree);
	tree = insert(-2, tree);
	print(tree);

	int choice;

	do {
		print_menu();
		choice = checkForExistence(1, 11, "Вы ввели несуществующий пункт. Повторите попытку: ");

		switch (choice)
		{
		case 1:
		{
			cout << "Введите элемент, который хотите добавить (int): ";
			int temp;
			temp = intValidation();

			tree = insert(temp, tree);

			cout << "Новое дерево: " << endl;
			print(tree);
			break;
		}
		case 2:
		{
			cout << "Введите элемент, который хотите удалить (int): ";
			int temp;
			temp = intValidation();

			remove(tree, temp);

			cout << "Новое дерево: " << endl;
			print(tree);
			break;
		}
		case 3:
		{
			cout << "Минимальный элемент: ";
			min(tree);
			cout << endl;
			break;
		}
		case 4:
		{
			cout << "Максимальный элемент: ";
			max(tree);
			cout << endl;
			break;
		}
		case 5:
		{
			cout << "Введите элемент, который хотите найти (int): ";
			int temp;
			temp = intValidation();

			find(tree, temp);
			cout << endl;
			break;
		}
		case 6:
		{
			cout << "Дерево: " << endl;
			print(tree);
			cout << "Прямой обход: ";
			preorder(tree);
			cout << endl;
			cout << endl;
			break;
		}
		case 7:
		{
			cout << "Дерево: " << endl;
			print(tree);
			cout << "Центрированный обход: ";
			inorder(tree);
			cout << endl;
			cout << endl;
			break;
		}
		case 8:
		{
			cout << "Дерево: " << endl;
			print(tree);
			cout << "Обратный обход: ";
			postorder(tree);
			cout << endl;
			cout << endl;
			break;
		}
		case 9:
		{
			cout << "Дерево: " << endl;
			print(tree);
			cout << "Обход в ширину: ";
			bfs(tree);
			cout << endl;
			cout << endl;
			break;
		}
		case 10:
		{
			print(tree);
			cout << endl;
			break;
		}
		case 11:
		{
			cout << "Всего доброго!" << endl;
			return 0;
		}
		}
	} while (choice != 11);
}

