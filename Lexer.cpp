#include "Erro.h"
#include "Lexer.h"

#include <iostream>
#include <set>
#include <vector>

using std::set;
using std::vector;
using std::string;
using std::cin;
using std::cout;

using namespace compilador;

// Verifica se o caractere é um digito
bool compilador::digito(char t) {
    return (t >= '0'  &&  t <= '9');
}

// Verifica se o caractere é uma letra
bool compilador::letra(char t) {
    return ((t >= 'a'  &&  t<='z')  ||  (t >= 'A'  &&  t <= 'Z'));
}

// Verifica se o caractere é de espaçamento
bool compilador::espaco(char t) {
    return (t == ' '  ||  t == '\t');
}

// Verifica se é fim de linha
bool compilador::fimDeLinha(char t) {
    return t == '\n';
}

// Verifica se é fim de texto
bool compilador::fimDeTexto(char t) {
    return t == '\0';
}

// Verifica se o caractere é válido para continuação de Idenficador
bool compilador::caractereValidoId(char t) {
    return (digito(t)  ||  letra(t));
}

// Verifica se o caractere é válido para comentário (não é fim de linha ou fim de texto)
bool compilador::caractereValidoComentario(char t) {
    return (!fimDeLinha(t) && !fimDeTexto(t));
}


// Construtores de Token

Token::Token(Tipo tipo, string lexema, int linha, int coluna) {
    this->tipo = tipo;
    this->lexema = lexema;
    this->linha = linha;
    this->coluna = coluna;
}

Token::Token(Tipo tipo, string lexema, string valor, int linha, int coluna) {
    this->tipo = tipo;
    this->lexema = lexema;
    this->valor = valor;
    this->linha = linha;
    this->coluna = coluna;
}

// Verifica se a palavra é reservada
bool Token::reservada(string palavra) {
    return reservadas.find(palavra) != reservadas.end();
}

// Verifica se a palavra é reservada composta
bool Token::composta(string palavra) {
    return not(compostas[palavra].empty());
}

// Retorna o tipo do Token, em string - Provavelmente sofrerá alterações
string Token::obterTipo() {
    switch (int(tipo)) {
        default:
            return "Comentario";
        case 1:
            return "Fim";
        case 2:
            return "Identificador";
        case 3:
            return "Numero";
        case 4:
            return "Reservado";
    }
}

// Retorna lexema do Token
string Token::obterLexema() {
    return lexema;
}

// Retorna valor do Token - usado somente para IDs e numeros
string Token::obterValor() {
    return valor;
}

// Retorna linha do Token
int Token::obterLinha() {
    return linha;
}

// Retorna coluna do Token
int Token::obterColuna() {
    return coluna;
}

// Construtor da classe Lexer
Lexer::Lexer(char *ptr) {   //início do texto de código é passado no ptr
    this->ptr = ptr;
    ant = nullptr;
    linha = 1;
    coluna = 1;
}

// Cria e retorna o próximo Token
Token* Lexer::proximoToken() {
    while(1) {
        char p = olhaProximoCaractere();
        if (espaco(p)) {    //se for espaçamento, vai pro próximo caractere
            obterCaractere();
        }
        else if (fimDeLinha(p)) {   //se for fim de linha, vai pro próximo caractere, mudando linha e coluna
            obterCaractere();
            linha++;
            coluna = 1;
        }
        else if (inicioDeComentario()) {    //se for inicio de comentário, tokeniza o comentário e retorna o token
            return tokenizaComentario();
        }
        else if (digito(p)) {   //se for dígito, tokeniza número e retorna o token
            return tokenizaNumero();
        }
        else if (letra(p)) {    //se for letra, tokeniza palavra e retorna o token
            return tokenizaPalavra();
        }
        else if (fimDeTexto(p)) {   //se for fim de texto, tokeniza fim de texto e retorna o token
            return tokenizaFim();
        }
        else {  //se for caractere invalido, informa erro léxico e retorna nulo
            erro(0, linha, coluna);
            obterCaractere();
            return nullptr;
        }
    }
}


// Retorna próximo caractere a ser analisado, que está sendo apontado pelo ptr
char Lexer::olhaProximoCaractere() {
    return *ptr;
}

// Retorna o próximo caractere a ser analisado e aponta para o próximo
char Lexer::obterCaractere() {
    coluna++;
    ant = ptr;
    if (letra(*ptr)) {              //deixar letra maiúscula        
        return toupper(*ptr++);
    }
    return *ptr++;
}

// Retorna o próximo caractere a ser analisado e aponta para o próximo - Sem alterar letras minúsculas
char Lexer::obterCaractereComentario() {
    coluna++;
    ant = ptr;
    return *ptr++;
}

// Verifica se é um início de comentário
bool Lexer::inicioDeComentario() {
    return (*ptr == '#' && (ant == nullptr || *ant == '\n'));
}

// Tokeniza número
Token* Lexer::tokenizaNumero() {
    string numero = "";
    numero += obterCaractere();
    while(digito(olhaProximoCaractere())) {
        numero += obterCaractere();
    }

    try {                                   //verifica se está dentro dos limites de inteiro
        stoi(numero);
    }
    catch (const std::out_of_range& oor) {  //caso não esteja, informa o erro
        erro(1, linha, coluna);    
    }

    Token* newTok = new Token(Token::Tipo::Numero, "NUMERO", numero, linha, coluna); //cria e retorna Token do tipo Numero
    return newTok;
}

// Tokeniza palavra (reservadas e identificadores)
Token* Lexer::tokenizaPalavra() {
    string palavra = "";
    palavra += obterCaractere();
    while (caractereValidoId(olhaProximoCaractere())) palavra += obterCaractere();

    if (Token::reservada(palavra)) {    //verifica se é reservada
        Token* newTok = new Token(Token::Tipo::Reservado, palavra, linha, coluna); //cria e retorna Token do tipo Reservado
        return newTok;
    }
    else if (Token::composta(palavra)) {    //verifica se a palavra é inicio de palavra reservada composta, se for, verifica proximos tokens
        string palavrainicial = palavra;
        Lexer save = *this; //copia estado atual do Lexer, serve de backup
        int i = 0;
        for (int k = 0; k < Token::compostas[palavrainicial].size(); k++) {
            while (i < Token::compostas[palavrainicial][k].size()) {    //verifica se o conjunto de palavras forma uma palavra reservada composta
                string palavraatual = "";
                int j;
                while (espaco(olhaProximoCaractere())) obterCaractere();
                palavraatual += obterCaractere();
                while (caractereValidoId(olhaProximoCaractere())) palavraatual += obterCaractere();
                if (palavraatual == Token::compostas[palavrainicial][k][i]) {
                    palavra += " " + palavraatual;
                    i++;
                }
                else break;
            }
            if (i == Token::compostas[palavrainicial][k].size()) {  //caso o conjunto forme uma palavra reservada...
                Token* newTok = new Token(Token::Tipo::Reservado, palavra, linha, coluna); //cria e retorna o Token do tipo Reservado
                return newTok;
            }
            else {  //se não formar uma palavra reservada...
                *this = save;   //retorna para o estado anterior do Lexer
                palavra = palavrainicial;
            }
        }
    }

    //se não for reservada...
    Token* newTok = new Token(Token::Tipo::Identificador, "IDENTIFICADOR", palavra, linha, coluna); //...cria e retorna Token do tipo Identificador
    return newTok;
}

// Tokeniza comentários
Token* Lexer::tokenizaComentario() {
    string comentario = "";
    comentario += obterCaractereComentario();
    while (caractereValidoComentario(olhaProximoCaractere())) comentario += obterCaractereComentario();

    Token* newTok = new Token(Token::Tipo::Comentario, comentario, linha, coluna); //cria objeto Token do tipo Comentario
    return newTok;
}

// Tokeniza fim de texto
Token* Lexer::tokenizaFim() {
    Token* newTok = new Token(Token::Tipo::Fim, "$", linha, coluna);  //cria objeto Token do tipo Fim
    return newTok;
}
