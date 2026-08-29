#include "catalogo.h"

bool Catalogo::cadastrar(const Livro &livro) {
   if (!indiceTitulos.adicionar(livro.getTitulo(), livro.getIsbn())) {
      return false;
   }

   if (!tabelaHashIsbn.inserir(livro)) {
      indiceTitulos.remover(livro.getTitulo(), livro.getIsbn());
      return false;
   }

   return true;
}

std::optional<Livro> Catalogo::buscarPorIsbn(const std::string &isbn) const {
   return tabelaHashIsbn.buscar(isbn);
}

std::vector<Livro> Catalogo::buscarPorTitulo(const std::string &titulo) const {
   const std::vector<std::string> isbns = indiceTitulos.buscar(titulo);
   std::vector<Livro> livros;
   livros.reserve(isbns.size());

   for (const std::string &isbn : isbns) {
      const std::optional<Livro> livro = tabelaHashIsbn.buscar(isbn);

      if (livro) {
         livros.push_back(*livro);
      }
   }

   return livros;
}

std::vector<Livro> Catalogo::listarTodos() const {
   return tabelaHashIsbn.listarTodos();
}

void Catalogo::visualizarHashIsbn(std::ostream &saida) const {
   tabelaHashIsbn.visualizarEstrutura(saida);
}
