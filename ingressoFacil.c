#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <wchar.h>
#include <ctype.h>

typedef struct
{
    char nome[50];
    char cpf[15];
    char dataNascimento[11];
} Ingresso;

Ingresso ingressos[100];
int contadorIngressos = 0;

bool validarCPF(const char *cpf)
{
    int len = strlen(cpf);

    if (len != 11)
        return false;

    for (int i = 0; i < len; i++)
    {
        if (!isdigit(cpf[i]))
            return false;
    }

    return true;
}

bool validarDataNascimento(const char *dataNascimento)
{
    // Verifica se a data de nascimento está no formato correto (dd/mm/yyyy)
    if (strlen(dataNascimento) != 10)
    {
        return false;
    }

    if (dataNascimento[2] != '/' || dataNascimento[5] != '/')
    {
        return false;
    }

    int dia, mes, ano;
    if (sscanf(dataNascimento, "%2d/%2d/%4d", &dia, &mes, &ano) != 3)
    {
        return false;
    }

    // Verifica se os valores da data são válidos
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900)
    {
        return false;
    }

    return true;
}

void venderIngresso()
{
    Ingresso novoIngresso;

    printf("Digite o nome do comprador: ");
    fflush(stdin);
    if (fgets(novoIngresso.nome, sizeof(novoIngresso.nome), stdin) != NULL)
    {
        novoIngresso.nome[strcspn(novoIngresso.nome, "\n")] = '\0';
    }
    else
    {
        // Tratar erro de leitura
        printf("Erro ao ler o nome do comprador.\n");
        return;
    }

    bool cpfValido = false;
    while (!cpfValido)
    {
        printf("Digite o CPF do comprador (Sem pontos e tracos, apenas numeros): ");
        fflush(stdin);
        fgets(novoIngresso.cpf, 15, stdin);

        // Remover o caractere '\n' lido pelo fgets
        novoIngresso.cpf[strcspn(novoIngresso.cpf, "\n")] = '\0';

        if (validarCPF(novoIngresso.cpf))
        {
            cpfValido = true;
        }
        else
        {
            printf("CPF invalido. Digite novamente.\n");
        }
    }

    bool dataValida = false;
    while (!dataValida)
    {
        printf("Digite a data de nascimento do comprador (DD/MM/AAAA): ");
        fflush(stdin);
        fgets(novoIngresso.dataNascimento, 11, stdin);

        // Remover o caractere '\n' lido pelo fgets
        novoIngresso.dataNascimento[strcspn(novoIngresso.dataNascimento, "\n")] = '\0';

        if (validarDataNascimento(novoIngresso.dataNascimento))
        {
            dataValida = true;
        }
        else
        {
            printf("Data de Nascimento invalida. Digite novamente.\n");
        }
    }

    ingressos[contadorIngressos++] = novoIngresso;

    printf("Ingresso vendido com sucesso!\n\n");
}

void listarIngressos()
{
    if (contadorIngressos == 0)
    {
        printf("Nenhum ingresso vendido.\n\n");
        return;
    }

    for (int i = 0; i < contadorIngressos; i++)
    {
        printf("Nome: %s\n", ingressos[i].nome);

        // Verifica se o CPF já está formatado com as pontuações
        if (strlen(ingressos[i].cpf) == 14)
        {
            printf("CPF: %s\n", ingressos[i].cpf);
        }
        else
        {
            char cpfFormatado[15];
            snprintf(cpfFormatado, sizeof(cpfFormatado), "%.3s.%.3s.%.3s-%.2s", ingressos[i].cpf, ingressos[i].cpf + 3, ingressos[i].cpf + 6, ingressos[i].cpf + 9);
            printf("CPF: %s\n", cpfFormatado);
        }

        printf("Data de Nascimento: %s\n", ingressos[i].dataNascimento);
        printf("===============================\n");
    }

    printf("\n");
}

void validarIngresso()
{
    char cpf[15];
    printf("Digite o CPF do comprador: ");
    fflush(stdin);
    fgets(cpf, 15, stdin);

    // Remover o caractere '\n' lido pelo fgets
    cpf[strcspn(cpf, "\n")] = '\0';

    bool cpfValido = validarCPF(cpf);

    int encontrado = 0;
    for (int i = 0; i < contadorIngressos; i++)
    {
        if (cpfValido && strcmp(cpf, ingressos[i].cpf) == 0)
        {
            encontrado = 1;
            printf("Ingresso valido! Aproveite o evento!\n\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("Ingresso invalido ou nao encontrado.\n\n");
    }
}

int main()
{

    system("cls");
    // setlocale(LC_ALL, "Portuguese"); => Em meus testes, as opções Portuguese, Portuguese_Brazil.UTF-8, gerou instabilidades na hora de apresentar os valores.

    char opcao;

    do
    {
        printf("====== Menu ======\n");
        printf("a) Vender ingresso\n");
        printf("b) Listar ingressos vendidos\n");
        printf("c) Validar ingresso\n");
        printf("d) Sair\n");
        printf("Digite a opcao desejada: ");
        scanf(" %c", &opcao);

        system("cls");

        switch (tolower(opcao))
        {
        case 'a':
            venderIngresso();
            break;
        case 'b':
            listarIngressos();
            break;
        case 'c':
            validarIngresso();
            break;
        case 'd':
            printf("Programa encerrado.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n\n");
            break;
        }

        system("pause");
        system("cls");
    } while (opcao != 'd');

    return 0;
}