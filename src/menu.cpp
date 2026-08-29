#include "menu.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

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
        std::cout << "[7] Visualizar hashing por ISBN" << std::endl;
        std::cout << "[0] Sair" << std::endl;
        std::cout << "Escolha uma opção: ";

        if (!(std::cin >> opcao)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcao = -1;
            std::cout << "[Erro] Opção inválida! Digite um número." << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcao) {
            case 1: {
                std::cout << "\n========= Cadastrar Livro =========" << std::endl;
                std::string isbn, titulo, autor, editora, anoInformado;
                int ano = 0;

                std::cout << "ISBN: ";
                std::getline(std::cin, isbn);
                
                std::cout << "Título: ";
                std::getline(std::cin, titulo);
                
                std::cout << "Autor(a): ";
                std::getline(std::cin, autor);
                
                std::cout << "Editora: ";
                std::getline(std::cin, editora);
                
                std::cout << "Ano de publicação: ";
                std::getline(std::cin, anoInformado);

                std::istringstream conversorAno(anoInformado);
                char caractereExtra;
                if (!(conversorAno >> ano) || (conversorAno >> caractereExtra)) {
                    std::cout << "[Erro] Ano inválido! Digite apenas números." << std::endl;
                    break;
                }

                if (isbn.empty() || titulo.empty() || autor.empty() || editora.empty()) {
                    std::cout << "[Erro] Todos os campos são obrigatórios." << std::endl;
                    break;
                }

                Livro livro(isbn, titulo, autor, editora, ano);
                
                if (catalogo.cadastrar(livro)) {
                    std::cout << "[Info] Livro cadastrado!" << std::endl;
                } else {
                    std::cout << "[Erro] ISBN inválido ou já cadastrado." << std::endl;
                }
                break;
            }
            case 2: {
                std::string isbn;
                std::cout << "\n============== Busca ==============" << std::endl;
                std::cout << "\nISBN: ";
                std::getline(std::cin, isbn);

                auto livro = catalogo.buscarPorIsbn(isbn);
                if (!livro) {
                    std::cout << "[Erro] Livro não encontrado." << std::endl;
                    break;
                }

                std::cout << "\n============ Resultado ============" << std::endl;
                std::cout << "ISBN: " << livro->getIsbn() << std::endl;
                std::cout << "Título: " << livro->getTitulo() << std::endl;
                std::cout << "Autor(a): " << livro->getAutor() << std::endl;
                std::cout << "Editora: " << livro->getEditora() << std::endl;
                std::cout << "Ano de publicação: " << livro->getAnoPublicacao() << std::endl;
                break;
            }
            case 3: {
                std::string titulo;
                std::cout << "\n========= Busca por Título =========" << std::endl;
                std::cout << "Título: ";
                std::getline(std::cin, titulo);

                const auto livros = catalogo.buscarPorTitulo(titulo);
                if (livros.empty()) {
                    std::cout << "[Erro] Livro não encontrado." << std::endl;
                    break;
                }

                std::cout << "\n============ Resultados ============" << std::endl;
                for (const auto &livro : livros) {
                    std::cout << "\nISBN: " << livro.getIsbn() << std::endl;
                    std::cout << "Título: " << livro.getTitulo() << std::endl;
                    std::cout << "Autor(a): " << livro.getAutor() << std::endl;
                    std::cout << "Editora: " << livro.getEditora() << std::endl;
                    std::cout << "Ano de publicação: " << livro.getAnoPublicacao() << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "\n========= Lista de Livros =========" << std::endl;
                auto livros = catalogo.listarTodos();
                if (livros.empty()) {
                    std::cout << "[Info] Nenhum livro cadastrado." << std::endl;
                    break;
                }

                for (const auto &livro : livros) {
                    std::cout << "\nISBN: " << livro.getIsbn() << std::endl;
                    std::cout << "Título: " << livro.getTitulo() << std::endl;
                    std::cout << "Autor(a): " << livro.getAutor() << std::endl;
                    std::cout << "Editora: " << livro.getEditora() << std::endl;
                    std::cout << "Ano de publicação: " << livro.getAnoPublicacao() << std::endl;
                }
                break;
            }
            case 7: {
                std::cout << "\n===== Hashing Extensivel por ISBN =====" << std::endl;
                catalogo.visualizarHashIsbn(std::cout);
                break;
            }
            case 0:
                std::cout << "[Info] Saindo..." << std::endl;
                break;
            default:
                std::cout << "[Erro] Opção inválida! Tente novamente." << std::endl;
        }
    } while (opcao != 0);
}
