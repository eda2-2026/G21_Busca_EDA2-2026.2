#include "menu.h"

#include <iostream>
#include <string>
#include <limits>

Menu::Menu(Catalogo &catalogo)
    : catalogo(catalogo) {
}

void Menu::executar() {
    int opcao = -1;

    do {
        std::cout << "\n============ Biblioteca ============" << std::endl;
        std::cout << "[1] Cadastrar livro" << std::endl;
        std::cout << "[2] Buscar por ISBN" << std::endl;
        std::cout << "[3] Buscar por título" << std::endl;
        std::cout << "[4] Atualizar livro" << std::endl;
        std::cout << "[5] Remover livro" << std::endl;
        std::cout << "[6] Listar todos os livros" << std::endl;
        std::cout << "[0] Sair" << std::endl;
        std::cout << "Escolha uma opção: ";

        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                std::cout << "\n========= Cadastrar Livro =========" << std::endl;
                std::string isbn, titulo, autor, editora;
                int ano;

                std::cout << "ISBN: ";
                std::getline(std::cin, isbn);
                
                std::cout << "Título: ";
                std::getline(std::cin, titulo);
                
                std::cout << "Autor(a): ";
                std::getline(std::cin, autor);
                
                std::cout << "Editora: ";
                std::getline(std::cin, editora);
                
                std::cout << "Ano de publicação: ";
                if (!(std::cin >> ano)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Erro: Ano de publicação inválido. Cadastro cancelado." << std::endl;
                    break;
                }

                Livro livro(isbn, titulo, autor, editora, ano);
                
                if (catalogo.cadastrar(livro)) {
                    std::cout << "Sucesso: Livro cadastrado na tabela hash!" << std::endl;
                } else {
                    std::cout << "Erro: O ISBN informado já existe no catálogo." << std::endl;
                }
                break;
            }
            case 2: {
                std::string isbn;
                std::cout << "\n========= Busca =========" << std::endl;
                std::cout << "\nISBN: ";
                std::getline(std::cin, isbn);

                auto livro = catalogo.buscarPorIsbn(isbn);
                if (!livro) {
                    std::cout << "Livro não encontrado." << std::endl;
                    break;
                }

                std::cout << "\n========= Resultado =========" << std::endl;
                std::cout << "ISBN: " << livro->getIsbn() << std::endl;
                std::cout << "Título: " << livro->getTitulo() << std::endl;
                std::cout << "Autor(a): " << livro->getAutor() << std::endl;
                std::cout << "Editora: " << livro->getEditora() << std::endl;
                std::cout << "Ano de publicação: " << livro->getAnoPublicacao() << std::endl;
                break;
            }
            case 0:
                std::cout << "Saindo..." << std::endl;
                break;
            default:
                std::cout << "Opção inválida! Tente novamente." << std::endl;
        }
    } while (opcao != 0);
}
