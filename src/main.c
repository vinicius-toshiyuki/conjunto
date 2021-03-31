#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "");
	wprintf(L"\ue0b0\n");
	return 0;
}
