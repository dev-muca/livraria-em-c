/*
AUTORES:
      MURILO BALEEIRO

ULTIMAS ALTERACOES:
      21/04/2022 - 17:47
*/

#include <stdio.h>  // Biblioteca de entrada e saida de dados
#include <string.h> // Biblioteca de manipulações de string
#include <stdlib.h>

#define LIVROS "livros.dat"         // Define uma constante chamada LIVROS com o valor livros.dat
#define AUTORES "autores.dat"       // Define uma constante chamada AUTORES com o valor autores.dat
#define CATEGORIAS "categorias.dat" // Define uma constante chamada CATEGORIAS com o valor categorias.dat
#define EDITORAS "editoras.dat"     // Define uma constante chamada EDITORES com o valor editoras.dat

// Cria uma estrutura de tipo livro
struct livro
{
  int codigo;            // Codigo do Livro
  char titulo[30];       // Titulo do Livro
  float preco;           // Preço do Livro
  int codAutor[4];       // Codigo dos Autores
  int codCategoria,      // Codigo da Categoria
      codEditora,        // Codigo da Editora
      edicao,            // Numero da Edição
      anoPublicacao,     // Ano de Publicação
      quantidadeEstoque; // Quantidade em Estoque
};

// Cria uma estrutura de tipo autor
struct autor
{
  int codigo;                   // Codigo do Autor
  char nome[15], sobrenome[15]; // Nome e Sobrenome do Autor
};

// Cria uma estrutura de tipo Categorias
struct categoria
{
  int codigo;         // Codigo da categoria
  char descricao[15]; // Descricao da categoria (Ex.: Romance, Tecnologia)
};

// Cria uma estrutura de tipo editoras
struct editora
{
  int codigo;          // Codigo da Editora
  char nome[30],       // Nome da Editora
      nomeContato[30], // Nome do Contato
      telefone[15],    // Telefone do Contato
      email[30];       // Email do Contato
};

// Funcao para cadastar os livros
void cadastrarLivro()
{
  // Declara uma struct do tipo livro com o nome livroCadastrado
  struct livro livroCadastrado;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoLivros
  FILE *arquivoLivros;
  // Declara uma variavel do tipo char com o nome de confirmarCadastro
  char confirmarCadastro;

  /* Verifica se existem autores cadastrados antes de capturar informacoes do livro, para que o usuario nao digite informacoes em vão e somente
  depois validar essa informacao */
  if (listarAutores() == 404)
  {
    system("cls");
    printf("ERRO: Nao sera possivel cadastrar um livro pois nao existem AUTORES a serem atribuidos.\n\n");
    return;
  }

  /* Verifica se existem editoras cadastradas antes de capturar informacoes do livro, para que o usuario nao digite informacoes em vão */
  if (listarEditoras() == 404)
  {
    system("cls");
    printf("ERRO: Nao sera possivel cadastrar um livro pois nao existem EDITORAS a serem atribuidas.\n\n");
    return;
  }

  /* Verifica se existem categorias cadastradas antes de capturar informacoes do livro, para que o usuario nao digite informacoes em vão */
  if (listarCategorias() == 404)
  {
    system("cls");
    printf("ERRO: Nao sera possivel cadastrar um livro pois nao existem CATEGORIAS a serem atribuidas.\n\n");
    return;
  }

  system("cls");

  // Captura os dados do codigo do livro
  printf("\nInforme o codigo do livro: ");
  fflush(stdin);
  scanf("%i", &livroCadastrado.codigo);

  // Captura os dados do titulo do livro
  printf("\nInforme o titulo do livro: ");
  fflush(stdin);
  gets(livroCadastrado.titulo);

  // Captura os dados do preco do livro
  printf("\nInforme o preco do livro (R$): ");
  fflush(stdin);
  scanf("%f", &livroCadastrado.preco);

  // Chama a funcao que lista os autores para facilitar a consulta do codigo ao usuario
  listarAutores();

  // Captura os codigos dos autores do livro
  for (int i = 0; i < 4; i++)
  {
    printf("Informe o codigo do Autor %i: ", i + 1);
    fflush(stdin);
    scanf("%i", &livroCadastrado.codAutor[i]);
  }

  // Chama a funcao que lista as categorias apra facilitar a consulta do codigo ao usuario
  listarCategorias();

  // Captura o codigo da categoria do livro
  printf("Informe o codigo da categoria do livro: ");
  fflush(stdin);
  scanf("%i", &livroCadastrado.codCategoria);

  // Chama a funcao que lista as editoras apra facilitar a consulta do codigo ao usuario
  listarEditoras();

  // Captura o codigo da editora do livro
  printf("Informe o codigo da editora: ");
  fflush(stdin);
  scanf("%i", &livroCadastrado.codEditora);

  // Captura o numero da edicao do livro
  printf("\nInforme o numero da edicao: ");
  fflush(stdin);
  scanf("%i", &livroCadastrado.edicao);

  // Captura o ano da publicacao do livro
  printf("\nInforme o ano da publicacao: ");
  fflush(stdin);
  scanf("%i", &livroCadastrado.anoPublicacao);

  // Captura a quantidade em estoque do livro
  printf("\nInforme a quantidade em estoque: ");
  fflush(stdin);
  scanf("%i", &livroCadastrado.quantidadeEstoque);

  // Confirma se o cadastro do livro devera ser efetuado de fato
  printf("\nConfirmar Cadastro? (S/N): ");
  fflush(stdin);
  scanf("%c", &confirmarCadastro);

  if (confirmarCadastro == 'S' || confirmarCadastro == 's')
  {
    // Realiza a abertura do arquivo de livros no modo AB (descricao das siglas abaixo)
    // A - Add    (Adicionar)
    // W - Write  (Escrever)
    // R - Read   (Ler)
    // B - Binary (Arquivos Binários)
    arquivoLivros = fopen(LIVROS, "ab");

    // 1º Argumento: os dados que eu quero que sejam salvos
    // 2º Argumento: qual o tamanho desses dados em bytes
    // 3º Argumento: quantas vezes você quer que esses dados sejam repetidos
    // 4º Argumento: endereço de memória em que esses arquivo sera salvo
    fwrite(&livroCadastrado, sizeof(livroCadastrado), 1, arquivoLivros);

    // fechamento do arquivo binário após escrita dos dados
    fclose(arquivoLivros);

    // Retorna um feedback para o usuario dizendo que o cadastro foi realizado
    system("color 0a");
    printf("\nCadastro realizado com sucesso!\n\n");
  }
  else
  {
    // Retorna um feedback para o usuario dizendo que o cadastro foi cancelado
    system("color 0c");
    printf("\nOperacao foi cancelada!\n\n");
  }
} // termino da funcao que cadastra os livros

// Funcao que lista todos os livros
void listarLivros()
{
  // Declara uma struct do tipo livro com o nome livroCadastrado
  struct livro livro;
  // Declara uma struct do tipo autor com o nome autor
  struct autor autor;
  // Declara uma struct do tipo categoria com o nome categoria
  struct categoria categoria;
  // Declara uma struct do tipo editora com o nome editora
  struct editora editora;

  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoLivros
  FILE *arquivoLivros;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoAutores
  FILE *arquivoAutores;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoCategorias
  FILE *arquivoCategorias;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoEditoras
  FILE *arquivoEditoras;

  // Realiza a abertura do arquivo de livros no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoLivros = fopen(LIVROS, "rb");

  // Verifica se existem livros cadastrados, se nao existir ja para a execucao da funcao e tras um feedback ao usuario
  if (fread(&livro, sizeof(livro), 1, arquivoLivros) == NULL)
  {
    system("color 0c");
    printf("Nenhum livro cadastrado!\n\n");
    return;
  }

  // Preenche a tabela com os dados dos autores
  printf("\nCODIGO | TITULO                                 | PRECO      | EDICAO | ANO  | ESTOQUE | CATEGORIA     | EDITORA        ");
  printf("\n************************************************************************************************************************");

  // Posiciona o ponteiro no comeco do arquivo de livros para leitura
  fseek(arquivoLivros, -sizeof(livro), 1);

  // Preenche os dados do Livro
  while (fread(&livro, sizeof(livro), 1, arquivoLivros) == 1)
  {

    // Realiza abertura do arquivo de Categorias para obter informacoes necessarias
    arquivoCategorias = fopen(CATEGORIAS, "rb");
    while (fread(&categoria, sizeof(categoria), 1, arquivoCategorias) == 1)
    {
      // Realiza abertura do arquivo de Editoras para obter informacoes necessarias
      arquivoEditoras = fopen(EDITORAS, "rb");
      while (fread(&editora, sizeof(editora), 1, arquivoEditoras) == 1)
      {

        // Se o codigo da editora obtido no cadastro do livro existir nos registros da editora, ira usar este dado no cabecalho
        if (editora.codigo == livro.codEditora)
        {
          // Se o codigo da categoria obtido no cadastro do livro existir nos registros de categoria, ira usar este dado no cabecalho
          if (categoria.codigo == livro.codCategoria)
          {
            // Monta o cabecalho e preenche sua estrutura com os dados obtidos
            printf("\n%-7i| %-39s| R$ %-8.2f| %-7i| %-5i| %-8i| %-14s| %-14s", livro.codigo, livro.titulo, livro.preco, livro.edicao, livro.anoPublicacao, livro.quantidadeEstoque, categoria.descricao, editora.nome);

            // Realiza abertura do arquivo de Autores para obter informacoes necessarias
            arquivoAutores = fopen(AUTORES, "rb");
            printf("\nAutores: ");
            while (fread(&autor, sizeof(autor), 1, arquivoAutores) == 1)
            {
              for (int i = 0; i < 4; i++)
              {
                // Se o codigo dop autor obtido no cadastro do livro existir nos registros dos autores, ira usar este dado no cabecalho
                if (livro.codAutor[i] == autor.codigo)
                {
                  // Imprime o nome e sobrenome dos autores logo abaixo o registro do livro
                  printf("%c%s %s ", 26, autor.nome, autor.sobrenome);
                }
              }
            }
            printf("\n");
          }
        }
      }
    }
  }
  printf("\n\n");
  // fechamento do arquivo binário após leitura dos dados
  fclose(arquivoLivros);
}

// Funcao que tras o relatorio de livros por categoria
void relatorioLivrosPorCategoria()
{
  // Declara uma struct do tipo livro com o nome livroCadastrado
  struct livro livro;
  // Declara uma struct do tipo autor com o nome autor
  struct autor autor;
  // Declara uma struct do tipo categoria com o nome categoria
  struct categoria categoria;
  // Declara uma struct do tipo editora com o nome editora
  struct editora editora;

  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoLivros
  FILE *arquivoLivros;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoAutores
  FILE *arquivoAutores;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoCategorias
  FILE *arquivoCategorias;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoEditoras
  FILE *arquivoEditoras;
  // Declara uma variavel do tipo int que ira armzenar o codigo da categoria a ser gerado relatorio
  int codCategoria;

  // Lista as categorias para facilitar a pesquisa do usuario
  listarCategorias();

  // Captura o codigo da categoria selecionada
  printf("\nInforme o codigo da categoria para o relatorio: ");
  fflush(stdin);
  scanf("%i", &codCategoria);

  // Realiza a abertura do arquivo de livros no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoLivros = fopen(LIVROS, "rb");

  // Preenche a tabela com os dados dos autores
  printf("\nCODIGO | TITULO                                 | PRECO      | EDICAO | ANO  | ESTOQUE | CATEGORIA     | EDITORA        ");
  printf("\n************************************************************************************************************************");

  // Posiciona o ponteiro no comeco do arquivo de livros para leitura
  fseek(arquivoLivros, -sizeof(livro), 1);

  // Preenche os dados do Livro
  while (fread(&livro, sizeof(livro), 1, arquivoLivros) == 1)
  {

    if (livro.codCategoria == codCategoria)
    {

      // Realiza abertura do arquivo de Categorias para obter informacoes necessarias
      arquivoCategorias = fopen(CATEGORIAS, "rb");
      while (fread(&categoria, sizeof(categoria), 1, arquivoCategorias) == 1)
      {
        // Realiza abertura do arquivo de Editoras para obter informacoes necessarias
        arquivoEditoras = fopen(EDITORAS, "rb");
        while (fread(&editora, sizeof(editora), 1, arquivoEditoras) == 1)
        {

          // Se o codigo da editora obtido no cadastro do livro existir nos registros da editora, ira usar este dado no cabecalho
          if (editora.codigo == livro.codEditora)
          {
            // Se o codigo da categoria obtido no cadastro do livro existir nos registros de categoria, ira usar este dado no cabecalho
            if (categoria.codigo == livro.codCategoria)
            {
              // Monta o cabecalho e preenche sua estrutura com os dados obtidos
              printf("\n%-7i| %-39s| R$ %-8.2f| %-7i| %-5i| %-8i| %-14s| %-14s", livro.codigo, livro.titulo, livro.preco, livro.edicao, livro.anoPublicacao, livro.quantidadeEstoque, categoria.descricao, editora.nome);

              // Realiza abertura do arquivo de Autores para obter informacoes necessarias
              arquivoAutores = fopen(AUTORES, "rb");
              printf("\nAutores: ");
              while (fread(&autor, sizeof(autor), 1, arquivoAutores) == 1)
              {
                for (int i = 0; i < 4; i++)
                {
                  // Se o codigo dop autor obtido no cadastro do livro existir nos registros dos autores, ira usar este dado no cabecalho
                  if (livro.codAutor[i] == autor.codigo)
                  {
                    // Imprime o nome e sobrenome dos autores logo abaixo o registro do livro
                    printf("%c%s %s ", 26, autor.nome, autor.sobrenome);
                  }
                }
              }
              printf("\n");
            }
          }
        }
      }
    }
  }
  printf("\n\n");
  // fechamento do arquivo binário após leitura dos dados
  fclose(arquivoLivros);
}

// Funcao que consulta um livro por palavra-chave
void consultarLivroPalavraChave()
{
  // Declara uma struct do livro autor com o nome livroConsulta
  struct livro livro;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoAutores
  FILE *arquivoLivros;
  // Declara uma variavel do tipo char que ira armazenar a palavra-chave para realizar a pesquisa de um livro
  char palavraChave[30];
  // Declara uma variavel do tipo int que sera usada de flag para demarcar se abusca foi concluida ou nao
  int found = 0;

  // Captura a palavra-chave para realização da consulta
  printf("\nInforme a palavra-chave: ");
  fflush(stdin);
  gets(palavraChave);

  // Realiza a abertura do arquivo de autores no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoLivros = fopen(LIVROS, "rb");

  // Imprime o cabeçalho e os livros com as palavras-chaves
  printf("\nCODIGO | TITULO                                 | PRECO      | EDICAO | ANO  | ESTOQUE | CATEGORIA     | EDITORA        ");
  printf("\n************************************************************************************************************************");

  while (fread(&livro, sizeof(livro), 1, arquivoLivros) == 1)
  {
    if (strstr(livro.titulo, palavraChave) != NULL)
    {
      printf("\n%-7i| %-39s| R$ %-8.2f| %-7i| %-5i| %-8i| %-14i| %-14i", livro.codigo, livro.titulo, livro.preco, livro.edicao, livro.anoPublicacao, livro.quantidadeEstoque, livro.codCategoria, livro.codEditora);
      found++;
    }
  }

  // Caso nenhum livro com a palavra-chave seja encontrado, retorna um feedback para o usuario
  if (found == 0)
  {
    system("color 0c");
    printf("\nNenhum livro com a palavra-chave %s foi encontrado!\n\n", palavraChave);
  }

  // Fechar o arquivo binario apos leitura
  fclose(arquivoLivros);
  printf("\n\n");
}

// Funcao que consulta livros por autores <<<<<< ANDAMENTO
void relatorioLivrosPorAutor()
{
  // Declara uma struct do livro autor com o nome livro
  struct livro livro;
  // Declara uma struct do livro autor com o nome livro
  struct autor autor;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoLivros
  FILE *arquivoLivros;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoAutores
  FILE *arquivoAutores;
  // Declara uma variavel do tipo int que ira armazenar o codigo do autor para realizar a pesquisa de um livro
  int codAutor;
  // Declara uma variavel do tipo int que sera usada de flag para demarcar se abusca foi concluida ou nao
  int found = 0;

  // Lista todos os autores para facilitar a consulta para o usuario
  listarAutores();

  // Captura a palavra-chave para realização da consulta
  printf("\nInforme o codigo do autor: ");
  fflush(stdin);
  scanf("%i", &codAutor);

  // Realiza a abertura do arquivo de autores no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoLivros = fopen(LIVROS, "rb");

  // Imprime o cabeçalho e os livros com o codigo do autor informado
  printf("\nCODIGO | TITULO                                 | PRECO      | EDICAO | ANO  | ESTOQUE | CATEGORIA     | EDITORA        ");
  printf("\n************************************************************************************************************************");

  while (fread(&livro, sizeof(livro), 1, arquivoLivros) == 1)
  {
    for (int i = 0; i < 4; i++)
    {
      if (codAutor == livro.codAutor[i])
      {
        printf("\n%-7i| %-39s| R$ %-8.2f| %-7i| %-5i| %-8i| %-14i| %-14i", livro.codigo, livro.titulo, livro.preco, livro.edicao, livro.anoPublicacao, livro.quantidadeEstoque, livro.codCategoria, livro.codEditora);
        found++;
      }
    }
  }

  // Fechar o arquivo binario apos leitura
  fclose(arquivoLivros);

  // Caso nenhum livro com o codigo do autor seja encontrado, retorna um feedback para o usuario
  if (found == 0)
  {
    arquivoAutores = fopen(AUTORES, "rb");
    while (fread(&autor, sizeof(autor), 1, arquivoAutores) == 1)
    {
      if (codAutor == autor.codigo)
      {
        system("color 0c");
        printf("\nNenhum livro com o autor %s %s foi encontrado!\n\n", autor.nome, autor.sobrenome);
      }
    }
    fclose(arquivoAutores);
  }

  printf("\n\n");
}

// Funcao para cadastrar os autores
void cadastrarAutor()
{
  // Declara uma struct do tipo autor com o nome autorCadastrado
  struct autor autorCadastrado;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoLivros
  FILE *arquivoAutores;
  // Declara uma variavel do tipo char com o nome de confirmarCadastro
  char confirmarCadastro;

  // Captura os dados do codigo do autor
  printf("\nInforme o codigo do autor: ");
  fflush(stdin);
  scanf("%i", &autorCadastrado.codigo);

  // Captura os dados do nome do autor
  printf("\nInforme o nome do autor: ");
  fflush(stdin);
  gets(autorCadastrado.nome);

  // Captura os dados do sobrenome do autor
  printf("\nInforme o sobrenome do autor: ");
  fflush(stdin);
  gets(autorCadastrado.sobrenome);

  // Confirma se o cadastro do autor devera ser efetuado de fato
  printf("\nConfirmar Cadastro? (S/N): ");
  fflush(stdin);
  scanf("%c", &confirmarCadastro);

  if (confirmarCadastro == 'S' || confirmarCadastro == 's')
  {
    // Realiza a abertura do arquivo de livros no modo AB (descricao das siglas abaixo)
    // A - Add    (Adicionar)
    // W - Write  (Escrever)
    // R - Read   (Ler)
    // B - Binary (Arquivos Binários)
    arquivoAutores = fopen(AUTORES, "ab");

    // 1º Argumento: os dados que eu quero que sejam salvos
    // 2º Argumento: qual o tamanho desses dados em bytes
    // 3º Argumento: quantas vezes você quer que esses dados sejam repetidos
    // 4º Argumento: endereço de memória em que esses arquivo sera salvo
    fwrite(&autorCadastrado, sizeof(autorCadastrado), 1, arquivoAutores);

    // fechamento do arquivo binário após escrita dos dados
    fclose(arquivoAutores);

    // Retorna um feedback para o usuario dizendo que o cadastro foi realizado
    system("color 0a");
    printf("\nCadastro realizado com sucesso!\n\n");
  }
  else
  {
    // Retorna um feedback para o usuario dizendo que o cadastro foi cancelado
    system("color 0c");
    printf("\nOperacao foi cancelada!\n\n");
  }
}

// Funcao que lista todos os autores
int listarAutores()
{
  // Declara uma struct do tipo autor com o nome autor
  struct autor autor;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoAutores
  FILE *arquivoAutores;

  // Realiza a abertura do arquivo de autores no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoAutores = fopen(AUTORES, "rb");

  // Preenche a tabela com os dados dos autores
  if (fread(&autor, sizeof(autor), 1, arquivoAutores) != 0)
  {
    printf("\nCODIGO | NOME                        | SOBRENOME         ");
    printf("\n*********************************************************");

    // Posiciona o ponteiro no comeco do arquivo para leitura
    fseek(arquivoAutores, -sizeof(autor), 1);

    while (fread(&autor, sizeof(autor), 1, arquivoAutores) == 1)
    {
      printf("\n%-7i| %-28s| %-20s", autor.codigo, autor.nome, autor.sobrenome);
    }
  }
  else
  {
    // Caso nao exista autores cadastrados para serem listados, ira informar um erro em vermelho e retornar o codigo de erro 404 em funcoes de callback
    system("color 0c");
    printf("Nenhum autor cadastrado!\n\n");
    return 404;
  }
  // Fechamento do arquivo binário após leitura dos dados
  fclose(arquivoAutores);
  printf("\n\n");
}

// Funcao que consulta autor por parte do nome
void consultarAutorNome()
{
  // Declara uma struct do tipo autor com o nome autor
  struct autor autor;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoAutores
  FILE *arquivoAutores;
  // Declara uma variavel do tipo char que ira armzenar o termo da pesquisa
  char inicialNome[15];

  // Captura os dados da inicial do nome do autor
  printf("\nInforme as iniciais do Autor: ");
  fflush(stdin);
  gets(inicialNome);

  // Realiza a abertura do arquivo de autores no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoAutores = fopen(AUTORES, "rb");

  // Preenche a tabela com os dados dos autores
  if (fread(&autor, sizeof(autor), 1, arquivoAutores) != 0)
  {
    printf("\nCODIGO | NOME                        | SOBRENOME         ");
    printf("\n*********************************************************");

    // Posiciona o ponteiro no comeco do arquivo para leitura
    fseek(arquivoAutores, -sizeof(autor), 1);

    while (fread(&autor, sizeof(autor), 1, arquivoAutores) == 1)
    {
      if (strncmp(autor.nome, inicialNome, strlen(inicialNome)) == 0)
      {
        printf("\n%-7i| %-28s| %-20s", autor.codigo, autor.nome, autor.sobrenome);
      }
    }
  }
  else
  {
    // Caso nao exista autores cadastrados para serem listados, ira informar um erro em vermelho e retornar o codigo de erro 404 em funcoes de callback
    system("color 0c");
    printf("Nenhum autor com as iniciais %s encontrado!\n\n", inicialNome);
    return 404;
  }
  // Fechamento do arquivo binário após leitura dos dados
  fclose(arquivoAutores);
  printf("\n\n");
}

// Funcao que atualiza os dados de um autor
void atualizarDadosAutor()
{
  // Declara uma struct do tipo autor com o nome autorCadastrado
  struct autor autorAtualizado;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoLivros
  FILE *arquivoAutores;
  // Declara uma variavel do tipo char com o nome de codAutor
  char codAutor;
  int found = 0;

  // Lista todos os autores para consulta previa do codigo para o usuario
  listarAutores();

  // Captura os dados de codigo do Autor para realizar a atualizacao cadastral
  printf("\nInforme o codigo do autor p/ atualizacao cadastral: ");
  fflush(stdin);
  scanf("%i", &codAutor);

  // Realiza a abertura do arquivo de autores no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoAutores = fopen(AUTORES, "rb+");

  // Localiza e exibe os dados do autor a ser atualizado

  while (found == 0 && fread(&autorAtualizado, sizeof(autorAtualizado), 1, arquivoAutores) == 1)
  {
    if (autorAtualizado.codigo == codAutor)
    {
      printf("\nCODIGO | NOME                        | SOBRENOME         ");
      printf("\n*********************************************************");
      printf("\n%-7i| %-28s| %-20s", autorAtualizado.codigo, autorAtualizado.nome, autorAtualizado.sobrenome);
      found = 1;
    }
  }

  // Caso o codigo informado nao exista ira retornar um feedback ao usuario que o autor nao foi encontrado
  if (found == 0)
  {
    system("color 0c");
    printf("\nAutor nao localizado!\n\n");
    return;
  }
  else
  {
    char opcao;
    printf("\n\nDeseja atualizar dados do Autor? (S/N): ");
    fflush(stdin);
    scanf("%c", &opcao);

    if (opcao == 'S' || opcao == 's')
    {
      // Reescreve o nome do Autor
      printf("\nNome Antigo: %s", autorAtualizado.nome);
      printf("\nNome Novo: ");
      fflush(stdin);
      gets(autorAtualizado.nome);

      // Reescreve o sobrenome do Autor
      printf("\nSobrenome Antigo: %s", autorAtualizado.sobrenome);
      printf("\nSobrenome Novo: ");
      fflush(stdin);
      gets(autorAtualizado.sobrenome);

      // Retorna um feedback para o usuario dizendo que o cadastro foi realizado
      system("color 0a");
      printf("\nDados Atualizados com Sucesso!\n\n");

      // Posiciona o ponteiro no comeco do arquivo autores para sobreescrita
      fseek(arquivoAutores, -sizeof(autorAtualizado), 1);

      // Grava o registro com os novos dados
      fwrite(&autorAtualizado, sizeof(autorAtualizado), 1, arquivoAutores);

      // Fecha o arquivo binario apos escrita dos novos dados
      fclose(arquivoAutores);
    }
    else
    {
      // Retorna um feedback para o usuario dizendo que o cadastro foi cancelado
      system("color 0c");
      printf("\nOperacao foi cancelada!\n\n");
    }
  }
}

// Funcao para cadastrar as categorias
void cadastrarCategoria()
{
  // Declara uma struct do tipo categoria com o nome categoriaCadastro
  struct categoria categoriaCadastro;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoCategoria
  FILE *arquivoCategoria;
  // Declara uma variavel do tipo char com o nome de confirmarCadastro
  char confirmarCadastro;

  // Captura os dados do codigo da categoria
  printf("\nInforme o codigo da categoria: ");
  fflush(stdin);
  scanf("%i", &categoriaCadastro.codigo);

  // Captura os dados da descricao da categoria
  printf("\nInforme a descricao da categoria: ");
  fflush(stdin);
  gets(categoriaCadastro.descricao);

  printf("\nConfirmar Cadastro? (S/N): ");
  fflush(stdin);
  scanf("%c", &confirmarCadastro);

  if (confirmarCadastro == 'S' || confirmarCadastro == 's')
  {
    // Realiza a abertura do arquivo de livros no modo AB (descricao das siglas abaixo)
    // A - Add    (Adicionar)
    // W - Write  (Escrever)
    // R - Read   (Ler)
    // B - Binary (Arquivos Binários)
    arquivoCategoria = fopen(CATEGORIAS, "ab");

    // 1º Argumento: os dados que eu quero que sejam salvos
    // 2º Argumento: qual o tamanho desses dados em bytes
    // 3º Argumento: quantas vezes você quer que esses dados sejam repetidos
    // 4º Argumento: endereço de memória em que esses arquivo sera salvo
    fwrite(&categoriaCadastro, sizeof(categoriaCadastro), 1, arquivoCategoria);

    // fechamento do arquivo binário após escrita dos dados
    fclose(arquivoCategoria);

    // Retorna um feedback para o usuario dizendo que o cadastro foi realizado
    system("color 0a");
    printf("\nCadastro realizado com sucesso!\n\n");
  }
  else
  {
    // Retorna um feedback para o usuario dizendo que o cadastro foi cancelado
    system("color 0c");
    printf("\nOperacao foi cancelada!\n\n");
  }
}

// Funcao que lista todos as categorias
int listarCategorias()
{
  // Declara uma struct do tipo categoria com o nome categoria
  struct categoria categoria;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoCategorias
  FILE *arquivoCategorias;
  // Declara uma variavel do tipo char que ira armazenar as informacoes das categorias e exibir na tela
  char categoriasOutput[100];

  // Realiza a abertura do arquivo de categorias no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoCategorias = fopen(CATEGORIAS, "rb");

  // Preenche a tabela com os dados das categorias
  if (fread(&categoria, sizeof(categoria), 1, arquivoCategorias) != 0)
  {
    printf("\nCODIGO | DESCRICAO                ");
    printf("\n****************************************");

    // Posiciona o ponteiro no comeco do arquivo para leitura
    fseek(arquivoCategorias, -sizeof(categoria), 1);

    // Imprime as informacoes das categorias
    while (fread(&categoria, sizeof(categoria), 1, arquivoCategorias) == 1)
    {
      printf("\n%-7i| %-24s", categoria.codigo, categoria.descricao);
    }
  }
  else
  {
    // Caso nao exista categorias cadastradas para serem listados, ira informar um erro em vermelho e retornar o codigo de erro 404 em funcoes de callback
    system("color 0c");
    printf("Nenhuma categoria cadastrada!\n\n");
    return 404;
  }

  // Fechamento do arquivo binário após leitura dos dados
  fclose(arquivoCategorias);
  printf("\n\n");
}

// Funcao que ira excluir uma categoria
void excluirCategoria()
{
  // Declara uma struct do tipo categoria com o nome categoria
  struct categoria categoria;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoCategorias
  FILE *arquivoCategorias, *arquivoCategoriasNew;

  char opcao;
  int codCateg;

  listarCategorias();
  printf("Digite o Codigo da categoria a ser excluida: ");
  fflush(stdin);
  scanf("%i", &codCateg);

  // Realiza a abertura do arquivo de categorias no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoCategorias = fopen(CATEGORIAS, "rb");

  // Preenche a tabela com os dados das categorias
  if (fread(&categoria, sizeof(categoria), 1, arquivoCategorias) != 0)
  {
    printf("\nCODIGO | DESCRICAO                ");
    printf("\n****************************************");

    // Posiciona o ponteiro no comeco do arquivo para leitura
    fseek(arquivoCategorias, -sizeof(categoria), 1);

    // Imprime as informacoes das categorias
    while (fread(&categoria, sizeof(categoria), 1, arquivoCategorias) == 1)
    {
      if (categoria.codigo == codCateg)
      {
        printf("\n%-7i| %-24s", categoria.codigo, categoria.descricao);
      }
    }
  }
  else
  {
    // Caso nao exista categorias cadastradas para serem listados, ira informar um erro em vermelho e retornar o codigo de erro 404 em funcoes de callback
    system("color 0c");
    printf("Nenhuma categoria cadastrada!\n\n");
    return 404;
  }

  fclose(arquivoCategorias);

  printf("\n\nConfirmar Exclusao? (S/N): ");
  fflush(stdin);
  scanf("%c", &opcao);

  if (opcao == 'S' || opcao == 's')
  {

    arquivoCategorias = fopen(CATEGORIAS, "rb");
    arquivoCategoriasNew = fopen("categoriasNEW.dat", "wb");

    while (fread(&categoria, sizeof(categoria), 1, arquivoCategorias) == 1)
    {
      if (categoria.codigo != codCateg)
      {
        fwrite(&categoria, sizeof(categoria), 1, arquivoCategoriasNew);
      }
    }

    fclose(arquivoCategorias);
    fclose(arquivoCategoriasNew);

    system("del categorias.dat");
    system("ren categoriasNEW.dat categorias.dat");
    system("color 0a");

    printf("\nCategoria excluida com Sucesso!");
    printf("\n\n");
  }
  else
  {
    system("color 0c");
    printf("\nOperacao Cancelada!");
  }
}

// Funcao para cadastrar as editoras
void cadastrarEditora()
{
  // Declara uma struct do tipo editora com o nome editoraCadastro
  struct editora editoraCadastro;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoEditora
  FILE *arquivoEditora;
  // Declara uma variavel do tipo char com o nome de confirmarCadastro
  char confirmarCadastro;

  // Captura os dados do codigo da editora
  printf("\nInforme o codigo da editora: ");
  fflush(stdin);
  scanf("%i", &editoraCadastro.codigo);

  // Captura os dados do nome da editora
  printf("\nInforme o nome da editora: ");
  fflush(stdin);
  gets(editoraCadastro.nome);

  // Captura os dados do nome do contato da editora
  printf("\nInforme o nome de contato para esta editora: ");
  fflush(stdin);
  gets(editoraCadastro.nomeContato);

  // Captura os dados do telefone do contato
  printf("\nInforme o telefone para este contato: ");
  fflush(stdin);
  gets(editoraCadastro.telefone);

  // Captura os dados do email do contato
  printf("\nInforme um e-mail para este contato: ");
  fflush(stdin);
  gets(editoraCadastro.email);

  // Confirma o cadastro da editora
  printf("\nConfirmar Cadastro? (S/N): ");
  fflush(stdin);
  scanf("%c", &confirmarCadastro);

  if (confirmarCadastro == 'S' || confirmarCadastro == 's')
  {
    // Realiza a abertura do arquivo de livros no modo AB (descricao das siglas abaixo)
    // A - Add    (Adicionar)
    // W - Write  (Escrever)
    // R - Read   (Ler)
    // B - Binary (Arquivos Binários)
    arquivoEditora = fopen(EDITORAS, "ab");

    // 1º Argumento: os dados que eu quero que sejam salvos
    // 2º Argumento: qual o tamanho desses dados em bytes
    // 3º Argumento: quantas vezes você quer que esses dados sejam repetidos
    // 4º Argumento: endereço de memória em que esses arquivo sera salvo
    fwrite(&editoraCadastro, sizeof(editoraCadastro), 1, arquivoEditora);

    // fechamento do arquivo binário após escrita dos dados
    fclose(arquivoEditora);

    // Retorna um feedback para o usuario dizendo que o cadastro foi realizado
    system("color 0a");
    printf("\nCadastro realizado com sucesso!\n\n");
  }
  else
  {
    // Retorna um feedback para o usuario dizendo que o cadastro foi cancelado
    system("color 0c");
    printf("\nOperacao foi cancelada!\n\n");
  }
}

// Funcao que lista todas as editoras
int listarEditoras()
{
  // Declara uma struct do tipo editora com o nome editoraCadastro
  struct editora editora;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoEditora
  FILE *arquivoEditora;

  // Realiza a abertura do arquivo de categorias no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoEditora = fopen(EDITORAS, "rb");

  // Preenche a tabela com os dados das categorias
  if (fread(&editora, sizeof(editora), 1, arquivoEditora) != 0)
  {
    printf("\nCODIGO | EDITORA                      | CONTATO            | TELEFONE       | EMAIL                                  ");
    printf("\n*********************************************************************************************************************");

    // Posiciona o ponteiro no comeco do arquivo para leitura
    fseek(arquivoEditora, -sizeof(editora), 1);

    while (fread(&editora, sizeof(editora), 1, arquivoEditora) == 1)
    {
      printf("\n%-7i| %-29s| %-19s| %-15s| %-39s", editora.codigo, editora.nome, editora.nomeContato, editora.telefone, editora.email);
    }
  }
  else
  {
    // Caso nao exista editoras cadastradas para serem listados, ira informar um erro em vermelho e retornar o codigo de erro 404 em funcoes de callback
    system("color 0c");
    printf("Nenhuma editora cadastrada!\n\n");
    return 404;
  }
  // Fechamento do arquivo binário após leitura dos dados
  fclose(arquivoEditora);
  printf("\n\n");
}

// Funcao que atualiza os dados das editoras
void atualizarDadosEditora()
{
  // Declara uma struct do tipo autor com o nome autorCadastrado
  struct editora editoraAtualizada;
  // Declara uma variavel ponteiro do tipo arquivo com o nome arquivoLivros
  FILE *arquivoEditora;
  // Declara uma variavel do tipo char com o nome de codAutor
  char codEditora;
  int found = 0;

  // Lista todos os autores para consulta previa do codigo para o usuario
  listarEditoras();

  // Captura os dados de codigo do Autor para realizar a atualizacao cadastral
  printf("\nInforme o codigo da Editora p/ atualizacao cadastral: ");
  fflush(stdin);
  scanf("%i", &codEditora);

  // Realiza a abertura do arquivo de autores no modo RB (descricao das siglas abaixo)
  // A - Add    (Adicionar)
  // W - Write  (Escrever)
  // R - Read   (Ler)
  // B - Binary (Arquivos Binários)
  arquivoEditora = fopen(EDITORAS, "rb+");

  // Localiza e exibe os dados do autor a ser atualizado

  while (found == 0 && fread(&editoraAtualizada, sizeof(editoraAtualizada), 1, arquivoEditora) == 1)
  {
    if (editoraAtualizada.codigo == codEditora)
    {
      printf("\nCODIGO | EDITORA                      | CONTATO            | TELEFONE       | EMAIL                                  ");
      printf("\n*********************************************************************************************************************");
      printf("\n%-7i| %-29s| %-19s| %-15s| %-39s", editoraAtualizada.codigo, editoraAtualizada.nome, editoraAtualizada.nomeContato, editoraAtualizada.telefone, editoraAtualizada.email);
      found = 1;
    }
  }

  // Caso o codigo informado nao exista ira retornar um feedback ao usuario que o autor nao foi encontrado
  if (found == 0)
  {
    system("color 0c");
    printf("\nEditora nao localizada!\n\n");
    return;
  }
  else
  {
    char opcao;
    printf("\n\nDeseja atualizar dados da Editora? (S/N): ");
    fflush(stdin);
    scanf("%c", &opcao);

    if (opcao == 'S' || opcao == 's')
    {
      // Reescreve o nome da Editora
      printf("\nNome Antigo: %s", editoraAtualizada.nome);
      printf("\nNome Novo: ");
      fflush(stdin);
      gets(editoraAtualizada.nome);

      // Reescreve o Contato da Editora
      printf("\nContato Antigo: %s", editoraAtualizada.nomeContato);
      printf("\nContato Novo: ");
      fflush(stdin);
      gets(editoraAtualizada.nomeContato);

      // Reescreve o telefone do contato da Editora
      printf("\nTelefone do Contato Antigo: %s", editoraAtualizada.telefone);
      printf("\nTelefone do Contato Novo: ");
      fflush(stdin);
      gets(editoraAtualizada.telefone);

      // Reescreve o email do contato da Editora
      printf("\nEmail do Contato Antigo: %s", editoraAtualizada.email);
      printf("\nEmail do Contato Novo: ");
      fflush(stdin);
      gets(editoraAtualizada.email);

      // Retorna um feedback para o usuario dizendo que o cadastro foi realizado
      system("color 0a");
      printf("\nDados Atualizados com Sucesso!\n\n");

      // Posiciona o ponteiro no comeco do arquivo autores para sobreescrita
      fseek(arquivoEditora, -sizeof(editoraAtualizada), 1);

      // Grava o registro com os novos dados
      fwrite(&editoraAtualizada, sizeof(editoraAtualizada), 1, arquivoEditora);

      // Fecha o arquivo binario apos escrita dos novos dados
      fclose(arquivoEditora);
    }
    else
    {
      // Retorna um feedback para o usuario dizendo que o cadastro foi cancelado
      system("color 0c");
      printf("\nOperacao foi cancelada!\n\n");
    }
  }
}

/* ######################################################################### */
/* ######## FUNCOES QUE DESENHAM OS MENUS NA TELA PARA O USUARIO ########### */
/* ######################################################################### */

// Funcao menuLivros destinada somente chamadas de funcoes relacionadas aos livros
void menuLivros()
{
  int opcao;

  do
  {
    system("cls");
    system("color 0f");
    system("title SISTEMA LIVRARIA C/C++");

    printf("\n###########################################");
    printf("\n##              MENU LIVROS              ##");
    printf("\n###########################################");
    printf("\n##  1) Cadastrar um Livro                ##");
    printf("\n##  2) Listar Livros Cadastrados         ##");
    printf("\n##  3) Consultar Livro p/ Palavra-Chave  ##");
    printf("\n##  4) Relatorio de livros p/ Categoria  ##");
    printf("\n##  5) Relatorio de livros p/ Autor      ##");
    printf("\n##  0) Voltar                            ##");
    printf("\n###########################################");
    printf("\n\n--> ");

    fflush(stdin);       // Limpar a memoria Buffer do Teclado
    scanf("%i", &opcao); // Obtem o valor da opcao informada pelo usuario
    system("cls");

    switch (opcao)
    {
    case 1:
      cadastrarLivro();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 2:
      listarLivros();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 3:
      consultarLivroPalavraChave();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 4:
      relatorioLivrosPorCategoria();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 5:
      relatorioLivrosPorAutor();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    default:
      break;
    }

  } while (opcao != 0);
}

// Funcao menuAutores destinada somente chamadas de funcoes relacionadas aos autores
void menuAutores()
{
  int opcao;

  do
  {
    system("cls");
    system("color 0f");
    system("title SISTEMA LIVRARIA C/C++");

    printf("\n#######################################");
    printf("\n##           MENU AUTORES            ##");
    printf("\n#######################################");
    printf("\n##   1) Cadastrar Autor              ##");
    printf("\n##   2) Listar Autores Cadastrados   ##");
    printf("\n##   3) Consultar Autor p/ Nome      ##");
    printf("\n##   4) Atualizar Dados do Autor     ##");
    printf("\n##   0) Voltar                       ##");
    printf("\n#######################################");
    printf("\n\n--> ");

    fflush(stdin);       // Limpar a memoria Buffer do Teclado
    scanf("%i", &opcao); // Obtem o valor da opcao informada pelo usuario
    system("cls");

    switch (opcao)
    {
    case 1:
      cadastrarAutor();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 2:
      listarAutores();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 3:
      consultarAutorNome();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 4:
      atualizarDadosAutor();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    default:
      break;
    }

  } while (opcao != 0);
}

// Funcao menuAutores destinada somente chamadas de funcoes relacionadas aos autores
void menuCategorias()
{
  int opcao;

  do
  {
    system("cls");
    system("color 0f");
    system("title SISTEMA LIVRARIA C/C++");

    printf("\n#######################################");
    printf("\n##          MENU CATEGORIAS          ##");
    printf("\n#######################################");
    printf("\n##   1) Cadastrar Categoria          ##");
    printf("\n##   2) Listar as Categorias         ##");
    printf("\n##   3) Excluir uma Categoria        ##");
    printf("\n##   0) Voltar                       ##");
    printf("\n#######################################");
    printf("\n\n--> ");

    fflush(stdin);       // Limpar a memoria Buffer do Teclado
    scanf("%i", &opcao); // Obtem o valor da opcao informada pelo usuario
    system("cls");

    switch (opcao)
    {
    case 1:
      cadastrarCategoria();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 2:
      listarCategorias();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 3:
      excluirCategoria();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    default:
      break;
    }

  } while (opcao != 0);
}

// Funcao menuAutores destinada somente chamadas de funcoes relacionadas aos autores
void menuEditoras()
{
  int opcao;

  do
  {
    system("cls");
    system("color 0f");
    system("title SISTEMA LIVRARIA C/C++");

    printf("\n#######################################");
    printf("\n##           MENU EDITORAS           ##");
    printf("\n#######################################");
    printf("\n##   1) Cadastrar Editora            ##");
    printf("\n##   2) Listar Editoras              ##");
    printf("\n##   3) Atualizar Dados Editora      ##");
    printf("\n##   0) Voltar                       ##");
    printf("\n#######################################");
    printf("\n\n--> ");

    fflush(stdin);       // Limpar a memoria Buffer do Teclado
    scanf("%i", &opcao); // Obtem o valor da opcao informada pelo usuario
    system("cls");

    switch (opcao)
    {
    case 1:
      cadastrarEditora();
      // para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 2:
      listarEditoras();
      //  para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    case 3:
      atualizarDadosEditora();
      //  para a execucao do programa e aguarda o usuario pressionar alguma tecla para continuar
      system("pause");
      break;

    default:
      break;
    }

  } while (opcao != 0);
}

// Funcao main que sera a principal funcao a ser executada no programa que ira fazer a chamada das demais funcoes
void main()
{
  int opcao;

  do
  {
    system("cls");
    system("color 0f");
    system("title SISTEMA LIVRARIA C/C++");

    printf("\n#######################################");
    printf("\n##           MENU PRINCIPAL          ##");
    printf("\n#######################################");
    printf("\n##     1) Menu de Livros             ##");
    printf("\n##     2) Menu de Autores            ##");
    printf("\n##     3) Menu de Categorias         ##");
    printf("\n##     4) Menu de Editoras           ##");
    printf("\n##     0) Sair                       ##");
    printf("\n#######################################");
    printf("\n\n--> ");

    fflush(stdin);       // Limpar a memoria Buffer do Teclado
    scanf("%i", &opcao); // Obtem o valor da opcao informada pelo usuario
    system("cls");

    switch (opcao)
    {
    case 1:
      menuLivros(); // Chama funcao que desenha o menu de livros
      break;

    case 2:
      menuAutores(); // Chama a funcao que desenha o menu de autores
      break;

    case 3:
      menuCategorias(); // Chama a funcao que desenha o menu de categorias
      break;

    case 4:
      menuEditoras(); // Chama a funcao que desenha o menu de editoras
      break;

    default:
      break;
    }

  } while (opcao != 0);

  system("color 0c");
  system("cls");
  printf("%c Sistema Finalizado %c\n", 158, 158);
}
