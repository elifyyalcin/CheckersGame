#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
using namespace std;


char turnC;
int turn;  // turn=1 means white moves, 2 means black moves
char tableC[8][8];
int tableI[8][8];

int notover = 1;
int impNo = 0; // zorunlu hamlede yenmesi gereken taş sayısı
char Input[4];
char InputOld[2];
int firstImpNo;
int counter = 0;


void updateTurn(int t) {
	fstream f;
	f.open("tableC.dat", ios::out | ios::in);
	if (t == 1) {
		f.seekg(256);
		f << 'w';
	}
	else {
		f.seekg(256);
		f << 'b';
	}
}


void WriteMove(char I[]) {
	fstream f;
	f.open("moves.dat", ios::out | ios::in | ios::app);
	if (turn == 1) {
		f << "white:  ";
	}
	else
		f << "black:  ";

	for (int i = 0; i < 4; i++) {

		f << I[i];
	}
	f << endl;
	f.close();
}

/*oyuncu yeni oyun secenegini sectiginde oyunun bastan baslamasi icin tablo sifirlaniyor*/
void tableCsıfırdanYaz() {
	fstream f;
	f.open("tableC.dat", ios::out | ios::in);
	for (int i = 0; i <= 28; i += 4) {
		f.seekg(i);
		f << '_';
	}
	for (int k = 32; k <= 92; k += 4) {
		f.seekg(k);
		f << 'w';
	}
	for (int l = 96; l <= 156; l += 4) {
		f.seekg(l);
		f << '_';
	}
	for (int m = 160; m <= 220; m += 4) {
		f.seekg(m);
		f << 'b';
	}
	for (int n = 224; n <= 252; n += 4) {
		f.seekg(n);
		f << '_';
	}

	f.seekg(256);
	f << 'w';

}

void readFile() {

	fstream f;
	f.open("tableC.dat", ios::out | ios::in);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			f.seekg(counter);
			f >> tableC[i][j];
			counter += 4;
		}
	}

	f.seekg(256); /*dosyanin 9.satirindan siranin kimde oldugunu okuyoruz*/
	f >> turnC;

	for (int k = 0; k < 8; k++) {
		for (int m = 0; m < 8; m++) {
			if (tableC[k][m] == 'w') { tableI[k][m] = 1; }
			else if (tableC[k][m] == 'b') { tableI[k][m] = 2; }
			else if (tableC[k][m] == '_') { tableI[k][m] = 0; }
			else if (tableC[k][m] == 'W') { tableI[k][m] = 11; }
			else if (tableC[k][m] == 'B') { tableI[k][m] = 22; }

		}
	}
}

void startgame() {
	readFile();
	if (turnC == 'w') {
		turn = 1;
	}
	else { turn = 2; }

}


void printTable() {

	for (int k = 0; k < 8; k++) {
		for (int m = 0; m < 8; m++) {
			if (tableI[k][m] == 1) { tableC[k][m] = 'w'; }
			else if (tableI[k][m] == 2) { tableC[k][m] = 'b'; }
			else if (tableI[k][m] == 0) { tableC[k][m] = '_'; }
			else if (tableI[k][m] == 11) { tableC[k][m] = 'W'; }
			else if (tableI[k][m] == 22) { tableC[k][m] = 'B'; }

		}
	}



	cout << endl << endl << endl;
	cout << "        -----------------------------------------------------------------" << endl;
	for (int i = 0; i < 8; i++) {
		cout << 8 - i << "	" << "|";
		for (int j = 0; j < 8; j++) {
			if (tableC[7 - i][j] == '_') { tableC[7 - i][j] = ' '; }
			cout << "   " << tableC[7 - i][j] << "	" << "|";

		}
		cout << endl << "        -----------------------------------------------------------------" << endl;

	}
	cout << endl << "            A       B       C       D       E       F       G       H	" << endl;
}

void askMove() {
	if (turn == 1)
		cout << "White makes move:" << endl;
	else
		cout << "Black makes move:" << endl;
}

int stampEatCheck(int b, int a, int forbidden) {
	// if forbidden is 0- no forbidden move  if 1- cant go right if 2- cant go left
	int sum = 0;

	int right = 0;
	int left = 0;
	int up = 0;
	int down = 0;

	if (b < 6 && forbidden != 1) {
		if ((tableI[a][b + 1] == 3 - turn || tableI[a][b + 1] == (3 - turn) * 11) && tableI[a][b + 2] == 0) {
			//cout << endl << a << b << "CHECKKK R ";
			right = 1 + stampEatCheck(b + 2, a, 2);
		}
		else {}
	}
	else {
	}

	if (b > 1 && forbidden != 2) {
		if ((tableI[a][b - 1] == 3 - turn || tableI[a][b - 1] == (3 - turn) * 11) && tableI[a][b - 2] == 0) {
			//cout << endl << a << b << "CHECKKK L ";
			left = 1 + stampEatCheck(b - 2, a, 1);
		}
		else {}
	}
	else {
	}

	if (a < 6 && turn == 1) {
		if ((tableI[a + 1][b] == 3 - turn || tableI[a + 1][b] == (3 - turn) * 11) && tableI[a + 2][b] == 0) {
			//cout << endl << a << b << "CHECKKK U ";
			up = 1 + stampEatCheck(b, a + 2, 0);
		}
		else {}
	}
	else {
	}

	if (a > 1 && turn == 2) {
		if ((tableI[a - 1][b] == 3 - turn || tableI[a - 1][b] == (3 - turn) * 11) && tableI[a - 2][b] == 0) {
			//cout << endl << a << b << "CHECKKK D ";
			down = 1 + stampEatCheck(b, a - 2, 0);
		}
		else {}
	}
	else {
	}

	sum = max({ right,left,up,down });

	return sum;
}


/*oyuncunun yiyebilecegi max tas sayisi*/
int stampEatCheckKing(int b, int a, int forbidden) {
	//forbidden  1 up    2 right    3 down    4 left
	int sum = 0;
	int right = 0;
	int left = 0;
	int up = 0;
	int down = 0;

	// Right Check
	if (b < 6 && forbidden != 2) {
		int c = b;
		while (c < 6) {
			if (tableI[a][c + 1] == 3 - turn || tableI[a][c + 1] == (3 - turn) * 11) {
				if (tableI[a][c + 2] == 0) {
					int rc = c + 2;
					while (rc < 8 && tableI[a][rc] == 0) {
						if (1 + stampEatCheckKing(rc, a, 4) > right) {
							right = 1 + stampEatCheckKing(rc, a, 4);
						}
						rc++;
					}
				}
				else {
					break;
				}
			}
			else if (tableI[a][c + 1] == turn) {
				break;
			}

			c++;

		}
	}

	// Left Check
	if (b > 1 && forbidden != 4) {
		int c = b;
		while (c > 1) {
			if (tableI[a][c - 1] == 3 - turn || tableI[a][c - 1] == (3 - turn) * 11) {
				if (tableI[a][c - 2] == 0) {
					int rc = c - 2;
					while (rc > 0 && tableI[a][rc] == 0) {
						if (1 + stampEatCheckKing(rc, a, 2) > left) {
							left = 1 + stampEatCheckKing(rc, a, 2);
						}

						rc--;
					}
				}
				else {
					break;
				}
			}
			else if (tableI[a][c - 1] == turn) {
				break;
			}
			c--;
		}
	}

	// Up check
	if (a < 6 && forbidden != 1) {
		int r = a;
		while (r < 6) {
			if (tableI[r + 1][b] == 3 - turn || tableI[r + 1][b] == (3 - turn) * 11) {
				if (tableI[r + 2][b] == 0) {
					int rc = r + 2;
					while (rc < 8 && tableI[rc][b] == 0) {
						if (1 + stampEatCheckKing(b, rc, 3) > up) {
							up = 1 + stampEatCheckKing(b, rc, 3);
						}
						rc++;
					}
				}
				else {
					break;
				}
			}
			else if (tableI[r + 1][b] == turn) {
				break;
			}
			r++;

		}
	}


	// Down Check
	if (a > 1 && forbidden != 3) {
		int r = a;
		while (r > 1) {
			if (tableI[r - 1][b] == 3 - turn || tableI[r - 1][b] == (3 - turn) * 11) {
				if (tableI[r - 2][b] == 0) {
					int rc = r - 2;
					while (rc > 0 && tableI[rc][b] == 0) {
						if (1 + stampEatCheckKing(b, rc, 1) > down) {
							down = 1 + stampEatCheckKing(b, rc, 1);
						}

						rc--;
					}
				}
				else {
					break;
				}
			}
			else if (tableI[r - 1][b] == turn) {
				break;
			}
			r--;
		}

	}

	sum = max({ right,left,up,down });
	return sum;
}


/*max sayida tas yemek icin yapilmasi gereken zorunlu hamle sayisi*/
void calculateImperativeMoves() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (tableI[i][j] == turn) {
				if (stampEatCheck(j, i, 0) > impNo)
					impNo = stampEatCheck(j, i, 0);
				else {}
			}
			else if (tableI[i][j] == turn * 11) {
				if (stampEatCheckKing(j, i, 0) > impNo)
					impNo = stampEatCheckKing(j, i, 0);
				else {}
			}
		}
	}
}

void takeInput() {

	for (int m = 0; m < 4; m++)
		cin >> Input[m];

}

/*dosyaya random erisip seekg() ile tek tasin yerini degistiriyoruz*/
void updateTable() {
	char value;
	int a;
	int b;
	int s;
	int seek;
	char t1 = 'w';
	char t2 = 'b';
	char zero = '_';
	char ww = 'W';
	char bb = 'B';

	InputOld[0] = Input[2];
	InputOld[1] = Input[3];

	int control = 0;
	int i;
	int o;

	fstream f;
	f.open("tableC.dat", ios::out | ios::in);


	if (Input[3] - 49 == 7 || Input[3] - 49 == 0) {

		if (turn == 1) {
			tableI[Input[3] - 49][Input[2] - 97] = 11;
			a = Input[3] - 49;
			b = Input[2] - 97;
			s = a * 10 + b;
			if (a == 0) {
				seek = (s * 4);
			}
			else if (a == 1) {
				seek = a * 32 + b * 4;
			}
			else if (a == 2) {
				seek = a * 32 + b * 4;
			}
			else if (a == 3) {
				seek = a * 32 + b * 4;
			}
			else if (a == 4) {
				seek = a * 32 + b * 4;
			}
			else if (a == 5) {
				seek = a * 32 + b * 4;
			}
			else if (a == 6) {
				seek = a * 32 + b * 4;
			}
			else if (a == 7) {
				seek = a * 32 + b * 4;
			}

			f.seekg(seek);
			f << ww;

		}

		else {
			tableI[Input[3] - 49][Input[2] - 97] = 22;
			a = Input[3] - 49;
			b = Input[2] - 97;
			s = a * 10 + b;
			if (a == 0) {
				seek = (s * 4);
			}
			else if (a == 1) {
				seek = a * 32 + b * 4;
			}
			else if (a == 2) {
				seek = a * 32 + b * 4;
			}
			else if (a == 3) {
				seek = a * 32 + b * 4;
			}
			else if (a == 4) {
				seek = a * 32 + b * 4;
			}
			else if (a == 5) {
				seek = a * 32 + b * 4;
			}
			else if (a == 6) {
				seek = a * 32 + b * 4;
			}
			else if (a == 7) {
				seek = a * 32 + b * 4;
			}

			f.seekg(seek);
			f << bb;

		}

	}

	else {
		if (tableI[Input[1] - 49][Input[0] - 97] > 3) {
			tableI[Input[3] - 49][Input[2] - 97] = 11 * turn;
			a = Input[3] - 49;
			b = Input[2] - 97;
			s = a * 10 + b;
			if (a == 0) {
				seek = (s * 4);
			}
			else if (a == 1) {
				seek = a * 32 + b * 4;
			}
			else if (a == 2) {
				seek = a * 32 + b * 4;
			}
			else if (a == 3) {
				seek = a * 32 + b * 4;
			}
			else if (a == 4) {
				seek = a * 32 + b * 4;
			}
			else if (a == 5) {
				seek = a * 32 + b * 4;
			}
			else if (a == 6) {
				seek = a * 32 + b * 4;
			}
			else if (a == 7) {
				seek = a * 32 + b * 4;
			}

			if (turn == 1) {
				f.seekg(seek);
				f << ww;
			}
			else {
				f.seekg(seek);
				f << bb;
			}



		}
		else {
			tableI[Input[3] - 49][Input[2] - 97] = turn;
			a = Input[3] - 49;
			b = Input[2] - 97;
			s = a * 10 + b;
			if (a == 0) {
				seek = (s * 4);
			}
			else if (a == 1) {
				seek = a * 32 + b * 4;
			}
			else if (a == 2) {
				seek = a * 32 + b * 4;
			}
			else if (a == 3) {
				seek = a * 32 + b * 4;
			}
			else if (a == 4) {
				seek = a * 32 + b * 4;
			}
			else if (a == 5) {
				seek = a * 32 + b * 4;
			}
			else if (a == 6) {
				seek = a * 32 + b * 4;
			}
			else if (a == 7) {
				seek = a * 32 + b * 4;
			}

			if (turn == 1) {
				f.seekg(seek);
				f << t1;
			}
			else {
				f.seekg(seek);
				f << t2;
			}



		}

	}

	tableI[Input[1] - 49][Input[0] - 97] = 0;
	a = Input[1] - 49;
	b = Input[0] - 97;
	s = a * 10 + b;
	if (a == 0) {
		seek = (s * 4);
	}
	else if (a == 1) {
		seek = a * 32 + b * 4;
	}
	else if (a == 2) {
		seek = a * 32 + b * 4;
	}
	else if (a == 3) {
		seek = a * 32 + b * 4;
	}
	else if (a == 4) {
		seek = a * 32 + b * 4;
	}
	else if (a == 5) {
		seek = a * 32 + b * 4;
	}
	else if (a == 6) {
		seek = a * 32 + b * 4;
	}
	else if (a == 7) {
		seek = a * 32 + b * 4;
	}

	f.seekg(seek);
	f << zero;


	if (Input[2] >= Input[0] + 2 && Input[3] == Input[1]) { //right
		i = Input[0] - 97;
		o = Input[2] - 97;
		while (i != o) {
			i++;
			if (tableI[Input[1] - 49][i] == 3 - turn || tableI[Input[1] - 49][i] == (3 - turn) * 11) {
				tableI[Input[1] - 49][i] = 0;
				a = Input[1] - 49;
				b = i;
				s = a * 10 + b;
				if (a == 0) {
					seek = (s * 4);
				}
				else if (a == 1) {
					seek = a * 32 + b * 4;
				}
				else if (a == 2) {
					seek = a * 32 + b * 4;
				}
				else if (a == 3) {
					seek = a * 32 + b * 4;
				}
				else if (a == 4) {
					seek = a * 32 + b * 4;
				}
				else if (a == 5) {
					seek = a * 32 + b * 4;
				}
				else if (a == 6) {
					seek = a * 32 + b * 4;
				}
				else if (a == 7) {
					seek = a * 32 + b * 4;
				}

				f.seekg(seek);
				f << zero;

				break;
			}
		}
	}

	else if (Input[2] <= Input[0] - 2 && Input[3] == Input[1]) { //left
		i = Input[0] - 97;
		o = Input[2] - 97;
		while (i != o) {
			i--;
			if (tableI[Input[1] - 49][i] == 3 - turn || tableI[Input[1] - 49][i] == (3 - turn) * 11) {
				tableI[Input[1] - 49][i] = 0;
				a = Input[1] - 49;
				b = i;
				s = a * 10 + b;
				if (a == 0) {
					seek = (s * 4);
				}
				else if (a == 1) {
					seek = a * 32 + b * 4;
				}
				else if (a == 2) {
					seek = a * 32 + b * 4;
				}
				else if (a == 3) {
					seek = a * 32 + b * 4;
				}
				else if (a == 4) {
					seek = a * 32 + b * 4;
				}
				else if (a == 5) {
					seek = a * 32 + b * 4;
				}
				else if (a == 6) {
					seek = a * 32 + b * 4;
				}
				else if (a == 7) {
					seek = a * 32 + b * 4;
				}

				f.seekg(seek);
				f << zero;

				break;
			}
		}
	}


	else if (Input[2] == Input[0] && Input[3] <= Input[1] - 2) { //down
		i = Input[1] - 49;
		o = Input[3] - 49;
		while (i != o) {
			i--;
			if (tableI[i][Input[0] - 97] == 3 - turn || tableI[i][Input[0] - 97] == (3 - turn) * 11) {
				tableI[i][Input[0] - 97] = 0;
				a = i;
				b = Input[0] - 97;
				s = a * 10 + b;
				if (a == 0) {
					seek = (s * 4);
				}
				else if (a == 1) {
					seek = a * 32 + b * 4;
				}
				else if (a == 2) {
					seek = a * 32 + b * 4;
				}
				else if (a == 3) {
					seek = a * 32 + b * 4;
				}
				else if (a == 4) {
					seek = a * 32 + b * 4;
				}
				else if (a == 5) {
					seek = a * 32 + b * 4;
				}
				else if (a == 6) {
					seek = a * 32 + b * 4;
				}
				else if (a == 7) {
					seek = a * 32 + b * 4;
				}

				f.seekg(seek);
				f << zero;

				break;
			}
		}

	}

	else if (Input[2] == Input[0] && Input[3] >= Input[1] + 2) { //up
		i = Input[1] - 49;
		o = Input[3] - 49;
		while (i != o) {
			i++;
			if (tableI[i][Input[0] - 97] == 3 - turn || tableI[i][Input[0] - 97] == (3 - turn) * 11) {
				tableI[i][Input[0] - 97] = 0;
				a = i;
				b = Input[0] - 97;
				s = a * 10 + b;
				if (a == 0) {
					seek = (s * 4);
				}
				else if (a == 1) {
					seek = a * 32 + b * 4;
				}
				else if (a == 2) {
					seek = a * 32 + b * 4;
				}
				else if (a == 3) {
					seek = a * 32 + b * 4;
				}
				else if (a == 4) {
					seek = a * 32 + b * 4;
				}
				else if (a == 5) {
					seek = a * 32 + b * 4;
				}
				else if (a == 6) {
					seek = a * 32 + b * 4;
				}
				else if (a == 7) {
					seek = a * 32 + b * 4;
				}

				f.seekg(seek);
				f << zero;

				break;
			}
		}
	}

}

bool InputValidation(int sameStampCheck) {

	if (sameStampCheck) {
		if (Input[0] != InputOld[0] || Input[1] != InputOld[1])
			return false;
	}


	if (impNo != 0) {
		if (stampEatCheck(Input[0] - 97, Input[1] - 49, 0) == impNo && tableI[Input[1] - 49][Input[0] - 97] == turn) {
			if (tableI[Input[3] - 49][Input[2] - 97] == 0 && stampEatCheck(Input[2] - 97, Input[3] - 49, 0) == impNo - 1) {
				if (turn == 1) {
					if (Input[2] - 97 == Input[0] - 97 + 2 && Input[3] - 49 == Input[1] - 49) {
						if (tableI[Input[1] - 49][Input[0] - 97 + 1] == 3 - turn || tableI[Input[1] - 49][Input[0] - 97 + 1] == (3 - turn) * 11) {
							updateTable();
							WriteMove(Input);
							return true;
						}
					}
					else if (Input[2] - 97 == Input[0] - 97 - 2 && Input[3] - 49 == Input[1] - 49) {
						if (tableI[Input[1] - 49][Input[0] - 97 - 1] == 3 - turn || tableI[Input[1] - 49][Input[0] - 97 - 1] == (3 - turn) * 11) {
							updateTable();
							WriteMove(Input);
							return true;
						}
					}
					else if (Input[2] - 97 == Input[0] - 97 && Input[3] - 49 == Input[1] - 49 + 2) {
						if (tableI[Input[1] - 49 + 1][Input[0] - 97] == 3 - turn || tableI[Input[1] - 49 + 1][Input[0] - 97] == (3 - turn) * 11) {
							updateTable();
							WriteMove(Input);
							return true;
						}
					}
					else
						return false;
				}
				else {
					if (Input[2] - 97 == Input[0] - 97 + 2 && Input[3] - 49 == Input[1] - 49) {
						if (tableI[Input[1] - 49][Input[0] - 97 + 1] == 3 - turn || tableI[Input[1] - 49][Input[0] - 97 + 1] == (3 - turn) * 11) {
							updateTable();
							WriteMove(Input);
							return true;
						}
					}
					else if (Input[2] - 97 == Input[0] - 97 - 2 && Input[3] - 49 == Input[1] - 49) {
						if (tableI[Input[1] - 49][Input[0] - 97 - 1] == 3 - turn || tableI[Input[1] - 49][Input[0] - 97 - 1] == (3 - turn) * 11) {
							updateTable();
							WriteMove(Input);
							return true;
						}
					}
					else if (Input[2] - 97 == Input[0] - 97 && Input[3] - 49 == Input[1] - 49 - 2) {
						if (tableI[Input[1] - 49 - 1][Input[0] - 97] == 3 - turn || tableI[Input[1] - 49 - 1][Input[0] - 97] == (3 - turn) * 11) {
							updateTable();
							WriteMove(Input);
							return true;
						}
					}
					else
						return false;
				}
			}
			else
				return false;
		}
		else
			return false;
	}
	else {
		if (tableI[Input[1] - 49][Input[0] - 97] == turn) {

			if (turn == 1) {
				if (Input[2] - 97 == Input[0] - 97 + 1 && Input[3] - 49 == Input[1] - 49) {
					if (tableI[Input[1] - 49][Input[0] - 97 + 1] == 0) {
						updateTable();
						WriteMove(Input);
						return true;
					}
				}
				else if (Input[2] - 97 == Input[0] - 97 - 1 && Input[3] - 49 == Input[1] - 49) {
					if (tableI[Input[1] - 49][Input[0] - 97 - 1] == 0) {
						updateTable();
						WriteMove(Input);
						return true;
					}
				}
				else if (Input[2] - 97 == Input[0] - 97 && Input[3] - 49 == Input[1] - 49 + 1) {
					if (tableI[Input[1] - 49 + 1][Input[0] - 97] == 0) {
						updateTable();
						WriteMove(Input);
						return true;
					}
				}
				else
					return false;
			}

			else {
				if (Input[2] - 97 == Input[0] - 97 + 1 && Input[3] - 49 == Input[1] - 49) {
					if (tableI[Input[1] - 49][Input[0] - 97 + 1] == 0) {
						updateTable();
						WriteMove(Input);
						return true;
					}
				}
				else if (Input[2] - 97 == Input[0] - 97 - 1 && Input[3] - 49 == Input[1] - 49) {
					if (tableI[Input[1] - 49][Input[0] - 97 - 1] == 0) {
						updateTable();
						WriteMove(Input);
						return true;
					}
				}
				else if (Input[2] - 97 == Input[0] - 97 && Input[3] - 49 == Input[1] - 49 - 1) {
					if (tableI[Input[1] - 49 - 1][Input[0] - 97] == 0) {
						updateTable();
						WriteMove(Input);
						return true;
					}
				}
				else
					return false;
			}
			//gitmek istenen nokta 1 birim ötede mi
			// o nokta boş mu
		}
		else {
			return false;
		}
	}
}


bool InputValidationKing(int sameStampCheck) {
	int control = 0;
	int i;
	int o;
	if (sameStampCheck) {
		if (Input[0] != InputOld[0] || Input[1] != InputOld[1])
			return false;
	}

	if (impNo != 0) {
		if (stampEatCheckKing(Input[0] - 97, Input[1] - 49, 0) == impNo && tableI[Input[1] - 49][Input[0] - 97] == turn * 11) {
			if (tableI[Input[3] - 49][Input[2] - 97] == 0) {
				if ((Input[2] - 97 >= Input[0] - 97 + 2) && (Input[1] - 49 == Input[3] - 49) && stampEatCheckKing(Input[2] - 97, Input[3] - 49, 4) == impNo - 1) { //right
					i = Input[0] - 97;
					o = Input[2] - 97;
					while (i != o) {
						i++;
						if (tableI[Input[1] - 49][i] == 3 - turn || tableI[Input[1] - 49][i] == (3 - turn) * 11) {
							control++;
						}
						else if (tableI[Input[1] - 49][i] == turn || tableI[Input[1] - 49][i] == turn * 11) {
							control += 2;
						}


					}
					if (control == 1) {
						updateTable();
						return true;
					}
					else { return false; }
				}

				//*********

				else if ((Input[2] - 97 <= Input[0] - 97 - 2) && (Input[1] - 49 == Input[3] - 49) && stampEatCheckKing(Input[2] - 97, Input[3] - 49, 2) == impNo - 1) { //left
					i = Input[0] - 97;
					o = Input[2] - 97;
					while (i != o) {

						i--;

						if (tableI[Input[1] - 49][i] == 3 - turn || tableI[Input[1] - 49][i] == (3 - turn) * 11) {
							control++;

						}
						else if (tableI[Input[1] - 49][i] == turn || tableI[Input[1] - 49][i] == turn * 11) {
							control += 2;
						}


					}
					if (control == 1) {
						updateTable();
						return true;
					}
					else { return false; }
				}

				//**********

				else if ((Input[2] - 97 == Input[0] - 97) && (Input[1] - 49 - 2 >= Input[3] - 49) && stampEatCheckKing(Input[2] - 97, Input[3] - 49, 1) == impNo - 1) { //down
					i = Input[1] - 49;
					o = Input[3] - 49;
					while (i != o) {

						i--;

						if (tableI[i][Input[0] - 97] == 3 - turn || tableI[i][Input[0] - 97] == (3 - turn) * 11) {
							control++;

						}
						else if (tableI[i][Input[0] - 97] == turn || tableI[i][Input[0] - 97] == turn * 11) {
							control += 2;
						}


					}
					if (control == 1) {
						updateTable();
						return true;
					}
					else { return false; }
				}

				//************

				else if ((Input[2] - 97 == Input[0] - 97) && (Input[1] - 49 + 2 <= Input[3] - 49) && stampEatCheckKing(Input[2] - 97, Input[3] - 49, 3) == impNo - 1) { //up
					i = Input[1] - 49;
					o = Input[3] - 49;
					while (i != o) {

						i++;

						if (tableI[i][Input[0] - 97] == 3 - turn || tableI[i][Input[0] - 97] == (3 - turn) * 11) {
							control++;

						}
						else if (tableI[i][Input[0] - 97] == turn || tableI[i][Input[0] - 97] == turn * 11) {
							control += 2;
						}


					}
					if (control == 1) {
						updateTable();
						return true;
					}
					else { return false; }
				}
			}
			else
				return false;
		}
		else
			return false;
	}
	else {

		/*gitmek istediğim yerin yönü
		gitmek istediğim yer boş mu
		gitmek istediğim yerle aramda taş var mı*/

		if (tableI[Input[1] - 49][Input[0] - 97] == turn * 11) {
			if ((Input[2] - 97 > Input[0] - 97) && (Input[1] - 49 == Input[3] - 49)) { //right
				if (tableI[Input[3] - 49][Input[2] - 97] == 0) {

					i = Input[0] - 97;
					o = Input[2] - 97;
					while (i != o) {
						i++;
						if (tableI[Input[1] - 49][i] != 0) {
							control++;
						}
					}

					if (control == 0) {
						updateTable();
						return true;
					}
					else { return false; }
				}
				else
					return false;
			}

			//************

			if ((Input[2] - 97 < Input[0] - 97) && (Input[1] - 49 == Input[3] - 49)) { //left
				if (tableI[Input[3] - 49][Input[2] - 97] == 0) {
					i = Input[0] - 97;
					o = Input[2] - 97;
					while (i != o) {
						i--;
						if (tableI[Input[1] - 49][i] != 0) {
							control++;
						}
					}
					if (control == 0) {
						updateTable();
						return true;
					}
					else { return false; }
				}
				else
					return false;
			}

			//********

			if ((Input[2] - 97 == Input[0] - 97) && (Input[1] - 49 < Input[3] - 49)) { //up
				if (tableI[Input[3] - 49][Input[2] - 97] == 0) {

					i = Input[1] - 49;
					o = Input[3] - 49;
					while (i != o) {
						i++;
						if (tableI[i][Input[0] - 97] != 0) {
							control++;
						}
					}
					if (control == 0) {
						updateTable();
						return true;
					}
					else { return false; }
				}
				else
					return false;
			}

			//********

			if ((Input[2] - 97 == Input[0] - 97) && (Input[1] - 49 > Input[3] - 49)) { //down
				if (tableI[Input[3] - 49][Input[2] - 97] == 0) {

					i = Input[1] - 49;
					o = Input[3] - 49;
					while (i != o) {

						i--;

						if (tableI[i][Input[0] - 97] != 0) {

							control++;
						}
					}

					if (control == 0) {
						updateTable();
						return true;
					}
					else { return false; }
				}
				else
					return false;
			}
		}
		else
			return false;
	}
}



void inputValidationCaller(int sameStampCheck) {
	//if(girdisi normal taşsa) if girdi== turn
	if (tableI[Input[1] - 49][Input[0] - 97] == turn) {
		while (!InputValidation(sameStampCheck)) {
			for (int m = 0; m < 4; m++)
				cout << Input[m];
			cout << "move is not valid.\nThere is a move that must be played!" << endl;
			askMove();
			takeInput();
		}
	}


	// if girdi== turn*11
	else if (tableI[Input[1] - 49][Input[0] - 97] == turn * 11) {
		while (!InputValidationKing(sameStampCheck)) {
			for (int m = 0; m < 4; m++)
				cout << Input[m];
			cout << "move is not valid.\nThere is a move that must be played!" << endl;
			askMove();
			takeInput();
		}
	}

	else {

		for (int m = 0; m < 4; m++)
			cout << Input[m];
		cout << "move is not valid.\nThere is a move that must be played!" << endl;
		askMove();
		takeInput();
		inputValidationCaller(sameStampCheck);

	}

}

void endGameCheck() {
	int white = 0;
	int black = 0;
	for (int k = 0; k < 8; k++) {
		for (int m = 0; m < 8; m++) {
			if (tableI[k][m] == 1 || tableI[k][m] == 11) {
				white++;
			}
			else if (tableI[k][m] == 2 || tableI[k][m] == 22) {
				black++;
			}
		}
	}
	if (white == 0) {
		cout << endl << endl << endl << "!!!BLACK WINS!!!";
		notover = 0;
	}
	if (black == 0) {
		cout << endl << endl << endl << "!!!WHITE WINS!!!";
		notover = 0;
	}
	if (white == 1 && black == 1) {
		cout << endl << endl << endl << "...DRAW...";
		notover = 0;
	}
}

void menu() {

	int s;
	int selection;

	cout << endl << "***WELCOME TO CHECKERS GAME!!!***" << endl << endl;
	cout << "__________________________________" << endl;
	cout << endl << "1--->NEW GAME" << endl;
	cout << "2--->CONTINUE GAME" << endl;
	cout << "3--->END GAME" << endl << endl;
	cout << "please choose:";

	cin >> selection;


	if (selection == 1) {

		tableCsıfırdanYaz();
		startgame();

		while (notover) {
			printTable();
			calculateImperativeMoves();
			cout << endl << endl << "Imperative Moves:  " << impNo << endl << endl;
			firstImpNo = impNo;
			int firstMove = 0;
			if (impNo == 0) {
				askMove();
				takeInput();
				inputValidationCaller(firstMove);
				printTable();
				firstMove = 1;
				impNo--;
			}

			for (int e = 0; e < firstImpNo; e++) {
				askMove();
				takeInput();
				inputValidationCaller(firstMove);
				printTable();
				firstMove = 1;
				impNo--;
			}

			turn = 3 - turn;
			updateTurn(turn);
			impNo = 0;
			cout << "\n\nT U R N    E N D E D \n\n";
			endGameCheck();
		}
	}
	else if (selection == 2) {
		startgame();
		while (notover) {

			printTable();
			calculateImperativeMoves();
			cout << endl << endl << "Imperative Moves:  " << impNo << endl << endl;
			firstImpNo = impNo;
			int firstMove = 0;

			if (impNo == 0) {
				askMove();
				takeInput();
				inputValidationCaller(firstMove);
				printTable();
				firstMove = 1;
				impNo--;
			}

			for (int e = 0; e < firstImpNo; e++) {
				askMove();
				takeInput();
				inputValidationCaller(firstMove);
				printTable();
				firstMove = 1;
				impNo--;
			}

			turn = 3 - turn;
			updateTurn(turn);
			impNo = 0;
			cout << "\n\nT U R N    E N D E D \n\n";
			endGameCheck();
		}
	}
	else if (selection = 3) {
		exit(0);
	}
}


int main()
{
	menu();
	return 0;
}
