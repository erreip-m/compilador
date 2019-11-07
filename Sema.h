#ifndef SEMA
#define SEMA

#include "Erro.h"
#include "Lexer.h"

#include <vector>

namespace compilador {

    class Sema {
        public:

            Sema();
            void analisa(std::vector<Token> token);
        
        private:
            std::vector<string> idsUsados;

            bool idUsado(string id);

    };

}

#endif