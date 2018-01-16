/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
    int linhainicial;
    int colunainicial;
    int linha;
    int coluna;
    int sleep;
    char ** tela;
}tela;

typedef struct peca_ {
    int linha;
    int coluna;
    int iMovimento;
    int qtMovimento;
    char ** peca;
    char * movimentos;
}peca;

void espera(int segundos){
    sleep(segundos);
}

void imprimeTela(tela * t, int debug){
    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            printf("%c", t->tela[i][j]);
        }
        printf("\n");
    }
    if(!debug){
        espera(t->sleep);
    }
    else {
        espera(debug);
    }
    system("clear");
}

void leDimensoes(tela * t){
    //printf("Informe o tamanho da tela (x, y): ");
    //scanf("%d %d", &t->x, &t->y);
    t->linha = 10;
    t->coluna = 20;
    
    t->linhainicial = t->linha;
    t->colunainicial = t->coluna;
}

void alocaTela(tela * t){
    int i;
    
    t-> tela = malloc(t->linha * sizeof(char*));
    
    for(i = 0; i < t->linha; i++){
        t->tela[i] = malloc(t->coluna * sizeof(char));
    }
    
}

void desalocaTela(tela * t){
    int i;
    
    for(i = 0; i < t->linha; i++){
        free(t->tela[i]);
    }
    free(t->tela);
}

void iniciaTela(tela * t){
    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            t->tela[i][j] = '.';
        }
    }
}

void alocaPeca(peca * p, int movimentos){
    int i, j;
    p->qtMovimento = movimentos;
    
    p->movimentos = malloc(p->qtMovimento * sizeof (char));
    
    for(i = 0; i < p->qtMovimento; i++){
        p->movimentos[i] = ' ';
    }
    
    p->peca = malloc(3 * sizeof (char*));
    
    for(i = 0; i < 3; i++){
        p->peca[i] = malloc(3 * sizeof(char));
    }
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            p->peca[i][j];
        }
    }
    
}

void desalocaPeca(peca * p){
    int i;
    
    free(p->movimentos);
    
    for(i = 0; i < 3; i++){
        free(p->peca[i]);
    }
    
    free(p->peca);
}

void inserePeca(peca *p, tela *t){
    int i, j;
    //desenhando a peca inicialmente
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            t->tela[p->linha + i][p->coluna + j] = p->peca[i][j];
        }
    }
}

int movimentaPeca(peca * p, tela * t){
    int i, j;
    int movimentou = 0;
    
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = '.';
        }
    }
    
    if(p->movimentos[p->iMovimento] == 'd'){
        if(p->coluna + 1 < t->colunainicial + 1){ //if para a peça não sair pra fora pela direita
        
        }
        p->coluna += 1;
        movimentou = 1;
    }
    else if(p->movimentos[p->iMovimento] == 'e'){ //if para a peça não sair pra fora pela esquerda
        if(p->coluna - 1 > -1){
            p->coluna -= 1;
        }
        movimentou = 1;
    }
    
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = p->peca[i][j];
        }
    }
    
    p->iMovimento += 1;
    
    return movimentou;
}

void descePeca(peca * p, tela * t){
    int i, j;
    
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = '.';
        }
    }
    
    if(p->linha + 1 < t->linhainicial + 1){
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
    t.sleep = 1;
    
    peca p;
    
    p.linha = 0;
    p.iMovimento = 0;
    
    //acoes sobre a tela
    leDimensoes(&t);
    
    alocaTela(&t);
    iniciaTela(&t);
    
    imprimeTela(&t, 0);
    
    //acoes sobre a peça
    alocaPeca(&p, 10);
    p.movimentos[0] = 'd';
    p.movimentos[1] = 'e';
    p.movimentos[2] = 'd';
    p.peca[0][0] = '#';
    p.peca[0][1] = '#';
    p.peca[0][2] = '#';
    p.peca[1][0] = '.';
    p.peca[1][1] = '.';
    p.peca[1][2] = '#';
    p.peca[2][0] = '.';
    p.peca[2][1] = '.';
    p.peca[2][2] = '.';
    
    inserePeca(&p, &t);
    imprimeTela(&t, 0);
    
    while(p.linha + 2 < t.linha){
        if(movimentaPeca(&p, &t)){
            imprimeTela(&t, 0);
            descePeca(&p, &t);
            imprimeTela(&t, 0);
        }
        else {
            descePeca(&p, &t);
            imprimeTela(&t, 0);
        }
        
    }
    
    

    return (EXIT_SUCCESS);
}

