#ifndef ERRO
#define ERRO

#include <iostream>

using std::cout;

namespace compilador {

    // Reporta erro na linha e coluna
    void erro(int numErro, int linha, int coluna) {
        switch (numErro) {
            case 0:
                cout << "\n#ERRO: CARACTERE INVALIDO. LINHA: " << linha << ", COLUNA: " << coluna << "\n\n";
                break;
            case 1:
                cout << "\n#ERRO: NUMERO EXCEDE LIMITE. LINHA: " << linha << ", COLUNA: " << coluna << "\n\n";     
                break;
        }
    }
}

#endif