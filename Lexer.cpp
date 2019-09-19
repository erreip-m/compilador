#include <ios>

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

//TODO função para "espiar" próximo char da cadeia e outra para pegá-lo

int main() {
    std::cout<<"teste";
}
