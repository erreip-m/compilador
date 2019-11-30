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

// Construtor da classe Parser
Parser::Parser(char* buffer) {
    this->lexer = new Lexer(buffer);
    this->sema = new Sema();
}

// Verifica se a palavra é terminal
bool Parser::terminal(string palavra) {
    return (Token::reservada(palavra) || palavra == "NUMERO" || palavra == "IDENTIFICADOR" || palavra == "$");
}

// Verifica se a instrução é válida, ou seja, está na tabela
bool Parser::instrucaoValida() {
    return not(tabela[{pilha.top(), tokenAtual->obterLexema()}].empty());
}

// Pede ao Lexer o próximo Token
void Parser::proximoToken() {
    do {
        tokenAnterior = tokenAtual;
        tokenAtual = lexer->proximoToken();
    } while(tokenAtual->obterTipo() == "Comentario");   //ignora Tokens do tipo Comentario
}

// Coloca na pilha as proximas instruções, com base na tabela
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

// Analisa todos os tokens passados pelo Lexer
void Parser::analisa() {
    proximoToken();     //pega token inicial
    pilha.push("$");    //$ marca o fim da pilha
    pilha.push("PROGRAMA"); //regra inicial da gramatica

    while(not(pilha.empty())) { //enquanto houver instrução na pilha

        if (terminal(pilha.top())) {    //se o topo da pilha for terminal...
            if (pilha.top() == tokenAtual->obterLexema()) { //e o token atual for igual...
                if (pilha.top() != "$") {
                    sema->analisa(*tokenAtual, *tokenAnterior); //chama analise semantica pro token atual e...
                    
                    proximoToken(); //pede o proximo token
                }
                pilha.pop();    //tira o terminal da pilha
            }
            else {  //caso o token atual não corresponda ao terminal no topo da pilha...
                erro(2, tokenAnterior->obterLinha(), tokenAnterior->obterColuna());   //informa erro sintático
                break;
            }
        }

        else {  //se o topo da pilha não for um terminal, então é uma regra
            if (instrucaoValida()) {
                obterInstrucao();   //coloca as instruções da regra na pilha
            }
            else {  //se a instrução não estiver na tabela...
                erro(2, tokenAnterior->obterLinha(), tokenAnterior->obterColuna());   //informa erro
                break;
            }
        }
    }

}

