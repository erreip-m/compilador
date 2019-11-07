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
	int tam = fread(buffer,sizeof(char),512000,stdin);
	buffer[tam] = '\0';
    Parser parser(buffer);
    parser.analisa();   
}

