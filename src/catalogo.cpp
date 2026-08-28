#include "catalogo.h"

bool Catalogo::cadastrar(const Livro &livro) {
   return tabelaHashIsbn.inserir(livro);
}

std::optional<Livro> Catalogo::buscarPorIsbn(const std::string &isbn) const {
   return tabelaHashIsbn.buscar(isbn);
}

std::vector<Livro> Catalogo::listarTodos() const {
   return tabelaHashIsbn.listarTodos();
}