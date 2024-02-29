#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PESSOAS 100
#define TAM_NOME 50
#define TAM_ENDERECO 100
#define TAM_CPF 15
#define TAM_DATA_NASC 11

typedef struct {
    char nome[TAM_NOME];
    char dataNascimento[TAM_DATA_NASC];
    int idade;
    char cpf[TAM_CPF];
    char endereco[TAM_ENDERECO];
} Pessoa;

Pessoa pessoas[MAX_PESSOAS];
int quantidadePessoas = 0;

void cadastrarPessoa();
void alterarPessoa();
void excluirPessoa();
void exibirPessoas();
int obterIndicePessoa();

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar pessoa\n");
        printf("2. Alterar dados de uma pessoa\n");
        printf("3. Excluir pessoa\n");
        printf("4. Exibir todas as pessoas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                cadastrarPessoa();
                break;
            case 2:
                alterarPessoa();
                break;
            case 3:
                excluirPessoa();
                break;
            case 4:
                exibirPessoas();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}

void cadastrarPessoa() {
    if (quantidadePessoas >= MAX_PESSOAS) {
        printf("Limite de pessoas atingido.\n");
        return;
    }

    Pessoa p;
    printf("Digite o nome: ");
    fgets(p.nome, TAM_NOME, stdin); p.nome[strcspn(p.nome, "\n")] = 0;
    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    fgets(p.dataNascimento, TAM_DATA_NASC, stdin); p.dataNascimento[strcspn(p.dataNascimento, "\n")] = 0;
    printf("Digite a idade: ");
    scanf("%d", &p.idade); getchar();
    printf("Digite o CPF: ");
    fgets(p.cpf, TAM_CPF, stdin); p.cpf[strcspn(p.cpf, "\n")] = 0;
    printf("Digite o endereco: ");
    fgets(p.endereco, TAM_ENDERECO, stdin); p.endereco[strcspn(p.endereco, "\n")] = 0;

    pessoas[quantidadePessoas++] = p;
    printf("Pessoa cadastrada com sucesso!\n");
}

void alterarPessoa() {
    int indice = obterIndicePessoa();
    if (indice == -1) {
        printf("Pessoa não encontrada.\n");
        return;
    }

    Pessoa* p = &pessoas[indice];
    printf("Alterando dados de: %s\n", p->nome);

    printf("Digite o novo nome (ou deixe em branco para não alterar): ");
    char temp[TAM_NOME];
    fgets(temp, TAM_NOME, stdin); temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(p->nome, temp);

    printf("Digite a nova data de nascimento (ou deixe em branco para não alterar): ");
    fgets(temp, TAM_DATA_NASC, stdin); temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(p->dataNascimento, temp);

    printf("Digite a nova idade: ");
    scanf("%d", &p->idade); getchar();

    printf("Digite o novo CPF (ou deixe em branco para não alterar): ");
    fgets(temp, TAM_CPF, stdin); temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(p->cpf, temp);

    printf("Digite o novo endereço (ou deixe em branco para não alterar): ");
    fgets(temp, TAM_ENDERECO, stdin); temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(p->endereco, temp);

    printf("Dados alterados com sucesso!\n");
}

void excluirPessoa() {
    int indice = obterIndicePessoa();
    if (indice == -1) {
        printf("Pessoa não encontrada.\n");
        return;
    }

    for (int i = indice; i < quantidadePessoas - 1; i++) {
        pessoas[i] = pessoas[i + 1];
    }
    quantidadePessoas--;
    printf("Pessoa excluída com sucesso!\n");
}

void exibirPessoas() {
    printf("Lista de Pessoas:\n");
    for (int i = 0; i < quantidadePessoas; i++) {
        Pessoa p = pessoas[i];
        printf("%d. Nome: %s, Data de Nascimento: %s, Idade: %d, CPF: %s, Endereço: %s\n",
               i + 1, p.nome, p.dataNascimento, p.idade, p.cpf, p.endereco);
    }
}

int obterIndicePessoa() {
    char cpfProcurado[TAM_CPF];
    printf("Digite o CPF da pessoa: ");
    fgets(cpfProcurado, TAM_CPF, stdin); cpfProcurado[strcspn(cpfProcurado, "\n")] = 0;

    for (int i = 0; i < quantidadePessoas; i++) {
        if (strcmp(pessoas[i].cpf, cpfProcurado) == 0) {
            return i;
        }
    }
    return -1;
}
