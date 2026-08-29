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
                std::cin >> ano;

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
            case 4: {
                std::string isbn;
                std::cout << "\n======= Atualizar Livro =======" << std::endl;
                std::cout << "ISBN do livro: ";
                std::getline(std::cin, isbn);

                auto livroAtual = catalogo.buscarPorIsbn(isbn);
                if (!livroAtual) {
                    std::cout << "[Erro] Livro não encontrado." << std::endl;
                    break;
                }

                std::string titulo = livroAtual->getTitulo();
                std::string autor = livroAtual->getAutor();
                std::string editora = livroAtual->getEditora();
                int ano = livroAtual->getAnoPublicacao();
                std::string entrada;

                std::cout << "Novo título [enter para manter o atual]: ";
                std::getline(std::cin, entrada);
                if (!entrada.empty()) {
                    titulo = entrada;
                }

                std::cout << "Novo autor(a) [enter para manter o atual]: ";
                std::getline(std::cin, entrada);
                if (!entrada.empty()) {
                    autor = entrada;
                }

                std::cout << "Nova editora [enter para manter a atual]: ";
                std::getline(std::cin, entrada);
                if (!entrada.empty()) {
                    editora = entrada;
                }

                std::cout << "Novo ano [enter para manter o atual]: ";
                std::getline(std::cin, entrada);
                if (!entrada.empty()) {
                    ano = std::stoi(entrada);
                }

                Livro livroAtualizado(isbn, titulo, autor, editora, ano);
                if (catalogo.atualizar(livroAtualizado)) {
                    std::cout << "[Info] Livro atualizado!" << std::endl;
                } else {
                    std::cout << "[Erro] Não foi possível atualizar o livro." << std::endl;
                }
                break;
            }
            case 5: {
                std::string isbn;
                std::cout << "\n======== Remover Livro ========" << std::endl;
                std::cout << "ISBN do livro: ";
                std::getline(std::cin, isbn);

                if (catalogo.removerPorIsbn(isbn)) {
                    std::cout << "[Info] Livro removido!" << std::endl;
                } else {
                    std::cout << "[Erro] Livro não encontrado." << std::endl;
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
            case 0:
                std::cout << "[Info] Saindo..." << std::endl;
                break;
            default:
                std::cout << "[Erro] Opção inválida! Tente novamente." << std::endl;
        }
    } while (opcao != 0);
}
