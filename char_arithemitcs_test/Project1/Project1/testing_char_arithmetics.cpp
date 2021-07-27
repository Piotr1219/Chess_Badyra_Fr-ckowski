#include <stdio.h>
using namespace std;

void main() {
	char char2 = 2;
	char char1 = 13;
	int number_int = 13;
	char res1 = char1 + char2;
	char res2 = char1 - char2;
	char res3 = char1 * char2;
	char res4 = char1 / char2;
	printf("Dodawanie char i char (13+2): %d\n", res1);
	printf("Odejmowanie char i char (13-2): %d\n", res2);
	printf("Mno¿enie char przez char (13*2): %d\n", res3);
	printf("Dzielenie char przez char (13/2): %d\n\n\n", res4);

	int int2 = 2;
	char res11 = char1 + int2;
	char res21 = char1 - int2;
	char res31 = char1 * int2;
	char res41 = char1 / int2;
	printf("Dodawanie char i int (13+2): %d\n", res11);
	printf("Odejmowanie char i int (13-2): %d\n", res21);
	printf("Mno¿enie char przez int (13*2): %d\n", res31);
	printf("Dzielenie char przez int (13/2): %d\n\n\n", res41);

	int int3 = 13;
	char char3 = 2;
	int res12 = int3 + char3;
	int res22 = int3 - char3;
	int res32 = int3 * char3;
	int res42 = int3 / char3;
	printf("Dodawanie int i char (13+2): %d\n", res12);
	printf("Odejmowanie int i char (13-2): %d\n", res22);
	printf("Mno¿enie int przez char (13*2): %d\n", res32);
	printf("Dzielenie int przez char (13/2): %d\n\n\n", res42);

	int A[7]{0, 1, 2, 3, 4, 5, 6 };

	char index = 2;
	printf("Index wynosi: %d\n", index);
	printf("Wartosc tablicy A od indexu (powinny wynosic tyle co index): %d\n\n\n", A[index]);

	char test_char = 15;
	int test_int = 15;

	if (test_char == test_int) {
		printf("Porownanie int i char o tej samej wartosci daje TRUE\n\n\n");
	}
	else {
		printf("Porownanie int i char o tej samej wartosci daje FALSE\n\n\n");
	}

}