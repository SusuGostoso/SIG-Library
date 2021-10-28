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

//Telas
void Tela_Sobre(void);
void Tela_Principal(void);
void Tela_Menu_Usuario(void);
void Tela_Creditos(void);
void Tela_Menu_Livro(void);

// Programa principal
int main(void)
{
    int play = 0, cont = 0, mod = 0;

    while (play != 666)
    {
        switch (play)
        {
            case 0:
                Tela_Principal(); //Exibição da Tela Principal
                printf("Insira o numero do modulo que deseja escolher: "); //Mensagem
                scanf("%d", &mod); //Captura do que o usuario digitou

                if(mod >= 1 & mod <= 5) {
                    play = mod;
                }
                else {
                    printf ("\n\tValor invalido!\n");
                    Sleep(1000);
                    play = 0;
                }
                continue;
            break;

            case 1: //Modulo Usuario
            
                Tela_Menu_Usuario();
                printf ("\n\t >>>Este modulo ainda está em desenvolvimento, retornando ao menu prinicipal...\n");
                Sleep(3000);
                play = 0;
                continue;
            
            break;

            case 2: //Modulo Staff  
               
                system("clear||cls");
                printf ("\n\t >>>Este modulo ainda está em desenvolvimento, retornando ao menu prinicipal...\n");
                Sleep(3000);
                play = 0;
                continue;

            break;

            case 3: //Modulo Livros
                
                Tela_Menu_Livro();
                printf ("\n\t >>>Este modulo ainda está em desenvolvimento, retornando ao menu prinicipal...\n");
                Sleep(3000);
                play = 0;
                continue;

            break;

            case 4: //Modulo Sobre 
            
                Tela_Sobre();
                printf ("\n\t >>>Este modulo ainda está em desenvolvimento, retornando ao menu prinicipal...\n");
                Sleep(3000);
                play = 0;
                continue;

            break;

            case 5: //Modulo Creditos 
            
                Tela_Creditos();
                printf ("\n\t >>>Este modulo ainda está em desenvolvimento, retornando ao menu prinicipal...\n");
                Sleep(3000);
                play = 0;
                continue;

            break;
        }

    }

    system("pause");
    return 0;
}

// Função para exibir informações do projeto
void Tela_Sobre(void)
{
    system("clear||cls");
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
}

void Tela_Principal(void) {
    system("clear||cls");
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
    printf("///            1. Modulo Usuario                                            ///\n");
    printf("///            2. Modulo Staff                                              ///\n");
    printf("///            3. Modulo Livros                                             ///\n");
    printf("///            4. Modulo Sobre                                              ///\n");
    printf("///            5. Modulo Creditos                                           ///\n");
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
}

void Tela_Menu_Usuario(void) {
    system("clear||cls");
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
    printf("///           0. Voltar ao menu anterior                                  ///\n");
    printf("///                                                                       ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
}

void Tela_Creditos(void) {
    system("clear||cls");
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
}

void Tela_Menu_Livro(void) {
    system("clear||cls");
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