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

// Assinatura das funções
void Tela_Sobre(void);
void Tela_Principal(void);
void Tela_Menu_Usuario(void);

// Programa principal
int main(void)
{
    Tela_Principal();

    int mod;
    printf("Insira o numero do modulo que deseja escolher: ");
    scanf("%d", &mod);

    switch (mod)
    {
        case 1:
        Tela_Menu_Usuario();
        break;

        case 2:
        printf("Voce escolheu o modulo de staffs.\n");
        break;

        case 3:
        printf("Voce escolheu o modulo de livros.\n");
        break;

        case 4:
        printf("Voce escolheu o modulo de sobre.\n");
        break;

        default :
        printf ("Valor invalido!\n");
        Tela_Principal();
    }

    printf("\n");
    getchar();

    system("pause");
    return 0;
}

// Função para exibir informações do projeto
void Tela_Sobre(void)
{
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
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    //getchar();
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
    printf("///               Developed by  @SusuGostoso - Out, 2021                    ///\n");
    printf("///             Developed by  @daividfernandoo - Out, 2021                  ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                       ///\n");
    printf("///           = = = = = = = = = = = = = = = = = = = = = = = =             ///\n");
    printf("///           = = = = = = = =  Menu Usuario = = = = = = = = =             ///\n");
    printf("///           = = = = = = = = = = = = = = = = = = = = = = = =             ///\n");
    printf("///                                                                       ///\n");
    printf("///           1. Cadastrar um novo usuario                                ///\n");
    printf("///           2. Pesquisar os dados de um usuario                         ///\n");
    printf("///           3. Atualizar o cadastro de um usuario                       ///\n");
    printf("///           4. Excluir um usuario do sistema                            ///\n");
    printf("///           0. Voltar ao menu anterior                                  ///\n");
    printf("///                                                                       ///\n");
    printf("///           Escolha a opção desejada:                                   ///\n");
    printf("///                                                                       ///\n");
    printf("///                                                                       ///\n");
    printf("/////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\t\t\t>>> Tecle <ENTER> para continuar...\n");
    getchar();
}