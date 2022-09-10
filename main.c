/*
O famoso jogo da Torre de Hanói é um "quebra-cabeça" que consiste em uma base contendo três pinos, em um dos quais são dispostos alguns discos uns sobre os outros, em ordem crescente de diâmetro, de cima para baixo.

Objetivo: mover todos os discos para o pino da direita.

Regras: clicando e arrastando com o mouse, você deve mover um disco de cada vez, sendo que um disco maior nunca pode ficar em cima de um disco menor.
*/


/*
Padrão de movimento com 3 discos -> move o menor para o alvo, o segundo menor para o auxiliar, o menor para o auxiliar, o terceiro menor para o alvo, o menor para o inicial, o segundo menor para o alvo, o menor para o alvo

Padrão de movimento com 4 discos -> menor pra torre 2, segundo menor pra torre alvo, menor pra torre alvo, terceira menor pra torre 2, menor pra torre 1, segundo menor pra torre 2, menor pra torre 2, quarto menor pra torre alvo, menor pra torre alvo, segundo maior pra torre 1, menor pra torre 1, terceira menor pra torre alvo, menor pra torre 2, segunda menor pra torre alvo, menor pra torre alvo

Numero de mov minimo = dobro + 1 do anterior
*/

#include <stdio.h>
#include <stdlib.h>

int idIndex = 1;

typedef struct
{
  int valor;
} disco;

struct pilha
{
  disco *discos;
  //int *discos;
  disco top;
  int count;
  int id;
};

struct pilha* novaPilha(int tamanho)
{
    struct pilha *pi = (struct pilha*)malloc(sizeof(struct pilha *) + tamanho * sizeof(disco));
  
    //pilha->top = -1;
    pi->discos = (disco*)malloc(sizeof(disco) + tamanho * sizeof(disco));
    pi->id = idIndex;
    pi->count = 0;
    idIndex = idIndex + 1;
 
    return pi;
}
void push(struct pilha *pilha, disco disco);
disco pop(struct pilha *pilha);
int peek(struct pilha *pilha);
int isEmpty(struct pilha *pilha);
void preenche_torre(struct pilha *pilha, disco *arrayDiscos, int tamanho);
void tentar_mover(struct pilha *pilha, struct pilha *pilhaAlvo);
int verificar_vitoria(struct pilha *pilha, int tamanho);

int main(int argc, char *argv[ ]) 
{ 
  int tamanho = atoi(argv[1]);

  struct pilha *torre1 = novaPilha(tamanho);
  struct pilha *torre2 = novaPilha(tamanho);
  struct pilha *torre3 = novaPilha(tamanho);

  // Fazer interfacezinha
  // Mover codigo da main para funcoes aparte

  disco discos[tamanho];

  printf("---ARRAYDISCOS---\n");
  for(int i = 0; i < tamanho; i++)
  {
    disco temp;
    temp.valor = i+1;
    discos[(tamanho-1) - i] = temp;
    printf("%d\n", discos[(tamanho-1)-i].valor);
  }

  for(int i = 0; i < tamanho; i++)
  {
    printf("%d[%d]\n", discos[i].valor,i);
  }
  printf("------------\n");

  preenche_torre(torre1,discos,tamanho);

  tentar_mover(torre1,torre2);
  tentar_mover(torre1,torre2);

  printf("\nVerificação: %s\n",verificar_vitoria(torre3, tamanho) == 1 ? "Pilha preenchida corretamente!" : "Pilha3 falta disco(s)");
  
  free(torre1);
  free(torre2);
  free(torre3);
}

void tentar_mover(struct pilha *pilha, struct pilha *pilhaAlvo)
{
  if(isEmpty(pilhaAlvo))
  {
    push(pilhaAlvo,pop(pilha));
    printf("Disco %d movido para pilha%d\n", peek(pilhaAlvo), pilhaAlvo->id);
    return;
  }

  if(peek(pilhaAlvo) > peek(pilha))
  {
    push(pilhaAlvo,pop(pilha));
    printf("Disco %d movido para pilha%d\n", peek(pilhaAlvo), pilhaAlvo->id);
    return;
  }


  printf("Não foi possível mover. Disco no topo da torre alvo -> %d\n", peek(pilhaAlvo));
}

int verificar_vitoria(struct pilha *pilha,int tamanho)
{
  struct pilha temp = *pilha;
  // temp.discos = pilha->discos;
  // temp.top = pilha->top;
  // temp.count = pilha->count;
  temp.id = pilha->id+1;

  int contagemDePops = 0;
  
  for(int i = 0; i < pilha->count; i++)
  {
    pop(&temp);
    contagemDePops+=1;
  }

  printf("contagemDePops = %d, Tamanho = %d\n", contagemDePops, tamanho);

  if(contagemDePops == tamanho)
  {
    return 1;
  }

  return 0;
}

int peek(struct pilha *pilha)
{
  return pilha->top.valor;
}

int isEmpty(struct pilha *pilha)
{
  return pilha->count <= 0;
}

void preenche_torre(struct pilha *pilha, disco *arrayDiscos,int tamanho)
{
  printf("\n---PREENCHENDO TORRE INICIAL---");
  for(int i = 0; i < tamanho; i++)
  {
    push(pilha,arrayDiscos[i]);
    printf("Inserido: disco %d em pilha%d\n", arrayDiscos[i].valor, pilha->id);
  }

  printf("-------------------------------\n");
  printf("\n");
}

void push(struct pilha *pilha, disco disco)
{
  pilha->top = disco;
  pilha->discos[pilha->count] = disco;
  printf("\nPushed disco %d para pilha%d\n",pilha->discos[pilha->count].valor, pilha->id);
  pilha->count+=1;
}

disco pop(struct pilha *pilha)
{
  if(isEmpty(pilha))
  {
    disco nulo;
    return nulo;
  }

  disco temp = pilha->top;
  
  printf("Disco %d POPPADO de pilha%d!\n",pilha->top.valor, pilha->id);

  pilha->top = pilha->discos[pilha->count-2];
  pilha->count-=1;

  return temp;
}