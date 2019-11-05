#ifndef LEXER
#define LEXER

#include <set>
#include <vector>
#include <map>

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

            // Mapa para palavras reservadas compostas da linguagem
            static std::map<std::string, std::vector<std::vector<std::string>>> compostas;

            // Conjunto de palavras reservadas da linguagem
            static std::set<std::string> reservadas;

            enum class Tipo {
                Comentario = 0,
                Fim = 1,
                Identificador = 2,
                Numero = 3, 
                Reservado = 4,
            };

            // Declaração do construtor da classe Token
            Token(Tipo tipo, std::string lexema);

            // Declaração de funções

            static bool reservada(std::string palavra);
            static bool composta(std::string palavra);
            std::string obterTipo();
            std::string obterLexema();

        private:

            // Variáveis para guardar informações do Token
            Tipo tipo;
            std::string lexema;
    };

    // Mapa para terminais com espaçamento - TODO
    std::map<std::string, std::vector<std::vector<std::string>>> Token::compostas {
        {"ACENDA", {{"LAMPADA"}}},
        {"AGUARDE", {{"ATE"}}},
        {"APAGUE", {{"LAMPADA"}}},
        {"ROBO", {{"MOVIMENTANDO"}, 
            {"OCUPADO"}, 
            {"PARADO"}, 
            {"PRONTO"}}},
        {"VIRE", {{"PARA"}}},
        {"DIREITA", {{"ROBO","BLOQUEADA"}}},
        {"ESQUERDA", {{"ROBO", "BLOQUEADA"}}},
        {"FRENTE", {{"ROBO", "BLOQUEADA"}}},
        {"LAMPADA", {{"ACESA", "A", "DIREITA"}, 
            {"ACESA", "A", "ESQUERDA"}, 
            {"ACESA", "A", "FRENTE"},
            {"APAGADA", "A", "DIREITA"},
            {"APAGADA", "A", "ESQUERDA"},
            {"APAGADA", "A", "FRENTE"}}}
    };

    // Inicialização do conjunto de palavras reservadas
    std::set<std::string> Token::reservadas = {
        "ACENDA LAMPADA",
        "AGUARDE ATE",
        "APAGUE LAMPADA",
        "COMO",
        "DEFINAINSTRUCAO",
        "DIREITA",
        "DIREITA ROBO BLOQUEADA",
        "ENQUANTO",
        "ENTAO",
        "ESQUERDA",
        "ESQUERDA ROBO BLOQUEADA",
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
        "FRENTE ROBO BLOQUEADA",
        "INICIO",
        "LAMPADA ACESA A DIREITA",
        "LAMPADA ACESA A ESQUERDA",
        "LAMPADA ACESA A FRENTE",
        "LAMPADA APAGADA A DIREITA",
        "LAMPADA APAGADA A ESQUERDA",
        "LAMPADA APAGADA A FRENTE",
        "MOVA",
        "PARE",
        "PASSO",
        "PASSOS",
        "PROGRAMAINICIO",
        "REPITA",
        "ROBO MOVIMENTANDO",
        "ROBO OCUPADO",
        "ROBO PARADO",
        "ROBO PRONTO",
        "SE",
        "SENAO",
        "VEZ",
        "VEZES",
        "VIRE PARA"
    };

    // Classe Lexer
    class Lexer {

        public:

            // Declaração do construtor de Token
            Lexer(char *ptr);
            Lexer(char *ptr, char* ant, int linha, int coluna);

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
