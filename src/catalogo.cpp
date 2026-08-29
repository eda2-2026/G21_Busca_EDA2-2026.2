#include "catalogo.h"

#include "normalizacao.h"

bool Catalogo::cadastrar(const Livro &livro) {
   if (!tabelaHashIsbn.inserir(livro)) {
      return false;
   }

   if (indiceTitulos.adicionar(livro.getTitulo(), livro.getIsbn())) {
      return true;
   }

   tabelaHashIsbn.remover(livro.getIsbn());
   return false;
}

std::optional<Livro> Catalogo::buscarPorIsbn(const std::string &isbn) const {
   return tabelaHashIsbn.buscar(isbn);
}

bool Catalogo::atualizar(const Livro &livro) {
   std::optional<Livro> livroAnterior = tabelaHashIsbn.buscar(livro.getIsbn());
   if (!livroAnterior) {
      return false;
   }

   if (normalizarTitulo(livroAnterior->getTitulo()) == normalizarTitulo(livro.getTitulo())) {
      return tabelaHashIsbn.atualizar(livro);
   }

   if (!indiceTitulos.adicionar(livro.getTitulo(), livro.getIsbn())) {
      return false;
   }

   if (!tabelaHashIsbn.atualizar(livro)) {
      indiceTitulos.remover(livro.getTitulo(), livro.getIsbn());
      return false;
   }

   if (indiceTitulos.remover(livroAnterior->getTitulo(), livro.getIsbn())) {
      return true;
   }

   tabelaHashIsbn.atualizar(*livroAnterior);
   indiceTitulos.remover(livro.getTitulo(), livro.getIsbn());
   return false;
}

bool Catalogo::removerPorIsbn(const std::string &isbn) {
   std::optional<Livro> livro = tabelaHashIsbn.buscar(isbn);
   if (!livro) {
      return false;
   }

   if (!indiceTitulos.remover(livro->getTitulo(), livro->getIsbn())) {
      return false;
   }

   if (tabelaHashIsbn.remover(livro->getIsbn())) {
      return true;
   }

   indiceTitulos.adicionar(livro->getTitulo(), livro->getIsbn());
   return false;
}

std::vector<Livro> Catalogo::listarTodos() const {
   return tabelaHashIsbn.listarTodos();
}