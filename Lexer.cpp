#include <iostream>
#include <set>

using std::set;
using std::string;
using std::cin;
using std::cout;

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
