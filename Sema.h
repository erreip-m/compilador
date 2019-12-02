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
            bool analisa(Token tokenAtual, Token tokenAnterior);
        
        private:

            // Vetor de ids já usados em declarações
            std::vector<string> idsUsados;

            // Flags para sinalizar o estado semântico
            int flagSentido, flagMova, flagDefinaInstrucao;

            // Declaração de funções

            bool idUsado(string id);
            bool verificaConflitoSentido(Token tok);
            bool verificaConflitoMova(Token tok);
            bool verificaConflitoId(Token tok);


    };

}

#endif