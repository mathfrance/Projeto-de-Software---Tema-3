/*

	Trabalho para a disciplina projeto de software
	05/04/2017

	Aluno:
	Marcello Gonçalves de Oliveira Alves

	Projeto para gestão de uma biblioteca

	Todos os direitos reservados.

*/

//Inclusão de Bibliotecas
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

#define qFunc 50 //Quantidade máxima de funcionarios permitido na biblioteca
#define qAlunos 5000 //  || de alunos ||
#define qLivros 15000 //  || de livros ||
#define qEditoras 500 // || de editoras ||
#define qEmprestimos 5000 // || de emprestimos ||

//Estruturas ----------------------------------------------------------------------
typedef struct {

	int cpf;
	char email[15];
	char nome[15];
	short sexo; // 1-mulher 2-homem
	char dataNasc[10];
	char login[10];
	char senha[6];

} pessoa;

typedef struct {

	char titulo[20];
	short editora;
	char autor[20];
	char areaC[20];
	short quantidade;
	short disponiveis;

} livro;

typedef struct {

	short tipo;
	char numero[12];
	short operadora; //Tim-1  Vivo-2  Oi-3 Claro-4 Nextel-5 Correios-6

} telefone;

typedef struct {

	char logradouro[30];
	int num;
	char complemento[10];
	char bairro[10];
	int cep;
	char estado[3]; //Usar UF
	char cidade[10];

} endereco;

typedef struct {

	char dataEmp[10];
	char dataEst[10];
	char dataCon[10];
	short idAluno;
	short idFunc;

} emprestimo;

typedef struct {

	pessoa estudante;
	short matricula;
	short sitMatr; // 1 - Ativa 2 - Bloqueada 3 - Debito
	char turma[20];
	endereco end;
	telefone tel;

} aluno;

typedef struct {

	short idAdm; // 1-funcionario 2-administrador
	endereco end;
	telefone tel;
	pessoa func;

} funcionario;

typedef struct {

	short id;
	char nome[30];
	char cnpj[15];

} editora;

//Ddefinindo estrutura de lista para aluno, funcionario, editora, emprestimo e livos  -----
typedef struct {

	funcionario F[qFunc];
	int Prim, Ult;

} funcEST;

typedef struct {

	aluno A[qAlunos];
	int Prim, Ult;

} alunoEST;

typedef struct {

	editora ED[qEditoras];
	int Prim, Ult;

} editEST;

typedef struct {

	emprestimo E[qEmprestimos];
	int Prim, Ult;

} empEST;

typedef struct {

	livro L[qLivros];
	int Prim, Ult;

} livroEST;


//Protopatipação de Funções na ordem em que esão dispostas no decorrer do codigo

void cadastrarEditora(editEST *ED);
void consultarEditora(editEST ED);
void excluirLivro(livroEST *L);
void zerarAluno(alunoEST *A);
void zerarEdit(editEST *ED);
void zerarLivro(livroEST *L);
void zerarEmp(empEST *E);
void zerarFunc(funcEST *F);
void salvarArquivosEmp(empEST E);
void salvarArquivosLivro(livroEST L);
void carregarArquivosLivro(livroEST *L);
void salvarArquivosEdit(editEST ED);
void carregarArquivosEdit(editEST *ED);
void salvarArquivosAluno(alunoEST A);
void carregarArquivosAluno(alunoEST *A);
void salvarArquivosFunc(funcEST F);
void carregarArquivosFunc(funcEST *F);
void editarLivro(livroEST *L, editEST ED);
void cadastrarLivro(livroEST *L, editEST ED);
void consultarLivro(livroEST L, editEST ED);
void menu();

//Funções para instaciar as listas criadas  ------------------------------------------------
void criarListaFunc(funcEST *F) {
	F -> Prim = 0;
	F -> Ult = F -> Prim;
}
void criarListaAluno(alunoEST *A) {
	A -> Prim = 0;
	A -> Ult = A -> Prim;
}
void criarListaEditora(editEST *ED) {
	ED -> Prim = 0;
	ED -> Ult = ED -> Prim;
}
void criarListaLivro(livroEST *L) {
	L -> Prim = 0;
	L -> Ult = L -> Prim;
}
void criarListaEmp(empEST *E) {
	E -> Prim = 0;
	E -> Ult = E -> Prim;
}

int verificarListaVaziaFunc (funcEST F) {
	return(F.Prim == F.Ult); // Quando Prim for igual a Ult a lista está vazia
}
int verificarListaVaziaAlun (alunoEST A) {
	return(A.Prim == A.Ult); // Quando Prim for igual a Ult a lista está vazia
}
int verificarListaVaziaEdit (editEST ED) {
	return(ED.Prim == ED.Ult); // Quando Prim for igual a Ult a lista está vazia
}
int verificarListaVaziaLivro (livroEST L) {
	return(L.Prim == L.Ult); // Quando Prim for igual a Ult a lista está vazia
}
int verificarListaVaziaEmp (empEST E) {
	return(E.Prim == E.Ult); // Quando Prim for igual a Ult a lista está vazia
}

int verificarListaCheiaFunc (funcEST F) {
	return(F.Ult == qFunc); // Quando Ult apontar para a posição Max a lista está cheia
}
int verificarListaCheiaAluno (alunoEST A) {
	return(A.Ult == qAlunos); // Quando Ult apontar para a posição Max a lista está cheia
}
int verificarListaCheiaEdit (editEST ED) {
	return(ED.Ult == qEditoras); // Quando Ult apontar para a posição Max a lista está cheia
}
int verificarListaCheiaLivro (livroEST L) {
	return(L.Ult == qLivros); // Quando Ult apontar para a posição Max a lista está cheia
}
int verificarListaCheiaEmp (empEST E) {
	return(E.Ult == qEmprestimos); // Quando Ult apontar para a posição Max a lista está cheia
}



void cadastrarEditora(editEST *ED){
	
	int edit, i = 0, aux = -1;
	char saida;
	int Z, P = ED->Prim;
	editora auxE;
	
	do {
		aux = -1;
		saida = 'n';
		
		system("cls");
		printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
		printf("\n\tSub Menu -> Editoras -> Cadastro de editoras");
		printf("\n\tInsira o ID da editora: ");
		scanf (" %d", &edit);
		fflush(stdin);
		
		for (i = 0; i < qEditoras; i++) {
			
			if (ED->ED[i].id == edit){
				
				aux = edit;
				
			}
			
		}
		
		if (i != -1) {
			
			if (ED->Ult == qEditoras) {
				
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Editoras -> Cadastro de editoras");
				printf("\n\tA lista de Editoras já está completa, favor excluir para novo cadastro.");
				getch();
				
			} else {
				
				
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Editoras -> Cadastro de editoras");
				printf("\n\tInsira o nome da Editora: ");
				gets(auxE.nome);
				printf("\n\tInsira o CNPJ: ");
				gets(auxE.cnpj);
				auxE.id = edit;
				
				P = ED -> Prim;
	
				while ((P < ED -> Ult))
					P++;
	
				if(P == ED-> Ult) {

					ED -> ED[P] = auxE;
					ED -> Ult ++;

				} else {

					for(Z = ED -> Ult; Z > P; Z--)
						ED -> ED[Z] = ED -> ED[Z-1];
					ED -> ED[P] = auxE;
					ED -> Ult++;
				}
				
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Editoras -> Cadastro de editoras");
				printf("\n\tEditora cadastrada com sucesso.");
				getch();
				
				
			}
			
		} else {
			
			do {
				
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Editoras -> Cadastro de editoras");
		
				printf("\n\n\tDesculpe, já existe ID no nosso banco de dados.");
				printf("\n\n\tDeseja fazer um novo cadastro?");
				printf("\n\tS - Sim, ótima ideia!");
				printf("\n\tN - Não, obrigado.");
				printf("\n\tOpção: ");
				scanf(" %c", &saida);
				
				
			} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
			
		}
		
		
	} while (saida != 'n' && saida != 'N');
	
}

void consultarEditora(editEST ED){

	int editora, i = 0, aux;
	char saida;

	do {
		aux = -1;
		saida = 'n';
		
		system("cls");
		printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
		printf("\n\tSub Menu -> Editoras -> Consulta de editoras");
		printf("\n\tInsira o ID da editira para busca: ");
		scanf(" %[^\n]", &editora);
		fflush(stdin);
		 
		
			for (i = 0; i < qEditoras; i++){
				
				if (ED.ED[i].id == editora) {
					
					aux = i;
					
				}
			}
			
			if (aux == -1) {
				
				do{
		
					system("cls");
					printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
					printf("\n\tSub Menu -> Editora -> Consulta de Editoras");
		
					printf("\n\n\tDesculpe, não foi possivel encontrar esta editora em nossa base de dados.");
					printf("\n\n\tDeseja fazer uma nova busca?");
					printf("\n\tS - Sim, ótima ideia!");
					printf("\n\tN - Não, obrigado.");
					printf("\n\tOpção: ");
					
					scanf(" %c", &saida);
					fflush(stdin);
			
				} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
				
				
			} else {

				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Editoras -> Consulta de editoras");
				printf("\n\n\tID:      %d", ED.ED[aux].id);
				printf("\n\tCNPJ:    %s", ED.ED[aux].cnpj);
				printf("\n\tEditora: %s", ED.ED[aux].nome);
				
				getch();
				
			}

	} while (saida != 'n' && saida != 'N');
	
}

void excluirLivro(livroEST *L){
	
	int i; short aux = -1; char saida = 'n'; livro X;
	char livro[30];
	int Z, P = L -> Prim;
	
	
	do {
		aux = -1;
			
		system("cls");
		printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
		printf("\n\tSub Menu -> Livros -> Excluir Livros");
		printf("\n\tInsira o titulo para buscar: ");
		scanf(" %[^\n]", &livro);
		fflush(stdin);
	
		for (i = 0; i < qLivros; i++) {
		
			if (strcmp(L->L[i].titulo,livro) == 0) {
				aux = i;
			
			}
		}
		
		if (aux == -1) {
		
			do{
		
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Excluir Livros");
		
				printf("\n\n\tDesculpe, não foi possivel encontrar este livro em nossa base de dados.");
				printf("\n\n\tDeseja fazer uma nova busca?");
				printf("\n\tS - Sim, ótima ideia!");
				printf("\n\tN - Não, obrigado.");
				printf("\n\tOpção: ");
				
				scanf(" %c", &saida);
				fflush(stdin);
			
			} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
		
		} else {
			
			if (L->L[aux].quantidade != L->L[aux].disponiveis) {
				
				saida = 'n';
				do{
		
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Excluir Livros");
		
				printf("\n\n\tAlguns exemplares se encontram emprestados. Deseja realmente excluir este livro permanentemente?");
				printf("\n\n\tDeseja fazer uma nova busca?");
				printf("\n\tS - Sim, ótima ideia!");
				printf("\n\tN - Não, obrigado.");
				printf("\n\tOpção: ");
				scanf(" %c", &saida);
			
				} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
	
					if (saida == 's' || saida == 'S') {

  					  
						while ((P < L -> Ult) && (livro != L->L[P].titulo)){
							P = P +1;
						}
   							
   							strcpy(L->L[aux].areaC, "0");
							strcpy(L->L[aux].autor, "0");
							L->L[aux].disponiveis = 0;
							L->L[aux].editora = 0;
							L->L[aux].quantidade = 0;
							strcpy(L->L[aux].titulo, "0");   							
				    
						for (Z = P; Z < L -> Ult; Z++)
							L -> L[Z] = L -> L[Z+1];
						L -> Ult --;  
	
						printf("\n\n\tLivro excluido com sucesso.");
						
						saida = 'n';
				  	  	 
			  		} else {
					
						printf("\n\n\tLivro não foi removido!");
					
					}
					
			} else {
				
						while ((P < L -> Ult) && (livro != L->L[P].titulo)){
							P = P +1;
							
						}
   							
   		
   							strcpy(L->L[aux].areaC, "0");
							strcpy(L->L[aux].autor, "0");
							L->L[aux].disponiveis = 0;
							L->L[aux].editora = 0;
							L->L[aux].quantidade = 0;
							strcpy(L->L[aux].titulo, "0"); 
   	
				    
						for (Z = P; Z < L -> Ult; Z++)
							L -> L[Z] = L -> L[Z+1];
						L -> Ult --;  
	
						printf("\n\n\tLivro excluido com sucesso.");
				
			}
		
		}
		
		
	} while (saida != 'n' && saida != 'N');//Fim do cod
	
	getch();

}

//Funções para limpar todas as listas ------------
void zerarAluno(alunoEST *A){
		
	int i;
	
	for (i = 0; i < qAlunos; i++) {
		
		strcpy(A->A[i].end.bairro, "0");
		A->A[i].end.cep = 0;
		strcpy(A->A[i].end.cidade, "0");
		strcpy(A->A[i].end.complemento, "0");
		strcpy(A->A[i].end.estado, "0");
		strcpy(A->A[i].end.logradouro, "0");
		A->A[i].end.num = 0;
			
		A->A[i].estudante.cpf = 0;
		strcpy(A->A[i].estudante.dataNasc, "0");
		strcpy(A->A[i].estudante.email, "0");
		strcpy(A->A[i].estudante.login, "0");
		strcpy(A->A[i].estudante.nome, "0");
		strcpy(A->A[i].estudante.senha, "0");
		A->A[i].estudante.sexo = 0;
		
		A->A[i].matricula = 0;
		A->A[i].sitMatr = 0;
		
		strcpy(A->A[i].tel.numero, "0");
		A->A[i].tel.operadora = 0;
		A->A[i].tel.tipo = 0;
			
		strcpy(A->A[i].turma, "0");
		
	}
}
void zerarEdit(editEST *ED){
	
	int i;
	
	for (i = 0; i < qEditoras; i++) {
		
		strcpy(ED->ED[i].cnpj, "0");	
		ED->ED[i].id = 0;
		strcpy(ED->ED[i].nome, "0");

		
	}
}
void zerarLivro(livroEST *L){
	
	int i;
	
	for (i = 0; i < qLivros; i++) {
		
		strcpy(L->L[i].areaC, "0");
		strcpy(L->L[i].autor, "0");
		L->L[i].disponiveis = 0;
		L->L[i].editora = 0;
		L->L[i].quantidade = 0;
		strcpy(L->L[i].titulo, "0");

	}
}
void zerarEmp(empEST *E){
	
	int i;
	
	for (i = 0; i < qEmprestimos; i++) {
		
			strcpy(E->E[i].dataCon, "0");
			strcpy(E->E[i].dataEmp, "0");
			strcpy(E->E[i].dataEst, "0");
			E->E[i].idAluno = 0;
			E->E[i].idFunc = 0;
		
	}
	
}
void zerarFunc(funcEST *F) {
	
	int i;
	
	for (i = 0; i < qFunc; i++) {
		
		F->F[i].idAdm = 0;
		strcpy(F->F[i].end.bairro, "0");
		F->F[i].end.cep = 0;
		strcpy(F->F[i].end.cidade,"0"); 
		strcpy(F->F[i].end.complemento,"0"); 
	    strcpy(F->F[i].end.estado, "0");
		strcpy(F->F[i].end.logradouro, "0");
		F->F[i].end.num = 0;
		F->F[i].func.cpf = 0;
		strcpy(F->F[i].func.dataNasc, "0");
		strcpy(F->F[i].func.email, "0");
		strcpy(F->F[i].func.login,"0"); 
		strcpy(F->F[i].func.nome,"0"); 
		strcpy(F->F[i].func.senha,"0"); 
		F->F[i].func.sexo  = 0;
		strcpy(F->F[i].tel.numero,"0"); 
		F->F[i].tel.operadora = 0;
		F->F[i].tel.tipo = 0;		
		
	}
	
}
//-----------

void salvarArquivosEmp(empEST E){
	
	FILE *arquivo;
	
	arquivo = fopen("Emprestimos.txt", "w+");
	
	int i;
	
	for (i = 0; i < qEmprestimos; i++) {
		
		if (E.E[i].idAluno == 0) {
			
			fprintf(arquivo, "0;0;0;0;0\n");
			
		} else {
			
			fprintf(arquivo, "%s;%s;%s;%d;%d\n",
			
				E.E[i].dataCon,
				E.E[i].dataEmp,
				E.E[i].dataEst, 
				E.E[i].idAluno,
				E.E[i].idFunc
			
			);
			
		}
		
	}
	
	fclose(arquivo);
}
void carregarArquivosEmp(empEST *E){
	
	FILE *arquivo;
	
	arquivo = fopen("Emprestimos.txt", "r+");
	
	//Variaveeis
	emprestimo aux;
	int i;
	char linha[300];
	int Z, P = E->Prim;
	 
	 for (i = 0; i < qEmprestimos; i++){
	 	
	 	fscanf(arquivo, "%s", linha);
	 	
	 	strcpy(aux.dataCon, strtok(linha, ";"));
	 	strcpy(aux.dataEmp, strtok(NULL, ";"));
	 	strcpy(aux.dataEst, strtok(NULL, ";"));
	 	aux.idAluno = atoi (strtok(NULL, ";"));
	 	aux.idFunc = atoi (strtok(NULL, "\n"));
	 	
	 	if (aux.idAluno != 0) {
				
				P = E -> Prim;
	
				while ((P < E -> Ult))
					P++;
	
				if(P == E-> Ult) {

					E -> E[P] = aux;
					E -> Ult ++;

				} else {

					for(Z = E -> Ult; Z > P; Z--)
						E -> E[Z] = E -> E[Z-1];
					E -> E[P] = aux;
					E -> Ult++;
				}
					
			} //Fim do if
		
	}
	
	fclose(arquivo);
}

void salvarArquivosLivro(livroEST L){
	
	FILE *arquivo;
	
	arquivo = fopen("Livros.txt", "w+");
	
	int i;
	
	for (i = 0; i < qLivros; i++) {
		
		if (L.L[i].quantidade == 0) {
			
			fprintf(arquivo, "0;0;0;0;0;0\n");
			
		} else {
		
			fprintf(arquivo, "%s;%s;%d;%d;%d;%s\n", 
			
				L.L[i].areaC,
				L.L[i].autor,
				L.L[i].disponiveis,
				L.L[i].editora,
				L.L[i].quantidade,
				L.L[i].titulo
			);
			
		}
		
	}
	
	fclose(arquivo);
}
void carregarArquivosLivro(livroEST *L){

	FILE *arquivo;
	
	arquivo = fopen ("Livros.txt", "r+");
	
	//Variaveis
	livro aux;
	int i;
	char linha[400];
	int Z, P = L->Prim;
	
	
	
	for (i = 0; i < qLivros; i++) {
		
		fscanf(arquivo, "%s", linha);
		
		strcpy(aux.areaC, strtok(linha, ";"));
		strcpy(aux.autor, strtok(NULL, ";"));
		aux.disponiveis = atoi (strtok(NULL, ";"));
		aux.editora = atoi (strtok(NULL, ";"));
		aux.quantidade = atoi (strtok(NULL, ";"));
		strcpy(aux.titulo, strtok(NULL, "\n"));
		
		if(aux.quantidade != 0) {
			
				P = L -> Prim;
	
				while ((P < L -> Ult))
					P++;
	
				if(P == L-> Ult) {

					L -> L[P] = aux;
					L -> Ult ++;

				} else {

					for(Z = L-> Ult; Z > P; Z--)
						L -> L[Z] = L -> L[Z-1];
					L -> L[P] = aux;
					L -> Ult++;
				}	
		} //fim do if

	}

	fclose(arquivo);
}

void salvarArquivosEdit(editEST ED){
	
	FILE *arquivo;
	
	arquivo = fopen ("Editoras.txt", "w+");
	
	//Variaveis
	int i;
	
	for (i = 0; i < qEditoras; i++){
		
		if(ED.ED[i].id == 0){
			
			fprintf(arquivo, "0;0;0\n");
			
		} else {
			
			fprintf(arquivo, "%s;%d;%s\n",
			
				ED.ED[i].cnpj,
				ED.ED[i].id,
				ED.ED[i].nome
			);
			
		}
		
	}
	
	fclose(arquivo);
}
void carregarArquivosEdit(editEST *ED){
	
	FILE *arquivo;
	
	arquivo = fopen("Editoras.txt", "r+");
	
	//Variaveeis
	editora aux;
	int i;
	char linha[100];
	int Z, P = ED->Prim;
	
	for (i = 0; i < qEditoras; i++) {
		
		fscanf(arquivo, "%s", linha);
		
		
		strcpy(aux.cnpj, strtok(linha, ";"));
		aux.id = atoi (strtok(NULL, ";"));
		strcpy(aux.nome, strtok(NULL, "\n"));
		
		if (aux.id != 0) {
				
				P = ED -> Prim;
	
				while ((P < ED -> Ult))
					P++;
	
				if(P == ED-> Ult) {

					ED -> ED[P] = aux;
					ED -> Ult ++;

				} else {

					for(Z = ED -> Ult; Z > P; Z--)
						ED -> ED[Z] = ED -> ED[Z-1];
					ED -> ED[P] = aux;
					ED -> Ult++;
				}
					
			} //Fim do if
		
	}
	
	fclose(arquivo);
}

void salvarArquivosAluno(alunoEST A){
	
	FILE *arquivo;
	
	arquivo = fopen("Alunos.txt", "w+");
	
	int i;
	
	for (i = 0; i < qAlunos; i++) {
		
		if (A.A[i].matricula == 0) {
			
			fprintf (arquivo, "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0\n");
		
		} else {
			
			fprintf(arquivo, "%s;%d;%s;%s;%s;%s;%d;%d;%s;%s;%s;%s;%s;%d;%d;%d;%s;%d;%d;%s\n", 
			
			A.A[i].end.bairro,
			A.A[i].end.cep,
			A.A[i].end.cidade,
			A.A[i].end.complemento,
			A.A[i].end.estado,
			A.A[i].end.logradouro,
			A.A[i].end.num,			
			A.A[i].estudante.cpf,
			A.A[i].estudante.dataNasc,
			A.A[i].estudante.email,
			A.A[i].estudante.login,
			A.A[i].estudante.nome,
			A.A[i].estudante.senha,
			A.A[i].estudante.sexo,			
			A.A[i].matricula,
			A.A[i].sitMatr,			
			A.A[i].tel.numero,
			A.A[i].tel.operadora,
			A.A[i].tel.tipo,			
			A.A[i].turma
			
			);
			
		}//fim do else
		
	}
	
	fclose(arquivo);
}
void carregarArquivosAluno(alunoEST *A){
	
	FILE *arquivo;
	
	arquivo = fopen("Alunos.txt", "r+");
	
	//criação de var -------
	aluno aux;
	int i;
	char linha[400];
	int Z, P = A->Prim;
	
	for (i = 0; i < qAlunos; i++){
		
		fscanf(arquivo, "%s", linha);
		
			
			strcpy(aux.end.bairro, strtok(linha, ";"));
			aux.end.cep = atoi (strtok(NULL, ";"));
			strcpy(aux.end.cidade, strtok(NULL, ";"));
			strcpy(aux.end.complemento, strtok(NULL, ";"));
			strcpy(aux.end.estado, strtok(NULL, ";"));
			strcpy(aux.end.logradouro, strtok(NULL, ";"));
			aux.end.num = atoi (strtok(NULL, ";"));
			 
			aux.estudante.cpf = atoi (strtok(NULL, ";"));
			strcpy(aux.estudante.dataNasc, strtok(NULL, ";"));
			strcpy(aux.estudante.email, strtok(NULL, ";"));
			strcpy(aux.estudante.login, strtok(NULL, ";"));
			strcpy(aux.estudante.nome, strtok(NULL, ";"));
			strcpy(aux.estudante.senha, strtok(NULL, ";"));
			aux.estudante.sexo = atoi (strtok(NULL, ";"));
			
			aux.matricula = atoi (strtok(NULL, ";"));
			aux.sitMatr = atoi (strtok(NULL, ";"));
			strcpy(aux.tel.numero, strtok(NULL, ";"));
			aux.tel.operadora = atoi (strtok(NULL, ";"));
			aux.tel.tipo = atoi (strtok(NULL, ";"));
			
			strcpy(aux.turma, strtok(NULL, "\n"));
			
			if (aux.matricula != 0) {
				
				P = A -> Prim;
	
				while ((P < A -> Ult))
					P++;
	
				if(P == A-> Ult) {

					A -> A[P] = aux;
					A -> Ult ++;

				} else {

					for(Z = A-> Ult; Z > P; Z--)
						A -> A[Z] = A -> A[Z-1];
					A -> A[P] = aux;
					A -> Ult++;
				}
					
			} //Fim do if
	}
	
	fclose(arquivo);
}

void salvarArquivosFunc (funcEST F) {
	
	FILE *arquivo;
	
	arquivo = fopen("Funcionarios.txt", "w+");
	
	int i;
	
	
	for (i = 0; i < qFunc; i++) {
		
		
		if (F.F[i].idAdm == 0){
			
			fprintf(arquivo, "0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0\n");
			
		} else {
			
			fprintf(arquivo, "%d;%s;%d;%s;%s;%s;%s;%d;%d;%s;%s;%s;%s;%s;%d;%s;%d;%d\n", 
		
				F.F[i].idAdm, 
				F.F[i].end.bairro, 
				F.F[i].end.cep, 
				F.F[i].end.cidade, 
				F.F[i].end.complemento, 
				F.F[i].end.estado, 
				F.F[i].end.logradouro, 
				F.F[i].end.num,
				F.F[i].func.cpf, 
				F.F[i].func.dataNasc, 
				F.F[i].func.email, 
				F.F[i].func.login, 
				F.F[i].func.nome, 
				F.F[i].func.senha, 
				F.F[i].func.sexo,
				F.F[i].tel.numero, 
				F.F[i].tel.operadora, 
				F.F[i].tel.tipo
			);
			
		}
		
		
		
		
	}
}
void carregarArquivosFunc(funcEST *F){

	FILE *arquivo;
	
	arquivo = fopen("Funcionarios.txt", "r+");	
	
	char linha[300];
	int i;
	funcionario aux;
	int A, P = F -> Prim;
	
	//------------------
		
	char* save = NULL;	
	

	for(i = 0; i < qFunc; i++){
		
		fscanf(arquivo, "%s", linha);
		
			aux.idAdm = atoi (strtok(linha, ";"));
			
					
			strcpy(aux.end.bairro, strtok(NULL,";"));
			aux.end.cep = atoi (strtok(NULL, ";"));
			strcpy(aux.end.cidade, strtok(NULL,";"));
			strcpy(aux.end.complemento, strtok(NULL,";"));
			strcpy(aux.end.estado, strtok(NULL,";"));
			strcpy(aux.end.logradouro, strtok(NULL,";"));
			aux.end.num = atoi (strtok(NULL, ";"));
	
			aux.func.cpf = atoi (strtok(NULL, ";"));
			strcpy(aux.func.dataNasc, strtok(NULL, ";"));
			strcpy(aux.func.email, strtok(NULL, ";"));
			strcpy(aux.func.login, strtok(NULL, ";"));
			strcpy(aux.func.nome, strtok(NULL, ";"));
			strcpy(aux.func.senha, strtok(NULL, ";"));
			aux.func.sexo = atoi (strtok(NULL, ";"));
			
			strcpy(aux.tel.numero, strtok(NULL, ";"));
			aux.tel.operadora = atoi (strtok(NULL, ";"));
			aux.tel.tipo = atoi (strtok(NULL, "\n"));
	
	
			//stardup só para cosulta posterior 
			/*
			aux.func.cpf = atoi (strtok(NULL, ";"));
			save = strtok(NULL, ";");
			strcpy(aux.func.dataNasc, strdup(save));	
			save = strtok(NULL,";");
			strcpy(aux.func.email, strdup(save));
			save = strtok(NULL,";");
			strcpy(aux.func.login, strdup(save));
			save = strtok(NULL,";");
			strcpy(aux.func.nome, strdup(save));
			save = strtok(NULL,";");
			strcpy(aux.func.senha, strdup(save));
			
			aux.func.sexo = atoi (strtok(NULL, ";"));
			save = strtok(NULL,";");
			strcpy(aux.tel.numero, strdup(save));
			aux.tel.operadora = atoi (strtok(NULL, ";"));
			aux.tel.tipo = atoi (strtok(NULL, "\n"));
			*/
			
			
			if(aux.idAdm != 0){
				
				P = F -> Prim;
	
				while ((P < F -> Ult))
					P++;
	
				if(P == F-> Ult) {

					F -> F[P] = aux;
					F -> Ult ++;

				} else {

					for(A = F-> Ult; A > P; A--)
						F -> F[A] = F -> F[A-1];
					F -> F[P] = aux;
					F -> Ult++;
				}
					
			} // fim do if
			
				
	}
	
		//Codigo para adionar o item na lista, como já está estipulado o tamanho maximo
		//nao precisa checar se a fila está cheia ou não.
	
	fclose(arquivo);
	
}


void editarLivro(livroEST *L, editEST ED){
	
	int i; short aux = - 1; char saida = 'n'; livro X;
	char livro[30];
	short codED;

	
	do {
			
		system("cls");
		printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
		printf("\n\tSub Menu -> Livros -> Editar Livros");
		printf("\n\tInsira o titulo para buscar: ");
		scanf(" %[^\n]", &livro);
		fflush(stdin);
	
		for (i = 0; i < qLivros; i++) {
		
			if (strcmp(L->L[i].titulo,livro) == 0) {
				aux = i;
			
			}
		}
		
		if (aux == -1) {
		
			do{
		
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Editar Livros");
		
				printf("\n\n\tDesculpe, não foi possivel encontrar este livro em nossa base de dados.");
				printf("\n\n\tDeseja fazer uma nova busca?");
				printf("\n\tS - Sim, ótima ideia!");
				printf("\n\tN - Não, obrigado.");
				printf("\n\tOpção: ");
				scanf(" %c", &saida);
			
			} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
		
		} else {
			
			if (L->L[aux].quantidade != L->L[aux].disponiveis) {
				
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Editar Livros");
				
				printf("\n\n\tInfelizmente um dos livros se encontra emprestado.\n\tNão é possível fazer alterações enquanto todos os exemplares forem devolvidos!");
				
				
			} else {
			
				
				do {
					saida = 'n';
					aux = -1;
			
			
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Editar Livros");		
				printf("\n\tLivro '%s'encotrado: ", livro);
				
				
				printf("\n\n\tNova Editora: ");
				scanf(" %d", &codED);
				fflush(stdin);
		
				for (i = 0;i < qEditoras; i++) {
			
					if (ED.ED[i].id == codED) {
				
						aux = 2;
				
					}
				}
			
				if (aux != 2){
			
			
				do {
				
					system("cls");
					printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
					printf("\n\tSub Menu -> Livros -> Editar Livros");
			
					printf("\n\n\tDesculpe, não foi possivel encontrar esta editora");
					printf("\n\n\tDeseja fazer uma nova busca?");
					printf("\n\tS - Sim, ótima ideia!");
					printf("\n\tN - Não, obrigado.");
					printf("\n\tOpção: ");
					scanf(" %c", &saida);
					fflush(stdin);
				
				
				} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
				
				
				} else if (aux == 2){
				
			
					printf("\n\n\tNovo Titulo: ");
					gets(X.titulo);
					fflush(stdin);
			
					printf("\n\tNova area de conhecimento: ");
					gets(X.areaC);
					fflush(stdin);
			
					printf("\n\tNovo Autor: ");
					gets(X.autor);
					fflush(stdin);
			
					printf("\n\tNova Quantidade de exemplares: ");
					scanf(" %d", &X.quantidade);
					fflush(stdin);
					X.disponiveis = X.quantidade;
					X.editora = codED;
					
					L->L[aux] = X;

					printf("\n\n\tDados salvos com sucesso.");	
			
				}
				
				} while (saida != 'n' && saida != 'N');
			}
		
		}
		
		
	} while (saida != 'n' && saida != 'N');//Fim do cod
	
	getch();
	
}

void cadastrarLivro(livroEST *L, editEST ED){
	
	int A, P = L -> Prim;
	livro X; short codED, i, aux = 1;
	char saida = 'n';
	
	do {
		
		aux = 1;
		printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
		printf("\n\tSub Menu -> Livros -> Cadastro de Livros");
		
		printf("\n\n\tInsira o codigo da editora: ");
		scanf(" %d", &codED);
		fflush(stdin);
		
		for (i = 0;i < qEditoras; i++) {
			
			if (ED.ED[i].id == codED) {
				
				printf("\n\tEditora '%s' foi encontrada!", ED.ED[i].nome);
				aux = 2;
				
			}
			
			
		}
		
		if (aux == 1){
			
			do {
				
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Cadastro de Livros");
		
				printf("\n\n\tDesculpe, não foi possivel encontrar esta editora");
				printf("\n\n\tDeseja fazer uma nova busca?");
				printf("\n\tS - Sim, ótima ideia!");
				printf("\n\tN - Não, obrigado.");
				printf("\n\tOpção: ");
				scanf(" %c", &saida);
				
				
			} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
			
			
		} else if (aux == 2) {
			
			
			if (verificarListaCheiaLivro(*L)) {

				printf("\n\n\tA lista está cheia logo não foi possível adicionar um novo item.");
				getch();

			} else {
				
				printf("\n\n\tTitulo: ");
				gets(X.titulo);
				fflush(stdin);
			
				printf("\n\tArea de conhecimento: ");
				gets(X.areaC);
				fflush(stdin);
			
				printf("\n\tAutor: ");
				gets(X.autor);
				fflush(stdin);
			
				printf("\n\tQuantidade de exemplares: ");
				scanf(" %d", &X.quantidade);
				fflush(stdin);
				X.disponiveis = X.quantidade;
				X.editora = codED;
				
	
				while ((P < L -> Ult))
					P++;
	
				if(P == L-> Ult) {
	
					L -> L[P] = X;
					L -> Ult ++;

				} else {

					for(A = L-> Ult; A > P; A--)
						L -> L[A] = L -> L[A-1];
					L -> L[P] = X;
					L -> Ult++;
				}
				
				printf("\n\n\tO livro foi adicionado com sucesso!");
				getch();
				
			}
			
		} // Fim do else if == 2
		
		
	} while (saida != 'n' && saida != 'N');

}

void consultarLivro(livroEST L, editEST ED) {
	
	char livro[20]; int i; short aux = -1; char saida = 'n';
	
	do {
	
	
	system("cls");
	printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
	printf("\n\tSub Menu -> Livros -> Consultar Livros");
	printf("\n\tInsira o nome para buscar: ");
	scanf(" %[^\n]", &livro);
	fflush(stdin);
	
	for (i = 0; i < qLivros; i++) {
		
		if (strcmp(L.L[i].titulo,livro) == 0) {
			
			aux = i;
			
		}
		
	}
			
		//Comparação de ID para exibir na tela.
		if (aux == -1) {
		
			do{
		
				system("cls");
				printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
				printf("\n\tSub Menu -> Livros -> Consultar Livros");
		
				printf("\n\n\tDesculpe, não foi possivel encontrar este livro em nossa base de dados.");
				printf("\n\n\tDeseja fazer uma nova busca?");
				printf("\n\tS - Sim, ótima ideia!");
				printf("\n\tN - Não, obrigado.");
				printf("\n\tOpção: ");
				scanf(" %c", &saida);
			
			} while (saida != 'n' && saida != 'N' && saida != 's' && saida != 'S');
		
		} else {
					
			printf("\n\n\tLivro '%s'encotrado: ", livro);
			
			//Comparação de ID para exibir na tela.
			for (i = 0; i < qEditoras; i++) {
		
				if (ED.ED[i].id == L.L[aux].editora) {
					printf("\n\tEditora:               %s", ED.ED[i].nome);
			
				}
			}
		
			printf("\n\tNome do autor:         %s", L.L[aux].autor);
			printf("\n\tArea de conhecimento:  %s", L.L[aux].areaC);
			printf("\n\tQuantidade de livros:  %d", L.L[aux].quantidade);
			printf("\n\tQuantidade disponivel: %d\n", L.L[aux].disponiveis);
			getch();
				
		
		}

	} while (saida != 'n' && saida != 'N');	 
	
}


void menu () {

	do { //Responsável por terminar o programa

		funcEST F;
		alunoEST A;
		editEST ED;
		livroEST L;
		empEST E;

		criarListaFunc(&F);
		criarListaAluno(&A);
		criarListaEditora(&ED);
		criarListaLivro(&L);
		criarListaEmp(&E);

		zerarFunc(&F);
		zerarAluno(&A);
		zerarEdit(&ED);
		zerarLivro(&L);
		zerarEmp(&E);
		
		///*
		carregarArquivosFunc(&F);
		carregarArquivosAluno(&A);
		carregarArquivosEdit(&ED);
		carregarArquivosLivro(&L);
		carregarArquivosEmp(&E);
		//*/
		
		/*
		F.F[0].idAdm = 1;
		strcpy(F.F[0].func.login, "123");
		strcpy(F.F[0].func.senha, "123");
		//*/
		
		printf ("\n\n\tRecomendamos que use a tela em tamanho máximo para mais conforto.");
		//sleep(3);

		short loginS = 0;
		int i; //Usado para os laços de repetição sem comprometimento e necessidade posterior de
		//uma posição qualquer da contagem
		do {
			
			system ("cls");
			printf ("\n\t\t\tLOGIN\n\n\n");
			printf("\n\t1 - Funcionário");
			printf("\n\t2 - Aluno");
			printf("\n\t3 - Sair");
			printf("\n\tOpcão: ");
			scanf("%d", &loginS);
			fflush(stdin);

			short saidaLogin = 0;
			char loginErro = 0;
			short menuP = 0;
			short menuS = 0;
			char login[10], senha[10];
			short aux = 0;

			if (loginS == 1) {

				do { //Checar Login de funcionario e gerente
					saidaLogin = 0;

					system("cls");
					printf ("\n\t\t\tLOGIN\n\n\n");
					printf ("\n\tUser: ");
					scanf ("%s", &login);
					fflush(stdin);
					printf("\n\tSenha: ");
					scanf ("%s", &senha);
					fflush(stdin);

					for (i = 0; i < 50; i++) {

						if (strcmp(F.F[i].func.login,login) == 0 && strcmp(F.F[i].func.senha,senha) == 0 &&
						        F.F[i].idAdm == 1) {

							printf ("\n\n\tLogin realizado com sucesso!");
							saidaLogin = 1;

						}

						if (strcmp(F.F[i].func.login,login) == 0 && strcmp(F.F[i].func.senha,senha) == 0 &&
						        F.F[i].idAdm == 2) {

							printf ("\n\n\tLogin realizado com sucesso!");
							saidaLogin = 3;

						}

					}

					if (saidaLogin == 0) {

						aux = 0;
						do {

							system ("cls");
							printf ("\n\t\t\tLOGIN\n\n\n");
							printf ("\n\n\tSenha e/ou usuário está(ão) errado(s).");
							printf("\n\tDeseja tentar novamente?");
							printf("\n\tS - Sim, parece ótimo.");
							printf("\n\tN - Não, sair.");
							printf("\n\tOpção: ");
							scanf ("%c", &loginErro);

							if (loginErro == 's' || loginErro =='S') {

								aux = 1;

							} else if (loginErro == 'n' || loginErro =='N') {

								aux = 2;
								saidaLogin = 2;

							}


						} while(aux != 1 && aux != 2);

					}


				} while (saidaLogin != 1 && saidaLogin != 2 && saidaLogin != 3);


				if (saidaLogin == 1) { //Menu para Funcionario comum ----------------------------------------------


					do {

						system("cls");
						printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");

						printf("\n\tSub Menus: ");
						printf("\n\t1 - Livros");
						printf("\n\t2 - Editoras");
						printf("\n\t3 - Alunos");
						printf("\n\t4 - Emprestimos e Devoluções");
						printf("\n\t5 - Relatórios");
						printf("\n\t6 - Sair");
						printf("\n\tOpcão: ");
						scanf("%d", &menuP);
						fflush(stdin);
						menuS = 0;

						if (menuP == 1) {
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Livros");

								printf("\n\t1 - Consultar Livro");
								printf("\n\t2 - Cadastrar Livro");
								printf("\n\t3 - Editar Livro");
								printf("\n\t4 - Excluir Livro");
								printf("\n\t5 - Livros com maior procura");
								printf("\n\t6 - Sair");
								printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {
									
									consultarLivro(L, ED);

								} else if (menuS == 2) {
									
									cadastrarLivro(&L, ED);

								} else if (menuS == 3) {
									
									editarLivro(&L, ED);

								} else if (menuS == 4) {
									
									excluirLivro(&L);

								} else if (menuS == 5) {

								}


							} while (menuS != 6);

						} else if (menuP == 2) { 
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Editoras");

								printf("\n\t1 - Consultar Editora");
								printf("\n\t2 - Cadastrar Editora");
								printf("\n\t3 - Editar Editora");
								printf("\n\t4 - Excluir Editora");
								printf("\n\t5 - Sair");
								printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {
									
									consultarEditora(ED);

								} else if (menuS == 2) {
									
									cadastrarEditora(&ED);

								} else if (menuS == 3) {
									
									

								} else if (menuS == 4) {

								}

							} while (menuS != 5);

						} else if (menuP == 3) {
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Alunos");


								printf("\n\t1 - Consultar Aluno");
								printf("\n\t2 - Editar Aluno");
								printf("\n\t3 - Cadastrar Aluno");
								printf("\n\t4 - Bloquear Aluno");
								printf("\n\t5 - Desbloquear Aluno");
								printf("\n\t6 - Sair");
								printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {

								} else if (menuS == 2) {

								} else if (menuS == 3) {

								} else if (menuS == 4) {

								} else if (menuS == 5) {

								}

							} while (menuS != 6);

						} else if (menuP == 4) {
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Emprestimos");

								printf("\n\t1 - Consultar Emprestimo");
								printf("\n\t2 - Realizar Emprestimo");
								printf("\n\t3 - Prorrogar Emprestimo");
								printf("\n\t4 - Efetuar Devolução");
								printf("\n\t5 - Baixa de alunos com debito");
								printf("\n\t6 - Sair");
								printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {

								} else if (menuS == 2) {

								} else if (menuS == 3) {

								} else if (menuS == 4) {

								} else if (menuS == 5) {

								}

							} while (menuS != 6);

						} else if (menuP == 5) {
							menuS = 0;
							do {

								system("cls");
								printf ("\n\t\t\tMENU FUNCIONARIO\n\n\n");
								printf("\n\tSub Menu -> Relatórios");

								printf("\n\t1 - Alunos ativos");
								printf("\n\t2 - Alunos bloquados");
								printf("\n\t5 - Alunos com debito.");
								printf("\n\t3 - Livros Diponíveis");
								printf("\n\t4 - Livros Indisponíveis");
								printf("\n\t5 - Editoras cadastradas");
							    printf("\n\t6 - Sair");
      					        printf("\n\tOpcão: ");
								scanf("%d", &menuS);
						        fflush(stdin);

								   if(menuS == 1) {

							       } else if (menuS == 2){

							       } else if (menuS == 3) {

							       } else if (menuS == 4) {

							       } else if (menuS == 5) {

							       }

							} while (menuS != 6);

						}

					} while (menuP != 6);

			    } else if (saidaLogin == 3) { //Menu Para Gerente -------------------------------------------------

					do {

						system("cls");
						printf ("\n\t\t\tMENU GERENTE\n\n\n");

      					printf("\n\tSub Menus: ");
						printf("\n\t1 - Livros");
						printf("\n\t2 - Editoras");
						printf("\n\t3 - Alunos");
						printf("\n\t4 - Emprestimos e Devoluções");
						printf("\n\t5 - Relatórios");
						printf("\n\t6 - Funcionarios");
						printf("\n\t7 - Sair");
     					printf("\n\tOpcão: ");
						scanf("%d", &menuP);
						fflush(stdin);
						menuS = 0;

						if (menuP == 1) {
							
							menuS = 0;
							do {

							    system("cls");
							    printf ("\n\t\t\tMENU GERENTE\n\n\n");
							    printf("\n\tSub Menu -> Livros");

							    printf("\n\t1 - Consultar Livro");
							    printf("\n\t2 - Cadastrar Livro");
							    printf("\n\t3 - Editar Livro");
							    printf("\n\t4 - Excluir Livro");
							    printf("\n\t5 - Livros com maior procura");
							    printf("\n\t6 - Livros com menor procura");
							    printf("\n\t7 - Sair");
       							printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {

							    } else if (menuS == 2){

							    } else if (menuS == 3) {

							    } else if (menuS == 4) {

							    } else if (menuS == 5) {

							    } else if (menuS == 6) {

							    }

						 } while (menuS != 7);


					} else if (menuP == 2) {
						
							menuS = 0;
							do {

							    system("cls");
							    printf ("\n\t\t\tMENU GERENTE\n\n\n");
							    printf("\n\tSub Menu -> Editoras");

							    printf("\n\t1 - Consultar Editora");
							    printf("\n\t2 - Cadastrar Editora");
							    printf("\n\t3 - Editar Editora");
							    printf("\n\t4 - Excluir Editora");
							    printf("\n\t5 - Sair");
       							printf("\n\tOpcão: ");
								scanf("%d", &menuS);
								fflush(stdin);

								if(menuS == 1) {

							    } else if (menuS == 2){

							    } else if (menuS == 3) {

							    } else if (menuS == 4) {

							    }

							    } while (menuS != 5);

					} else if (menuP == 3) {
						menuS = 0;	
						do {

						    system("cls");
						    printf ("\n\t\t\tMENU GERENTE\n\n\n");
						    printf("\n\tSub Menu -> Alunos");

						    printf("\n\t1 - Consultar Aluno");
						    printf("\n\t2 - Editar Aluno");
						    printf("\n\t3 - Bloquear Aluno");
						    printf("\n\t4 - Desbloquear Aluno");
						    printf("\n\t5 - Sair");
       						printf("\n\tOpcão: ");
							scanf("%d", &menuS);
							fflush(stdin);

							if(menuS == 1) {

							} else if (menuS == 2){

							} else if (menuS == 3) {

							} else if (menuS == 4) {

							}

			      		} while (menuS != 5);

					} else if (menuP == 4) {
						menuS = 0;
						do {

							system("cls");
							printf ("\n\t\t\tMENU GERENTE\n\n\n");
							printf("\n\tSub Menu -> Emprestimos");
	
		    			    printf("\n\t1 - Consultar Emprestimo");
							printf("\n\t2 - Realizar Emprestimo");
							printf("\n\t3 - Prorrogar Emprestimo");
							printf("\n\t4 - Efetuar Devolução");
							printf("\n\t5 - Baixa de alunos com debito");
							printf("\n\t6 - Sair");
     						printf("\n\tOpcão: ");
							scanf("%d", &menuS);
							fflush(stdin);

							if(menuS == 1) {

							} else if (menuS == 2){

							} else if (menuS == 3) {

							} else if (menuS == 4) {

							} else if (menuS == 5) {

							}

						} while (menuS != 6);

					} else if (menuP == 5) {
					    menuS = 0;
					    do {

					        system("cls");
					        printf ("\n\t\t\tMENU GERENTE\n\n\n");
					        printf("\n\tSub Menu -> Relatórios");

					        printf("\n\t1 - Alunos ativos");
					        printf("\n\t2 - Alunos bloquados");
					        printf("\n\t5 - Alunos com debito.");
					        printf("\n\t3 - Livros Diponíveis");
					        printf("\n\t4 - Livros Indisponíveis");
					        printf("\n\t5 - Editoras cadastradas");
					     	printf("\n\t6 - Sair");
							printf("\n\tOpcão: ");
							scanf("%d", &menuS);
							fflush(stdin);

							if(menuS == 1) {

							} else if (menuS == 2) {

							} else if (menuS == 3) {

							} else if (menuS == 4) {

							} else if (menuS == 5) {

							}

						} while (menuS != 6);


				   } else if (menuP == 6) {
				     	menuS = 0;
						do {

							system("cls");
							printf ("\n\t\t\tMENU GERENTE\n\n\n");
							printf("\n\tSub Menu -> Funcionários");

							printf("\n\t1 - Consultar Funcionario");
							printf("\n\t2 - Editar Funcionario");
							printf("\n\t3 - Demitir Funcionario");
							printf("\n\t4 - Promover Funcionario");
							printf("\n\t5 - Sair");
							printf("\n\tOpcão: ");
							scanf("%d", &menuS);
							fflush(stdin);
							
							if(menuS == 1) {

							} else if (menuS == 2) {

							} else if (menuS == 3) {

							} else if (menuS == 4) {

							}

						} while (menuS != 5);

					}

				} while (menuP != 7);

			}   

			} else if (loginS == 2){ //Menu para o aluno -----------------------------------------------
			
				
				do { //Checar Login de aluno
					saidaLogin = 0;

					system("cls");
					printf ("\n\t\t\tLOGIN\n\n\n");
					printf ("\n\tUser: ");
					scanf ("%s", &login);
					fflush(stdin);
					printf("\n\tSenha: ");
					scanf ("%s", &senha);
					fflush(stdin);

					for (i = 0; i < 50; i++) {

						if (strcmp(A.A[i].estudante.login,login) == 0 && strcmp(A.A[i].estudante.senha,senha) == 0) {

							printf ("\n\n\tLogin realizado com sucesso!");
							saidaLogin = 1;

						}

					}

					if (saidaLogin == 0) {

						aux = 0;
						do {

							system ("cls");
							printf ("\n\t\t\tLOGIN\n\n\n");
							printf ("\n\n\tSenha e/ou usuário está(ão) errado(s).");
							printf("\n\tDeseja tentar novamente?");
							printf("\n\tS - Sim, parece ótimo.");
							printf("\n\tN - Não, sair.");
							printf("\n\tOpção: ");
							scanf ("%c", &loginErro);

							if (loginErro == 's' || loginErro =='S') {

								aux = 1;

							} else if (loginErro == 'n' || loginErro =='N') {

								aux = 2;
								saidaLogin = 2;

							}


						} while(aux != 1 && aux != 2);

					}


				} while (saidaLogin != 1 && saidaLogin != 2);
				
				if(saidaLogin == 1) {
					
					//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
					menuS = 0;
					do{
					
					
					system("cls");
					printf ("\n\t\t\tMENU ALUNO\n\n\n");

					printf("\n\t1 - Consultar Livros");
					printf("\n\t2 - Reservar Livro");
					printf("\n\t3 - Verificar dados cadastrais");
					printf("\n\t4 - Acompanhar emprestimo");
					printf("\n\t5 - Sair");
					printf("\n\tOpcão: ");
					scanf("%d", &menuS);
					fflush(stdin);
						
						if (menuS == 1) {
							
						} else if (menuS == 2) {
							
						} else if (menuS == 3) {
							
						} else if (menuS == 4) {
							
						}
					
					} while (menuS != 5);
				}
			
			
			}

			salvarArquivosFunc(F);
			salvarArquivosAluno(A);
			salvarArquivosEdit(ED);
			salvarArquivosLivro(L);
			salvarArquivosEmp(E);

			printf("\n\n\n\tObrigado por utilizar nosso sistema.");
			

		} while (loginS != 3);

	} while (0);
}	

//função Primaria --------------------------------------------------------------------------
int main () {

	setlocale(LC_ALL, "ptb");
	menu();
	getch();

}
