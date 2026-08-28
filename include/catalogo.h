#ifndef CATALOGO_H
#define CATALOGO_H

#include "livro.h"
#include "tabela_hash_extensivel_isbn.h"

#include <string>
#include <vector>
#include <optional>

class Catalogo {
    
private:
    TabelaHashExtensivelIsbn tabelaHashIsbn;

public:
    Catalogo() = default;

    bool cadastrar(const Livro &livro);
    std::optional<Livro> buscarPorIsbn(const std::string &isbn) const;
    std::vector<Livro> listarTodos() const;  
};

#endif
