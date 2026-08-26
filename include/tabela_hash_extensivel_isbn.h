#ifndef TABELA_HASH_EXTENSIVEL_ISBN_H
#define TABELA_HASH_EXTENSIVEL_ISBN_H

#include "livro.h"

#include <cstddef>
#include <memory>
#include <vector>

struct BucketIsbn {
	explicit BucketIsbn(std::size_t profundidadeLocal,
						std::size_t capacidade);

	std::size_t profundidadeLocal;
	std::size_t capacidade;
	std::vector<Livro> livros;
};

class TabelaHashExtensivelIsbn {
public:
	explicit TabelaHashExtensivelIsbn(
		std::size_t capacidadeBucket = 4);

	std::size_t getProfundidadeGlobal() const;
	std::size_t getCapacidadeBucket() const;
	std::size_t getTamanhoDiretorio() const;

private:
	std::size_t profundidadeGlobal;
	std::size_t capacidadeBucket;
	std::vector<std::shared_ptr<BucketIsbn>> diretorio;
};

#endif
