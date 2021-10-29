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
void Tela_Creditos(void);
void Tela_Menu_Livro(void);
void Tela_Sobre(void);

//Telas Secundárias
void MensagemErro(char msg[256], int mID);

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
                printf("Insira o número do módulo que deseja escolher: "); //Mensagem
                scanf("%d", &escolha); //Captura do que o usuario digitou

                if(escolha >= 1 & escolha <= 5) {
                    Menu_id = escolha;
                }
                else {
                    MsgEx("Valor inválido, tente novamente.");
                }
                continue;
            break;

            case 1: //módulo Usuario
            
                Tela_Menu_Usuario();
                
                printf("\n\t>>> Digite a opção que deseja escolher: "); //Mensagem
                scanf("%d", &escolha); //Captura do que o usuario digitou

                if(escolha >= 1 & escolha <= 4) {
                    escolha += 5;
                    Menu_id = escolha;
                }
                else if(escolha == 0){
                    Menu_id = 0;
                } else {
                    MsgEx("Opção inválida, tente novamente!", 1);
                }
                continue;
            
            break;

            case 2: //módulo Staff  
               
                Clear();
                MsgEx("Este módulo ainda está em desenvolvimento, retornando ao menu prinicipal...");
                continue;

            break;

            case 3: //módulo Livros
                
                Tela_Menu_Livro();
                MsgEx("Este módulo ainda está em desenvolvimento, retornando ao menu prinicipal...");
                continue;

            break;

            case 4: //módulo Sobre 
            
                Tela_Sobre();
                Menu_id = 0;
                continue;

            break;

            case 5: //módulo Creditos 
            
                Tela_Creditos();
                Menu_id = 0;
                continue;

            break;

            case 6: //módulo Usuario: Cadastrar um novo usuario 
                Clear();
                MsgEx("Este módulo ainda está em desenvolvimento, retornando ao menu prinicipal...");
                continue;
            break;

            case 7: //módulo Usuario: Pesquisar os dados de um usuario 
                Clear();
                MsgEx("Este módulo ainda está em desenvolvimento, retornando ao menu prinicipal...");
                continue;
            break;

            case 8: //módulo Usuario: Atualizar o cadastro de um usuario 
                Clear();
                MsgEx("Este módulo ainda está em desenvolvimento, retornando ao menu prinicipal...");
                continue;
            break;

            case 9: //módulo Usuario: Excluir um usuario do sistema 
                Clear();
                MsgEx("Este módulo ainda está em desenvolvimento, retornando ao menu prinicipal...");
                continue;
            break;
        }

    }

    system("pause");
    return 0;
}

void MensagemErro(char msg[256], int mID) //Modo de uso: MsgEx("mensagem", [id do menu a ser voltado])
{
    Menu_id = mID;
    printf ("\n\t <<ERRO>> %s\n", msg);
    Sleep(2000);
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
    printf("///            2. Módulo Staff                                              ///\n");
    printf("///            3. Módulo Livros                                             ///\n");
    printf("///            4. Módulo Sobre                                              ///\n");
    printf("///            5. Módulo Creditos                                           ///\n");
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
    printf("///                                                                       ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
}