#include "Erro.h"
#include "Sema.h"

#include <map>
#include <stack>
#include <utility>
#include <vector>

using std::vector;

using namespace compilador;

// Construtor de Sema
Sema::Sema() {
    flagSentido = 0;
    flagMova = 0;
    flagDefinaInstrucao = 0;
}

// Verifica se o id já foi declarado
bool Sema::idUsado(string id) {
    bool usado = false;
    for (int i = 0; i < idsUsados.size(); i++) {
        if (id == idsUsados[i]) {
            usado = true;
            break;
        }
    }
    return usado;
}

// Verifica se há conflito de sentidos - ex: Vire Para Direita sucedido por Vire Para Esquerda
bool Sema::verificaConflitoSentido(string tok) {
    bool conflito = false;
    if (tok == "DIREITA") {
        if (flagSentido == 0) {
            flagSentido = 1;
        }
        else if (flagSentido == 2) {
            conflito = true;
        }
    }
    else if (tok == "ESQUERDA") {
        if (flagSentido == 0) {
            flagSentido = 2;
        }
        else if (flagSentido == 1) {
            conflito = true;
        }
    }
    else if (tok != "VIRE PARA") {
        flagSentido = 0;
    }
    return conflito;
}

// Verifica se a instrução Mova não é sucedida por Aguarde Ate Robo Pronto
bool Sema::verificaConflitoMova(string tok) {
    bool conflito = false;
    if (tok == "MOVA") {
        flagMova = 1;
    }
    else if (flagMova >= 1 && (tok == "NUMERO" || tok == "PASSO" || tok == "PASSOS")) {
        flagMova = 2;
    }
    else if (flagMova == 2 && tok == "AGUARDE ATE") {
        flagMova = 3;
    }
    else if (flagMova == 2 && tok != "AGUARDE ATE") {
        conflito = true;
        flagMova = 0;
    }
    else if (flagMova == 3 && tok != "ROBO PRONTO") {
        conflito = true;
        flagMova = 0;
    }
    else {
        flagMova = 0;
    }
    return conflito;
}

// Verifica se há conflito de ids
bool Sema::verificaConflitoId(string tok) {
    bool conflito = false;
    if (tok == "DEFINAINSTRUCAO") {
        flagDefinaInstrucao = 1;
    }
    else if (flagDefinaInstrucao == 1) {
        if (idUsado(tok)) {
            conflito = true;
        }
        else {
            idsUsados.push_back(tok);
        }
        flagDefinaInstrucao = 0;
    }
    else {
        flagDefinaInstrucao = 0;
    }
    return conflito;
}

// Analisa semanticamente um token por vez
void Sema::analisa(Token token) {
    string tok = token.obterLexema();

    if (verificaConflitoSentido(tok)) {
        erro(5, token.obterLinha(), token.obterColuna());   //se houver conflito
    }

    if (verificaConflitoMova(tok)) {
        erro(4, token.obterLinha(), token.obterColuna());   //se houver conflito
    }

    if (verificaConflitoId(tok)) {
        erro(3, token.obterLinha(), token.obterColuna());   //se houver conflito
    }

}