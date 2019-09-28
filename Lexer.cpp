#include <iostream>
#include <set>

using std::set;
using std::string;
using std::cin;
using std::cout;

// Lista de palavras reservadas

//      programainicio, execucaoinicio, fimexecucao, fimprograma

//      definainstrucao, como

//      inicio, fim

//      repita, vezes, fimrepita

//      enquanto, faca, fimpara

//      se, ent ao, fimse, senao, fimsenao

//      mova, passo, passos, vire para, pare, finalize, apague lampada, acenda lampada, aguarde ate

//      robo pronto, robo ocupado, robo parado, robo movimentando, frente robo bloqueada, 
//      direita robo bloqueada, esquerda robo bloqueada, lampada acesa a frente, 
//      lampada apagada a frente, lampada acesa a esquerda,  lampada apagada a esquerda,
//      lampada apagada a esquerda, lampada acesa a direita, lampada apagada a direita
      
//      esquerda, direita

class Token {
    public:
        const set<string> reservadas {
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
        enum class Tipo {
            Comentario,
            Identificador,
            Numero, 
            Reservado
          /*Reservados:
            A,
            ACENDA,
            ACESA,
            AGUARDE,
            APAGADA,
            APAGUE,
            ATE,
            BLOQUEADA,
            COMO,
            DEFINAINSTRUCAO,
            DIREITA,
            ENQUANTO,
            ENTAO,
            ESQUERDA,
            EXECUCAOINICIO,
            FACA,
            FIM,
            FIMEXECUCAO,
            FIMPARA,
            FIMPROGRAMA,
            FIMREPITA,
            FIMSE,
            FIMSENAO,
            FINALIZE,
            FRENTE,
            INICIO,
            LAMPADA,
            MOVA,
            MOVIMENTANDO,
            OCUPADO,
            PARA,
            PARADO,
            PARE,
            PASSO,
            PASSOS,
            PROGRAMAINICIO,
            PRONTO,
            REPITA,
            ROBO,
            SE,
            SENAO,
            VEZ,
            VEZES,
            VIRE*/
        };
        Token(Tipo tipo, string lexema);
        Tipo obterTipo();
        string obterLexema();

    private:
        Tipo tipo;
        string lexema;
};

Token::Token(Tipo tipo, string lexema) {
    this->tipo = tipo;
    this->lexema = lexema;
}

Token::Tipo Token::obterTipo() {
    return tipo;
}

string Token::obterLexema() {
    return lexema;
}

class Lexer {
    private:
        int *ptr;
};

// Verifica se o caractere é um digito
bool digito(char t) {
    return (t >= '0'  &&  t <= '9');
}

// Verifica se o caractere é uma letra
bool letra(char t) {
    return ((t >= 'a'  &&  t<='z')  ||  (t >= 'A'  &&  t <= 'Z'));
}

// Verifica se o caractere é de espaçamento
bool espaco(char t) {
    return (t == ' '  ||  t == '\t'  ||  t == '\n');
}

//TODO dividir em inicio de identifiador e resto
bool caractereValido(char t) {
    return (digito(t)  ||  letra(t)  ||  espaco(t));
}


int main() {
    Token tok(Token::Tipo::Identificador, "teste123");
    cout << tok.obterLexema() << "\n";
}
