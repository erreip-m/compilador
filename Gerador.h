// INCOMPLETO

#ifndef GERADOR
#define GERADOR

#include "Lexer.h"

namespace compilador {

    // Classe Gerador
    class Gerador {

        public:

            // Declaração do construtor da classe Gerador
            Gerador(FILE* arquivo);

            // Declaração da função
            static void geraCodigo(Token token);
        
        private:

            // Ponteiro pro arquivo que vai conter o código gerado
            FILE* arquivoGerado;
    };

}

#endif