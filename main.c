#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

/*Funções de exibição*/

   typedef struct {
        int chave_primaria;
        char descricao[100];
        int quantidade;
        float valorCompra;
        float valorVenda;
    } PRODUTO;

void selectLinha(FILE *arquivo,PRODUTO *produto);
void insereTraco(int qtd,int quebraLinha);
void clear();
void exibeTitulo();
void escolhaMenu();
int  geraChavePrimaria();
void selectAll(int mostraMenu);
void gravaProduto(FILE *arquivo, PRODUTO *produto,int geraChavePrimaria);
void buscaProdutoId(int id,PRODUTO *produto);

char nome_arquivo[13] = "produtos.txt"; 

FILE *arquivo;

void insert()
{
    int continua =1;

    while(continua != 2)
    {
        PRODUTO produto;

        printf("\nINSERÇÃO DE PRODUTOS\n");
        insereTraco(20,1);
    
        printf("DESCRIÇÃO (máx 100 caracteres): \t");
        scanf(" %[^\n]",produto.descricao);
        setbuf(stdout, 0);
        fflush(stdout);

        printf("QUANTIDADE: \t");
        scanf("%d",&produto.quantidade);

        printf("VALOR COMPRA (R$) \t");
        scanf("%f",&produto.valorCompra);

        printf("VALOR VENDA (R$) \t");
        scanf("%f",&produto.valorVenda);

        arquivo =  fopen(nome_arquivo,"a+");

        gravaProduto(arquivo,&produto,1);

        insereTraco(20,1);
        printf("Continuar cadastrando?\n 1\t SIM\n 2 \t NÃO\n");
        scanf("%d",&continua);

        fclose(arquivo);
    }

    escolhaMenu();
}

void gravaProduto(FILE *arquivo, PRODUTO *produto,int gerarChavePrimaria)
{
    int chavaPrimaria;
    if (gerarChavePrimaria)
    chavaPrimaria = geraChavePrimaria();
    else 
    chavaPrimaria = produto->chave_primaria;

    fprintf(arquivo,"%d; %s; %d; %.2f; %.2f\n",chavaPrimaria,produto->descricao,produto->quantidade,produto->valorCompra,produto->valorVenda);
    fflush(arquivo);
}

void update()
{
    int idProduto, opcao;
    PRODUTO produto;
    exibeTitulo();
    selectAll(0);
    printf("\n\n\nINSIRA O ID DO PRODUTO QUE SEJA ALTERAR: \t");
    scanf("%d",&idProduto);
    printf("\nINFORMAÇÃO QUE SERÁ ATUALIZADA\n");
    insereTraco(20,1);
    printf("1- DESCRIÇÃO\n2- VALOR DE COMPRA\n3- VALOR DE VENDA\n4- QUANTIDADE\n");
    scanf("%d",&opcao);

    buscaProdutoId(idProduto,&produto);

    if (opcao == 1)
    {
        printf("Nova descrição:\t");
        scanf(" %[^\n]",produto.descricao);
    }

    else if (opcao ==2)
    {
        printf("Novo valor de compra:\t");
        scanf("%f",&produto.valorCompra);
    }

    else  if (opcao ==3)
    {
        printf("Novo valor de venda:\t");
        scanf("%f",&produto.valorVenda);
    }
        
    else if (opcao == 4)
    {
        printf("Nova quantidade:\t");
        scanf("%d",&produto.quantidade);
    }


    delete(idProduto);
   
    arquivo = fopen(nome_arquivo,"a+");
    gravaProduto(arquivo,&produto,0);
    fclose(arquivo);
    insereTraco(20,1);
    printf("PRODUTO ATUALIZADO\n");
    insereTraco(20,1);
    printf("ID: %d\nDescrição: %s \nQuantidade: %d\nValor compra: %.2f\nValor venda: %.2f\n", produto.chave_primaria,produto.descricao,produto.quantidade,produto.valorCompra,produto.valorVenda);

    escolhaMenu();
}

void delete(int id)
{
    exibeTitulo();

    int idProduto = id;
    int tamanhoArray = 0;
    PRODUTO *produtos = (PRODUTO*)calloc(0,sizeof(PRODUTO));
    PRODUTO produto;

    if (id == 0)
    {
        selectAll(0);
        printf("INSIRA O ID DO PRODUTO QUE DESEJA EXCLUIR: \t");
        scanf("%d",&idProduto);
        insereTraco(20,1);
    }

    arquivo = fopen(nome_arquivo,"r+");

    while(!feof(arquivo))
    {
       PRODUTO produto;
       selectLinha(arquivo,&produto);
       tamanhoArray++;
       produtos = (PRODUTO*) realloc(produtos, tamanhoArray*sizeof(PRODUTO));
       produtos[tamanhoArray-1] = produto;
    } 

        
    fclose(arquivo);

    arquivo = fopen(nome_arquivo,"w+");
     for (int i=0;i<tamanhoArray;i++)
     {
         produto = produtos[i];

         if (produto.chave_primaria != idProduto)
         {
              gravaProduto(arquivo,&produto,0);
         }
     }  

      fclose(arquivo); 

    if (id == 0)
    selectAll(1);

}    
    
//Falta implementação - Busca com filtro
void selectWith()
{
    exibeTitulo();

}

void buscaProdutoId(int id,PRODUTO *produto)
{
    PRODUTO produtoLocal;  
    arquivo = fopen(nome_arquivo,"r+");
    while(!feof(arquivo))
    {
    selectLinha(arquivo,&produtoLocal);
    if (produtoLocal.chave_primaria == id)
       break;
    }
    fclose(arquivo); 
    *produto = produtoLocal;
}
void selectAll(int mostraMenu)
{
    arquivo = fopen(nome_arquivo,"r");
    int qtdProduto = 1;
    PRODUTO produto;

if (tamanhoArquivo(nome_arquivo) == 0)
{
    
    printf("\n\nALERTA: ARQUIVO VAZIO. INSIRA INFORMAÇÕES NO MENU ABAIXO\a\n\n\n"); 
    
}
else
{
   while(!feof(arquivo))
     {
    
     selectLinha(arquivo,&produto);
    
     printf("\nProduto %d\n",qtdProduto);
 
     insereTraco(20,1);

    printf("ID: %d\nDescrição: %s \nQuantidade: %d\nValor compra: %.2f\nValor venda: %.2f\n", produto.chave_primaria,produto.descricao,produto.quantidade,produto.valorCompra,produto.valorVenda);
     qtdProduto++;

     }
}

    if (mostraMenu)
        escolhaMenu();

    fclose(arquivo);
    
}

void escolhaMenu(void)
{
    int opcao;

    exibeTitulo();
    printf("\nOPÇÕES\n");
    insereTraco(38,1);

    printf("| 1 |\tInserção\n");
    insereTraco(38,1);
    printf("| 2 |\tDeleção\n");
    insereTraco(38,1);
    printf("| 3 |\tAtualização\n");
    insereTraco(38,1);
    printf("| 4 |\tExibir todos\n");
     /*printf("| 5 |\tBusca por filtro\n");
    insereTraco(38,1);*/ //falta a implementação
    insereTraco(38,1);

    scanf("%d",&opcao);
    clear();

    switch(opcao)
    {
        case 1: insert();break;
        case 2: delete(0);break;
        case 3: update();break;
        case 4: selectAll(1);break;
        //case 5: selectWith(1);break; falta a implementação
        default: exit(0);
    }
}

int main ()
{
    system("chcp 65001"); //atualizar padrão para UTF8
    setlocale(LC_ALL, "Portuguese_Brasil");

    escolhaMenu();

   return 0;
}

/*Funções para exibição*/

void insereTraco(int qtd,int quebraLinha)
{
    int i;

    for(i=0;i<qtd;i++)
    {
        printf("-");
    }

if (quebraLinha == 1)
    printf("\n");
}

void clear()
{
       #if defined(__linux__) || defined(__unix__) || defined(__Apple__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
void exibeTitulo()
{
    insereTraco(38,1);
    printf("SISTEMA DE GERENCIAMENTO PARA ESTOQUE\n");
    insereTraco(38,1);
}

int quantidadeDeLinhas()
{
    arquivo = fopen(nome_arquivo,"r");
    int qtdLinha; 

     while(!feof(arquivo))
     {
         if (fgetc(arquivo) == '\n')
            qtdLinha ++;
     }

     return  qtdLinha + 1;
}

int tamanhoArquivo(const char* file_name)
{
    FILE *file = fopen(file_name, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;

    fclose(file);
}


void selectLinha(FILE *arquivo,PRODUTO *produto)
{
    fscanf(arquivo, "%d;%[^;];%d;%f;%f\n",&produto->chave_primaria,&produto->descricao,&produto->quantidade,&produto->valorCompra,&produto->valorVenda);
}

int geraChavePrimaria()
{
    PRODUTO produto;
    FILE * arquivo;
    
    arquivo = fopen(nome_arquivo,"r");

    if (tamanhoArquivo(nome_arquivo) == 0)
    {
        return 1;
    }

     while(!feof(arquivo))
     {
       selectLinha(arquivo, &produto);
     }

    fclose(arquivo);

    return produto.chave_primaria + 1;

}