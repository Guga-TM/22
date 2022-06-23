#include <windows.h>
#include <iostream>
#include <conio.h>
#include <iostream>
int main(int argc, char* argv[]) {
	int j = 0;
	int n;
	n = atoi(argv[1]);
	char tmp;
	char* data = new char[n];
	for (int i = 0; i < n; i++) {
		data[i] = argv[2][i];
	}

	for (int i = 0; i < n; i++) {
		j = i;
		for (int k = i; k < n; k++) {
			if (argv[2][j] > argv[2][k]) {
				j = k;
			}
		}
		tmp = argv[2][i];
		argv[2][i] = argv[2][j];
		argv[2][j] = tmp;
	}

	printf("%s", argv[2]);
	Sleep(1000);
}


