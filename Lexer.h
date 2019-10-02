#ifndef LEXER
#define LEXER

#include <set>
#include <vector>

namespace compilador {
    // Verifica se o caractere é um digito
    bool digito(char t);

    // Verifica se o caractere é uma letra
    bool letra(char t);

    // Verifica se o caractere é de espaçamento
    bool espaco(char t);

    // Verifica se é fim de linha
    bool fimDeLinha(char t);

    // Verifica se é fim de texto
    bool fimDeTexto(char t);

    // Verifica se o caractere é válido para continuação de Idenficador
    bool caractereValidoId(char t);

    // Verifica se o caractere é válido para comentário (não é fim de linha ou fim de texto)
    bool caractereValidoComentario(char t);

    // Classe Token
    class Token {

        public:

            // Conjunto de palavras reservadas da linguagem
            static std::set<std::string> reservadas;

            // Tipos de Token - Invalido é temporário, apenas para demonstração
            enum class Tipo {
                Comentario = 0,
                Fim = 1,
                Identificador = 2,
                Invalido = 3,
                Numero = 4, 
                Reservado = 5,
            };

            // Declaração do construtor da classe Token
            Token(Tipo tipo, std::string lexema);

            // Declaração de funções

            static bool reservada(std::string palavra);
            std::string obterTipo();
            std::string obterLexema();

        private:

            // Variáveis para guardar informações do Token
            Tipo tipo;
            std::string lexema;
    };

    // Inicialização do conjunto de palavras reservadas
    std::set<std::string> Token::reservadas = {
        "A",
        "ACENDA",
        "ACESA",
        "AGUARDE",
        "APAGADA",
        "APAGUE",
        "ATE",
        "BLOQUEADA",
        "COMO",
        "DEFINAINSTRUCAO",
        "DIREITA",
        "ENQUANTO",
        "ENTAO",
        "ESQUERDA",
        "EXECUCAOINICIO",
        "FACA",
        "FIM",
        "FIMEXECUCAO",
        "FIMPARA",
        "FIMPROGRAMA",
        "FIMREPITA",
        "FIMSE",
        "FIMSENAO",
        "FINALIZE",
        "FRENTE",
        "INICIO",
        "LAMPADA",
        "MOVA",
        "MOVIMENTANDO",
        "OCUPADO",
        "PARA",
        "PARADO",
        "PARE",
        "PASSO",
        "PASSOS",
        "PROGRAMAINICIO",
        "PRONTO",
        "REPITA",
        "ROBO",
        "SE",
        "SENAO",
        "VEZ",
        "VEZES",
        "VIRE"
    };

    // Classe Lexer
    class Lexer {

        public:

            // Declaração do construtor de Token
            Lexer(char *ptr);

            // Declaração de função
            Token* proximoToken();

        private:

            // Variáveis para guardar informações do Lexer
            char *ptr, *ant;    //ant serve como ptr anterior
            int linha, coluna;

            // Declaração de funções privadas

            char olhaProximoCaractere();
            char obterCaractere();
            char obterCaractereComentario();
            bool inicioDeComentario();
            Token* tokenizaNumero();
            Token* tokenizaPalavra();
            Token* tokenizaComentario();
            Token* tokenizaFim();
            Token* tokenizaInvalido();
    };

}

#endif