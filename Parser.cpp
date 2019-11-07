#include "Erro.h"
#include "Lexer.h"
#include "Parser.h"
#include "Sema.h"

#include <map>
#include <stack>
#include <utility>

using std::string;
using std::vector;

using namespace compilador;

Parser::Parser(char* buffer) {
    this->lexer = new Lexer(buffer);
}

bool Parser::terminal(string palavra) {
    return (Token::reservada(palavra) || palavra == "NUMERO" || palavra == "IDENTIFICADOR" || palavra == "$");
}

bool Parser::instrucaoValida() {
    return not(tabela[{pilha.top(), tokenAtual->obterLexema()}].empty());
}

void Parser::proximoToken() {
    do {
        tokenAtual = lexer->proximoToken();
    } while(tokenAtual->obterTipo() == "Comentario");
    tokens.push_back(*tokenAtual);
}

void Parser::obterInstrucao() {
    vector<string> instrucao;

    instrucao = tabela[{pilha.top(), tokenAtual->obterLexema()}];

    pilha.pop();

    if (instrucao[0] == "&") return;

    while(not(instrucao.empty())) {
        pilha.push(instrucao.back());
        instrucao.pop_back();
    }
}

void Parser::analisa() {
    proximoToken();
    pilha.push("$");
    pilha.push("PROGRAMA");

    while(not(pilha.empty())) {
        if (terminal(pilha.top())) {
            if (pilha.top() == tokenAtual->obterLexema()) {
                if (pilha.top() != "$") proximoToken();
                pilha.pop();
            }
            else {
                erro(2, lexer->obterLinha(), lexer->obterColuna());
                break;
            }
        }

        else {
            if (instrucaoValida()) {
                obterInstrucao();
            }
            else {
                erro(2, lexer->obterLinha(), lexer->obterColuna());
                break;
            }
        }
    }

    Sema sema;
    sema.analisa(tokens);

}

