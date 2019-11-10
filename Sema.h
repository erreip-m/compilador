#ifndef SEMA
#define SEMA

#include "Erro.h"
#include "Lexer.h"

#include <vector>

namespace compilador {

    // Classe Sema
    class Sema {

        public:

            // Declaração do construtor da classe Sema
            Sema();

            // Declaração da função
            void analisa(Token token);
        
        private:

            // Vetor de ids já usados em declarações
            std::vector<string> idsUsados;

            // Flags para sinalizar o estado semântico
            int flagSentido, flagMova, flagDefinaInstrucao;

            // Declaração de funções

            bool idUsado(string id);
            bool verificaConflitoSentido(string tok);
            bool verificaConflitoMova(string tok);
            bool verificaConflitoId(string tok);


    };

}

#endif