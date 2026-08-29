#ifndef CATALOGO_H
#define CATALOGO_H

#include "indice_titulos_hash.h"
#include "livro.h"
#include "tabela_hash_extensivel_isbn.h"

#include <iosfwd>
#include <string>
#include <vector>
#include <optional>

class Catalogo {
    
private:
    TabelaHashExtensivelIsbn tabelaHashIsbn;
    IndiceTitulosHash indiceTitulos;

public:
    Catalogo() = default;

    bool cadastrar(const Livro &livro);
    std::optional<Livro> buscarPorIsbn(const std::string &isbn) const;
    std::vector<Livro> buscarPorTitulo(const std::string &titulo) const;
    std::vector<Livro> listarTodos() const;  
    void visualizarHashIsbn(std::ostream &saida) const;
};

#endif
