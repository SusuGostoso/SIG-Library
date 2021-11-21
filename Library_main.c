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
void TagBook(int IDTag, char* StrX);

void ListUsers(void);
int GetFreeUser();
void RegistrarUsuario(char uNome[128], char uCel[12], char uCidade[128], char uEndereco[128], char Username[32], char uSenha[128], int uDiaNasc, int uMesNasc, int uAnoNasc, int uAdmin);
int AbrirArquivo(char Arquivo[40], char* StrF);
void CarregarUsuarios(void);

//Variáveis púlicas
int Menu_id = 0;
int Logado = 0; //Verificar se o usuário fez login
int Staff = 0; //Verficiar se o usuário é um administrador

//usuários fictícios
#define MAX_USERS 10
#define MAX_LIVROS 50

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
    struct user_data_nascimento nascimento;
}
Usuario[MAX_USERS];

// Programa principal
int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    
    CarregarUsuarios(); //Carregar Usuários

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
                    printf("\n\t Admin: %d", Usuario[Logado].admin);
                    
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

            tUsuario(1);
        
        break;

        case 3: //Esqueci a senha
        {
            int ForgetEx = 1;
            int dd, mm, yy; //Data de nascimento (dia, mês, ano)
            char nome[50], cel[12], username[32], password[128];

            while(ForgetEx != 666)
            {
                Header("///          = = = = = = = =   Recuperar Senha   = = = = = = = =          ///");

                if(ForgetEx == 1) //Nome e Sobrenome
                {
                    printf("\tInforme seu Nome e Sobrenome: ");
                    if(scanf("%[A-Z a-z]", nome) != 1) {
                        Msg("Nome inválido, tente novamente...");
                        continue;
                    }
                    ForgetEx++;
                }
                else if(ForgetEx == 2) //Data de Nascimento
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
                else if(ForgetEx == 3) //Número de celular (apenas numeros)
                {
                    printf("\n\tOlá, %s.\n", nome);

                    printf("\n\tInforme seu número de celular (somente números): ");
                    
                    if ((scanf("%[0-9]", cel) != 1) || (strlen(cel) != 11)) {
                        Msg("Número de celular inválido, tente novamente...");
                        continue;
                    }
                    ForgetEx++;
                }
                else if(ForgetEx == 4) //Usuário
                {
                    printf("\n\tOlá, %s.\n\n", nome);

                    printf("\tInforme o seu nome de usuário (exemplo: Susu_Gostoso): ");
                    if(scanf("%[A-Z_a-z]", username) != 1) {
                        Msg("Usuário inválido, utilize somente letras.");
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
        
            Header("///          = = = = = = = = =  Alugar  Livro  = = = = = = = = =          ///");
            MsgEx("Função ainda em desenvolvimento...", 2);
        
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
                Clear();
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
                    if(scanf("%[A-ZÁÉÍÓÚÂÊÔÇÀÃÕ a-záéíóúâêôçàãõ0-9_]", bNome) != 1) {
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
            
            while(1)
            {
                Clear();
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

                RegistrarUsuario(nome, cel, city, end, username, password, dd, mm, yy, 0);

                Menu_id = 0;
                printf("\n\t[INFO] Usuário cadastrado com sucesso, retornando ao menu inicial...\n");
                Sleep(1500);
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
        
            Header("///          = = = = = = Atualizar Dados de Usuário  = = = = = =          ///");
            MsgEx("Função ainda em desenvolvimento...", 1);
        
        break;

        case 4: //Excluir um usuario do sistema 
        
            Header("///          = = = = = = = =  Excluir Usuário  = = = = = = = = =          ///");
            MsgEx("Função ainda em desenvolvimento...", 1);
        
        break;


    }
}

int GetFreeUser()
{
    int i = 0;
    char nome[20];

    while (1)
    {
        FILE *file;
        sprintf(nome, "Users\\User_%d.txt", i);
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

/*
struct user_estrutura
{
    char nome[128];
    char celular[12];
    char cidade[128];
    char endereco[128];
    char nomeusuario[32];
    char senha[128];
    int admin;
    struct user_data_nascimento nascimento;
}
*/

void RegistrarUsuario(char uNome[128], char uCel[12], char uCidade[128], char uEndereco[128], char Username[32], char uSenha[128], int uDiaNasc, int uMesNasc, int uAnoNasc, int uAdmin)
{
    char str[256];
    int ID_User = GetFreeUser();

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
    fprintf(file, "%d", uAdmin); //Ano de Nascimento
    fclose(file); //Fechamento do arquivo
    //printf("Usuário ID %d (%s): cadastrado com sucesso.\n", ID_User, uNome);
    //Menu_id = 2;
    //Sleep(2000);
}

void CarregarUsuarios(void)
{
    char Susu[256], nome[25];

    int i, x = 0;
    char *token;

    char tmpq[256];
    char *temp[10];

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
                } //Fim do Switch
                
                token = strtok(NULL, "\n");
                x++;
            } // Fim do While
            //printf("\n");
            //printf("[%d] '%s' Carregado com sucesso. \n", i, Usuario[i].nome);
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
    
    if(Staff != 0)
    {
        printf("\tBem vindo, administrador %s.\n", Usuario[Logado].nome);
    }
    else
    {
        printf("\tBem vindo, %s.\n", Usuario[Logado].nome);
    }
    
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
    printf("///            1. Módulo Usuario                                            ///\n");
    printf("///            2. Módulo Livros                                             ///\n");
    printf("///            3. Módulo Sobre                                              ///\n");
    printf("///            4. Módulo Creditos                                           ///\n");
    //printf("///            5. Módulo Staff                                              ///\n"); 
    printf("///            0. Sair                                                      ///\n");
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
    printf("///           1. Cadastrar um novo usuario                                ///\n");
    printf("///           2. Pesquisar os dados de um usuario                         ///\n");
    printf("///           3. Atualizar o cadastro de um usuario                       ///\n");
    printf("///           4. Excluir um usuario do sistema                            ///\n");
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
    if(Staff != 0)
    {
        printf("///           3. Cadastrar Livro                                          ///\n");
        printf("///           4. Excluir Livro                                            ///\n");
        printf("///           5. Alterar Livro                                            ///\n");
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
    Sleep(1000);
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

    if(chose >= 1 && chose <= max_opcoes)
    {
        chose += incremento;
        Menu_id = chose;
    }
    else if(chose == 0)
    {
        if(Menu_id == 0)
        {
            Menu_id = 666;
        }
        else
        {
            Menu_id = 0;
        }
    }
    else
    {
        MsgEx("Opção inválida, tente novamente!", Menu_id);
    }
}
