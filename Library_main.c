///////////////////////////////////////////////////////////////////////////////
///             Universidade Federal do Rio Grande do Norte                 ///
///                 Centro de Ensino Superior do Seridó                     ///
///               Departamento de Computação e Tecnologia                   ///
///                  Disciplina DCT1106 -- Programação                      ///
///                 Projeto de Controle de Biblioteca                       ///
///               Developed by  @SusuGostoso - Out, 2021                    ///
///             Developed by  @daividfernandoo - Out, 2021                  ///
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//=========> Assinatura das funções

//Defines
#define MsgEx(msg,...) MensagemErro(msg, (0, ##__VA_ARGS__))
#define Clear() system("clear||cls")

//Telas Principais
void Tela_Principal(void);
void Tela_Menu_Usuario(void);
void Tela_Menu_Livro(void);
void Tela_Creditos(void);
void Tela_Sobre(void);
void Tela_Login(void);

//Telas Secundárias
void tUsuario(int ID);
void tLivros(int ID);
void tLogin(int ID);

//Funções
void MensagemErro(char msg[256], int mID);
void Msg(char msg[256]);
void Escolha_Usuario(int max_opcoes, int incremento);
void Header(char title[128]);
int ValidarData(int dd, int mm, int yy);
int Exists(int codigo, char info[50], int arquivo_variavel); //Função retorna se existe um usuário (info: nome de usuário) ou livro (info: id do livro)

//Funções de Usuário
void ListUsers(void);
int GetFree(int prefixo); //BOOK ou USER (para livros e usuários)
void RegistrarUsuario(char uNome[128], char uCel[12], char uCidade[128], char uEndereco[128], char Username[32], char uSenha[128], int uDiaNasc, int uMesNasc, int uAnoNasc, int uAdmin, int uDinheiro);
int AbrirArquivo(char Arquivo[40], char* StrF);
void CarregarUsuarios(void);
int ExcluirUsuario(char username[128]);
int UserExists(char username[50]);
int AlterarUsuario(char username[32], char alternativa[128], char texto[256]);

//Funções Livros
void RegistrarLivro(char bNome[128], char bAutor[128], int bAno, int bPaginas, char bEditora[128], int bEdicao, int bDepartamento);
void CarregarLivros(void);
void ListarLivros(void);
void TagBook(int IDTag, char* StrX);

//Funções Livros-Alugados
void AlugarLivro(char usuario[32], int id_livro, int valorpago, int dia, int mes, int ano, int hora, int minuto, int prazo);
void ListarAlugados(void);
void CarregarAlugados(void);
int GetBookByID(int id);

//Variáveis púlicas
int Menu_id = 0;
int Logado = -1; //Verificar se o usuário fez login
int Staff = 0; //Verficiar se o usuário é um administrador
struct tm *agora; //ponteiro para struct que armazena data e hora
time_t segundos; //variável do tipo time_t para armazenar o tempo em segundos

//usuários fictícios
#define MAX_USERS 25
#define MAX_LIVROS 50
#define BOOK 60001
#define USER 60002
#define ALUGADO 60003
#define DINHEIRO_PADRAO 50

struct user_data_nascimento {
    int dia, mes, ano;
};

struct user_estrutura
{
    char nome[128];
    char celular[12];
    char cidade[128];
    char endereco[128];
    char nomeusuario[32];
    char senha[128];
    int admin;
    int dinheiro;
    struct user_data_nascimento nascimento;
}
Usuario[MAX_USERS];

struct iBook
{
    int id;
    char nome[128];
    char autor[128];
    int ano;
    int paginas;
    char editora[128];
    int edicao;
    int departamento;
}
Livros[MAX_LIVROS];

struct aLivros
{
    char usuario[32];
    int idlivro;
    int valorpago;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int prazo; //em dias
}
Alugados[MAX_LIVROS];

struct sGeral
{
    int alugados;
    int livros;
    int usuarios;
};
struct sGeral geral;

// Programa principal
int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    CarregarUsuarios(); //Carregar Usuários
    CarregarLivros(); //Carregar Livros
    CarregarAlugados(); //Carregar Livros Alugados

    if(Logado != -1) {
        Staff = Usuario[Logado].admin;
    }

    int escolha = 0;

    while (Menu_id != 666)
    {
        switch (Menu_id)
        {
            case 0: //Tela Principal

                if(Logado != -1) //Verificar se o usuário está logado
                {
                    Tela_Principal(); //Exibição da Tela Principal
                    Escolha_Usuario(4, 0); //Escolha dele, 4 opções, incremento de 0 (se escolher 1, o Menu_id será 1)
                    continue;
                }
                else //Se não estiver logado...
                {
                    Tela_Login(); //Exibição da tela de menu
                    Escolha_Usuario(3, 15); //Escolha do usuario, 3 opções, incremento de 15 (se escolher 1, o Menu_id será 16)
                }
                
            break;

            case 1: //módulo Usuario

                Tela_Menu_Usuario(); //Exibição de Tela 'Usuario'
                Escolha_Usuario(4, 5); //Escolha dele, 4 opções, incremento de 5 (se escolher 1, o Menu_id será 6)
                continue;
            
            break;

            case 2: //módulo Livros  

                Tela_Menu_Livro(); //Exibição de Tela 'Livros'
                Escolha_Usuario(5, 10); //Escolha dele, 5 opções, incremento de 10 (se escolher 1, o Menu_id será 11)
                continue;

            break;

            case 3: //módulo Sobre

                Tela_Sobre(); //Exibição de Tela 'Sobre'
                Menu_id = 0; //Menu Principal
                continue;

            break;

            case 4: //módulo Creditos 
            
                Tela_Creditos(); //Exibição de Tela 'Creditos'
                Menu_id = 0; //Menu Principal
                continue;

            break;

            case 5: //módulo Staff (em breve)

                Clear();
                MsgEx("Este módulo ainda está em desenvolvimento, retornando ao menu prinicipal...");
                continue;

            break;

            case 6: case 7: case 8: case 9: //módulo Usuario: pesquisar, cadastrar, alterar, excluir...
                
                tUsuario((Menu_id-5));
                continue;

            break;

            case 11: case 12: case 13: case 14: case 15: //módulo Livros: cadastrar, alterar, alugar, excluir e pesquisar.
                
                tLivros((Menu_id-10));
                continue;

            break;

            case 16: case 17: case 18: //Módulo login: login, cadastro, esqueci minha senha

                tLogin((Menu_id-15));
                continue;

            break;

            default:
                Clear();
                MsgEx("Este módulo ainda está em desenvolvimento, retornando ao menu prinicipal...");
                continue;
        }

    }

    //system("pause");
    return 0;
}

void tLogin(int ID)
{
    switch (ID) //Login
    {
        case 1: //Login
        {
            char vUser[50], vPass[50];
            int Tentativas = 3;

            while(1)
            {
                if(Tentativas <= 0)
                {
                    Clear();
                    MsgEx("Você ultrapassou o número de tentativas de login, retornando ao menu principal...");
                    Menu_id = 0;
                    break;
                }

                Clear();
                Header("///          = = = = = = = = =  Login Usuário  = = = = = = = = =          ///");

                printf("\n\tInforme seu nome de usuário: ");
                if(scanf("%s", vUser) != 1) {
                    Tentativas--;
                    printf("\n\t\tVocê tem %d tentativas.\n", Tentativas);
                    Msg("Usuário inválido, tente novamente...");
                    continue;
                }

                printf("\n\tInforme sua senha: ");
                if(scanf("%s", vPass) != 1) {
                    Tentativas--;
                    printf("\n\t\tVocê tem %d tentativas.\n", Tentativas);
                    Msg("Senha inválida, tente novamente...");
                    continue;
                }

                int l = 0;
                Logado = -1;

                while(l < MAX_USERS)
                {
                    if (strcmp(Usuario[l].nome, "InvalidUser") != 0)
                    {
                        if (strcmp(vUser, Usuario[l].nomeusuario) == 0)
                        {
                            if (strcmp(vPass, Usuario[l].senha) == 0)
                            {
                                Logado = l;
                                break;
                            }
                        }
                    }
                    l++;
                }

                if(Logado != -1) //Logou com sucesso
                {
                    Clear();
                    Menu_id = 0;
                    printf("\n\n\t >>>> Usuário logado com sucesso. Seja bem vindo %s!\n", vUser);
                    printf("\n\t Usuário: %s", Usuario[Logado].nome);
                    printf("\n\t Celular: %s", Usuario[Logado].celular);
                    printf("\n\t Cidade: %s", Usuario[Logado].cidade);
                    printf("\n\t Endereço: %s", Usuario[Logado].endereco);
                    printf("\n\t Nome de Usuário: %s", Usuario[Logado].nomeusuario);
                    printf("\n\t Data de Nascimento: %d/%d/%d", Usuario[Logado].nascimento.dia, Usuario[Logado].nascimento.mes, Usuario[Logado].nascimento.ano);
                    printf("\n\t Dinheiro: R$ %d", Usuario[Logado].dinheiro);

                    Staff = Usuario[Logado].admin;

                    Sleep(500);
                    printf("\n\n\t\tRetornando ao menu principal...");
                    Sleep(1600);
                    break;
                }
                else
                {
                    Tentativas--;
                    printf("\n\t\tVocê tem %d tentativas.\n", Tentativas);
                    Msg("Usuário e/ou senha incorretos.");
                    continue;
                }
            }
        
        }
        break;

        case 2: //Cadastra
        {
            tUsuario(1);
        }
        break;

        case 3: //Esqueci a senha
        {
            int ForgetEx = 1;
            int dd, mm, yy; //Data de nascimento (dia, mês, ano)
            char nome[50], cel[12], username[32], password[128];

            while(ForgetEx != 666)
            {
                Header("///          = = = = = = = =   Recuperar Senha   = = = = = = = =          ///");

                if(ForgetEx == 1) //Nome de usuário
                {
                    printf("\n\tOlá, %s.\n\n", nome);

                    printf("\tInforme o seu nome de usuário (exemplo: Susu_Gostoso): ");
                    if(scanf("%[A-Z_a-z]", username) != 1) {
                        Msg("Usuário inválido, utilize somente letras.");
                        continue;
                    }
                    ForgetEx++;
                }
                else if(ForgetEx == 2) //Nome e Sobrenome
                {
                    printf("\tInforme seu Nome e Sobrenome: ");
                    if(scanf("%[A-Z a-z]", nome) != 1) {
                        Msg("Nome inválido, tente novamente...");
                        continue;
                    }
                    ForgetEx++;
                }
                else if(ForgetEx == 3) //Data de Nascimento
                {
                    printf("\n\tOlá, %s.\n\n", nome);

                    printf("\tInforme sua data de nascimento (Exemplo: 17/09/1997): ");
                    scanf("%d/%d/%d", &dd, &mm, &yy);

                    if((ValidarData(dd, mm, yy) == 0))
                    {
                        Msg("Data inválida, tente novamente...");
                        continue;
                    }
                    ForgetEx++;
                }
                else if(ForgetEx == 4) //Número de celular (apenas numeros)
                {
                    printf("\n\tOlá, %s.\n", nome);

                    printf("\n\tInforme seu número de celular (somente números): ");
                    
                    if ((scanf("%[0-9]", cel) != 1) || (strlen(cel) != 11)) {
                        Msg("Número de celular inválido, tente novamente...");
                        continue;
                    }
                    ForgetEx++;
                }
                else if(ForgetEx == 5) //Nova senha
                {

                    printf("\n\tOlá, %s.\n\n", nome);

                    printf("\tInforme sua nova senha: ");
                    if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", password) != 1) {
                        Msg("Senha inválida, por favor tente novamente.");
                        continue;
                    }
                    
                    ForgetEx = 666;
                    continue;
                }
            }

            //Resumo das informações
            Header("///          = = = = = = = =   Recuperar Senha   = = = = = = = =          ///");
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=[ Informações gerais ]=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            printf("\n\tNome: %s\n", nome);
            printf("\n\tData de Nascimento: %d/%d/%d\n", dd, mm, yy);
            printf("\n\tCelular: %s\n", cel);
            printf("\n\tNome de usuário: %s\n", username);
            printf("\n\tNova Senha: %s\n", password);
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

            int z;
            printf("\nAs informações estão corretas? (1=SIM | 2=NÃO): ");
            scanf("%d", &z);

            if(z != 1) { //Caso o usuário escolha que as informações estão incorretas, ele retorna a primeira etapa.
                tLogin(3);
            }
            else {
                Menu_id = 0;
                printf("\n\t[INFO] Senha alterada com sucesso, retornando ao menu inicial...\n");
                Sleep(1500);
            }
        }
        break;
    }
}

void tLivros(int ID)
{
    switch (ID) //Livros
    {
        case 1: //Alugar
        {
            int aEtapa = 1, aLivroID, aPrazo;

            while(1)
            {
                Header("///          = = = = = = = = =  Alugar  Livro  = = = = = = = = =          ///");

                if(aEtapa == 1)
                {
                    printf("Informe o ID do livro: ");
                    if((scanf("%d", &aLivroID) != 1)) {
                        Msg("ID inválido, tente novamente...");
                        continue;
                    }
                    aEtapa++;
                }
                else if(aEtapa == 2)
                {
                    printf("\n\t\t [1]\t5 dias\n");
                    printf("\t\t [2]\t10 dias\n");
                    printf("\t\t [3]\t15 dias\n\n");
                    printf("\t\t [0]\tCancelar\n\n");

                    printf("Informe o prazo do aluguel: ");

                    if((scanf("%d", &aPrazo) != 1)) {
                        Msg("ID inválido, tente novamente...");
                        continue;
                    }

                    if(aPrazo >= 1 && aPrazo <= 3)
                    {
                        aPrazo *= 5;
                    }
                    else if(aPrazo == 0) //Sair 
                    {
                        Menu_id = 2;
                        break;
                    }
                    else //Erro
                    {
                        Msg("ID inválido, tente novamente...");
                        continue;
                    }

                    aEtapa++;
                }
                else if(aEtapa == 3)
                {
                    time(&segundos);
                    agora = localtime(&segundos);

                    float preco = (Livros[aLivroID-100].paginas * 0.05);

                    AlugarLivro(Usuario[Logado].nomeusuario, aLivroID, (int)preco, agora->tm_mday, agora->tm_mon+1, agora->tm_year+1900, agora->tm_hour, agora->tm_min, aPrazo);

                    printf("\nLivro Alugado com sucesso. \n");
                    Menu_id = 0;
                    Sleep(2500);
                    break;
                }
            }
        }
        break;

        case 2: //Pesquisar
        
            Header("///          = = = = = = = = = Pesquisar Livro = = = = = = = = =          ///");
            MsgEx("Função ainda em desenvolvimento...", 2);
        
        break;

        case 3: //Cadastrar
        {
            int cEtapas = 1;

            char bNome[128], bAutor[128], bEditora[128], tmpBook[50];
            int bAno, bPaginas, bEdicao, y, bDepartamento;

            while(1)
            {
                Header("///          = = = = = = = = = Cadastrar Livro = = = = = = = = =          ///");
                printf("\n");

                if(cEtapas == 1) //Autor
                {
                    printf("Informe o nome do autor do livro: ");
                    if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", bAutor) != 1) {
                        Msg("Autor inválido, tente novamente...");
                        continue;
                    }
                    cEtapas++;
                }
                else if(cEtapas == 2) //Nome do Livro
                {
                    printf("Informe o nome do livro: ");
                    if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ0-9_:]", bNome) != 1) {
                        Msg("Nome inválido, tente novamente...");
                        continue;
                    }
                    cEtapas++;
                }
                else if(cEtapas == 3) //Ano de Lançamento
                {
                    printf("Informe o ano de lançamento do livro: ");
                    if((scanf("%d", &bAno) != 1)) {
                        Msg("Ano inválido, tente novamente...");
                        continue;
                    }
                    cEtapas++;
                }
                else if(cEtapas == 4) //Páginas
                {
                    printf("Informe o número de Páginas do livro: ");
                    if((scanf("%d", &bPaginas) != 1)) {
                        Msg("Número inválido, tente novamente...");
                        continue;
                    }
                    cEtapas++;
                }
                else if(cEtapas == 5) //Editora
                {
                    printf("Informe a Editora do livro: ");
                    if(scanf("%[A-Z a-z.()-,0-9]", bEditora) != 1) {
                        Msg("Nome da Editora inválido, tente novamente...");
                        continue;
                    }
                    cEtapas++;
                }
                else if(cEtapas == 6) //Edição
                {
                    printf("Informe a Edição do livro (somente números): ");
                    if((scanf("%d", &bEdicao) != 1)) {
                        Msg("Número inválido, tente novamente...");
                        continue;
                    }
                    cEtapas++;
                }
                else if(cEtapas == 7) //Departamento [tags]
                {

                    for(y = 1; y <= 29; y++)
                    {
                        TagBook(y, tmpBook);
                        printf("[ID: %d]: %s\n", y, tmpBook);
                    }
                    printf("\n\n");

                    printf("Informe o Departamento do livro (ID): ");
                    
                    if((scanf("%d", &bDepartamento) != 1)) {
                        Msg("Número inválido, tente novamente...");
                        continue;
                    }
            
                    if(bDepartamento < 1 || bDepartamento > 29)
                    {
                        Msg("Número inválido, tente novamente...");
                        continue;
                    }
                    cEtapas++;
                }
                else if(cEtapas == 8) //Finalização
                {
                    Clear();
                    //Resumo das informações
                    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=[ Informações do Livro ]=-=-=-=-=-=-=-=-=-=-=-=-=\n");
                    printf("\n\t Autor: %s\n", bAutor);
                    printf("\n\t Nome: %s\n", bNome);
                    printf("\n\t Ano de Lançamento: %d\n", bAno);
                    printf("\n\t Páginas: %d\n", bPaginas);
                    printf("\n\t Editora: %s\n", bEditora);
                    printf("\n\t Edição: %d\n", bEdicao);
                    TagBook(bDepartamento, tmpBook);
                    printf("\n\t Departamento: [%d] %s\n", bDepartamento, tmpBook);
                    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

                    printf("As informações estão corretas? (1=SIM, 2=NÃO): ");
                    if((scanf("%d", &y) != 1)) {
                        Msg("Número inválido, tente novamente...");
                        continue;
                    }


                    //Registro 
                    RegistrarLivro(bNome, bAutor, bAno, bPaginas, bEditora, bEdicao, bDepartamento);
                    //(char bNome[128], char bAutor[128], int bAno, int bPaginas, char bEditora[128], int bEdicao, int bDepartamento)

                    if(y != 1) { //Caso o usuário escolha que as informações estão incorretas, ele retorna a primeira etapa.
                        cEtapas = 1;
                        continue;
                    }
                    break;
                }
            }
            
            MsgEx("Livro cadastrado com sucesso, retornando ao menu livros...", 2);
        }
        break;

        case 4: //Excluir
        
            Header("///          = = = = = = = = =  Excluir Livro  = = = = = = = = =          ///");
            MsgEx("Função ainda em desenvolvimento...", 2);
        
        break;

        case 5: //Alterar
        
            Header("///          = = = = = = = = =  Alterar Livro  = = = = = = = = =          ///");
            MsgEx("Função ainda em desenvolvimento...", 2);
        
        break;
    }
}

void tUsuario(int ID)
{
    int etapa = 1; 
    int dd, mm, yy; //Data de nascimento (dia, mês, ano)
    char nome[50], cel[12], city[50], end[90], username[32], password[128];

    switch (ID)
    {
        case 1: //Cadastrar um novo usuario 

            if(Staff != 0 || Logado == -1) //Se for administrador: registra um novo usuário
            {
                while(1)
                {
                    Header("///          = = = = = = = =  Cadastrar Usuário  = = = = = = = =          ///");

                    if(etapa == 1) //Nome e Sobrenome
                    {
                        printf("\tInforme seu nome: ");
                        if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", nome) != 1) {
                            Msg("Nome inválido, tente novamente...");
                            continue;
                        }
                        etapa++;
                    }
                    else if(etapa == 2) //Data de Nascimento
                    {
                        printf("\n\tOlá, %s.\n\n", nome);

                        printf("\tInforme sua data de nascimento (Exemplo: 17/09/1997): ");
                        scanf("%d/%d/%d", &dd, &mm, &yy);

                        if((ValidarData(dd, mm, yy) == 0))
                        {
                            Msg("Data inválida, tente novamente...");
                            continue;
                        }
                        etapa++;
                    }
                    else if(etapa == 3) //Número de celular (apenas numeros)
                    {
                        printf("\n\tOlá, %s.\n\n", nome);

                        printf("\tInforme seu número de celular (somente números): ");
                        if((scanf("%[0-9]", cel) != 1) || (strlen(cel) != 11)) {
                            Msg("Número de celular inválido, tente novamente...");
                            continue;
                        }
                        etapa++;
                    }
                    else if(etapa == 4) //Cidade
                    {
                        printf("\n\tOlá, %s.\n\n", nome);

                        printf("\tInforme a cidade que você reside: ");
                        if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", city) != 1) {
                            Msg("Cidade inválida, tente novamente...");
                            continue;
                        }
                        etapa++;
                    }
                    else if(etapa == 5) //Endereço
                    {
                        printf("\n\tOlá, %s.\n\n", nome);

                        printf("\tInforme seu endereço: ");
                        if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ.,0-9]", end) != 1) {
                            Msg("Endereço inválido, tente novamente...");
                            continue;
                        }
                        etapa++;
                    }
                    else if(etapa == 6) //Usuário
                    {
                        printf("\n\tOlá, %s.\n\n", nome);

                        printf("\tInforme o seu nome de usuário (exemplo: Susu_Gostoso): ");
                        if(scanf("%[A-Za-z_]", username) != 1) {
                            Msg("Usuário inválido, utilize somente letras.");
                            continue;
                        }
                        etapa++;
                    }
                    else if(etapa == 7) //Senha
                    {
                        printf("\n\tOlá, %s.\n\n", nome);

                        printf("\tInforme sua senha: ");
                        if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ.,@#$()0-9]", password) != 1) {
                            Msg("Senha inválida, por favor tente novamente.");
                            continue;
                        }
                        break;
                    }
                }

                //Resumo das informações
                Clear();
                printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=[ Informações gerais ]=-=-=-=-=-=-=-=-=-=-=-=-=\n");
                printf("\n\tNome: %s\n", nome);
                printf("\n\tData de Nascimento: %d/%d/%d\n", dd, mm, yy);
                printf("\n\tCelular: %s\n", cel);
                printf("\n\tCidade: %s\n", city);
                printf("\n\tEndereço: %s\n", end);
                printf("\n\tNome de usuário: %s\n", username);
                printf("\n\tSenha: %s\n", password);
                printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

                int z;
                printf("\nAs informações estão corretas? (1=SIM | 2=NÃO): ");
                scanf("%d", &z);

                if(z != 1) { //Caso o usuário escolha que as informações estão incorretas, ele retorna a primeira etapa.
                    tUsuario(1);
                }
                else {

                    RegistrarUsuario(nome, cel, city, end, username, password, dd, mm, yy, 0, DINHEIRO_PADRAO);

                    Menu_id = 0;
                    printf("\n\t[INFO] Usuário cadastrado com sucesso, retornando ao menu inicial...\n");
                    Sleep(1500);
                }
            }
            else //Se for usuário comum, apenas ver os dados.
            {
                Header("///          = = = = = = = = Minhas  Informações = = = = = = = =          ///");

                printf("\n\tNome: %s", Usuario[Logado].nome);
                printf("\n\tCelular: %s", Usuario[Logado].celular);
                printf("\n\tCidade: %s", Usuario[Logado].cidade);
                printf("\n\tEndereço: %s", Usuario[Logado].endereco);
                printf("\n\tNome de Usuário: %s", Usuario[Logado].nomeusuario);
                printf("\n\tData de Nascimento: %d/%d/%d", Usuario[Logado].nascimento.dia, Usuario[Logado].nascimento.mes, Usuario[Logado].nascimento.ano);
                printf("\n\tDinheiro: %d", Usuario[Logado].dinheiro);

                Menu_id = 1;
                printf("\n\n\t\t\t>>> Tecle <ENTER> para voltar ao menu usuário...\n");
                getchar();
            }

        break;

        case 2: //Pesquisar usuario
        {
            char FindName[128];
            int i, nFound = 0, escolher_usuario;
            int Encontrados[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

            while(1)
            {
                Header("///          = = = = = = = = Pesquisar Usuário = = = = = = = = =          ///");

                printf("\tInforme nome/telefone/endereço do usuário: ");
                if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ.,0-9]", FindName) != 1) {
                    Msg("Usuário inválido, tente novamente...");
                    continue;
                }

                printf("\n\tUsuário(s) encontrado(s):\n");
                for(i = 0; i < MAX_USERS; i++)
                {
                    if (strcmp(Usuario[i].nome, "InvalidUser") != 0) //Verificando se o usuário é válido...
                    {
                        if(strstr(Usuario[i].nome, FindName) != NULL 
                            || strstr(Usuario[i].celular, FindName) != NULL 
                            || strstr(Usuario[i].cidade, FindName) != NULL 
                            || strstr(Usuario[i].endereco, FindName) != NULL
                            || strstr(Usuario[i].nomeusuario, FindName) != NULL)
                        {
                            Encontrados[nFound] = i;
                            printf("\n\t\t<<[%d]>> %s (%s)", nFound+1, Usuario[i].nome, Usuario[i].nomeusuario);
                            nFound++;
                        }
                    }
                } //Fim do for

                if(nFound > 0)
                {
                    printf("\n\t\t<<[0]>> Sair");
                    printf("\n\n\tInforme qual usuário quer ver as informações: ");
                    scanf("%d", &escolher_usuario);

                    if(escolher_usuario >= 1 && escolher_usuario <= nFound)
                    {
                        const int a = Encontrados[(escolher_usuario-1)];

                        if(a >= 0)
                        {
                            Header("///          = = = = = = = = Pesquisar Usuário = = = = = = = = =          ///");

                            printf("\n\tNome: %s", Usuario[a].nome);
                            printf("\n\tCelular: %s", Usuario[a].celular);
                            printf("\n\tCidade: %s", Usuario[a].cidade);
                            printf("\n\tEndereço: %s", Usuario[a].endereco);
                            printf("\n\tNome de Usuário: %s", Usuario[a].nomeusuario);

                            Menu_id = 1;
                            printf("\n\n\t\t\t>>> Tecle <ENTER> para voltar ao menu usuário...\n");
                            getchar();
                            break;
                        }
                    }
                    else
                    {
                        Menu_id = 0;
                        printf("\n\tVoltando ao menu inicial...\n");
                        Sleep(1500);
                        break;
                    }
                }
                else
                {
                    printf("\n\t[ERRO]: Nenhum usuário encontrado.\n");
                    Sleep(1500);
                    continue;
                }

                break;
            } //Fim do  While
        }
        break;

        case 3: //Atualizar o cadastro de um usuario 
        {
            char Alt_nome[128], Alt_celular[12], Alt_cidade[128], Alt_endereco[128], Alt_usuario[32], Alt_senha[128], Alt_help[20];
            int etp = 0, Alt_dia, Alt_mes, Alt_ano, Alt_admin, Alt_dinheiro, id, max_opcoes;

            while(1)
            {
                Header("///          = = = = = = Atualizar Dados de Usuário  = = = = = =          ///");

                if(etp == 0) //Etapa 0: Escolher qual dado alterar
                {
                    if(Staff != 0) //Se for admin
                    {
                        printf("\tInforme o nome de usuário da conta que deseja alterar: ");
                        if(scanf("%[A-Za-z_]", Alt_usuario) != 1) {
                            Msg("Usuário inválido, utilize somente letras.");
                            continue;
                        }

                        id = Exists(USER, Alt_usuario, 1);

                        if(id == -1)
                        {
                            Msg("Usuário não existe, tente novamente.");
                            continue;
                        }

                        max_opcoes = 9;
                    }
                    else //Se for usuário comum
                    {  
                        id = Logado;
                        max_opcoes = 7;
                    }

                    printf("\n\t [1] Nome (%s)", Usuario[id].nome);
                    printf("\n\t [2] Celular (%s)", Usuario[id].celular);
                    printf("\n\t [3] Cidade (%s)", Usuario[id].cidade);
                    printf("\n\t [4] Endereço (%s)", Usuario[id].endereco);
                    printf("\n\t [5] Nome de Usuário (%s)", Usuario[id].nomeusuario);
                    printf("\n\t [6] Data de Nascimento (%d/%d/%d)", Usuario[id].nascimento.dia, Usuario[id].nascimento.mes, Usuario[id].nascimento.ano);
                    printf("\n\t [7] Senha");

                    if(Staff != 0) //Se for admin
                    {
                        printf("\n\t [8] Nível de admin (%d)", Usuario[id].admin);
                        printf("\n\t [9] Dinheiro (%d)", Usuario[id].dinheiro);
                    }

                    printf("\n\n\t [0] Cancelar\n\n");

                    printf("\tInforme qual informação deseja alterar [1-%d]: ", max_opcoes);
                    if(scanf("%d", &etp) != 1) {
                        etp = 0;
                        Msg("Informação inválida, por favor tente novamente.");
                        continue;
                    }

                    if(etp < 0 || etp > max_opcoes)
                    {
                        etp = 0;
                        Msg("Informação inválida, por favor tente novamente.");
                        continue;
                    }
                    else if(etp == 0)
                    {
                        Menu_id = 1;
                        break;
                    }
                    continue;
                }
                else if(etp == 1) //Etapa 1: Alterar nome
                {
                    printf("\t Informe seu nome: ");

                    if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", Alt_nome) != 1) {
                        Msg("Nome inválido, tente novamente...");
                        continue;
                    }

                    if(AlterarUsuario(Usuario[id].nomeusuario, "nome", Alt_nome) == 1)
                    {
                        printf("\n\tNome alterado com sucesso.\n");
                        Sleep(2000);
                        etp = 0;
                    }
                    else {
                        Msg("Ocorreu algum erro ao alterar, por favor tente novamente.");
                        continue;
                    }
                }
                else if(etp == 2) //Etapa 2: Alterar celular
                {
                    printf("\tInforme seu número de celular (somente números): ");
                    if((scanf("%[0-9]", Alt_celular) != 1) || (strlen(Alt_celular) != 11)) {
                        Msg("Número de celular inválido, tente novamente...");
                        continue;
                    }

                    if(AlterarUsuario(Usuario[id].nomeusuario, "celular", Alt_celular) == 1)
                    {
                        printf("\n\t [INFO] Celular alterado com sucesso.\n");
                        Sleep(2000);
                        etp = 0;
                    }
                    else {
                        Msg("Ocorreu algum erro ao alterar, por favor tente novamente.");
                        continue;
                    }
                }
                else if(etp == 3) //Etapa 3: Alterar cidade
                {
                    printf("\tInforme a cidade que você reside: ");
                    if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ]", Alt_cidade) != 1) {
                        Msg("Cidade inválida, tente novamente...");
                        continue;
                    }

                    if(AlterarUsuario(Usuario[id].nomeusuario, "cidade", Alt_cidade) == 1)
                    {
                        printf("\n\t [INFO] Cidade alterada com sucesso.\n");
                        Sleep(2000);
                        etp = 0;
                    }
                    else {
                        Msg("Ocorreu algum erro ao alterar, por favor tente novamente.");
                        continue;
                    }
                }
                else if(etp == 4) //Etapa 4: Alterar Endereço
                {
                    printf("\tInforme seu endereço: ");
                    if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ.,0-9]", Alt_endereco) != 1) {
                        Msg("Endereço inválido, tente novamente...");
                        continue;
                    }

                    if(AlterarUsuario(Usuario[id].nomeusuario, "endereco", Alt_endereco) == 1)
                    {
                        printf("\n\t [INFO] Endereço alterado com sucesso.\n");
                        Sleep(2000);
                        etp = 0;
                    }
                    else {
                        Msg("Ocorreu algum erro ao alterar, por favor tente novamente.");
                        continue;
                    }
                }
                else if(etp == 5) //Etapa 5: Nome de usuário
                {
                    printf("\tInforme o seu nome de usuário (exemplo: Susu_Gostoso): ");
                    if(scanf("%[A-Za-z_]", Alt_usuario) != 1) {
                        Msg("Usuário inválido, utilize somente letras.");
                        continue;
                    }

                    if(AlterarUsuario(Usuario[id].nomeusuario, "nomeusuario", Alt_usuario) == 1)
                    {
                        printf("\n\t\t [INFO] Nome de usuário alterado com sucesso!\n");
                        Sleep(2000);
                        etp = 0;
                    }
                    else {
                        Msg("Ocorreu algum erro ao alterar, por favor tente novamente.");
                        continue;
                    }
                }
                else if(etp == 6) //Etapa 6: Data de Nascimento
                {
                    printf("\tInforme sua data de nascimento (Exemplo: 17/09/1997): ");
                    scanf("%d/%d/%d", &Alt_dia, &Alt_mes, &Alt_ano);

                    if((ValidarData(Alt_dia, Alt_mes, Alt_ano) == 0))
                    {
                        Msg("Data inválida, tente novamente...");
                        continue;
                    }

                    sprintf(Alt_help, "%d/%d/%d", Alt_dia, Alt_mes, Alt_ano);
                    if(AlterarUsuario(Usuario[id].nomeusuario, "nascimento", Alt_help) == 1)
                    {
                        printf("\n\t\t [INFO] Data de nascimento alterada com sucesso!\n");
                        Sleep(2000);
                        etp = 0;
                    }
                    else {
                        Msg("Ocorreu algum erro ao alterar, por favor tente novamente.");
                        continue;
                    }
                }
                else if(etp == 7) //Etapa 7: Senha
                {
                    printf("\tInforme sua senha: ");
                    if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ.,@#$()0-9]", Alt_senha) != 1) {
                        Msg("Senha inválida, por favor tente novamente.");
                        continue;
                    }

                    if(AlterarUsuario(Usuario[id].nomeusuario, "senha", Alt_senha) == 1)
                    {
                        printf("\n\t\t [INFO] Senha alterada com sucesso!\n");
                        Sleep(2000);
                        etp = 0;
                    }
                    else {
                        Msg("Ocorreu algum erro ao alterar, por favor tente novamente.");
                        continue;
                    }
                }
                else if(etp == 8 && Staff != 0) //Etapa 8: Nível de admin
                {
                    printf("\tInforme o nível de admin (0-1): ");
                    if(scanf("%d", &Alt_admin) != 1) {
                        Msg("Nível de admin inválido, por favor tente novamente.");
                        continue;
                    }

                    sprintf(Alt_help, "%d", Alt_admin);
                    if(AlterarUsuario(Usuario[id].nomeusuario, "admin", Alt_help) == 1)
                    {
                        printf("\n\t\t [INFO] Nível de admin alterado com sucesso!\n");
                        Sleep(2000);
                        etp = 0;
                    }
                    else {
                        Msg("Ocorreu algum erro ao alterar, por favor tente novamente.");
                        continue;
                    }
                }
                else if(etp == 9 && Staff != 0) //Etapa 9: Dinheiro
                {
                    printf("\tInforme o valor do dinheiro (Exemplo: 600): ");
                    if(scanf("%d", &Alt_dinheiro) != 1) {
                        Msg("Dinheiro inválido, por favor tente novamente.");
                        continue;
                    }

                    sprintf(Alt_help, "%d", Alt_dinheiro);
                    if(AlterarUsuario(Usuario[id].nomeusuario, "dinheiro", Alt_help) == 1)
                    {
                        printf("\n\t\t [INFO] Dinheiro alterado com sucesso!\n");
                        Sleep(2000);
                        etp = 0;
                    }
                    else {
                        Msg("Ocorreu algum erro ao alterar, por favor tente novamente.");
                        continue;
                    }

                }
                else //Erro
                {
                    Msg("Ocorreu algum erro ao alterar, tente novamente mais tarde.");
                    etp = 0;
                    continue;
                }
                Menu_id = 1;
                break;
            }
        }
        break;

        case 4: //Excluir um usuario do sistema 
        {
            char UsernameRemove[32];
            int i, uRemove = -1;

            while(1)
            {
                Header("///          = = = = = = = =  Excluir Usuário  = = = = = = = = =          ///");

                if(Staff != 0)
                {
                    printf("\n\tInforme o nome de usuário da pessoa: ");
                    scanf("%s", UsernameRemove);
                    uRemove = Exists(USER, UsernameRemove, 1);
                }
                else {
                    uRemove = Logado;
                }
                
                i = 0;
                if(uRemove != -1)
                {
                    printf("\n\tNome: %s", Usuario[uRemove].nome);
                    printf("\n\tCelular: %s", Usuario[uRemove].celular);
                    printf("\n\tCidade: %s", Usuario[uRemove].cidade);
                    printf("\n\tEndereço: %s", Usuario[uRemove].endereco);

                    printf("\n\n\t Tem certeza que deseja excluir esse usuário? (1=SIM, 0=NÃO): ");
                    scanf("%d", &i);

                    if(i == 1) //Confirmação
                    {
                        if(ExcluirUsuario(Usuario[uRemove].nomeusuario))
                        {
                            printf("\n\t\t\t\tUSUÁRIO REMOVIDO COM SUCESSO.\n");
                            Logado = -1;
                        }
                        else
                        {
                            Msg("Não foi possível excluir o usuário.");
                            continue;
                        }
                    }

                    Menu_id = 0;
                    printf("\n\t\tRetornando ao menu principal...\n");
                    Sleep(2000);
                    break;
                }
                else
                {
                    Msg("Nome de usuário não encontrado.");
                    continue;
                }
            }   
        }
        break;
    }
}

int GetFree(int prefixo)
{
    int i = 0;
    char nome[35];

    while (1)
    {
        FILE *file;

        if(prefixo == BOOK)
        {
            sprintf(nome, "Livros\\Livro_%d.txt", i);
        }
        else if (prefixo == USER)
        {
            sprintf(nome, "Users\\User_%d.txt", i);
        }
        else if(prefixo == ALUGADO)
        {
            sprintf(nome, "Livros\\Alugado_%d.txt", i);
        }

        file = fopen(nome, "r");

        if((file != NULL)) {
            i++;
            fclose(file);
            continue;
        }
        break;
    }
    return i;
}

void RegistrarLivro(char bNome[128], char bAutor[128], int bAno, int bPaginas, char bEditora[128], int bEdicao, int bDepartamento)
{
    char str[256];
    int ID_Book = GetFree(BOOK);

    FILE *file; //Criando variável para manipulação de arquivos
    sprintf(str, "Livros\\Livro_%d.txt", ID_Book);
    file = fopen(str, "w"); //Abrindo o arquivo

    fprintf(file, "%d\n", (ID_Book+100));   //ID do Livro
    fprintf(file, "%s\n", bNome);           //Nome do Livro
    fprintf(file, "%s\n", bAutor);          //Autor do Livro
    fprintf(file, "%d\n", bAno);            //Ano de Lançamento do Livro
    fprintf(file, "%d\n", bPaginas);        //Número de páginas do Livro
    fprintf(file, "%s\n", bEditora);        //Editora do Livro
    fprintf(file, "%d\n", bEdicao);         //Edição do Livro
    fprintf(file, "%d", bDepartamento);   //Departamento do Livro
    fclose(file); //Fechamento do arquivo
}

void ListarLivros(void)
{
    int l;
    char tmpBook[50];

    float preco;

    for(l = 0; l < MAX_LIVROS; l++)
    {
        if (strcmp(Livros[l].nome, "InvalidBook") != 0)
        {
            preco = (Livros[l].paginas * 0.05);

            printf("\n\n==================================================\n");
            printf("\n\t Livro [ID %d]: %s", Livros[l].id, Livros[l].nome);
            printf("\n\t Autor: %s", Livros[l].autor);
            printf("\n\t Ano de Lançamento: %d", Livros[l].ano);
            printf("\n\t Páginas: %d", Livros[l].paginas);
            printf("\n\t Editora: %s", Livros[l].editora);
            printf("\n\t Edição: %d", Livros[l].edicao);
            TagBook(Livros[l].departamento, tmpBook);
            printf("\n\t Departamento [%d]: %s ", Livros[l].departamento, tmpBook);
            printf("\n\t Preço: R$ %d", (int)preco);
        }
    }
}

//Listar livros alugados
void ListarAlugados(void)
{
    int l;

    for(l = 0; l < MAX_LIVROS; l++)
    {
        if (strcmp(Alugados[l].usuario, "InvalidBook") != 0)
        {
            printf("\n\n==================================================\n");
            if (strcmp(Alugados[l].usuario, Usuario[Logado].nomeusuario) == 0)
            {
                printf("\n\t Usuário: %s [VOCÊ]", Alugados[l].usuario);
            }
            else
            {
                printf("\n\t Usuário: %s", Alugados[l].usuario);
            }
            printf("\n\t Livro [ID %d]: %s", Alugados[l].idlivro, Livros[GetBookByID(Alugados[l].idlivro)].nome);
            printf("\n\t Preço do Aluguel: R$ %d", Alugados[l].valorpago);
            printf("\n\t Prazo do Aluguel: %d dias", Alugados[l].prazo);
            printf("\n\t Data/Hora do Aluguel: %d/%d/%d %d:%d", Alugados[l].dia, Alugados[l].mes, Alugados[l].ano, Alugados[l].hora, Alugados[l].minuto);
        }
    }
}


int GetBookByID(int id) {
    return ((int)id-100);
}

void CarregarAlugados(void)
{
    char Susu[256], nome[25], tmpq[256], *temp[10], *token;
    int i, x = 0;

    for(i = 0; i < MAX_LIVROS; i++)
    {
        x = 0;

        sprintf(nome, "Livros\\Alugado_%d.txt", i);
        
        if(AbrirArquivo(nome, Susu))
        {
            token = strtok(Susu, "\n");
            while( token != NULL )
            {
                sprintf(tmpq, "%s", token);
                switch (x)
                {
                    case 0: //Usuário que alugou
                        strcpy(Alugados[i].usuario, tmpq);
                        break;
                    case 1: //ID do Livro Alugado
                        Alugados[i].idlivro = strtol(tmpq, temp, 10);
                        break;
                    case 2: //Valor pago
                        Alugados[i].valorpago = strtol(tmpq, temp, 10);
                        break;
                    case 3: //Dia do aluguel
                        Alugados[i].dia = strtol(tmpq, temp, 10);
                        break;
                    case 4: //Mês do aluguel
                        Alugados[i].mes = strtol(tmpq, temp, 10);
                        break;
                    case 5: //Ano do aluguel
                        Alugados[i].ano = strtol(tmpq, temp, 10);
                        break;
                    case 6: //Hora do aluguel
                        Alugados[i].hora = strtol(tmpq, temp, 10);
                        break;
                    case 7: //Minuto do aluguel
                        Alugados[i].minuto = strtol(tmpq, temp, 10);
                        break;
                    case 8: //Prazo em dias do aluguel
                        Alugados[i].prazo = strtol(tmpq, temp, 10);
                        break;
                } //Fim do Switch
                
                token = strtok(NULL, "\n");
                x++;
            } // Fim do While

            geral.alugados++;
        } //Fim do if
        else
        {
            strcpy(Alugados[i].usuario, "InvalidBook");
        }
    } //Fim do for
}

void CarregarLivros(void)
{
    char Susu[256], nome[25];

    int i, x = 0;
    char *token;

    char tmpq[256];
    char *temp[10];

    for(i = 0; i < MAX_LIVROS; i++)
    {
        x = 0;

        sprintf(nome, "Livros\\Livro_%d.txt", i);
        
        if(AbrirArquivo(nome, Susu))
        {
            token = strtok(Susu, "\n");
            while( token != NULL )
            {
                sprintf(tmpq, "%s", token);
                switch (x)
                {
                    case 0: //ID
                        Livros[i].id = strtol(tmpq, temp, 10);
                        break;
                    case 1: //Nome
                        strcpy(Livros[i].nome, tmpq);
                        break;
                    case 2: //Autor
                        strcpy(Livros[i].autor, tmpq);
                        break;
                    case 3: //Ano de Lançamento
                        Livros[i].ano = strtol(tmpq, temp, 10);
                        break;
                    case 4: //Número de páginas
                        Livros[i].paginas = strtol(tmpq, temp, 10);
                        break;
                    case 5: //Editora
                        strcpy(Livros[i].editora, tmpq);
                        break;
                    case 6: //Edição
                        Livros[i].edicao = strtol(tmpq, temp, 10);
                        break;
                    case 7: //Departamento
                        Livros[i].departamento = strtol(tmpq, temp, 10);
                        break;
                } //Fim do Switch
                
                token = strtok(NULL, "\n");
                x++;
            } // Fim do While
            //printf("\n");
            //printf("[%d] '%s' Carregado com sucesso. \n", i, Usuario[i].nome);
        
            geral.livros++;
        } //Fim do if
        else
        {
            strcpy(Livros[i].nome, "InvalidBook");
        }
    } //Fim do for
}

void AlugarLivro(char usuario[32], int id_livro, int valorpago, int dia, int mes, int ano, int hora, int minuto, int prazo)
{
    char str[256];
    int ID_lAlugar = GetFree(ALUGADO);

    FILE *file; //Criando variável para manipulação de arquivos
    sprintf(str, "Livros\\Alugado_%d.txt", ID_lAlugar);
    file = fopen(str, "w"); //Abrindo o arquivo

    fprintf(file, "%s\n", usuario); //Usuário que alugou o livro
    fprintf(file, "%d\n", id_livro); //ID do Livro Alugado
    fprintf(file, "%d\n", valorpago); //Valor pago pelo livro
    fprintf(file, "%d\n", dia); //Dia de Aluguel
    fprintf(file, "%d\n", mes); //Mês de Aluguel
    fprintf(file, "%d\n", ano); //Ano de Aluguel
    fprintf(file, "%d\n", hora); //Hora de Aluguel
    fprintf(file, "%d\n", minuto); //Minuto de Aluguel
    fprintf(file, "%d", prazo); //Prazo do Aluguel

    fclose(file); //Fechamento do arquivo
}

int AlterarUsuario(char username[32], char alternativa[128], char texto[256])
{

    int id = Exists(USER, username, 1); //Pegar ID da variável do struct pelo nome de usuário
    int numerico, nasc[3];
    char *tmpNumero[20];

    if(id == -1)
    {
        return 0;
    }

    if (strcmp(alternativa, "nome") == 0)
    {
        RegistrarUsuario(texto, Usuario[id].celular, Usuario[id].cidade, Usuario[id].endereco, Usuario[id].nomeusuario, Usuario[id].senha, Usuario[id].nascimento.dia, Usuario[id].nascimento.mes, Usuario[id].nascimento.ano, Usuario[id].admin, Usuario[id].dinheiro);
    }
    else if (strcmp(alternativa, "celular") == 0)
    {
        RegistrarUsuario(Usuario[id].nome, texto, Usuario[id].cidade, Usuario[id].endereco, Usuario[id].nomeusuario, Usuario[id].senha, Usuario[id].nascimento.dia, Usuario[id].nascimento.mes, Usuario[id].nascimento.ano, Usuario[id].admin, Usuario[id].dinheiro);
    }
    else if (strcmp(alternativa, "cidade") == 0)
    {
        RegistrarUsuario(Usuario[id].nome, Usuario[id].celular, texto, Usuario[id].endereco, Usuario[id].nomeusuario, Usuario[id].senha, Usuario[id].nascimento.dia, Usuario[id].nascimento.mes, Usuario[id].nascimento.ano, Usuario[id].admin, Usuario[id].dinheiro);
    }
    else if (strcmp(alternativa, "endereco") == 0)
    {
        RegistrarUsuario(Usuario[id].nome, Usuario[id].celular, Usuario[id].cidade, texto, Usuario[id].nomeusuario, Usuario[id].senha, Usuario[id].nascimento.dia, Usuario[id].nascimento.mes, Usuario[id].nascimento.ano, Usuario[id].admin, Usuario[id].dinheiro);
    }
    else if (strcmp(alternativa, "nomeusuario") == 0)
    {
        RegistrarUsuario(Usuario[id].nome, Usuario[id].celular, Usuario[id].cidade, Usuario[id].endereco, texto, Usuario[id].senha, Usuario[id].nascimento.dia, Usuario[id].nascimento.mes, Usuario[id].nascimento.ano, Usuario[id].admin, Usuario[id].dinheiro);
    }
    else if (strcmp(alternativa, "senha") == 0)
    {
        RegistrarUsuario(Usuario[id].nome, Usuario[id].celular, Usuario[id].cidade, Usuario[id].endereco, Usuario[id].nomeusuario, texto, Usuario[id].nascimento.dia, Usuario[id].nascimento.mes, Usuario[id].nascimento.ano, Usuario[id].admin, Usuario[id].dinheiro);
    }
    else if (strcmp(alternativa, "nascimento") == 0)
    {
        char *dia, *mes, *ano;
        dia = strtok(texto, "/");
        mes = strtok(NULL, "/");
        ano = strtok(NULL, "/");

        nasc[0] = strtol(dia, tmpNumero, 10);
        nasc[1] = strtol(mes, tmpNumero, 10);
        nasc[2] = strtol(ano, tmpNumero, 10);
        
        RegistrarUsuario(Usuario[id].nome, Usuario[id].celular, Usuario[id].cidade, Usuario[id].endereco, Usuario[id].nomeusuario, Usuario[id].senha, nasc[0], nasc[1], nasc[2], Usuario[id].admin, Usuario[id].dinheiro);
    }
    else if (strcmp(alternativa, "admin") == 0)
    {
        numerico = strtol(texto, tmpNumero, 10);
        RegistrarUsuario(Usuario[id].nome, Usuario[id].celular, Usuario[id].cidade, Usuario[id].endereco, Usuario[id].nomeusuario, Usuario[id].senha, Usuario[id].nascimento.dia, Usuario[id].nascimento.mes, Usuario[id].nascimento.ano, numerico, Usuario[id].dinheiro);
    }
    else if (strcmp(alternativa, "dinheiro") == 0)
    {
        numerico = strtol(texto, tmpNumero, 10);
        RegistrarUsuario(Usuario[id].nome, Usuario[id].celular, Usuario[id].cidade, Usuario[id].endereco, Usuario[id].nomeusuario, Usuario[id].senha, Usuario[id].nascimento.dia, Usuario[id].nascimento.mes, Usuario[id].nascimento.ano, Usuario[id].admin, numerico);
    }
    else
    {
        return 0;
    }
    return 1;
}


void RegistrarUsuario(char uNome[128], char uCel[12], char uCidade[128], char uEndereco[128], char Username[32], char uSenha[128], int uDiaNasc, int uMesNasc, int uAnoNasc, int uAdmin, int uDinheiro)
{
    int existe = Exists(USER, Username, 1);
    char str[256];
    int ID_User, l;

    if(existe != -1) //Se o usuário existir...
    {
        ID_User = existe;

        existe = Exists(USER, Username, 0);

        strcpy(Usuario[existe].nome, uNome);
        strcpy(Usuario[existe].nomeusuario, Username);
        strcpy(Usuario[existe].celular, uCel);
        strcpy(Usuario[existe].cidade, uCidade);
        strcpy(Usuario[existe].endereco, uEndereco);
        strcpy(Usuario[existe].senha, uSenha);
        Usuario[existe].nascimento.dia = uDiaNasc;
        Usuario[existe].nascimento.mes = uMesNasc;
        Usuario[existe].nascimento.ano = uAnoNasc;
        Usuario[existe].admin = uAdmin;
        Usuario[existe].dinheiro = uDinheiro;
    }
    else
    {
        ID_User = GetFree(USER);

        for(l = 0; l < MAX_USERS; l++)
        {
            if (strcmp(Usuario[l].nome, "InvalidUser") == 0)
            {
                existe = l;
                break;
            }
        }

        strcpy(Usuario[existe].nome, uNome);
        strcpy(Usuario[existe].nomeusuario, Username);
        strcpy(Usuario[existe].celular, uCel);
        strcpy(Usuario[existe].cidade, uCidade);
        strcpy(Usuario[existe].endereco, uEndereco);
        strcpy(Usuario[existe].senha, uSenha);
        Usuario[existe].nascimento.dia = uDiaNasc;
        Usuario[existe].nascimento.mes = uMesNasc;
        Usuario[existe].nascimento.ano = uAnoNasc;
        Usuario[existe].admin = uAdmin;
        Usuario[existe].dinheiro = uDinheiro;
    }

    FILE *file; //Criando variável para manipulação de arquivos
    sprintf(str, "Users\\User_%d.txt", ID_User);
    file = fopen(str, "w"); //Abrindo o arquivo

    fprintf(file, "%s\n", uNome); //Nome Completo
    fprintf(file, "%s\n", uCel); //Celular
    fprintf(file, "%s\n", uCidade); //Cidade
    fprintf(file, "%s\n", uEndereco); //Endereço
    fprintf(file, "%s\n", Username); //Nome de Usuário
    fprintf(file, "%s\n", uSenha); //Senha
    fprintf(file, "%d\n", uDiaNasc); //Dia de Nascimento
    fprintf(file, "%d\n", uMesNasc); //Mês de Nascimento
    fprintf(file, "%d\n", uAnoNasc); //Ano de Nascimento
    fprintf(file, "%d\n", uAdmin); //Ano de Nascimento
    fprintf(file, "%d", uDinheiro); //Dinheiro
    fclose(file); //Fechamento do arquivo
}


/*

//Pegar o id do arquivo do usuário, exemplo: User_3.txt, retornará 3
Exists(USER, "nome de usuário", 1)

//Pegar o id da variável da struct Usuario[ID], retornará o id pelo nome de usuário
Exists(USER, "nome de usuário", 0)

//Pegar o id do arquivo do livro, exemplo: Livro_3.txt, retornará 3
Exists(BOOK, "id do livro, exemplo: 103", 1)

//Pegar o id da variável da struct Livro[ID], retornará o id pelo id do livro, no caso de 103, retornará 3
Exists(BOOK, "id do livro, exemplo: 103", 0)

*/

int Exists(int codigo, char info[50], int arquivo_variavel)
{
    char Susu[256], nome[35], tmpq[256], *token;
    int i, x = 0, valor = -1, codigoespecifico, max_for;

    if(codigo == USER)
        max_for = MAX_USERS;
    else
        max_for = MAX_LIVROS; 

    for(i = 0; i < max_for; i++)
    {
        if(arquivo_variavel == 1) //Arquivo
        {
            x = 0;

            if(codigo == USER)
            {
                sprintf(nome, "Users\\User_%d.txt", i);
                codigoespecifico = 4;
            }
            else
            {
                sprintf(nome, "Livros\\Livro_%d.txt", i);
                codigoespecifico = 0;
            } 
            
            if(AbrirArquivo(nome, Susu))
            {
                token = strtok(Susu, "\n");
                while( token != NULL )
                {
                    sprintf(tmpq, "%s", token);

                    if(x == codigoespecifico) //Linha 5 do arquivo (nome do usuário)
                    {
                        if (strcmp(tmpq, info) == 0) //Se o nome de usuário for o mesmo informado
                        {
                            valor = i;
                            break;
                        }
                    }
                    token = strtok(NULL, "\n");
                    x++;
                }
            }
        }
        else //Variável
        {
            if(codigo == USER) //Pegar id variável do user
            {
                if (strcmp(Usuario[i].nome, "InvalidUser") != 0 && strcmp(Usuario[i].nomeusuario, info) == 0)
                {
                    valor = i;
                }
            }
            else //Pegar id variável do livro
            {
                sprintf(nome, "%d", Livros[i].id);
                if (strcmp(Livros[i].nome, "InvalidBook") != 0 && strcmp(nome, info) == 0)
                {
                    valor = i;
                }
            }

            
        }
    }
    return valor;
}

int ExcluirUsuario(char username[128])
{
    char Susu[256], nome[25], tmpq[256], *token;
    int i, x = 0, removed = 0, id_var;

    id_var = Exists(USER, username, 1);

    for(i = 0; i < MAX_USERS; i++)
    {
        if(removed != 0) {
            break;
        }

        x = 0;
        sprintf(nome, "Users\\User_%d.txt", i);
        
        if(AbrirArquivo(nome, Susu))
        {
            token = strtok(Susu, "\n");
            while( token != NULL )
            {
                sprintf(tmpq, "%s", token);
                
                if(x == 4)
                {
                    if (strcmp(username, tmpq) == 0) //Se o usuário existir...
                    {
                        remove(nome);
                        removed = 1;
                        break;
                    }
                }
                
                token = strtok(NULL, "\n");
                x++;
            }
        }
    } //Fim do for

    
    if(removed == 1 && id_var != -1) //Se por acaso removeu
    {
        strcpy(Usuario[id_var].nome, "InvalidUser");
        strcpy(Usuario[id_var].nomeusuario, "@DAjdaijidax#$$!!@@#$");
    }

    return removed;
}

void CarregarUsuarios(void)
{
    char Susu[256], nome[25], tmpq[256], *temp[10], *token;
    int i, x = 0;

    for(i = 0; i < MAX_USERS; i++)
    {
        x = 0;

        sprintf(nome, "Users\\User_%d.txt", i);
        
        if(AbrirArquivo(nome, Susu))
        {
            token = strtok(Susu, "\n");
            while( token != NULL )
            {
                sprintf(tmpq, "%s", token);
                switch (x)
                {
                    case 0: 
                        strcpy(Usuario[i].nome, tmpq);
                        break;
                    case 1: 
                        strcpy(Usuario[i].celular, tmpq);
                        break;
                    case 2: 
                        strcpy(Usuario[i].cidade, tmpq);
                        break;
                    case 3: 
                        strcpy(Usuario[i].endereco, tmpq);
                        break;
                    case 4: 
                        strcpy(Usuario[i].nomeusuario, tmpq);
                        break;
                    case 5: 
                        strcpy(Usuario[i].senha, tmpq);
                        break;
                    case 6: 
                        Usuario[i].nascimento.dia = strtol(tmpq, temp, 10);
                        break;
                    case 7: 
                        Usuario[i].nascimento.mes = strtol(tmpq, temp, 10);
                        break;
                    case 8: 
                        Usuario[i].nascimento.ano = strtol(tmpq, temp, 10);
                        break;
                    case 9: 
                        Usuario[i].admin = strtol(tmpq, temp, 10);
                        break;
                    case 10:
                        Usuario[i].dinheiro = strtol(tmpq, temp, 10);
                        break;
                } //Fim do Switch
                
                token = strtok(NULL, "\n");
                x++;
            } // Fim do While
            //printf("\n");
            //printf("[%d] '%s' Carregado com sucesso. \n", i, Usuario[i].nome);

            geral.usuarios++;
        } //Fim do if
        else
        {
            strcpy(Usuario[i].nome, "InvalidUser");
        }
    } //Fim do for
}

int AbrirArquivo(char Arquivo[40], char* StrF)
{
    char texto[256];
    strcpy(StrF, "");

    FILE *file; //Criando variável para manipulação de arquivos
    file = fopen(Arquivo, "r");
    if((file != NULL))
    {
        while(fgets(texto, sizeof(texto), file) != NULL)
        {
             strcat(StrF, texto);
        }
    } 
    else
    {
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

void ListUsers(void)
{
    int l;

    for(l = 0; l < MAX_USERS; l++)
    {
        if (strcmp(Usuario[l].nome, "InvalidUser") != 0)
        {
            printf("\n\n\n==================================================\n");
            printf("\n\t Usuário: [%d]: %s", l, Usuario[l].nome);
            printf("\n\t Celular: %s", Usuario[l].celular);
            printf("\n\t Cidade: %s", Usuario[l].cidade);
            printf("\n\t Endereço: %s", Usuario[l].endereco);
            printf("\n\t Nome de Usuário: %s", Usuario[l].nomeusuario);
            printf("\n\t Senha: %s", Usuario[l].senha);
            printf("\n\t Admin: %d", Usuario[l].admin);
            printf("\n\t Dinheiro: R$ %d", Usuario[l].dinheiro);
            printf("\n\t Data de Nascimento: %d/%d/%d", Usuario[l].nascimento.dia, Usuario[l].nascimento.mes, Usuario[l].nascimento.ano);
        }
    }
}

// Função para exibir informações do projeto
void Tela_Sobre(void)
{
    Clear();
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///             Universidade Federal do Rio Grande do Norte                 ///\n");
    printf("///                 Centro de Ensino Superior do Seridó                     ///\n");
    printf("///               Departamento de Computação e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programação                      ///\n");
    printf("///                  Projeto de Controle de Biblioteca                      ///\n");
    printf("///               Developed by  @SusuGostoso - Out, 2021                    ///\n");
    printf("///             Developed by  @daividfernandoo - Out, 2021                  ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///        = = = = = Projeto de Controle de Biblioteca = = = = =            ///\n");
    printf("///                             SIG-Library                                 ///\n");
    printf("///                                                                         ///\n");
    printf("///   Um Sistema de Controle de Biblioteca é o programa responsável por     ///\n");
    printf("///   controlar os empréstimos de livros aos usuários de uma  biblioteca.   ///\n");
    printf("///   O presente projeto propõe um sistema capaz de gerir o cadastro dos    ///\n");
    printf("///   livros e usuários da biblioteca, permitindo o controle e verificação  ///\n");
    printf("///   dos empréstimos e dos prazos de devolução.                            ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t\t\t>>> Tecle <ENTER> para voltar ao menu principal...\n");
    getchar();
}

void Tela_Principal(void) {
    Clear();
    time(&segundos);
    agora = localtime(&segundos);

    int idade = (agora->tm_year+1900)-Usuario[Logado].nascimento.ano;

    char* diasemana[7] = {"Domingo", "Segunda Feira", "Terça Feira", "Quarta Feira", "Quinta Feira", "Sexta Feira", "Sábado"};

    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         /// %d Usuários carregados. \n", geral.usuarios);
    printf("///             Universidade Federal do Rio Grande do Norte                 /// %d Livros carregados. \n", geral.livros);
    printf("///                 Centro de Ensino Superior do Seridó                     /// %d Livros alugados. \n", geral.alugados);
    printf("///               Departamento de Computação e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programação                      ///\n");
    printf("///                  Projeto de Controle de Biblioteca                      ///\n");
    printf("///               Developed by  @SusuGostoso - Out, 2021                    ///\n");
    printf("///             Developed by  @daividfernandoo - Out, 2021                  ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///        = = = = = Projeto de Controle de Biblioteca = = = = =            ///\n");
    printf("///                             SIG-Library                                 ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                 ///////////////////////////\n");
    printf("///            [1] Menu Usuário                     /// %s (%d anos) \n", Usuario[Logado].nome, idade);
    printf("///            [2] Menu Livros                      /// %d/%d/%d %d:%d [%s] \n", agora->tm_mday, agora->tm_mon+1, agora->tm_year+1900, agora->tm_hour, agora->tm_min, diasemana[agora->tm_wday]);
    printf("///            [3] Sobre                            /// Dinheiro: R$ %d\n", Usuario[Logado].dinheiro);
    printf("///            [4] Créditos                         ///////////////////////////\n");
    printf("///            [0] Sair                                                     ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
}

void Tela_Login(void) {
    Clear();
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///             Universidade Federal do Rio Grande do Norte                 ///\n");
    printf("///                 Centro de Ensino Superior do Seridó                     ///\n");
    printf("///               Departamento de Computação e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programação                      ///\n");
    printf("///                  Projeto de Controle de Biblioteca                      ///\n");
    printf("///               Developed by  @SusuGostoso - Out, 2021                    ///\n");
    printf("///             Developed by  @daividfernandoo - Out, 2021                  ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///        = = = = = Projeto de Controle de Biblioteca = = = = =            ///\n");
    printf("///                             SIG-Library                                 ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Logar                                                     ///\n");
    printf("///            2. Cadastrar                                                 ///\n");
    printf("///            3. Recuperação de senha                                      ///\n");
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
}

void Tela_Menu_Usuario(void) {
    Clear();
    printf("\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                       ///\n");
    printf("///          ===================================================          ///\n");
    printf("///          = = = = = = = = = = = = = = = = = = = = = = = = = =          ///\n");
    printf("///          = = = =  Projeto de Controle de Biblioteca  = = = =          ///\n");
    printf("///          = = = = = = = = = = = = = = = = = = = = = = = = = =          ///\n");
    printf("///          ===================================================          ///\n");
    printf("///               Developed by  @SusuGostoso - Out, 2021                  ///\n");
    printf("///             Developed by  @daividfernandoo - Out, 2021                ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                       ///\n");
    printf("///           = = = = = = = = = = = = = = = = = = = = = = = =             ///\n");
    printf("///           = = = = = = = =  Menu  Usuario  = = = = = = = =             ///\n");
    printf("///           = = = = = = = = = = = = = = = = = = = = = = = =             ///\n");
    printf("///                                                                       ///\n");


    if(Staff != 0) //Se for administrador
    { 
        printf("///           1. Cadastrar um novo usuario                                ///\n");
        printf("///           2. Pesquisar os dados de um usuario                         ///\n");
        printf("///           3. Atualizar o cadastro de um usuario                       ///\n");
        printf("///           4. Excluir um usuario do sistema                            ///\n");
    }
    else //Se não for administrador
    {
        printf("///           1. Meus dados                                               ///\n");
        printf("///           2. Pesquisar os dados de um usuario                         ///\n");
        printf("///           3. Atualizar meus dados                                     ///\n");
        printf("///           4. Excluir minha conta                                      ///\n");
    }
    printf("///           0. Voltar ao menu principal                                 ///\n");
    printf("///                                                                       ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
}

void Tela_Creditos(void) {
    Clear();
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///             Universidade Federal do Rio Grande do Norte                 ///\n");
    printf("///                 Centro de Ensino Superior do Seridó                     ///\n");
    printf("///               Departamento de Computação e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programação                      ///\n");
    printf("///                  Projeto de Controle de Biblioteca                      ///\n");
    printf("///               Developed by  @SusuGostoso - Out, 2021                    ///\n");
    printf("///             Developed by  @daividfernandoo - Out, 2021                  ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///           = = = =  Projeto de Controle de Biblioteca  = = = =          ///\n");
    printf("///                                                                         ///\n");
    printf("///            Este projeto está sendo desenvolvido por:                    ///\n");
    printf("///                                                                         ///\n");
    printf("///            Sueliton dos Santos Medeiros                                 ///\n");
    printf("///            Matrícula: 20210065543                                       ///\n");
    printf("///            E-mail: sueliton.medeiros.098@ufrn.edu.br                    ///\n");
    printf("///            Redes sociais: @suelitonx                                    ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///            Daivid Fernando Soares dos Santos                            ///\n");
    printf("///            Matrícula: 20210053346                                       ///\n");
    printf("///            E-mail: daivid.santos.127@ufrn.edu.br                        ///\n");
    printf("///            Redes sociais: @daivid_fernando                              ///\n");
    printf("///                                                                         ///\n");
    printf("///            Repositório: https://github.com/SusuGostoso/SIG-Library      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t\t\t>>> Tecle <ENTER> para voltar ao menu principal...\n");
    getchar();
}

void Tela_Menu_Livro(void) {
    Clear();
    printf("\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                       ///\n");
    printf("///          ===================================================          ///\n");
    printf("///          = = = = = = = = = = = = = = = = = = = = = = = = = =          ///\n");
    printf("///          = = = =  Projeto de Controle de Biblioteca  = = = =          ///\n");
    printf("///          = = = = = = = = = = = = = = = = = = = = = = = = = =          ///\n");
    printf("///          ===================================================          ///\n");
    printf("///               Developed by  @SusuGostoso - Out, 2021                  ///\n");
    printf("///             Developed by  @daividfernandoo - Out, 2021                ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                       ///\n");
    printf("///           = = = = = = = = = = = = = = = = = = = = = = = =             ///\n");
    printf("///           = = = = = = = =   Menu Livros   = = = = = = = =             ///\n");
    printf("///           = = = = = = = = = = = = = = = = = = = = = = = =             ///\n");
    printf("///                                                                       ///\n");
    printf("///           1. Alugar Livro                                             ///\n");
    printf("///           2. Pesquisar Livro                                          ///\n");
    if(Staff != 0) //Se for admin
    {
        printf("///           3. Cadastrar Livro                                          ///\n");
        printf("///           4. Excluir Livro                                            ///\n");
        printf("///           5. Alterar Livro                                            ///\n");
    }
    else //Se for usuário
    {
        printf("///           3. Meus livros alugados                                     ///\n");
        printf("///           4. Entregar Livro                                           ///\n");
    }
    printf("///           0. Voltar ao menu principal                                 ///\n");
    printf("///                                                                       ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
}

int ValidarData(int dd, int mm, int yy)
{
    //Checar ano
    if (yy >= 1900 && yy <= 9999)
    {
        //Checar meses
        if (mm >= 1 && mm <= 12)
        {
            //Checar dias
            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
                return 1;
            else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
                return 1;
            else if ((dd >= 1 && dd <= 28) && (mm == 2))
                return 1;
            else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
                return 1;
            else
                return 0;
        }
        else return 0;
    }
    return 0;
}

void TagBook(int IDTag, char* StrX)
{
    switch(IDTag)
    {
        case 1: strcpy (StrX, "Administração, Negócios e Economia"); break;
        case 2: strcpy (StrX, "Arte, Cinema e Fotografia"); break;
        case 3: strcpy (StrX, "Artesanato, Casa e Estilo de Vida"); break;
        case 4: strcpy (StrX, "Autoajuda"); break;
        case 5: strcpy (StrX, "Biografias e Histórias Reais"); break;
        case 6: strcpy (StrX, "Ciências"); break;
        case 7: strcpy (StrX, "Computação, Informática e Mídias Digitais"); break;
        case 8: strcpy (StrX, "Crônicas, Humor e Entretenimento"); break;
        case 9: strcpy (StrX, "Direito"); break;
        case 10: strcpy (StrX, "Educação, Referência e Didáticos"); break;
        case 11: strcpy (StrX, "Engenharia e Transporte"); break;
        case 12: strcpy (StrX, "Erótico"); break;
        case 13: strcpy (StrX, "Esportes e Lazer"); break;
        case 14: strcpy (StrX, "Fantasia, Horror e Ficção Científica"); break;
        case 15: strcpy (StrX, "Gastronomia e Culinária"); break;
        case 16: strcpy (StrX, "HQs, Mangás e Graphic Novels"); break;
        case 17: strcpy (StrX, "História"); break;
        case 18: strcpy (StrX, "Infantil"); break;
        case 19: strcpy (StrX, "Inglês e Outras Línguas"); break;
        case 20: strcpy (StrX, "Jovens e Adolescentes"); break;
        case 21: strcpy (StrX, "LGBT"); break;
        case 22: strcpy (StrX, "Literatura e Ficção"); break;
        case 23: strcpy (StrX, "Medicina"); break;
        case 24: strcpy (StrX, "Policial, Suspense e Mistério"); break;
        case 25: strcpy (StrX, "Política, Filosofia e Ciências Sociais"); break;
        case 26: strcpy (StrX, "Religião e Espiritualidade"); break;
        case 27: strcpy (StrX, "Romance"); break;
        case 28: strcpy (StrX, "Saúde e Família"); break;
        case 29: strcpy (StrX, "Turismo e Guias de Viagem"); break;
    }
}

void MensagemErro(char msg[256], int mID) //Modo de uso: MsgEx("mensagem", [id do menu a ser voltado])
{
    Menu_id = mID;
    printf ("\n\t <<ERRO>> %s\n", msg);
    Sleep(2000);
}

void Msg(char msg[256])
{
    printf ("\n\t <<ERRO>> %s\n", msg);
    Sleep(1500);
}

void Header(char title[128])
{
    Clear();
    printf("\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                       ///\n");
    printf("///          ===================================================          ///\n");
    printf("///          = = = = = = = = = = = = = = = = = = = = = = = = = =          ///\n");
    printf("///          = = = =  Projeto de Controle de Biblioteca  = = = =          ///\n");
    printf("%s\n", title);
    printf("///          = = = = = = = = = = = = = = = = = = = = = = = = = =          ///\n");
    printf("///          ===================================================          ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
}

void VerificarLogin()
{
    if(Logado == -1)
    {
        Menu_id = 0;
        MsgEx("Acesso negado.");
    }
}

void Escolha_Usuario(int max_opcoes, int incremento)
{
    int chose;

    printf("\n\t>>> Digite a opção que deseja escolher: "); //Mensagem
    scanf("%d", &chose); //Captura do que o usuario digitou

    if(chose >= 1 && chose <= max_opcoes) {
        chose += incremento;
        Menu_id = chose;
    }
    else if(chose == 0) {
        if(Menu_id == 0) {
            Menu_id = 666;
        }
        else {
            Menu_id = 0;
        }
    }
    else {
        MsgEx("Opção inválida, tente novamente!", Menu_id);
    }
}
