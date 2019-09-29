#include <iostream>
#include <set>
#include <vector>

using std::set;
using std::vector;
using std::string;
using std::cin;
using std::cout;

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
    return (t == ' '  ||  t == '\t');
}

// Verifica se é fim de linha
bool fimDeLinha(char t) {
    return t == '\n';
}

// Verifica se é fim de texto
bool fimDeTexto(char t) {
    return t == '\0';
}

// Verifica se o caractere é válido para continuação de Idenficador
bool caractereValidoId(char t) {
    return (digito(t)  ||  letra(t));
}

// Verifica se o caractere é válido para comentário (não é fim de linha ou fim de texto)
bool caractereValidoComentario(char t) {
    return (!fimDeLinha(t) && !fimDeTexto(t));
}

// Classe Token
class Token {

    public:

        // Conjunto de palavras reservadas da linguagem
        static set<string> reservadas;

        // Tipos de Token - Invalido é temporário, apenas para demonstração
        enum class Tipo {
            Comentario = 0,
            Fim = 1,
            Identificador = 2,
            Invalido = 3,
            Numero = 4, 
            Reservado = 5,
        };

        // Declaração do construtor da classe Token
        Token(Tipo tipo, string lexema);

        // Declaração de funções

        static bool reservada(string palavra);
        string obterTipo();
        string obterLexema();

    private:

        // Variáveis para guardar informações do Token
        Tipo tipo;
        string lexema;
};

// Inicialização do conjunto de palavras reservadas
set<string> Token::reservadas = {
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

// Construtor de Token
Token::Token(Tipo tipo, string lexema) {
    this->tipo = tipo;
    this->lexema = lexema;
}

// Verifica se a palavra é reservada
bool Token::reservada(string palavra) {
    return reservadas.find(palavra) != reservadas.end();
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
            return "Invalido";
        case 4:
            return "Numero";
        case 5:
            return "Reservado";
    }
}

// Retorna lexema do Token
string Token::obterLexema() {
    return lexema;
}

// Classe Lexer
class Lexer {

    public:

        // Declaração do construtor de Token
        Lexer(char *ptr);

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
        void erro(int numErro);
};

// Construtor da classe Lexer
Lexer::Lexer(char *ptr) {   //início do texto de código é passado no ptr
    this->ptr = ptr;
    ant = nullptr;          //ant é um ponteiro pro
    linha = 1;
    coluna = 1;
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
        std::stoi(numero);
    }
    catch (const std::out_of_range& oor) {  //caso não esteja, envia um erro
        erro(1);    
    }

    Token* newTok = new Token(Token::Tipo::Numero, numero); //cria objeto Token do tipo Numero
    return newTok;
}

// Tokeniza palavra (reservadas e identificadores)
Token* Lexer::tokenizaPalavra() {
    string palavra = "";
    palavra += obterCaractere();
    while (caractereValidoId(olhaProximoCaractere())) palavra += obterCaractere();

    if (Token::reservada(palavra)) {    //verifica se é reservada
        Token* newTok = new Token(Token::Tipo::Reservado, palavra); //cria objeto Token do tipo Reservado
        return newTok;
    }
    Token* newTok = new Token(Token::Tipo::Identificador, palavra); //cria objeto Token do tipo Identificador
    return newTok;
}

// Tokeniza comentários
Token* Lexer::tokenizaComentario() {
    string comentario = "";
    comentario += obterCaractereComentario();
    while (caractereValidoComentario(olhaProximoCaractere())) comentario += obterCaractereComentario();

    Token* newTok = new Token(Token::Tipo::Comentario, comentario); //cria objeto Token do tipo Comentario
    return newTok;
}

// Tokeniza fim de texto
Token* Lexer::tokenizaFim() {
    Token* newTok = new Token(Token::Tipo::Fim, "\0");  //cria objeto Token do tipo Fim
    return newTok;
}

// Tokeniza caractere inválido - Temporário, apenas para demonstração
Token* Lexer::tokenizaInvalido() {
    string invalido = "";
    invalido = obterCaractere(); 
    Token* newTok = new Token(Token::Tipo::Invalido, invalido); //cria objeto Token do tipo Invalido
    return newTok;
}

// Cria e retorna o próximo Token
Token* Lexer::proximoToken() {
    while(5 - 3 * 2 > -265) {
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
        else {  //se for caractere invalido, tokeniza invalido e retorna o token - Temporário
            erro(0);
            return tokenizaInvalido();
        }
    }
}

// Retorno de erros
void Lexer::erro(int numErro) {
    switch (numErro) {
        case 0:
            cout << "\n#ERRO: CARACTERE INVALIDO. LINHA: " << linha << ", COLUNA: " << coluna << "\n\n";
            break;
        case 1:
            cout << "\n#ERRO: NUMERO EXCEDE LIMITE. LINHA: " << linha << ", COLUNA: " << coluna << "\n\n";     
            break;
    }
}


int main() {
    char buffer[512001];
	int tam = fread(buffer,sizeof(char),512000,stdin);
	buffer[tam] = '\0';

    Lexer lexer(buffer);
    vector<Token> tokens;
    while(1) {
        Token* temp = lexer.proximoToken();
        if (temp->obterLexema() != "\0") {
            tokens.push_back(*temp);
            cout << "\tToken: " << tokens.back().obterTipo() << ", Lexema: " << tokens.back().obterLexema() << "\n"; 
        }
        else break;
    }
}
