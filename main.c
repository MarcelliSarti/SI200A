#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

/*Funções de exibição*/

void insereTraco(int qtd,int quebraLinha);
void clear();
void exibeTitulo();

FILE *arquivo;

   typedef struct {
        char descricao[100];
        int quantidade;
        float valorCompra;
        float valorVenda;
    } PRODUTO;

void insert()
{
    int continua =1;
    int tamanhoArray = 0;

    PRODUTO *produto = (PRODUTO*)malloc(sizeof(PRODUTO));

    while(continua != 2)
    {

    printf("\nINSERÇÃO DE PRODUTOS\n");
    insereTraco(20,1);

    printf("DESCRIÇÃO (máx 100 caracteres): \t");
    scanf("%s",&produto[tamanhoArray].descricao);

    printf("QUANTIDADE: \t");
    scanf("%d",&produto[tamanhoArray].quantidade);

    printf("VALOR COMPRA (R$) \t");
    scanf("%f",&produto[tamanhoArray].valorCompra);

    printf("VALOR VENDA (R$) \t");
    scanf("%f",&produto[tamanhoArray].valorVenda);

    tamanhoArray++;
    produto = (PRODUTO*) realloc(produto,tamanhoArray);
  
    insereTraco(20,1);
    printf("Continuar cadastrando?\n 1\t SIM\n 2 \t NÃO\n");
    scanf("%d",&continua);

    }

    arquivo = fopen("produtos.txt","a+");
  
    for (int i=0;i<tamanhoArray;i++)
    {
        if (i==tamanhoArray-1)
        fprintf(arquivo,"%s %d %.2f %.2f",produto[i].descricao,produto[i].quantidade,produto[i].valorCompra,produto[i].valorVenda);
        else
         fprintf(arquivo,"%s %d %.2f %.2f\n",produto[i].descricao,produto[i].quantidade,produto[i].valorCompra,produto[i].valorVenda);

        fflush(arquivo);
    }

    fclose(arquivo);

    escolhaMenu();
}

void update()
{
    exibeTitulo();
}

void delete()
{
    exibeTitulo();
}

void selectWith()
{
    exibeTitulo();
}
void selectAll()
{
    arquivo = fopen("produtos.txt","r");
    int qtdProduto = 1;
    PRODUTO produto;

     while(!feof(arquivo))
     {
     fscanf(arquivo,"%s %d %f %f",produto.descricao,&produto.quantidade,&produto.valorCompra,&produto.valorVenda);
     
     printf("\nProduto %d\n",qtdProduto);
     insereTraco(20,1);

     qtdProduto++;

     printf("Descrição: %s\nQuantidade: %d\nValor compra: %.2f\nValor venda: %.2f\n",produto.descricao,produto.quantidade,produto.valorCompra,produto.valorVenda);
     }

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
    printf("| 4 |\tBusca por filtro\n");
    insereTraco(38,1);
    printf("| 5 |\tInventário\n");
    insereTraco(38,1);

    scanf("%d",&opcao);
    clear();

    switch(opcao)
    {
        case 1: insert();break;
        case 2: delete();break;
        case 3: update();break;
        case 4: selectWith();break;
        case 5: selectAll();break;
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