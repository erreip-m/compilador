#include "Erro.h"
#include "Lexer.h"
#include "Parser.h"
#include "Sema.h"
#include "Lexer.cpp"
#include "Parser.cpp"
#include "Sema.cpp"

#include <iostream>
#include <set>
#include <vector>

using std::set;
using std::vector;
using std::string;
using std::cin;
using std::cout;

using namespace compilador;


int main() {
    char buffer[512001];
    // FILE* teste;
    // teste = fopen("Testes/entrada1_correta.txt", "r");
	int tam = fread(buffer, sizeof(char), 512000, stdin /*teste*/);
	buffer[tam] = '\0';
    Parser parser(buffer);
    parser.analisa();   
}

