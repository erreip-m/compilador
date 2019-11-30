#ifndef PARSER
#define PARSER

#include "Lexer.h"
#include "Sema.h"

#include <map>
#include <stack>
#include <utility>

namespace compilador {

    // Classe Parser
    class Parser {

        public:

            // Declaração do construtor da classe Parser
            Parser(char* buffer);

            // Declaração da função
            void analisa();

        private:

            // Variaveis para guardar informação do Parser

            std::stack<std::string> pilha;

            Token* tokenAtual, *tokenAnterior;
            Lexer* lexer;
            Sema* sema;

            static std::map<std::pair<std::string, std::string>, std::vector<std::string>> tabela;

            // Declaração de funções

            bool terminal(std::string palavra); 
            bool instrucaoValida();
            void proximoToken();
            void obterInstrucao();

    };

    // Inicialização da tabela
    std::map<std::pair<std::string, std::string>, std::vector<std::string>> Parser::tabela {
        {{"PROGRAMA", "PROGRAMAINICIO"}, {"PROGRAMAINICIO", "DECLARACAO'", "EXECUCAOINICIO", "COMANDO", "FIMEXECUCAO", "FIMPROGRAMA"}},

        {{"DECLARACAO", "DEFINAINSTRUCAO"}, {"DEFINAINSTRUCAO", "IDENTIFICADOR", "COMO", "COMANDO"}},

        {{"DECLARACAO'", "DEFINAINSTRUCAO"}, {"DECLARACAO", "DECLARACAO'"}},
        {{"DECLARACAO'", "EXECUCAOINICIO"}, {"&"}},

        {{"COMANDO","LAMPADA APAGADA A DIREITA"}, {{"INSTRUCAO"}}},
        {{"COMANDO","LAMPADA ACESA A DIREITA"}, {{"INSTRUCAO"}}},
        {{"COMANDO","LAMPADA APAGADA A ESQUERDA"}, {"INSTRUCAO"}},
        {{"COMANDO","LAMPADA ACESA A ESQUERDA"}, {"INSTRUCAO"}},
        {{"COMANDO","LAMPADA APAGADA A FRENTE"}, {"INSTRUCAO"}},
        {{"COMANDO","LAMPADA ACESA A FRENTE"}, {"INSTRUCAO"}},
        {{"COMANDO","ESQUERDA ROBO BLOQUEADA"}, {"INSTRUCAO"}},
        {{"COMANDO","DIREITA ROBO BLOQUEADA"}, {"INSTRUCAO"}},
        {{"COMANDO","FRENTE ROBO BLOQUEADA"}, {"INSTRUCAO"}},
        {{"COMANDO","ROBO MOVIMENTANDO"}, {"INSTRUCAO"}},
        {{"COMANDO","ROBO PARADO"}, {"INSTRUCAO"}},
        {{"COMANDO","ROBO OCUPADO"}, {"INSTRUCAO"}},
        {{"COMANDO","ROBO PRONTO"}, {"INSTRUCAO"}},
        {{"COMANDO","AGUARDE ATE"}, {"INSTRUCAO"}},
        {{"COMANDO","ACENDA LAMPADA"}, {"INSTRUCAO"}},
        {{"COMANDO","APAGUE LAMPADA"}, {"INSTRUCAO"}},
        {{"COMANDO","FINALIZE"}, {"INSTRUCAO"}},
        {{"COMANDO","PARE"}, {"INSTRUCAO"}},
        {{"COMANDO","IDENTIFICADOR"}, {"INSTRUCAO"}},
        {{"COMANDO","VIRE PARA"}, {"INSTRUCAO"}},
        {{"COMANDO","MOVA"}, {"INSTRUCAO"}},
        {{"COMANDO","SE"}, {"CONDICIONAL"}},
        {{"COMANDO","EQUANTO"}, {"LACO"}},
        {{"COMANDO","REPITA"}, {"ITERACAO"}},
        {{"COMANDO","INICIO"}, {"BLOCO"}},

        {{"COMANDO'","LAMPADA APAGADA A DIREITA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","LAMPADA ACESA A DIREITA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","LAMPADA APAGADA A ESQUERDA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","LAMPADA ACESA A ESQUERDA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","LAMPADA APAGADA A FRENTE"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","LAMPADA ACESA A FRENTE"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","ESQUERDA ROBO BLOQUEADA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","DIREITA ROBO BLOQUEADA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","FRENTE ROBO BLOQUEADA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","ROBO MOVIMENTANDO"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","ROBO PARADO"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","ROBO OCUPADO"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","ROBO PRONTO"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","AGUARDE ATE"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","ACENDA LAMPADA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","APAGUE LAMPADA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","FINALIZE"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","PARE"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","IDENTIFICADOR"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","VIRE PARA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","MOVA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","SE"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","EQUANTO"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","REPITA"}, {"COMANDO", "COMANDO'"}},
        {{"COMANDO'","FIM"}, {"&"}},
        {{"COMANDO'","INICIO"}, {"COMANDO", "COMANDO'"}},

        {{"BLOCO","INICIO"}, {"INICIO", "COMANDO'", "FIM"}},

        {{"ITERACAO","REPITA"}, {"REPITA", "NUMERO", "VEZES'", "COMANDO", "FIMREPITA"}},

        {{"VEZES'","VEZES"}, {"VEZES"}},
        {{"VEZES'","VEZ"}, {"VEZ"}},

        {{"LACO","ENQUANTO"}, {"ENQUANTO", "CONDICAO", "FACA", "COMANDO", "FIMPARA"}},

        {{"CONDICIONAL","SE"}, {"SE", "CONDICAO", "ENTAO", "COMANDO", "FIMSE", "SENAO'"}},

        {{"SENAO'","SENAO"}, {"SENAO", "COMANDO", "FIMSENAO"}},
        {{"SENAO'","LAMPADA APAGADA A DIREITA"}, {"&"}},
        {{"SENAO'","LAMPADA ACESA A DIREITA"}, {"&"}},
        {{"SENAO'","LAMPADA APAGADA A ESQUERDA"}, {"&"}},
        {{"SENAO'","LAMPADA ACESA A ESQUERDA"}, {"&"}},
        {{"SENAO'","LAMPADA APAGADA A FRENTE"}, {"&"}},
        {{"SENAO'","LAMPADA ACESA A FRENTE"}, {"&"}},
        {{"SENAO'","ESQUERDA ROBO BLOQUEADA"}, {"&"}},
        {{"SENAO'","DIREITA ROBO BLOQUEADA"}, {"&"}},
        {{"SENAO'","ROBO MOVIMENTANDO"}, {"&"}},
        {{"SENAO'","ROBO PARADO"}, {"&"}},
        {{"SENAO'","ROBO OCUPADO"}, {"&"}},
        {{"SENAO'","ROBO PRONTO"}, {"&"}},
        {{"SENAO'","AGUARDE ATE"}, {"&"}},
        {{"SENAO'","ACENDA LAMPADA"}, {"&"}},
        {{"SENAO'","APAGUE LAMPADA"}, {"&"}},
        {{"SENAO'","FINALIZE"}, {"&"}},
        {{"SENAO'","PARE"}, {"&"}},
        {{"SENAO'","IDENTIFICADOR"}, {"&"}},
        {{"SENAO'","VIRE PARA"}, {"&"}},
        {{"SENAO'","MOVA"}, {"&"}},
        {{"SENAO'","FIMSENAO"}, {"&"}},
        {{"SENAO'","FIMSE"}, {"&"}},
        {{"SENAO'","SE"}, {"&"}},
        {{"SENAO'","FIMPARA"}, {"&"}},
        {{"SENAO'","ENQUANTO"}, {"&"}},
        {{"SENAO'","FIMREPITA"}, {"&"}},
        {{"SENAO'","REPITA"}, {"&"}},
        {{"SENAO'","FIM"}, {"&"}},
        {{"SENAO'","INICIO"}, {"&"}},
        {{"SENAO'","DEFINAINSTRUCAO"}, {"&"}},
        {{"SENAO'","FIMEXECUCAO"}, {"&"}},
        {{"SENAO'","EXECUCAOINICIO"}, {"&"}},

        {{"INSTRUCAO","LAMPADA APAGADA A DIREITA"}, {"CONDICAO"}},
        {{"INSTRUCAO","LAMPADA ACESA A DIREITA"}, {"CONDICAO"}},
        {{"INSTRUCAO","LAMPADA APAGADA A ESQUERDA"}, {"CONDICAO"}},
        {{"INSTRUCAO","LAMPADA ACESA A ESQUERDA"}, {"CONDICAO"}},
        {{"INSTRUCAO","LAMPADA APAGADA A FRENTE"}, {"CONDICAO"}},
        {{"INSTRUCAO","LAMPADA ACESA A FRENTE"}, {"CONDICAO"}},
        {{"INSTRUCAO","ESQUERDA ROBO BLOQUEADA"}, {"CONDICAO"}},
        {{"INSTRUCAO","DIREITA ROBO BLOQUEADA"}, {"CONDICAO"}},
        {{"INSTRUCAO","FRENTE ROBO BLOQUEADA"}, {"CONDICAO"}},
        {{"INSTRUCAO","ROBO MOVIMENTANDO"}, {"CONDICAO"}},
        {{"INSTRUCAO","ROBO PARADO"}, {"CONDICAO"}},
        {{"INSTRUCAO","ROBO OCUPADO"}, {"CONDICAO"}},
        {{"INSTRUCAO","ROBO PRONTO"}, {"CONDICAO"}},
        {{"INSTRUCAO","AGUARDE ATE"}, {"AGUARDE ATE"}},
        {{"INSTRUCAO","ACENDA LAMPADA"}, {"ACENDA LAMPADA"}},
        {{"INSTRUCAO","APAGUE LAMPADA"}, {"APAGUE LAMPADA"}},
        {{"INSTRUCAO","FINALIZE"}, {"FINALIZE"}},
        {{"INSTRUCAO","PARE"}, {"PARE"}},
        {{"INSTRUCAO","IDENTIFICADOR"}, {"IDENTIFICADOR"}},
        {{"INSTRUCAO","VIRE PARA"}, {"VIRE PARA", "SENTIDO"}},
        {{"INSTRUCAO","MOVA"}, {"MOVA", "NUMERO", "PASSOS'"}},

        {{"PASSOS'","PASSOS"}, {"PASSOS"}},
        {{"PASSOS'","PASSO"}, {"PASSO"}},
        {{"PASSOS","LAMPADA APAGADA A DIREITA"}, {"&"}},
        {{"PASSOS","LAMPADA ACESA A DIREITA"}, {"&"}},
        {{"PASSOS","LAMPADA APAGADA A ESQUERDA"}, {"&"}},
        {{"PASSOS","LAMPADA ACESA A ESQUERDA"}, {"&"}},
        {{"PASSOS","LAMPADA APAGADA A FRENTE"}, {"&"}},
        {{"PASSOS","LAMPADA ACESA A FRENTE"}, {"&"}},
        {{"PASSOS","ESQUERDA ROBO BLOQUEADA"}, {"&"}},
        {{"PASSOS","DIREITA ROBO BLOQUEADA"}, {"&"}},
        {{"PASSOS","ROBO MOVIMENTANDO"}, {"&"}},
        {{"PASSOS","ROBO PARADO"}, {"&"}},
        {{"PASSOS","ROBO OCUPADO"}, {"&"}},
        {{"PASSOS","ROBO PRONTO"}, {"&"}},
        {{"PASSOS","AGUARDE ATE"}, {"&"}},
        {{"PASSOS","ACENDA LAMPADA"}, {"&"}},
        {{"PASSOS","APAGUE LAMPADA"}, {"&"}},
        {{"PASSOS","FINALIZE"}, {"&"}},
        {{"PASSOS","PARE"}, {"&"}},
        {{"PASSOS","IDENTIFICADOR"}, {"&"}},
        {{"PASSOS","VIRE PARA"}, {"&"}},
        {{"PASSOS","MOVA"}, {"&"}},
        {{"PASSOS","FIMSENAO"}, {"&"}},
        {{"PASSOS","FIMSE"}, {"&"}},
        {{"PASSOS","SE"}, {"&"}},
        {{"PASSOS","FIMPARA"}, {"&"}},
        {{"PASSOS","ENQUANTO"}, {"&"}},
        {{"PASSOS","FIMREPITA"}, {"&"}},
        {{"PASSOS","REPITA"}, {"&"}},
        {{"PASSOS","FIM"}, {"&"}},
        {{"PASSOS","INICIO"}, {"&"}},
        {{"PASSOS","DEFINAINSTRUCAO"}, {"&"}},
        {{"PASSOS","FIMEXECUCAO"}, {"&"}},
        {{"PASSOS","EXECUCAOINICIO"}, {"&"}},

        {{"CONDICAO","LAMPADA APAGADA A DIREITA"}, {"LAMPADA APAGADA A DIREITA"}},
        {{"CONDICAO","LAMPADA ACESA A DIREITA"}, {"LAMPADA ACESA A DIREITA"}},
        {{"CONDICAO","LAMPADA APAGADA A ESQUERDA"}, {"LAMPADA APAGADA A ESQUERDA"}},
        {{"CONDICAO","LAMPADA ACESSA A ESQUERDA"}, {"LAMPADA ACESSA A ESQUERDA"}},
        {{"CONDICAO","LAMPADA APAGADA A FRENTE"}, {"LAMPADA APAGADA A FRENTE"}},
        {{"CONDICAO","LAMPADA ACESA A FRENTE"}, {"LAMPADA ACESA A FRENTE"}},
        {{"CONDICAO","ESQUERDA ROBO BLOQUEADA"}, {"ESQUERDA ROBO BLOQUEADA"}},
        {{"CONDICAO","DIREITA ROBO BLOQUEADA"}, {"DIREITA ROBO BLOQUEADA"}},
        {{"CONDICAO","FRENTE ROBO BLOQUEADA"}, {"FRENTE ROBO BLOQUEADA"}},
        {{"CONDICAO","ROBO MOVIMENTANDO"}, {"ROBO MOVIMENTANDO"}},
        {{"CONDICAO","ROBO PARADO"}, {"ROBO PARADO"}},
        {{"CONDICAO","ROBO OCUPADO"}, {"ROBO OCUPADO"}},
        {{"CONDICAO","ROBO PRONTO"}, {"ROBO PRONTO"}},

        {{"SENTIDO","DIREITA"}, {"DIREITA"}},
        {{"SENTIDO","ESQUERDA"}, {"ESQUERDA"}}
    };

}

#endif
