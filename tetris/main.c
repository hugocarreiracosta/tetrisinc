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
    int qtdPeca;
}tela;

typedef struct peca_ {
    int linha;
    int coluna;
    int qtMovimentos;
    char * movimentos;
    int movimentosIndice;
    char ** peca;
}peca;

void alocarMovimentos(peca * p){
    
    //alocando vetor com os movimentos
    p->movimentos = malloc( p->qtMovimentos * sizeof (char) );
    
}

void sleepTela(int segundos){
    sleep(segundos);
    system("clear");
}

void imprimirTela(tela * t, int sleepSeg){

    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            printf("%c", t->tela[i][j]);
        }
        printf("\n");
    }
    
    if(sleepSeg){
        sleepTela(t->sleep);
    }
    else {
        sleepTela(0);
    }
}

void lerAquivo(tela * t, FILE * entrada, peca * p){
    
    int i;
    
    fscanf(entrada, "%d", &t->linha);
    fscanf(entrada, "%d", &t->coluna);
    fscanf(entrada, "%d", &t->sleep);
    fscanf(entrada, "%d", &t->qtdPeca);
    
    for(i = 0; i < t->qtdPeca; i++){
         fscanf(entrada, "%d", &p->coluna);
    
        //condição para a peça não começar fora da tela
        if(p->coluna > t->coluna - 3){
            p->coluna = t->coluna - 3; 
        }
        else if(p->coluna < 0){
            p->coluna = 0;
        }

        fscanf(entrada, " %c %c %c\n", &p->peca[0][0], &p->peca[0][1], &p->peca[0][2]);
        fscanf(entrada, "%c %c %c\n", &p->peca[1][0], &p->peca[1][1], &p->peca[1][2]);
        fscanf(entrada, "%c %c %c", &p->peca[2][0], &p->peca[2][1], &p->peca[2][2]);
        fscanf(entrada, "%d", &p->qtMovimentos);

        alocarMovimentos(p);

        for(i = 0; i < p->qtMovimentos; i++){
            fscanf(entrada, " %c", &p->movimentos[i]); 
        }  
    }
    
    
    
}

void alocarTela(tela * t){
    
    int i;
    
    t->tela = malloc( t->linha * sizeof(char*) );
    for(i = 0; i < t->linha; i++){
        t->tela[i] = malloc( t->coluna * sizeof(char) );
    }
    
}

void desalocarTela(tela * t){
    
    int i;
    
    for(i = 0; i < t->linha; i++){
        free(t->tela[i]);
    }
    free(t->tela);

}

void preencherTela(tela * t){

    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            t->tela[i][j] = '.';
        }
    }

}

void alocarPeca(peca * p){

    int i, j;
    //alocando peça
    p->peca = malloc( 3 * sizeof (char*) );
    for(i = 0; i < 3; i++){
        p->peca[i] = malloc(3 * sizeof(char));
    }
    
}

void desalocarPeca(peca * p){

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

void descerPeca(peca * p, tela * t){
    
    int i, j;
    
    //limpar tela
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = '.';
        }
    }
    
    //descer
    if(p->linha + 1 < t->linha + 1){
        p->linha += 1;
    }
    
    //reinserir peça na tela na nova posição
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = p->peca[i][j];
        }
    }
}

void moverPeca(peca * p, tela * t){
    
    int i, j, moveu = 0, desceu = 0;
    
    //limpar tela
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = '.';
        }
    }
    
    //movimentar
    if(p->movimentos[p->movimentosIndice] == 'd'){ //movimento p/ DIRETA
        if(p->coluna + 1 < t->coluna - 2){ //if para a peça não sair pra fora pela direita
            p->coluna += 1;
        }
        moveu = 1;
    }
    else if(p->movimentos[p->movimentosIndice] == 'e'){ //movimento p/ ESQUERDA
        if(p->coluna - 1 > -1){ //if para a peça não sair pra fora pela esquerda
            p->coluna -= 1;
        }
        moveu = 1;
    }
    else if(p->movimentos[p->movimentosIndice] == 'b'){ //movimento p/ BAIXO
        if(p->linha + 2 < t->linha){ //if para a peça não sair pra fora por baixo
            descerPeca(p, t);
        }
        moveu = 1;
        desceu = 1;
    }
    
    //reinserir peça na tela na nova posição
    for(i = 0; (i < 3 && p->linha + i < t->linha); i++){
        for(j = 0; (j < 3 && p->coluna + j < t->coluna); j++){
            t->tela[p->linha + i][p->coluna + j] = p->peca[i][j];
        }
    }
    
    p->movimentosIndice += 1;
    
    if(moveu == 1 & desceu == 0){
        imprimirTela(t, 1);
    }
    else if(moveu == 1 & desceu == 1){
        imprimirTela(t, 0);
    }
}

void gerarSaida(tela * t, FILE * saida, peca * p){
    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            fprintf(saida, "%c", t->tela[i][j]);
            //fprintf(saida, "\n");
        }
        fprintf(saida, "\n");
    }
    fprintf(saida, "\n");

}

int main(int argc, char** argv) {
    
    int i;
    tela t;
    peca p;
    char quebraLinha[2];
    
    //abrindo arquivo de saida
    FILE *saida;
    saida = fopen("saida.txt", "a");
    
    //lendo entrada em arquivo
    FILE *entrada; 
    entrada = fopen("entrada.txt", "r");
    
    p.movimentosIndice = 0; //sempre começa com zero
    //p.qtMovimentos = 2; //pegar no arquivo txt
    
    //posição atual da peça na tela
    p.linha = 0; //sempre começa com zero
    //p.coluna = 0; //pegar no arquivo txt
    
    //acoes sobre a tela
    alocarPeca(&p);
    lerAquivo(&t, entrada, &p);
    alocarTela(&t);
    preencherTela(&t);
    imprimirTela(&t, 1);
    
    
    //ações sobre a peça
    //p.movimentos[0] = 'd';
    //p.movimentos[1] = 'e';
    //p.movimentos[2] = 'b';
    //p.movimentos[3] = 'e';
    
    //desenhar peca
    inserirPeca(&p, &t);
    imprimirTela(&t, 1);
    
    int descecont = 3;
    
    if((p.peca[2][0] == '.') && (p.peca[2][1] == '.') && (p.peca[2][2] == '.')){
        descecont--;
        if((p.peca[1][0] == '.') && (p.peca[1][1] == '.') && (p.peca[1][2] == '.')){
            descecont --;
            if((p.peca[0][0] == '.') && (p.peca[0][1] == '.') && (p.peca[0][2] == '.')){
                descecont --;
            }
        }
        
        while(p.linha + descecont < t.linha){ //condição de parada para a peça não sair pra fora por baixo
            moverPeca(&p, &t);
            descerPeca(&p, &t);
            imprimirTela(&t, 1);
        }
    }
    else {
        while(p.linha + descecont < t.linha){ //condição de parada para a peça não sair pra fora por baixo
            moverPeca(&p, &t);
            descerPeca(&p, &t);
            imprimirTela(&t, 1);
        }
    }
    
    gerarSaida(&t, saida, &p);
    fclose(saida);
    fclose(entrada);
    
    return (EXIT_SUCCESS);
}