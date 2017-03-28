# Projeto-de-Software---Tema-3--- Sistema de Controle de Bibliotecas

O  objetivo  do  presente  trabalho  é  projetar  um  sistema  para  o  gerenciamento  de  uma  biblioteca. 
Neste sistema poderão ser gerenciadas, por exemplo, as informações das editoras, dos livros, dos 
leitores, dos funcionários da biblioteca e dos empréstimos dos livros.
As entidades envolvidas no sistema são:

1.  Editora. Uma editora possui e-mail, nome, site, endereço e telefone;
2.  As editoras publicam Livros e livros possuem isbn, nome, area de conhecimento e autor(es).
3.  Devem  ser  mantidas  informações  sobre  a  disponibilidade  ou  não  do  livro  no  estoque  da 
biblioteca. O aluno consulta o Livro, é notificado da sua existência no acervo da biblioteca e 
informado  da  quantidade  de  exemplares  disponíveis  para  locação.  Se  não  tiver  nenhum 
exemplar,  deverá  ser  informado  da  próxima  data  prevista  para  a  devolução  de  um  destes 
exemplates e notificado se deseja fazer uma reserva.
4.  Telefones são identificados pelo seu tipo (fixo ou móvel), pelo número e pela operadora;
5.  O Endereco é composto do tipo (rua, avenida, alameda, etc), nome, número, complemento, 
bairro,  cep,  cidade,  estado).  O  endereço  deve  ser  persistido  no  sistema,  porém  os  dados 
devem ser obtidos através de consulta ao WebServices dos Correios. Caso o endereço não 
exista nos correios, o sistema deve permitir o cadastramento do mesmo.
6.  Livros  são  emprestados  aos  alunos.  Para  cada  empréstimo  devem  ser  registradas  as 
seguintes  informações:  data  do  emprestimo,  data  prevista  para  devolução  (30  dias  após  a 
data  do  empréstimo),  data  da  devolução  efetiva,  para  qual  Aluno  e  qual  funcionario 
registrou este empréstimo).
7.  Caso o aluno efetue a entrega de um empréstimo com atraso, o sistema deverá gerar uma 
Multa, que deverá ter um valor, data do pagamento (que não poderá  ser maior que a data
atual) e qual emprestimo ela se refere. Somente após o pagamento da multa, a devolução do 
empréstimo será efetivada;
8.  Um aluno será identificado pela sua matricula, turma, endereco e telefone.
9.  A Matricula  do aluno  possui  um  numero  e  uma  situacao,  que  pode ser ativa,  trancada  ou 
jubilada;
10. Um aluno, cuja situação da matrícula for diferente de ativa, não poderá efetuar empréstimos.
11. O registro de um empréstimo é efetuado por um Funcionario da Biblioteca. Este funcionário 
é  um  usuário  do sistema.  Este  usuário  possui  a  informação  se  é  ou  não administrador  do 
sistema, login, senha, endereço e telefone.
12. Autores,  Alunos,  Funcionários  são  todos  instancias  da  classe  Pessoa,  que  possui  CPF,  email, nome, sexo e data de nascimento).
13. O  sistema  deverá  permitir  que  se  consulte  quais  livros  estão  com  seus  empréstimos  em 
atraso;
14. Quais alunos estão com pendências na biblioteca;
15. Quais livros consultados que não constam do acervo da biblioteca;
16. Quais são os livros mais e menos procurados.
17. Dado um livro o sistema deverá listar todos os empréstimos relacionados a ele;
18. Dado um aluno, o sistema deverá listar todos os empréstimos efetuados a ele.
