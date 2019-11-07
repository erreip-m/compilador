#include "Erro.h"
#include "Sema.h"

#include <map>
#include <stack>
#include <utility>
#include <vector>

using std::vector;

using namespace compilador;

Sema::Sema() {
}

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

void Sema::analisa(vector<Token> tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].obterLexema() == "DEFINAINSTRUCAO") {
            if (idUsado(tokens[++i].obterValor())) {
                erro(3, 0, 0);
            }
            else {
                idsUsados.push_back(tokens[i].obterValor());
            }
        }
        else if (tokens[i].obterLexema() == "MOVA") {
            i+=2;
            if (tokens[i].obterLexema() == "PASSO" || tokens[i].obterLexema() == "PASSOS") i++;
            if (!(tokens[i].obterLexema() == "AGUARDE ATE" &&
                tokens[++i].obterLexema() == "ROBO PRONTO")) {
                    erro(4, 0, 0);
                }
        }
        else if (tokens[i].obterLexema() == "VIRE PARA") {
            string sentido = tokens[++i].obterLexema();
            if (tokens[i+1].obterLexema() == "VIRE PARA" && tokens[i+2].obterLexema() != sentido) {
                erro(5, 0, 0);
            }
        }
    }
}