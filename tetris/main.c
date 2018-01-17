/* 
 * File:   main.c
 * Author: Hugo Carreira Costa e Wendell Ávila
 *
 * Created on 16 de Janeiro de 2018, 12:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct tela_ {
    int linha;
    int coluna;
    int sleep;
    char ** tela;
}tela;

typedef struct peca_ {
    int linha;
    int coluna;
    int qtMovimentos;
    char ** peca;
    char * movimentos;
    int movimentosIndice;
}peca;

void sleepTela(int segundos){
    sleep(segundos);
    system("clear");
}

void imprimirTela(tela * t){

    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            printf("%c", t->tela[i][j]);
        }
        printf("\n");
    }
    
    sleepTela(t->sleep);
}

void leDimensoes(tela * t){

    t->linha = 10;
    t->coluna = 20;

}

void alocaTela(tela * t){
    
    int i;
    
    t->tela = malloc( t->linha * sizeof(char*) );
    for(i = 0; i < t->linha; i++){
        t->tela[i] = malloc( t->coluna * sizeof(char) );
    }
    
}

void desalocaTela(tela * t){
    
    int i;
    
    for(i = 0; i < t->linha; i++){
        free(t->tela[i]);
    }
    free(t->tela);

}

void preencheTela(tela * t){

    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            t->tela[i][j] = '.';
        }
    }

}

void alocaPeca(peca * p){

    int i, j;
    
    //alocando vetor com os movimentos
    p->movimentos = malloc( p->qtMovimentos * sizeof (char) );
    
    //alocando peça
    p->peca = malloc( 3 * sizeof (char*) );
    for(i = 0; i < 3; i++){
        p->peca[i] = malloc(3 * sizeof(char));
    }
    
}

void desalocaPeca(peca * p){

    int i;
    
    //desalocando vetor dos movimentos
    free(p->movimentos);
    
    //desalocando peça
    for(i = 0; i < 3; i++){
        free(p->peca[i]);
    }
    free(p->peca);
    
}

void inserirPeca(peca *p, tela *t){
    
    int i, j;
    
    //inserindo peça na tela
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            t->tela[p->linha + i][p->coluna + j] = p->peca[i][j];
        }
    }
}

// funcoes acima ja foram revisadas

void movimentaPeca(peca * p, tela * t){
    
    int i, j, movimento = 0;
    
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = '.';
        }
    }
    
    if(p->movimentos[p->movimentosIndice] == 'd'){
        if(p->coluna + 1 < t->coluna - 2){ //if para a peça não sair pra fora pela direita
            p->coluna += 1;
        }
        movimento = 1;
    }
    else if(p->movimentos[p->movimentosIndice] == 'e'){ 
        if(p->coluna - 1 > -1){ //if para a peça não sair pra fora pela esquerda
            p->coluna -= 1;
        }
        movimento = 1;
    }
    
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = p->peca[i][j];
        }
    }
    
    p->movimentosIndice += 1;
    
    if(movimento){
        imprimirTela(t);
    }
}

void descePeca(peca * p, tela * t){
    int i, j;
    
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = '.';
        }
    }
    
    if(p->linha + 1 < t->linha + 1){
        p->linha += 1;
    }
    
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = p->peca[i][j];
        }
    }
}

int main(int argc, char** argv) {
    
    int i;
    tela t;
    peca p;
    
    t.sleep = 1;
    p.movimentosIndice = 0;
    p.qtMovimentos = 3;
    
    //posição atual da peça na tela
    p.linha = 0; //sempre começa com zero
    p.coluna = 0; //pegar no arquivo txt
    
    //acoes sobre a tela
    leDimensoes(&t);
    alocaTela(&t);
    preencheTela(&t);
    imprimirTela(&t);
    
    //acoes sobre a peça
    alocaPeca(&p);
    p.movimentos[0] = 'd';
    p.movimentos[1] = 'e';
    p.movimentos[2] = 'd';
    
    //desenhar peca
    p.peca[0][0] = '#';
    p.peca[0][1] = '#';
    p.peca[0][2] = '#';
    p.peca[1][0] = '.';
    p.peca[1][1] = '.';
    p.peca[1][2] = '#';
    p.peca[2][0] = '.';
    p.peca[2][1] = '.';
    p.peca[2][2] = '.';
    
    inserirPeca(&p, &t);
    imprimirTela(&t);
    
    while(p.linha + 2 < t.linha){ //condição de parada para a peça não sair pra fora por baixo
        movimentaPeca(&p, &t);
        descePeca(&p, &t);
        imprimirTela(&t);
    }
    
   
    return (EXIT_SUCCESS);
}