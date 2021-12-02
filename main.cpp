#include"header.h"

#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "portuguese");
	int opcao = 0;
	while (opcao != 4) {

		opcao = menu();

		limpaTela();

		switch (opcao) {
		case 1:
			cadastro();
		break;
		case 2:
			cadastrar_notas();
		break;
		case 3:
			lista();
		break;
		}
	}
}
