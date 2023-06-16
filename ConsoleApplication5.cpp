// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;

typedef vector<vector<int>> VVint;
typedef vector<int> Vint;
typedef vector<string> Vstr;

typedef map<string, int> MInt;
typedef map<string, bool> MBool;
typedef map<int, string> MStr;
typedef map<string, int> MStrInt;

Vstr::iterator ItStr;

template<class T>
class Graf
{
public:
	Graf();

	void InsertNode();
	void InsertEdge();

	void Print();

	void DelNode();
	void DelEdge();

	int ChekNode(string S);

	VVint CreateMatrix();

	void AlgorithmDijkstra();

	void DeepCrawl();

	void BreadthTraversal();

	int MinAlgortmD(MBool, MInt, MStr, int);
	~Graf();
private:
	VVint Mrtx;
	Vstr Title;
	int Node;
	int Edge;
};

template<class T>
Graf<T>::Graf()
{
	Node = 0;
	Edge = 0;
}
template<class T>
Graf<T>::~Graf()
{
	Title.clear();
	Mrtx.clear();
}

template<class T>
VVint Graf<T>::CreateMatrix()
{
	for (int D = 0; D < this->Node; D++)
		this->Vec.push_back(Vint);
	for (int D = 0; D < this->Node; D++)
		for (int E = 0; E < this->Node; E++)
			this->Vec[D].push_back(0);
	return*this;
}
template<class T>
void Graf<T>::Print()
{
	cout << '\t';
	for (int D = 0; D < this->Node;D++)
		cout << this->Title[D] << '\t';
	cout << endl;
	cout << "-----------------------------------------------" << endl;
	for (int D = 0; D < this->Node; D++)
	{
		cout << Title[D] << "\t|";
		for (int E = 0;E < this->Node; E++)
			cout << this->Mrtx[D][E] << '\t';
		cout << endl;
	}
}

template<class T>
int Graf<T>::ChekNode(string S)
{
	bool C = 1;
	int A = 0;
	while ((A < Node) && C)
		if (Title[A] == S)
			C = 0;
		else
			A++;
	if (C)
		return -1;
	else
		return A;
}

template<class T>
void Graf<T>::InsertNode()
{
	string S;
	cout << "Введите имя узла" << endl;
	getline(cin >> ws, S);
	Title.push_back(S);
	Node++;
	Vint NewV;
	Mrtx.push_back(NewV);
	for (int D = 0; D < Node - 1; D++)
		Mrtx[D].push_back(0);
	for (int D = 0; D < Node; D++)
		Mrtx[Node - 1].push_back(0);
}
template<class T>
void Graf<T>::InsertEdge()
{
	string S;
	int A, D, E;
	bool C;
	cout << "Имеет ли создаваемое ребро направление:" << endl;
	cout << "1) Да" << endl;
	cout << "2) No" << endl;
	cout << "Введите выбранное уточнение" << endl;
	cin >> A;
	if (A == 1)
		C = 1;
	else
		C = 0;
	if (C)
	{
		cout << "Введите имя узла, из которого идёт ребро" << endl;
		getline(cin >> ws, S);

		A = ChekNode(S);
		if (A < 0)
		{
			cout << "Узла с таким именем не существует" << endl;
		}
		else
		{
			D = A;
			cout << "Введите имя узла, к которому идёт ребро" << endl;
			getline(cin >> ws, S);

			A = ChekNode(S);
			if (A < 0)
			{
				cout << "Узла с таким именем не существует" << endl;
			}
			else
			{
				E = A;
				if (Mrtx[D][E] == 0)
				{
					cout << "Введите вес ребра" << endl;
					cin >> A;
					Mrtx[D][E] = A;
				}
				else
				{
					cout << "Между выбранными узлами уже есть ребро." << endl;
					cout << "Заменить уже существующее ребро новым?" << endl;
					cout << "1) Да" << endl;
					cout << "2) Нет" << endl;
					cout << "Введите выбранное уточнение" << endl;
					cin >> A;
					if (A == 1)
						C = 1;
					if (C)
					{
						cout << "Введите вес ребра" << endl;
						cin >> A;
						Mrtx[D][E] = A;
						Mrtx[E][D] = 0;
					}
				}
			}
		}
	}
	else
	{
		cout << "Введите имя первого узла" << endl;
		getline(cin >> ws, S);

		A = ChekNode(S);
		if (A < 0)
		{
			cout << "Узла с таким именем не существует" << endl;
		}
		else
		{
			D = A;
			cout << "Введите имя второго узла" << endl;
			getline(cin >> ws, S);

			A = ChekNode(S);
			if (A < 0)
			{
				cout << "Узла с таким именем не существует" << endl;
			}
			else
			{
				E = A;
				if (Mrtx[D][E] == 0)
				{
					cout << "Введите вес ребра" << endl;
					cin >> A;
					Mrtx[D][E] = A;
					Mrtx[E][D] = A;
				}
				else
				{
					cout << "Между выбранными узлами уже есть ребро." << endl;
					cout << "Заменить существующее ребро новым?" << endl;
					cout << "1) Да" << endl;
					cout << "2) No" << endl;
					cout << "Введите выбранное уточнение" << endl;
					cin >> A;
					if (A == 1)
						C = 1;
					if (C)
					{
						cout << "Введите вес ребра" << endl;
						cin >> A;
						Mrtx[D][E] = A;
						Mrtx[E][D] = A;
					}
				}
			}
		}
	}
}

template<class T>
void Graf<T>::DelNode()
{
	bool Fstr = 1;
	string S;
	int A;
	cout << "Введите имя узла, которое хотите удалить" << endl;
	getline(cin >> ws, S);

	A = ChekNode(S);
	if (A < 0)
	{
		cout << "Узла с таким именем не существует" << endl;
	}
	else
	{
		VVint temp;
		Vstr tempTit;
		for (int D = 0; D < Node; D++)
		{
			if (D != A)
			{
				S = Title[D];
				tempTit.push_back(S);
			}
		}
		Title.clear();
		Title = tempTit;

		for (int D = 0; D < Node - 1; D++)
		{
			Vint V;
			temp.push_back(V);
		}

		for (int D = 0; D < Node; D++)
		{
			Mrtx[A][D] = -1;
			Mrtx[D][A] = -1;
		}

		for (int D = 0; D < Node; D++)
		{
			if (Mrtx[D][0] > -1)
			{
				for (int E = 0; E < Node; E++)
					if (Mrtx[D][E] > -1)
						if (Fstr)
							temp[D].push_back(Mrtx[D][E]);
						else
							temp[D - 1].push_back(Mrtx[D][E]);
			}
			else
				Fstr = 0;

		}
		Mrtx.clear();
		Mrtx = temp;
		Node--;
	}

}
template<class T>
void Graf<T>::DelEdge()
{
	string S;
	int A, D, E;
	cout << "Enter the name of the nodes between which you want to remove the edge" << endl;
	cout << "Enter the name of the first node" << endl;
	getline(cin >> ws, S);
	A = ChekNode(S);
	if (A < 0)
	{
		cout << "Узла с таким именем не существует" << endl;
	}
	else
	{
		D = A;
		cout << "Введите имя второго узла" << endl;
		getline(cin >> ws, S);
		A = ChekNode(S);
		if (A < 0)
		{
			cout << "Узла с таким именем не существует" << endl;
		}
		else
		{
			E = A;
			Mrtx[D][E] = 0;
			Mrtx[E][D] = 0;
			cout << "Ребро убрано" << endl;
		}
	}
}

template<class T>
int Graf<T>::MinAlgortmD(MBool mb, MInt mi, MStr ms, int A)
{
	int K;
	Vstr temp;
	string Min;
	for (int D = 0; D < Node; D++)
		if (Mrtx[A][D] != 0)
			temp.push_back(ms[D]);

	K = temp.size();

	int mn = 100000;

	for (int D = 0; D < K; D++)
	{
		if (!mb[temp[D]])
		{
			if (mn > mi[temp[D]])
			{
				mn = mi[temp[D]];
				Min = temp[D];
			}
		}
	}
	temp.clear();
	if (mn != 100000)
		return ChekNode(Min);
	else
		return -1;
}
template<class T>
void Graf<T>::AlgorithmDijkstra()
{
	string S1;
	string S;
	cout << "Введите номер элемента, для которого вы хотите запустить алгоритм Дейкстры" << endl;
	getline(cin >> ws, S);
	S1 = S;
	int A = ChekNode(S);

	int B = 0;
	MBool Map_trav_node;
	MInt Map_min_val;
	MStr Map_node;
	MStrInt Map_Num_node;
	for (int D = 0; D < Node; D++)
	{
		Map_min_val[Title[D]] = 100000;
		Map_trav_node[Title[D]] = 0;
		Map_node[D] = Title[D];
		Map_Num_node[Title[D]] = D;
	}

	Map_min_val[S] = 0;

	int K;
	bool C = 1, F;
	int nod = Node;
	Vint travNode;

	while ((nod > 0) && C)
	{
		Vstr NodeT;
		for (int D = 0; D < Node; D++)
		{
			if (Mrtx[A][D] != 0)
				NodeT.push_back(Map_node[D]);
		}
		K = NodeT.size();
		for (int D = 0; D < K; D++)
		{
			if (Map_min_val[NodeT[D]] > Map_min_val[S] + Mrtx[Map_Num_node[S]][Map_Num_node[NodeT[D]]])
			{
				Map_min_val[NodeT[D]] = Map_min_val[S] + Mrtx[Map_Num_node[S]][Map_Num_node[NodeT[D]]];
			};
		}


		K = MinAlgortmD(Map_trav_node, Map_min_val, Map_node, A);
		if (K < 0)
		{
			Map_trav_node[S] = 1;
			if (travNode[travNode.size() - 1] != Map_Num_node[S1])
			{
				A = travNode[travNode.size() - 1];
				S = Title[A];
				travNode.erase(travNode.end() - 1);
				for (int D = 0; D < Node; D++)
					F = Map_trav_node[Title[D]];
				if (F)
					nod--;
				else
					nod++;
			}
			else
			{
				C = 0;
			}
		}
		else
		{
			travNode.push_back(Map_Num_node[S]);
			Map_trav_node[S] = 1;
			A = K;
			S = Title[A];
		}
		NodeT.clear();
	}
	if (C)
		for (int D = 0; D < Node; D++)
		{
			cout << "Самое короткое расстояние от узла " << S1 << " до узла  " << Title[D] << " -  " << Map_min_val[Title[D]] << endl;
		}
	else
	{
		for (int D = 0; D < Node; D++)
		{
			if (Map_min_val[Title[D]] != 100000)
				cout << "Самое короткое расстояние от узла " << S1 << " до узла " << Title[D] << " - " << Map_min_val[Title[D]] << endl;
		}
		cout << "Минимальное расстояние до узлов, которое мог вычислить алгоритм " << endl;
	}
	Map_trav_node.clear();
	Map_min_val.clear();
	Map_node.clear();
	Map_Num_node.clear();
	travNode.clear();
}

template<class T>
void Graf<T>::DeepCrawl()
{
	string S1;
	string S;
	cout << " Введите элемент, с которого начнется сканирование " << endl;
	getline(cin >> ws, S);
	S1 = S;

	MStr NumTitl;
	MStrInt TitlNum;
	MBool Passed_elements;

	for (int D = 0; D < Node; D++)
	{
		NumTitl[D] = Title[D];
		TitlNum[Title[D]] = D;
		Passed_elements[Title[D]] = 0;
	}

	Vint Chain;
	Vint Ways;

	bool C = 1, fi = 1;
	int nod = Node;

	int K;
	int B;
	while ((nod > 0) && C)
	{
		for (int D = 0; D < Node; D++)
			if (Mrtx[TitlNum[S]][D] != 0)
				Ways.push_back(D);

		K = Ways.size();
		B = 0;
		if (!Passed_elements[S])
		{
			nod--;
			cout << S << "->";
			Passed_elements[S] = 1;
			while ((K > B) && fi)
			{
				if (!Passed_elements[NumTitl[Ways[B]]])
				{
					fi = 0;
				}
				else
				{
					B++;
				}
			}

			if (!fi)
			{
				Chain.push_back(TitlNum[S]);
				S = NumTitl[Ways[B]];

			}
			else
			{
				S = NumTitl[Chain[Chain.size() - 1]];
				Chain.erase(Chain.end() - 1);
				cout << endl;
			}
		}
		else
		{
			cout << S << "->";
			if (S == S1)
			{
				while ((K > B) && fi)
				{
					if (!Passed_elements[NumTitl[Ways[B]]])
					{
						fi = 0;
					}
					else
						B++;
				}
				if (fi)
				{
					C = 0;
				}
				else
				{
					Chain.push_back(TitlNum[S]);
					S = NumTitl[Ways[B]];
				}
			}
			else
			{
				while ((K > B) && fi)
				{
					if (!Passed_elements[NumTitl[Ways[B]]])
					{
						fi = 0;
					}
					else
						B++;
				}
				if (!fi)
				{
					Chain.push_back(TitlNum[S]);
					S = NumTitl[Ways[B]];
				}
				else
				{
					S = NumTitl[Chain[Chain.size() - 1]];
					Chain.erase(Chain.end() - 1);
				}
			}
		}
		Ways.clear();
		fi = 1;
	}
	NumTitl.clear();
	TitlNum.clear();
	Passed_elements.clear();
	Chain.clear();
	Ways.clear();
}
template<class T>
void Graf<T>::BreadthTraversal()
{
	string S1;
	string S;
	cout << " Введите элемент, с которого начнется сканирование " << endl;
	getline(cin >> ws, S);
	S1 = S;

	MStr NumTitl;
	MStrInt TitlNum;
	MBool Passed_elements;

	for (int D = 0; D < Node; D++)
	{
		NumTitl[D] = Title[D];
		TitlNum[Title[D]] = D;
		Passed_elements[Title[D]] = 0;
	}

	Vint Chain;
	Vint Ways;

	bool C = 1, fi = 1;
	int nod = Node;

	int K = 1, Kp = 0;
	int B;

	Chain.push_back(TitlNum[S]);
	Passed_elements[S] = 1;

	while (C)
	{
		if (K == Kp)
		{
			C = 0;
		}
		else
		{
			for (int D = Kp; D < K; D++)
			{
				S = NumTitl[Chain[D]];
				cout << S << "->";
				for (int D = 0; D < Node; D++)
					if (Mrtx[TitlNum[S]][D] != 0)
						Ways.push_back(D);

				for (int D = 0; D < Ways.size();D++)
					if (!Passed_elements[NumTitl[Ways[D]]])
					{
						Passed_elements[NumTitl[Ways[D]]] = 1;
						Chain.push_back(Ways[D]);
					}
			}
			Kp = K;
			K = Chain.size();
			Ways.clear();
		}
	}
	C = 1;
	for (int D = 0; D < Node; D++)
	{
		if (!Passed_elements[Title[D]])
			C = Passed_elements[Title[D]];
	}
	if (C)
	{
		cout << " Алгоритм обошел все элементы " << endl;
	}
	else
	{
		cout << " Алгоритм не обошел все элементы " << endl;
	}
	NumTitl.clear();
	TitlNum.clear();
	Passed_elements.clear();
	Chain.clear();
	Ways.clear();
}

void Menu()
{
	cout << "\tГлавное меню" << endl;
	cout << "1) Добавление узла" << endl;
	cout << "2) Добавление ребра" << endl;
	cout << "3) Удаление узла" << endl;
	cout << "4) Удаление ребра" << endl;
	cout << "5) Вывод матрицы смежности " << endl;
	cout << "6) Решение графа алгоритмом Дейкстры " << endl;
	cout << "7) Глубокое сканирование" << endl;
	cout << "8) Обход по ширине" << endl;
	cout << "9) Завершение работы с графом" << endl;
}

int main()
{
	Graf<int> graf;
	setlocale(LC_ALL, "Russian");

	bool F = 1;
	int A;

	while (F)
	{
		Menu();
		cout << "Выберите номер действия:" << endl;
		cin >> A;
		switch (A)
		{
		case 1:
		{
			system("cls");
			graf.InsertNode();
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			graf.InsertEdge();
			system("cls");
			break;
		}
		case 3:
		{
			system("cls");
			graf.DelNode();
			system("cls");
			break;
		}
		case 4:
		{
			system("cls");
			graf.DelEdge();
			system("cls");
			break;
		}
		case 5:
		{
			system("cls");
			graf.Print();
			break;
		}
		case 6:
		{
			system("cls");
			graf.AlgorithmDijkstra();
			break;
		}
		case 7:
		{
			system("cls");
			graf.DeepCrawl();
			break;
		}
		case 8:
		{
			system("cls");
			graf.BreadthTraversal();
			break;
		}
		case 9:
		{
			system("cls");
			F = 0;
			break;
		}
		default:
			cout << "Выберите номер действия, который есть в этом меню" << endl;
		}
	}
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
