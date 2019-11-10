#ifndef ERRO
#define ERRO

#include <iostream>

using namespace std;;


// Reporta erro na linha e coluna
void erro(int numErro, int linha, int coluna) {
    switch (numErro) {
        case 0:
            cout << "\n#ERRO LEXICO: CARACTERE INVALIDO. LINHA: " << linha << ", COLUNA: " << coluna << "\n\n";
            break;
        case 1:
            cout << "\n#ERRO LEXICO: NUMERO EXCEDE LIMITE. LINHA: " << linha << ", COLUNA: " << coluna << "\n\n";     
            break;
        case 2:
            cout << "\n#ERRO SINTATICO: EXPRESSAO MAL FORMADA. LINHA: " << linha << ", COLUNA: " << coluna << "\n\n";     
            break;
        case 3:
            cout << "\n#ERRO SEMANTICO: IDENTIFICADOR PREVIAMENTE USADO EM OUTRA DEFINICAO. LINHA: " << linha << ", COLUNA: " << coluna << "\n\n";
            break;
        case 4:
            cout << "\n#ERRO SEMANTICO: INSTRUCAO \"MOVA\" NAO SUCEDIDA POR \"AGUARDE ATE ROBO PRONTO\". LINHA: " << linha << ", COLUNA: " << coluna << "\n\n"; 
            break;
        case 5:
            cout << "\n#ERRO SEMANTICO: VIRAR PARA SENTIDOS DIFERENTES SEGUIDAMENTE. LINHA: " << linha << ", COLUNA: " << coluna << "\n\n";
            break;
    }
}

#endif