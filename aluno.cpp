#include <iostream>
#include <locale.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include"header.h"
#include <iostream>

using namespace std;

void lerALuno(Aluno aluno) {
    cout <<" Nome: " << aluno.nome << endl
        << " Matricula: " << aluno.matricula << endl
        << " AEP1: " << aluno.aep1 << endl
        << " Prova1: " << aluno.prova1 << endl
        << " AEP2: " << aluno.aep2 << endl
        << " PROVA2: " << aluno.prova2 << endl
        << " SUB1: " << aluno.sub<< endl
        << " Media: " << aluno.media<< endl
        << " Status: " << aluno.status << endl<< endl;
}

int menu() {
    int opcao = 0;
    bool repetir = true;
    while(repetir){
        cout << "<==========================================>" << endl;
        cout << "<========SELECIONE UMA OPÇAO ABAIXO========> " << endl;
        cout << "<========1 - Cadastrar novo aluno==========>" << endl;
        cout << "<========2 - Cadastrar notas de um aluno.==>" << endl;
        cout << "<========3 - Solicitar lista de alunos.====>" << endl;
        cout << "<========4 - Finalizar o programa.=========>" << endl;
        cout << "<==========================================>" << endl;
        cin >> opcao;
        if(opcao > 0 && opcao < 5) {
            repetir = false;
        } else {
            limpaTela();
            cout << "<==========================================>" << endl;
            cout << "             OPÇÃO INVALIDA                 " << endl;
            cout << "<==========================================>" << endl << endl;
        }
    }
    return opcao;
}

void limpaTela() {
    system("cls");
}

bool cadastraAluno (Aluno aluno) {
	std::ofstream arquivo;
	arquivo.open("banco.csv", std::fstream::app);

	if (!arquivo.is_open()) {
		cout << "Houve um erro ao abrir o arquivo!\n";
		return false;
	}

	arquivo << aluno.nome << ";"
			<< aluno.matricula << ";"
			<< aluno.aep1 << ";"
			<< aluno.prova1 << ";"
			<< aluno.aep2 << ";"
			<< aluno.prova2 << ";"
			<< aluno.sub << ";"
			<< aluno.media << ";"
			<< aluno.status << ";\n";

	arquivo.close();
	return true;
}


void cadastro () {
	Aluno alunoCadastro;
	cout << "------------------------------------" << endl;
	cout << "Digite o nome do aluno: ";
	cin >> alunoCadastro.nome;
	cout << "------------------------------------" << endl;
	cout << "Digite a matricula: ";
	cin >> alunoCadastro.matricula;
	cout << "------------------------------------" << endl;
	alunoCadastro.aep1 = 0;
	alunoCadastro.prova1 = 0;
	alunoCadastro.aep2 = 0;
	alunoCadastro.prova2 = 0;
	alunoCadastro.media = 0;
	alunoCadastro.sub = 0;
	alunoCadastro.status = "reprovado";

	if (cadastraAluno (alunoCadastro)) {
            cout << "<==========================================>" << endl;
            cout << "        ALUNO CADASTRADO COM SUCESSO!       " << endl;
            cout << "<==========================================>" << endl << endl;
	} else {
            cout << "<==========================================>" << endl;
            cout << "           ERRO AO CADASTRAR ALUNO!!!       " << endl;
            cout << "<==========================================>" << endl << endl;
	}
}

void lista(){
	//variaveis
	int rodar_arquivo = 0;
	int b = 0;
	char delimitador = ';';
	std::string str;
	std::ifstream arquivo;
	std::ofstream arquivo_new_geral;
	std::ofstream arquivo_sub1;
	std::ofstream arquivo_sub2;
	std::ofstream arquivo_aprovados;
	std::ofstream arquivo_reprovados;
	int w =0;
	arquivo.open("banco.csv", std::ios::in);
	// contar numero de linhas do arquivo
	if (!arquivo.is_open()) {
		cout << "Houve um erro ao abrir o arquivo!\n";
	}
	else{
		while (arquivo.good()) {
			rodar_arquivo = arquivo.get();
			if (rodar_arquivo == '\n') {
				b++;
			}
		}
	}
	std::string line;
	std::string linha[b];
	int i = 0;
	arquivo.close();
	std::vector<struct Aluno> alunos(b);

	// jogar todas as linhas para linha[i]

	arquivo.open("banco.csv", std::ios::in);
	do{
		arquivo >> linha[i];
		i++;
	}while(getline(arquivo, line));
	arquivo.close();

	//dividir as linhas para a estrutura

	for(int i = 0; i < b; i++){
		w = 0;
		std::stringstream X(linha[i]);
		while (getline(X, str, ';')){
			if(w == 0){
				alunos[i].nome = str;
			} else if(w == 1){
				alunos[i].matricula = str;
			} else if(w == 2){
				alunos[i].aep1 = std::stof(str);
			} else if(w == 3){
				alunos[i].prova1 = std::stof(str);
			} else if(w == 4){
				alunos[i].aep2 = std::stof(str);
			} else if(w == 5){
				alunos[i].prova2 = std::stof(str);
			} else if(w == 6){
				alunos[i].sub = std::stof(str);
			} else if(w == 7){
				alunos[i].media = std::stof(str);
			} else if(w == 8){
				alunos[i].status = str;
			}
			w++;
		}
	}
	//switch opcoes das listas

	int opcao_lista = 0;
	while (opcao_lista != 6){
		cout << "Escolha uma das opções a seguir: " << endl
		          << "Digite 1 para lista geral de alunos" << endl
		          << "Digite 2 para lista de alunos reprovados" << endl
		          << "Digite 3 para lista de alunos aprovados" << endl
		          << "Digite 4 para lista de alunos que precisão da substitutiva do primeiro bimestre" << endl
		          << "Digite 5 para lista de alunos que precisão da substitutiva do segundo bimestre" << endl
				  << "Digite 6 para voltar" << endl;
		          cin >> opcao_lista;
		          limpaTela();
    switch(opcao_lista){
      	case 1:
      		//gerar arquivo
      		limpaTela();
            arquivo_new_geral.open("geral1.csv");

			if (!arquivo_new_geral.is_open()) {
				cout << "Houve um erro ao abrir o arquivo!\n";
				break;
			}
      		//criar arquivo geral
			for(int i = 0; i < b; i++){
				arquivo_new_geral << alunos[i].nome << ";"
								<< alunos[i].matricula << ";"
								<< alunos[i].aep1 << ";"
								<< alunos[i].prova1 << ";"
								<< alunos[i].aep2 << ";"
								<< alunos[i].prova2 << ";"
								<< alunos[i].sub << ";"
								<< alunos[i].media << ";"
								<< alunos[i].status << "\n";
			}
            arquivo_new_geral.close();
            remove("geral.csv");
            rename("geral1.csv", "geral.csv");
			cout << "RELATÓRIO ATUALIZADO!" << endl;
      	break;
      	case 2:
      		//gerar arquivo

      		limpaTela();
			arquivo_reprovados.open("reprovados1.csv");

			if (!arquivo_reprovados.is_open()) {
				cout << "Houve um erro ao abrir o arquivo!\n";
				break;
			}

      		//printar na tela todos os alunos reprovados
      		for(int i = 0; i < b; i++){
      			if(alunos[i].status == "reprovado"){
      				arquivo_reprovados << alunos[i].nome << ";"
								<< alunos[i].matricula << ";"
								<< alunos[i].aep1 << ";"
								<< alunos[i].prova1 << ";"
								<< alunos[i].aep2 << ";"
								<< alunos[i].prova2 << ";"
								<< alunos[i].sub << ";"
								<< alunos[i].media << ";"
								<< alunos[i].status << "\n";
				  }
			}
			arquivo_reprovados.close();
			remove("reprovados.csv");
            rename("reprovados1.csv", "reprovados.csv");
			cout << "RELATÓRIO ATUALIZADO!" << endl;
      	break;
      	case 3:
      		//gerar arquivo

      		limpaTela();
			arquivo_aprovados.open("aprovados1.csv");

			if (!arquivo_aprovados.is_open()) {
				cout << "Houve um erro ao abrir o arquivo!\n";
				break;
			}
      		//printar na tela todos os alunos reprovados
      		for(int i = 0; i < b; i++){
      			if(alunos[i].status == "aprovado"){
      				arquivo_aprovados << alunos[i].nome << ";"
								<< alunos[i].matricula << ";"
								<< alunos[i].aep1 << ";"
								<< alunos[i].prova1 << ";"
								<< alunos[i].aep2 << ";"
								<< alunos[i].prova2 << ";"
								<< alunos[i].sub << ";"
								<< alunos[i].media << ";"
								<< alunos[i].status << "\n";
				  }
			}
			arquivo_aprovados.close();
			remove("aprovados.csv");
            rename("aprovados1.csv", "aprovados.csv");
			cout << "RELATÓRIO ATUALIZADO!" << endl;
      	break;
      	case 4:
      		//gerar arquivo

      		limpaTela();
			arquivo_sub1.open("sub_1_bm1.csv");

			if (!arquivo_sub1.is_open()) {
				cout << "Houve um erro ao abrir o arquivo!\n";
				break;
			}
      		//printar na tela todos os alunos que precisam da substitutiva 1bm
      		for(int i = 0; i < b; i++){
      			if((alunos[i].aep1 +  alunos[i].prova1) < 6){
      				arquivo_sub1 << alunos[i].nome << ";"
							<< alunos[i].matricula << ";"
							<< alunos[i].aep1 << ";"
							<< alunos[i].prova1 << ";"
							<< alunos[i].aep2 << ";"
							<< alunos[i].prova2 << ";"
							<< alunos[i].sub << ";"
							<< alunos[i].media << ";"
							<< alunos[i].status << "\n";
				  }
			  }
            arquivo_sub1.close();
            remove("sub_1_bm.csv");
            rename("sub_1_bm1.csv", "sub_1_bm.csv");
            cout << "RELATÓRIO ATUALIZADO!" << endl;

      	break;
      	case 5:
      		//gerar arquivo

      		limpaTela();
			arquivo_sub2.open("sub_2_bm1.csv");

			if (!arquivo_sub2.is_open()) {
				cout << "Houve um erro ao abrir o arquivo!\n";
				break;
			}
      		//printar na tela todos os alunos que precisam da substitutiva 1bm
      		for(int i = 0; i < b; i++){
      			if((alunos[i].aep2 +  alunos[i].prova2) < 6){
      				arquivo_sub2 << alunos[i].nome << ";"
								<< alunos[i].matricula << ";"
								<< alunos[i].aep1 << ";"
								<< alunos[i].prova1 << ";"
								<< alunos[i].aep2 << ";"
								<< alunos[i].prova2 << ";"
								<< alunos[i].sub << ";"
								<< alunos[i].media << ";"
								<< alunos[i].status << "\n";
				  }
			  }
            arquivo_sub2.close();
            remove("sub_2_bm.csv");
            rename("sub_2_bm1.csv", "sub_2_bm.csv");
            cout << "RELATÓRIO ATUALIZADO!" << endl;

      	break;
		}
	}
}



void cadastrar_notas (){
	limpaTela();
	std::string matricula_alt;
	cout << "<==========================================>" << endl;
	cout << "Digite uma matricula para alterar as notas: ";
	cin >> matricula_alt;
	//variaveis
	int rodar_arquivo = 0;
	int b = 0;
	std::string str;
	std::fstream arquivo;
	int w =0;
	arquivo.open("banco.csv", std::ios::in);
	// contar numero de linhas do arquivo
	if (!arquivo.is_open()) {
		cout << "Houve um erro ao abrir o arquivo!\n";
	}
	else{
		while (arquivo.good()) {
			rodar_arquivo = arquivo.get();
			if (rodar_arquivo == '\n') {
				b++;
			}
		}
	}
	std::string line;
	std::string linha[b];
	int tamanho = 0;
	arquivo.close();
	std::vector<struct Aluno> alunos(b);

	// jogar todas as linhas para linha[i]

	arquivo.open("banco.csv", std::ios::in);
	do{
		arquivo >> linha[tamanho];
		tamanho++;
	}while(getline(arquivo, line));
	arquivo.close();

	//dividir as linhas para a estrutura
	for(int i = 0; i < b; i++){
		w = 0;
		std::stringstream X(linha[i]);
		while (getline(X, str, ';')){
			if(w == 0){
				alunos[i].nome = str;
			} else if(w == 1){
				alunos[i].matricula = str;
			} else if(w == 2){
				alunos[i].aep1 = std::stof(str);
			} else if(w == 3){
				alunos[i].prova1 = std::stof(str);
			} else if(w == 4){
				alunos[i].aep2 = std::stof(str);
			} else if(w == 5){
				alunos[i].prova2 = std::stof(str);
			} else if(w == 6){
				alunos[i].sub = std::stof(str);
			} else if(w == 7){
				alunos[i].media = std::stof(str);
			} else if(w == 8){
				alunos[i].status = str;
			}
			w++;
		}
	}
	//laço para encontrar a matricula correta e alterar as notas
	for(int i = 0; i < b; i++){
		if(alunos[i].matricula == matricula_alt){


            int opcao_notas = 0;
            bool repetir = true;
            while (repetir){
            cout << "<==========================================>" << endl;
            lerALuno(alunos[i]);
            cout << "<==========================================>" << endl;
			cout << "Escolha uma das opções a seguir: " << endl
		          << "Digite 1 alterar a nota da AEP1" << endl
		          << "Digite 2 alterar a nota da prova1" << endl
		          << "Digite 3 alterar a nota da AEP2" << endl
		          << "Digite 4 alterar a nota da prova2" << endl
		          << "Digite 5 alterar a nota da substitutiva" << endl
				  << "Digite 6 para voltar" << endl;
            cout << "<==========================================>" << endl;
		          cin >> opcao_notas;
                if(opcao_notas > 0 && opcao_notas < 7) {
                    repetir = false;
                } else {
                    limpaTela();
                    cout << "<==========================================>" << endl;
                    cout << "             OPÇÃO INVALIDA                 " << endl;
                    cout << "<==========================================>" << endl << endl;
                }
            }
	    	switch(opcao_notas){
	    		case 1:
	    			limpaTela();
	    			cout << " Nome: " << alunos[i].nome
								<< " Matricula: " << alunos[i].matricula
								<< " AEP1: " << alunos[i].aep1
								<< " Prova1: " << alunos[i].prova1
								<< " AEP2: " << alunos[i].aep2
								<< " PROVA2: " << alunos[i].prova2
								<< " SUB1: " << alunos[i].sub
								<< " Media: " << alunos[i].media
								<< " Status: " << alunos[i].status << endl;
					cout << "Digite a nota da AEP1: ";
					cin >> alunos[i].aep1;
					//verificar media
					//se a sub for diferente de 0
					if(alunos[i].sub != 0){
						//se o primeiro bimestre for maior q o segundo
						if((alunos[i].aep1 + alunos[i].prova1) > (alunos[i].aep2 + alunos[i].prova2)){
							alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].sub)) / 2;
						} else{
							//se n for maior
							alunos[i].media = ((alunos[i].sub) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
						}
					}
					else{
						//se a sub for 0
						alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
					}
	    		break;
	    		case 2:
	    			limpaTela();
	    			cout << " Nome: " << alunos[i].nome
								<< " Matricula: " << alunos[i].matricula
								<< " AEP1: " << alunos[i].aep1
								<< " Prova1: " << alunos[i].prova1
								<< " AEP2: " << alunos[i].aep2
								<< " PROVA2: " << alunos[i].prova2
								<< " SUB1: " << alunos[i].sub
								<< " Media: " << alunos[i].media
								<< " Status: " << alunos[i].status << endl;
					cout << "Digite a nota da Prova1: ";
					//std::getline(cin,alunos[i].prova1)
					cin >> alunos[i].prova1;
					//verificar media
					//se a sub for diferente de 0
					if(alunos[i].sub != 0){
						//se o primeiro bimestre for maior q o segundo
						if((alunos[i].aep1 + alunos[i].prova1) > (alunos[i].aep2 + alunos[i].prova2)){
							alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].sub)) / 2;
						} else{
							//se n for maior
							alunos[i].media = ((alunos[i].sub) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
						}
					}
					else{
						//se a sub for 0
						alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
					}
	    		break;
	    		case 3:
	    			limpaTela();
	    			cout << " Nome: " << alunos[i].nome
								<< " Matricula: " << alunos[i].matricula
								<< " AEP1: " << alunos[i].aep1
								<< " Prova1: " << alunos[i].prova1
								<< " AEP2: " << alunos[i].aep2
								<< " PROVA2: " << alunos[i].prova2
								<< " SUB1: " << alunos[i].sub
								<< " Media: " << alunos[i].media
								<< " Status: " << alunos[i].status << endl;
					cout << "Digite a nota da AEP2: ";
					cin >> alunos[i].aep2;
					//verificar media
					//se a sub for diferente de 0
					if(alunos[i].sub != 0){
						//se o primeiro bimestre for maior q o segundo
						if((alunos[i].aep1 + alunos[i].prova1) > (alunos[i].aep2 + alunos[i].prova2)){
							alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].sub)) / 2;
						} else{
							//se n for maior
							alunos[i].media = ((alunos[i].sub) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
						}
					}
					else{
						//se a sub for 0
						alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
					}
	    		break;
	    		case 4:
	    			limpaTela();
	    			cout << " Nome: " << alunos[i].nome
								<< " Matricula: " << alunos[i].matricula
								<< " AEP1: " << alunos[i].aep1
								<< " Prova1: " << alunos[i].prova1
								<< " AEP2: " << alunos[i].aep2
								<< " PROVA2: " << alunos[i].prova2
								<< " SUB1: " << alunos[i].sub
								<< " Media: " << alunos[i].media
								<< " Status: " << alunos[i].status << endl;
					cout << "Digite a nota da Prova2: ";
					cin >> alunos[i].prova2;
					//verificar media
					//se a sub for diferente de 0
					if(alunos[i].sub != 0){
						//se o primeiro bimestre for maior q o segundo
						if((alunos[i].aep1 + alunos[i].prova1) > (alunos[i].aep2 + alunos[i].prova2)){
							alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].sub)) / 2;
						} else{
							//se n for maior
							alunos[i].media = ((alunos[i].sub) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
						}
					}
					else{
						//se a sub for 0
						alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
					}
	    		break;
	    		case 5:
	    			limpaTela();
	    			cout << " Nome: " << alunos[i].nome
								<< " Matricula: " << alunos[i].matricula
								<< " AEP1: " << alunos[i].aep1
								<< " Prova1: " << alunos[i].prova1
								<< " AEP2: " << alunos[i].aep2
								<< " PROVA2: " << alunos[i].prova2
								<< " SUB1: " << alunos[i].sub
								<< " Media: " << alunos[i].media
								<< " Status: " << alunos[i].status << endl;
					cout << "Digite a nota da Prova2: ";
					cin >> alunos[i].sub;
					//verificar media
					//se a sub for diferente de 0
					if(alunos[i].sub != 0){
						//se o primeiro bimestre for maior q o segundo
						if((alunos[i].aep1 + alunos[i].prova1) > (alunos[i].aep2 + alunos[i].prova2)){
							alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].sub)) / 2;
						} else{
							//se n for maior
							alunos[i].media = ((alunos[i].sub) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
						}
					}
					else{
						//se a sub for 0
						alunos[i].media = ((alunos[i].aep1 + alunos[i].prova1) + (alunos[i].aep2 + alunos[i].prova2)) / 2;
					}
	    		break;
	    		case 6:
	    		    limpaTela();
                break;
			}
		}
	}
	std::ofstream arquivo_new;
	arquivo_new.open("bancoNovo.csv");

	// contar numero de linhas do arquivo
	if (!arquivo_new.is_open()) {
		cout << "Houve um erro ao abrir o arquivo!\n";
	}
	else{
		for(int i = 0; i < b; i++){
			if(alunos[i].media >= 6){
                alunos[i].status = "aprovado";
                arquivo_new << alunos[i].nome << ";"
                        << alunos[i].matricula << ";"
                        << alunos[i].aep1 << ";"
                        << alunos[i].prova1 << ";"
                        << alunos[i].aep2 << ";"
                        << alunos[i].prova2 << ";"
                        << alunos[i].sub << ";"
                        << alunos[i].media << ";"
                        << alunos[i].status << "\n";
			 }else {
                alunos[i].status = "reprovado";
                arquivo_new << alunos[i].nome << ";"
                        << alunos[i].matricula << ";"
                        << alunos[i].aep1 << ";"
                        << alunos[i].prova1 << ";"
                        << alunos[i].aep2 << ";"
                        << alunos[i].prova2 << ";"
                        << alunos[i].sub << ";"
                        << alunos[i].media << ";"
                        << alunos[i].status << "\n";
			}
		}
	}
	arquivo_new.close();
    remove("banco.csv");
	rename("bancoNovo.csv", "banco.csv");
}
