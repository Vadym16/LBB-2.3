#include <iostream>
#include <string>

using namespace std;

string plus_prob(string line);
int parnist(int a);
void view(uint16_t a);
void shufr(char c, int row, int pos);

struct Byte1 {
	uint16_t par1 : 1;
	uint16_t up : 4;
	uint16_t row_b : 2;
};

struct Byte2 {
	uint16_t par2 : 1;
	uint16_t low : 4;
	uint16_t pos_b : 4;
};

union shufr_b {
	struct {
		Byte1 b1;
		Byte2 b2;
	};
	uint16_t words[2];
 };

int main()
{
	setlocale(LC_ALL, "ukr");

	string txt[4] = {
		"First line",
		"Second line",
		"Third line",
		"Fourth line"
	};

	for (int i = 0; i < 4; i++) {
		txt[i] = plus_prob(txt[i]);
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 16; j++) {
			shufr(txt[i][j], i, j);
		}
	}

}

string plus_prob(string line) {
	while (line.length() < 16) {
		line += ' ';
	}
	return line;
}

int parnist(int a) {
	int par = 0;
	while (a) {
		par ^= (a & 1);
		a >>= 1;
	}
	return par;
}

void view(uint16_t a) {
	for (int i = 16; i >= 0; i--) {
		cout << ((a >> i) & 1);
	}
	cout << endl;
}

void shufr(char c, int row, int pos) {
	int ascii = static_cast<int>(c);
	int up = (ascii >> 4) & 0xF;
	int low = ascii & 0xF;

	int row_b = row & 0x3;
	int pos_b = pos & 0xF;
	int par1 = parnist(row_b << 2 | up);
	int par2 = parnist(pos_b << 4 | low);

	shufr_b sh;

	sh.b1.row_b = row_b;
	sh.b1.par1 = par1;
	sh.b1.up = up;
	sh.b2.pos_b = pos_b;
	sh.b2.par2 = par2;
	sh.b2.low = low;


	cout << "Буква: " << c << endl;
	cout << "Байт 1: ";
	view(sh.words[0]);
	cout << "Байт 2: ";
	view(sh.words[1]);

}