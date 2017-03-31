#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <locale.h>

//Variaveis Globais
#define TRUE 1 
#define FALSE 0

//Estruturas ----------------------------------------------------------------------
typedef struct {
	
	int cpf;
	char email[15];
	char nome[15];
	short sexo; // 0-mulher 1-homem
	char dataNasc[10];
	
} pessoa;

typedef struct {
	
	char titulo[30];
	char editora[15];
	pessoa autor;
	char areaC[30];
	short quantidade;

} livro;

typedef struct {
	
	short tipo;
	char numero[12];
	short operadora; //Tim-0  Vivo-1  Oi-2 Claro-3 Nextel-4 Correios-5
	
} telefone;

typedef struct {
	
	char logradouro[30];
	int num;
	char complemento[15];
	char bairro[15];
	int cep;
	char estado[3]; //Usar UF 
	char cidade[15];
	
} endereco;

typedef struct {
	
	char dataEmp[10];
	char dataEst[10];
	char dataCon[10];
	int idAluno;
	int idFunc;

	
 } emprestimo;

typedef struct {
	
	pessoa estudante;
	int matricula;
	short sitMatr; // 0-trancada 1-ativa 2-jubilada
	char turma;
	endereco end;
	telefone tel;
	
} aluno;

typedef struct {
	
	short idAdm; // 0-funcionario 1-administrador
	char login[10];
	char senha[10];
	endereco end;
	telefone tel;
	pessoa func;
	
} funcionario;



//Protopatipação de Funções ---------------------------------------------------------------
void menu();


//Funções ----------------------------------------------------------------------------------



void menu () {
	
}

//função Primaria --------------------------------------------------------------------------
int main () {
	
	setlocale(LC_ALL, "ptb");
	menu();
	getch();
	
}
