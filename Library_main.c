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

//Telas Secundárias
void mUsuario(int ID);
void mLivros(int ID);

//Funções
void MensagemErro(char msg[256], int mID);
void Escolha_Usuario(int max_opcoes, int incremento);
void Header(char title[500]);

//Variáveis púlicas
int Menu_id = 0;

// Programa principal
int main(void)
{
    int escolha = 0;

    while (Menu_id != 666)
    {
        switch (Menu_id)
        {
            case 0: //Tela Principal

                Tela_Principal(); //Exibição da Tela Principal
                Escolha_Usuario(4, 0); //Escolha dele, 4 opções, incremento de 0 (se escolher 1, o Menu_id será 1)
                continue;
                
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
                
                mUsuario((Menu_id-5));
                continue;

            break;

            case 11: case 12: case 13: case 14: case 15: //módulo Livros: cadastrar, alterar, alugar, excluir e pesquisar.
                
                mLivros((Menu_id-10));
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

void MensagemErro(char msg[256], int mID) //Modo de uso: MsgEx("mensagem", [id do menu a ser voltado])
{
    Menu_id = mID;
    printf ("\n\t <<ERRO>> %s\n", msg);
    Sleep(2000);
}

void Header(char title[500])
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

void mLivros(int ID)
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
        Header("///          = = = = = = = = = Cadastrar Livro = = = = = = = = =          ///");
        MsgEx("Função ainda em desenvolvimento...", 2);
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

void mUsuario(int ID)
{
    switch (ID)
    {
        case 1: //Cadastrar um novo usuario
        Header("///          = = = = = = = = Cadastrar Usuário = = = = = = = = =          ///");
        MsgEx("Função ainda em desenvolvimento...", 1);
        break;

        case 2: //Pesquisar usuario
        Header("///          = = = = = = = = Pesquisar Usuário = = = = = = = = =          ///");
        MsgEx("Função ainda em desenvolvimento...", 1);
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
    printf("///           3. Cadastrar Livro                                          ///\n");
    printf("///           4. Excluir Livro                                            ///\n");
    printf("///           5. Alterar Livro                                            ///\n");
    printf("///           0. Voltar ao menu principal                                 ///\n");
    printf("///                                                                       ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
}