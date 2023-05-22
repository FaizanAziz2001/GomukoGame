
#include <iostream>
#include <fstream>
using namespace std;

#define difficulty 3
#define capacity 100
#define maxp 10
struct board
{
	char b[capacity][capacity] = {};
	int dim;
	char Symb[maxp] = {};
	char name[maxp][capacity];
	int turn = 0, NOP;
	int WC = 0;
	int winningorder[maxp];
	int Wincount;
};

struct position
{
	int ri;
	int ci;
};

void init(board& B)
{
	ifstream fin("Grid.txt");
	fin >> B.dim;

	cout << "Number of players: ";
	cin >> B.NOP;

	for (int ri = 0; ri < B.dim; ri++)
	{
		for (int ci = 0; ci < B.dim; ci++)
			fin >> B.b[ri][ci];
	}

	for (int i = 0; i < B.NOP; i++)
	{
		cout << "Enter Player " << i + 1 << " name: ";
		cin >> B.name[i];
		cout << "Enter symbol : ";
		cin >> B.Symb[i];
	}

	cout << "Enter Win count:";
	cin >> B.Wincount;

}

void init_comp(board& B)
{
	ifstream fin("Grid.txt");
	fin >> B.dim;

	for (int ri = 0; ri < B.dim; ri++)
	{
		for (int ci = 0; ci < B.dim; ci++)
			fin >> B.b[ri][ci];
	}
	cout << "Enter Player " << 1 << " name: ";
	cin >> B.name[0];
	cout << "Enter symbol : ";
	cin >> B.Symb[0];
	cout << endl;

	cout << "Enter Bot name: ";
	cin >> B.name[1];
	cout << "Enter symbol : ";
	cin >> B.Symb[1];


	cout << "Enter Win count:";
	cin >> B.Wincount;

	B.turn = 0;
	srand(time(NULL));
}

void display(board B)
{
	system("cls");
	for (int ri = 0; ri < B.dim; ri++)
	{
		for (int ci = 0; ci < B.dim; ci++)
			cout << B.b[ri][ci] << " ";
		cout << endl;
	}
}

void displayturnmessage(char B[], char sym)
{
	cout << B << "'s Turn " << endl << "Symbol: " << sym << endl << endl;
}

void selectposition(position& pos)
{
	cout << "Enter the row number: ";
	cin >> pos.ri;
	cout << "Enter the column number: ";
	cin >> pos.ci;

	pos.ri--;
	pos.ci--;
}

bool validation(board B, position pos)
{
	return ((pos.ri >= 0 && pos.ci >= 0) && (pos.ri < B.dim&& pos.ci < B.dim) && (B.b[pos.ri][pos.ci] == '-'));
}

void update(char b[][capacity], position pos, char sym)
{
	b[pos.ri][pos.ci] = sym;
}

void changeturn(int& num, int nop, int data[], int WC)
{

	if (num >= nop - 1)
		num = 0;
	else
		num++;

	for (int i = 0; i < WC; i++)
	{
		for (int j = 0; j < WC; j++)
		{
			if (data[j] == num)
			{
				num++;
				if (num == nop)
					num = 0;
			}

		}

	}

}

void changeturn_comp(int& num)
{

	num = (num + 1) % 2;

}

bool Husingsinglepointcheck(board B, int dim, position pos, char sym, int Wincount)
{
	int dcount = 0, ucount = 0;
	for (int ri = pos.ri + 1, i = 0; i < Wincount - 1; i++, ri++)
	{
		if (ri >= dim or B.b[ri][pos.ci] != sym)
			break;
		dcount++;
	}

	for (int ri = pos.ri - 1, i = 0; i < Wincount - 1; i++, ri--)
	{
		if (ri < 0 or B.b[ri][pos.ci] != sym)
			break;
		ucount++;
	}

	if (ucount + dcount == Wincount - 1)
		return true;
	return false;
}

bool Vusingsinglepointcheck(board B, int dim, position pos, char sym, int Wincount)
{
	int lcount = 0, rcount = 0;
	for (int ci = pos.ci + 1, i = 0; i < Wincount - 1; i++, ci++)
	{
		if (ci >= dim or B.b[pos.ri][ci] != sym)
			break;
		rcount++;
	}

	for (int ci = pos.ci - 1, i = 0; i < Wincount - 1; i++, ci--)
	{
		if (ci < 0 or B.b[pos.ri][ci] != sym)
			break;
		lcount++;
	}

	if (lcount + rcount == Wincount - 1)
		return true;
	return false;
}

bool Daig1usingsinglepointcheck(board B, int dim, position pos, char sym, int Wincount)
{
	int lcount = 0, rcount = 0;
	for (int ri = pos.ri + 1, ci = pos.ci + 1, i = 0; i < Wincount - 1; i++, ri++, ci++)
	{
		if (ri >= dim or ci >= dim or B.b[ri][ci] != sym)
			break;
		rcount++;
	}

	for (int ri = pos.ri - 1, ci = pos.ci - 1, i = 0; i < Wincount - 1; i++, ri--, ci--)
	{
		if (ri < 0 or ci < 0 or B.b[ri][ci] != sym)
			break;
		rcount++;
	}

	if (lcount + rcount == Wincount - 1)
		return true;
	return false;
}

bool Daig2usingsinglepointcheck(board B, int dim, position pos, char sym, int Wincount)
{
	int lcount = 0, rcount = 0;
	for (int ri = pos.ri + 1, ci = pos.ci - 1, i = 0; i < Wincount - 1; i++, ri++, ci--)
	{
		if (ri >= dim or ci < 0 or B.b[ri][ci] != sym)
			break;
		rcount++;
	}

	for (int ri = pos.ri - 1, ci = pos.ci + 1, i = 0; i < Wincount - 1; i++, ri--, ci++)
	{
		if (ri < 0 or ci >= dim or B.b[ri][ci] != sym)
			break;
		rcount++;
	}

	if (lcount + rcount == Wincount - 1)
		return true;
	return false;
}

bool Patterncheck(board B, position pos, char sym, int Wincount)
{
	if (Husingsinglepointcheck(B, B.dim, pos, sym, Wincount))
	{
		return true;

	}
	if (Vusingsinglepointcheck(B, B.dim, pos, sym, Wincount))
	{
		return true;

	}
	if (Daig1usingsinglepointcheck(B, B.dim, pos, sym, Wincount))
	{
		return true;

	}
	if (Daig2usingsinglepointcheck(B, B.dim, pos, sym, Wincount))
	{
		return true;

	}
	return false;


}

void Leaderboard(board B)
{
	for (int i = 0; i < B.NOP; i++)
	{
		cout << i + 1 << ". " << B.name[B.winningorder[i]] << endl;
	}
}

void Computer_move(board B, position& P)
{


	for (int ri = 0; ri < B.dim; ri++)
	{
		for (int ci = 0; ci < B.dim; ci++)
		{
			P.ri = ri, P.ci = ci;
			if (validation(B, P))
			{
				B.b[ri][ci] = B.Symb[B.turn];
				if (Patterncheck(B, P, B.Symb[B.turn], B.Wincount))
				{
					return;
				}
				B.b[ri][ci] = '-';
			}

		}
	}

	while (B.Wincount >= difficulty)
	{

		for (int ri = 0; ri < B.dim; ri++)
		{
			for (int ci = 0; ci < B.dim; ci++)
			{
				P.ri = ri, P.ci = ci;
				if (validation(B, P))
				{
					B.b[ri][ci] = B.Symb[B.turn - 1];
					if (Patterncheck(B, P, B.Symb[B.turn - 1], B.Wincount))
					{
						return;
					}
					B.b[ri][ci] = '-';
				}

			}
		}
		B.Wincount--;
	}


	do
	{
		P.ri = rand() % B.dim;
		P.ci = rand() % B.dim;
	} while (!validation(B, P));

}

void human()
{
	char cont;
	do
	{
		system("cls");
		int count = 0;
		board B;
		position pos;
		init(B);
		display(B);
		do
		{
			displayturnmessage(B.name[B.turn], B.Symb[B.turn]);
			do
			{
				cout << "Select the position " << endl;
				selectposition(pos);
			} while (!validation(B, pos));

			update(B.b, pos, B.Symb[B.turn]);
			display(B);

			if (Patterncheck(B, pos, B.Symb[B.turn], B.Wincount))
			{
				B.winningorder[B.WC++] = B.turn;
				if (B.WC == B.NOP - 1)
				{
					changeturn(B.turn, B.NOP, B.winningorder, B.WC);
					B.winningorder[B.WC++] = B.turn;
					break;
				}
			}

			count++;

			if (count != pow(B.dim, 2))
			{
				changeturn(B.turn, B.NOP, B.winningorder, B.WC);

			}
			else if (B.WC == 1)
			{
				cout << "Game is a draw between remaining players" << endl;
				break;
			}
			else
			{
				cout << "Game is a draw" << endl;
				break;
			}



		} while (count != pow(B.dim, 2));

		cout << endl << "Leader Board: " << endl;
		Leaderboard(B);
		cout << "Do you want to continue?(Y of yes)";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');


}

void computer()
{
	char cont;

	board B;
	position pos;

	do
	{
		int count = 0;
		system("cls");
		init_comp(B);
		display(B);

		do
		{
			displayturnmessage(B.name[B.turn], B.Symb[B.turn]);
			if (B.turn == 0)
			{
				do
				{
					cout << "Select the position " << endl;
					selectposition(pos);
				} while (!validation(B, pos));
			}
			else
			{
				Computer_move(B, pos);
			}

			update(B.b, pos, B.Symb[B.turn]);
			display(B);

			if (Patterncheck(B, pos, B.Symb[B.turn], B.Wincount))
			{
				cout << B.name[B.turn] << " wins" << endl;
				break;
			}

			count++;

			if (count != pow(B.dim, 2))
			{
				changeturn_comp(B.turn);

			}
			else
			{
				cout << "Game is a draw" << endl;
				break;
			}

		} while (count != pow(B.dim, 2));

		cout << "Do you want to continue?(Y of yes)";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');


}

void menu()
{
	system("cls");
	cout << "1. To play Multiplayer " << endl
		<< "2. To play with bot" << endl;
}

int main()
{
	int choice;
	char cont;
	do
	{
		menu();
		cout << "Enter number: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			human();
			break;
		case 2:
			computer();
			break;
		}
		cout << endl;
		cout << "Press you want to exit(Y for yes)?";
		cin >> cont;
	} while (cont != 'y' && cont != 'Y');

}

