#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define MAX_USUARIOS 20


// Defini��o das estruturas de dados
typedef struct {
    char codigoCadastro[20];
    char nomeResponsavel[50];
    char nomeEmpresa[50];
    char cnpj[15];
    char razaoSocial[50];
    char nomeFantasia[50];
    char telefone[15];
    char endereco[100];
    char email[50];
    char dataAbertura[15];
    double residuosTratados;
    double valorCustoEstimado;
} DadosIndustria;

typedef struct {
    char username[20];
    char password[20];
} Usuario;

void exibirMenuInicial(Usuario usuarios[], int *numUsuarios);
void exibirMenuPrincipal(Usuario usuarios[], int numUsuarios);
void cadastrarLogin(Usuario usuarios[], int *numUsuarios);
void realizarLogin(Usuario usuarios[], int numUsuarios);
void cadastrarIndustria();
void exibirMenuLogado(Usuario usuario);
void introduzirInformacoes();
void salvarDados(DadosIndustria industria);
void gerarRelatorio();
void visualizarDadosIndustria();
void esperarTecla();



void esperarTecla() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n'){
    }  // Consumir todos os caracteres at� o Enter
}


int main() {

    setlocale(LC_ALL, "portuguese");
    Usuario usuarios[MAX_USUARIOS];

    int numUsuarios = 0;

    exibirMenuInicial(usuarios, &numUsuarios);

    return 0;
}

void exibirMenuInicial(Usuario usuarios[], int *numUsuarios) {

    int escolha;

    printf("***********************************\n");
    printf("*        AMBIENTAL S.A            *\n");
    printf("*      GEST�O SUSTENT�VEL         *\n");
    printf("*     CADASTROS & RELAT�RIOS      *\n");
    printf("***********************************\n");

    printf("\nO que deseja?\n");
    printf("\n[1] Entrar no menu principal \n[2] Logout \n\nOp��o Escolhida: ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        exibirMenuPrincipal(usuarios, *numUsuarios);
    } else if (escolha == 2) {
        printf("\nEncerrando.... Obrigado.\n");
        exit(0);
    } else {
        printf("\nEscolha errada, retornando...\n");
        esperarTecla();
        exibirMenuInicial(usuarios, numUsuarios);
    }
}

void exibirMenuPrincipal(Usuario usuarios[], int numUsuarios) {
    int opcao;

    printf("\nAcesse uma das op��es abaixo: \n");
    printf("\n[1] Cadastrar Novo Login.\n");
    printf("[2] Acessar Sistema.\n");
    printf("[3] Sair do programa.\n");
    printf("\nOp��o Escolhida: ");

    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            cadastrarLogin(usuarios, &numUsuarios);
            break;
        case 2:
            realizarLogin(usuarios, numUsuarios);
            break;
        case 3:
            printf("\nEncerrando. Obrigado...\n");
            exit(0);
            break;
        default:
            printf("\nOp��o errada! Digite outra vez.\n\n");
            esperarTecla();
            exibirMenuPrincipal(usuarios, numUsuarios);
    }
}

void cadastrarLogin(Usuario usuarios[], int *numUsuarios) {
    system("cls");
    printf("CADASTRO DE LOGIN\n");
    printf("------------------\n");

    // Verifica se h� espa�o dispon�vel para cadastrar um novo usu�rio
    if (*numUsuarios < MAX_USUARIOS) {
        printf("Digite o nome de usu�rio: ");
        scanf("%s", usuarios[*numUsuarios].username);

        printf("Digite a senha: ");
        scanf("%s", usuarios[*numUsuarios].password);

        // Incrementa o n�mero de usu�rios cadastrados
        (*numUsuarios)++;

        printf("\nLogin cadastrado com sucesso!\n");
    } else {
        printf("\nLimite de usu�rios atingido. Imposs�vel cadastrar mais logins.\n");
    }

    esperarTecla();
    exibirMenuPrincipal(usuarios, *numUsuarios);
}

void realizarLogin(Usuario usuarios[], int numUsuarios) {

    Usuario usuarioLogado;
    int i;
    char inputUsername[20];
    char inputPassword[20];

    printf("\nRealizar Login\n");
    printf("Informe o nome de usu�rio: ");
    scanf("%s", inputUsername);

    for (i = 0; i < numUsuarios; ++i) {
        if (strcmp(usuarios[i].username, inputUsername) == 0) {
            printf("Informe a senha: ");
            scanf("%s", inputPassword);

            if (strcmp(usuarios[i].password, inputPassword) == 0) {
                strcpy(usuarioLogado.username, inputUsername);
                strcpy(usuarioLogado.password, inputPassword);

                // Chamar a fun��o para exibir o novo menu ap�s login
                exibirMenuLogado(usuarioLogado);
                return;
            }
        }
    }

    printf("Login falhou. Nome de usu�rio ou senha inv�lidos.\n");
    esperarTecla();
    exibirMenuPrincipal(usuarios, numUsuarios);
}

void exibirMenuLogado(Usuario usuario) {
    DadosIndustria industria;

    int opcao;

    do {
        printf("\nBem-vindo, %s!\n", usuario.username);
        printf("Selecione uma op��o:\n");
        printf("[1] Cadastrar Ind�stria\n");
        printf("[2] Visualizar Dados da Ind�stria\n");
        printf("[3] Introduzir informa��es sobre res�duos e custo\n");
        printf("[4] Gerar Relat�rio e Salvar em Arquivo\n");
        printf("[5] Logout\n");
        printf("Op��o Escolhida: ");

        scanf("%d", &opcao);
        getchar();  // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                cadastrarIndustria();
                break;
            case 2:
                visualizarDadosIndustria();
                break;
            case 3:
                introduzirInformacoes(&industria);
                break;
            case 4:
                gerarRelatorio(industria);
                break;
            case 5:
                printf("Logout realizado com sucesso.\n");
                esperarTecla();
                return;  // Retorna ao menu principal
            default:
                printf("Op��o errada! Digite outra vez.\n");
                esperarTecla();
        }
    } while (1);
}

void cadastrarIndustria() {
    system("cls");

    printf("CADASTRO DE IND�STRIA\n");
    printf("----------------------\n");

    DadosIndustria industria;

    printf("Codigo de Cadastro: ");
    fflush(stdin);
    fgets(industria.codigoCadastro, sizeof(industria.codigoCadastro), stdin);
    industria.codigoCadastro[strcspn(industria.codigoCadastro, "\n")] = '\0';

    printf("Nome Respons�vel: ");
    fgets(industria.nomeResponsavel, sizeof(industria.nomeResponsavel), stdin);
    industria.nomeResponsavel[strcspn(industria.nomeResponsavel, "\n")] = '\0';

    printf("Nome Empresa: ");
    fgets(industria.nomeEmpresa, sizeof(industria.nomeEmpresa), stdin);
    industria.nomeEmpresa[strcspn(industria.nomeEmpresa, "\n")] = '\0';

    printf("CNPJ: ");
    fgets(industria.cnpj, sizeof(industria.cnpj), stdin);
    industria.cnpj[strcspn(industria.cnpj, "\n")] = '\0';

    printf("Raz�o Social: ");
    fgets(industria.razaoSocial, sizeof(industria.razaoSocial), stdin);
    industria.razaoSocial[strcspn(industria.razaoSocial, "\n")] = '\0';

    printf("Nome Fantasia: ");
    fgets(industria.nomeFantasia, sizeof(industria.nomeFantasia), stdin);
    industria.nomeFantasia[strcspn(industria.nomeFantasia, "\n")] = '\0';

    printf("Telefone: ");
    fgets(industria.telefone, sizeof(industria.telefone), stdin);
    industria.telefone[strcspn(industria.telefone, "\n")] = '\0';

    printf("Endere�o: ");
    fgets(industria.endereco, sizeof(industria.endereco), stdin);
    industria.endereco[strcspn(industria.endereco, "\n")] = '\0';

    printf("Email: ");
    fgets(industria.email, sizeof(industria.email), stdin);
    industria.email[strcspn(industria.email, "\n")] = '\0';

    printf("Data de Abertura: ");
    fgets(industria.dataAbertura, sizeof(industria.dataAbertura), stdin);
    industria.dataAbertura[strcspn(industria.dataAbertura, "\n")] = '\0';

    salvarDados(industria);

    printf("\nCadastro realizado com sucesso!\n");
    esperarTecla();

    return;
}

int lerDados(const char *codigoCadastro, DadosIndustria *industria) {
    FILE *arquivo;
    arquivo = fopen("dados_industria.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, "Codigo Cadastro: ") != NULL) {
            char codigo[20];
            sscanf(linha, "Codigo Cadastro: %s", codigo);

            // Verificar se o c�digo encontrado corresponde ao desejado
            if (strcmp(codigo, codigoCadastro) == 0) {
                // Ler os dados da ind�stria
                fscanf(arquivo, "Nome Respons�vel: %[^\n]\n", industria->nomeResponsavel);
                fscanf(arquivo, "Nome Empresa: %[^\n]\n", industria->nomeEmpresa);
                fscanf(arquivo, "CNPJ: %[^\n]\n", industria->cnpj);
                fscanf(arquivo, "Raz�o Social: %[^\n]\n", industria->razaoSocial);
                fscanf(arquivo, "Nome Fantasia: %[^\n]\n", industria->nomeFantasia);
                fscanf(arquivo, "Telefone: %[^\n]\n", industria->telefone);
                fscanf(arquivo, "Endere�o: %[^\n]\n", industria->endereco);
                fscanf(arquivo, "Email: %[^\n]\n", industria->email);
                fscanf(arquivo, "Data de Abertura: %[^\n]\n", industria->dataAbertura);
                fscanf(arquivo, "Res�duos Tratados Trimestre: %lf toneladas\n", &industria->residuosTratados);
                fscanf(arquivo, "Valor Custo Estimado Anual: R$ %lf\n", &industria->valorCustoEstimado);
                fclose(arquivo);
                return 1;  // C�digo de cadastro encontrado
            }
        }
    }

    fclose(arquivo);
    return 0;  // C�digo de cadastro n�o encontrado
}

void visualizarDadosIndustria() {
    system("cls");
    DadosIndustria industria;
    char codigoCadastro[20];

    printf("Digite o codigo de cadastro da ind�stria: ");
    scanf("%s", codigoCadastro);

    if (lerDados(codigoCadastro, &industria)) {
        system("cls");
        printf("Dados da Empresa\n");
        printf("-----------------\n");
        printf("Codigo Cadastro: %s\n", codigoCadastro);
        printf("Nome Respons�vel: %s\n", industria.nomeResponsavel);
        printf("Nome Empresa: %s\n", industria.nomeEmpresa);
        printf("CNPJ: %s\n", industria.cnpj);
        printf("Raz�o Social: %s\n", industria.razaoSocial);
        printf("Nome Fantasia: %s\n", industria.nomeFantasia);
        printf("Telefone: %s\n", industria.telefone);
        printf("Endere�o: %s\n", industria.endereco);
        printf("Email: %s\n", industria.email);
        printf("Data de Abertura: %s\n", industria.dataAbertura);
        printf("Res�duos Tratados Trimestre: %.2lf toneladas\n", industria.residuosTratados);
        printf("Valor Custo Estimado Anual: R$ %.2lf\n", industria.valorCustoEstimado);

        esperarTecla();
    } else {
        printf("Erro ao ler os dados da ind�stria.\n");
        esperarTecla();
    }
}

void atualizarDadosIndustria(DadosIndustria *industria, const char *codigoCadastro) {
    FILE *arquivo;
    arquivo = fopen("dados_industria.txt", "r+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura e escrita.\n");
        esperarTecla();
        return;
    }

    DadosIndustria temp;
    char linha[100];
    long int posicaoInicial = -1;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, "Codigo Cadastro: ") != NULL) {
            char codigo[20];
            sscanf(linha, "Codigo Cadastro: %s", codigo);

            // Verificar se o c�digo encontrado corresponde ao desejado
            if (strcmp(codigo, codigoCadastro) == 0) {
                posicaoInicial = ftell(arquivo) - strlen(linha);

                // Ler as informa��es existentes da ind�stria
                fscanf(arquivo, "Nome Respons�vel: %[^\n]\n", temp.nomeResponsavel);
                fscanf(arquivo, "Nome Empresa: %[^\n]\n", temp.nomeEmpresa);
                fscanf(arquivo, "CNPJ: %[^\n]\n", temp.cnpj);
                fscanf(arquivo, "Raz�o Social: %[^\n]\n", temp.razaoSocial);
                fscanf(arquivo, "Nome Fantasia: %[^\n]\n", temp.nomeFantasia);
                fscanf(arquivo, "Telefone: %[^\n]\n", temp.telefone);
                fscanf(arquivo, "Endere�o: %[^\n]\n", temp.endereco);
                fscanf(arquivo, "Email: %[^\n]\n", temp.email);
                fscanf(arquivo, "Data de Abertura: %[^\n]\n", temp.dataAbertura);
                fscanf(arquivo, "Res�duos Tratados Trimestre: %lf toneladas\n", &temp.residuosTratados);
                fscanf(arquivo, "Valor Custo Estimado Anual: R$ %lf\n", &temp.valorCustoEstimado);
                fgets(linha, sizeof(linha), arquivo);  // Consumir linha de separa��o

                // Atualizar as informa��es de res�duo e custo
                printf("Quantidade de res�duos tratados Trimestre (em toneladas): ");
                scanf("%lf", &temp.residuosTratados);

                printf("Valor estimado de custo Anual (em reais): ");
                scanf("%lf", &temp.valorCustoEstimado);

                // Voltar ao in�cio do registro no arquivo para reescrever as informa��es
                fseek(arquivo, posicaoInicial, SEEK_SET);

                // Reescrever as informa��es no arquivo
                fprintf(arquivo, "odigo Cadastro: %s\n", codigoCadastro);
                fprintf(arquivo, "Nome Respons�vel: %s\n", temp.nomeResponsavel);
                fprintf(arquivo, "Nome Empresa: %s\n", temp.nomeEmpresa);
                fprintf(arquivo, "CNPJ: %s\n", temp.cnpj);
                fprintf(arquivo, "Raz�o Social: %s\n", temp.razaoSocial);
                fprintf(arquivo, "Nome Fantasia: %s\n", temp.nomeFantasia);
                fprintf(arquivo, "Telefone: %s\n", temp.telefone);
                fprintf(arquivo, "Endere�o: %s\n", temp.endereco);
                fprintf(arquivo, "Email: %s\n", temp.email);
                fprintf(arquivo, "Data de Abertura: %s\n", temp.dataAbertura);
                fprintf(arquivo, "Res�duos Tratados Trimestre: %.2lf toneladas\n", temp.residuosTratados);
                fprintf(arquivo, "Valor Custo Estimado Anual: R$ %.2lf\n", temp.valorCustoEstimado);
                fprintf(arquivo, "---------------------------------\n");

                fclose(arquivo);

                printf("\nInforma��es atualizadas com sucesso!\n");
                esperarTecla();
                return;
            }
        }
    }

    fclose(arquivo);

    if (posicaoInicial == -1) {
        printf("\nCodigo de cadastro n�o encontrado.\n");
        esperarTecla();
    }
}

void introduzirInformacoes(DadosIndustria *industria) {
    // Solicitar c�digo de cadastro ao usu�rio
    char inputCodigo[20];
    printf("Digite o codigo de cadastro da ind�stria: ");
    scanf("%19s", inputCodigo);
    getchar();  // Limpar o buffer de entrada

    // Chamar a fun��o para atualizar as informa��es de res�duo e custo
    atualizarDadosIndustria(industria, inputCodigo);

    return;
}

void salvarDados(DadosIndustria industria) {
    FILE *arquivo;

    // Abre o arquivo para escrita (o modo "a" � utilizado para adicionar ao final do arquivo)
    if ((arquivo = fopen("dados_industria.txt", "a")) != NULL) {
        // Escreve os dados da ind�stria no arquivo

        fprintf(arquivo, "Codigo Cadastro: %s\n", industria.codigoCadastro);
        fprintf(arquivo, "Nome Respons�vel: %s\n", industria.nomeResponsavel);
        fprintf(arquivo, "Nome Empresa: %s\n", industria.nomeEmpresa);
        fprintf(arquivo, "CNPJ: %s\n", industria.cnpj);
        fprintf(arquivo, "Raz�o Social: %s\n", industria.razaoSocial);
        fprintf(arquivo, "Nome Fantasia: %s\n", industria.nomeFantasia);
        fprintf(arquivo, "Telefone: %s\n", industria.telefone);
        fprintf(arquivo, "Endere�o: %s\n", industria.endereco);
        fprintf(arquivo, "Email: %s\n", industria.email);
        fprintf(arquivo, "Data de Abertura: %s\n", industria.dataAbertura);
        fprintf(arquivo, "Res�duos Tratados Trimestre: %.2lf toneladas\n", industria.residuosTratados);
        fprintf(arquivo, "Valor Custo Estimado Anual: R$ %.2lf\n", industria.valorCustoEstimado);
        fprintf(arquivo, "---------------------------------\n");

        // Fecha o arquivo
        fclose(arquivo);

        printf("\nDados salvos com sucesso!\n");
    } else {
        printf("\nErro ao abrir o arquivo para escrita.\n");
    }
}

void gerarRelatorio() {
    char codigoCadastro[20];
    char dataFormatada[50];
    DadosIndustria industria;

    printf("Digite o c�digo de cadastro da ind�stria: ");
    scanf("%19s", codigoCadastro);
    getchar();  // Limpar o buffer de entrada

    // Ler os dados da ind�stria do arquivo
    if (lerDados(codigoCadastro, &industria)) {
        // Calcular o total de insumos semestral
        double totalInsumosSemestral = industria.residuosTratados * 2;

        // Calcular o total de gastos mensais (considerando um ano dividido por 12)
        double totalGastosMensais = industria.valorCustoEstimado / 12;

        // Obter a data e hora atuais
        time_t t;
        struct tm *data;
        time(&t);
        data = localtime(&t);
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y %H:%M:%S", data);

        // Criar e abrir o arquivo para salvar o relat�rio
        FILE *relatorio;
        char nomeArquivo[50];
        sprintf(nomeArquivo, "relatorio_%s.txt", codigoCadastro);
        relatorio = fopen(nomeArquivo, "w");

        if (relatorio != NULL) {
            fprintf(relatorio, "Relat�rio de Atividades\n");
            fprintf(relatorio, "------------------------\n");
            fprintf(relatorio, "C�digo da Empresa: %s\n", codigoCadastro);
            fprintf(relatorio, "Nome Fantasia: %s\n", industria.nomeFantasia);
            fprintf(relatorio, "Raz�o Social: %s\n", industria.razaoSocial);
            fprintf(relatorio, "Data de Gera��o do Relat�rio: %s\n", dataFormatada);
            fprintf(relatorio, "Total de insumos tratados semestralmente: %.2lf toneladas\n", totalInsumosSemestral);
            fprintf(relatorio, "Total de gastos mensais: R$ %.2lf\n", totalGastosMensais);

            fclose(relatorio);

            printf("\nRelat�rio gerado e salvo com sucesso!\n");
            esperarTecla();
        } else {
            printf("\nErro ao criar o arquivo de relat�rio.\n");
        }
    } else {
        printf("\nC�digo de cadastro n�o encontrado.\n");
        esperarTecla();
    }
}
