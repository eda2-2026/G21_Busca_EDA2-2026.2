#include "tabela_hash_extensivel_isbn.h"

#include <stdexcept>

BucketIsbn::BucketIsbn(std::size_t profundidadeLocal,
					   std::size_t capacidade)
	: profundidadeLocal(profundidadeLocal), capacidade(capacidade) {
}

TabelaHashExtensivelIsbn::TabelaHashExtensivelIsbn(
	std::size_t capacidadeBucket)
	: profundidadeGlobal(1), capacidadeBucket(capacidadeBucket) {
	if (capacidadeBucket == 0) {
		throw std::invalid_argument(
			"A capacidade do bucket deve ser maior que zero");
	}

	diretorio.push_back(std::make_shared<BucketIsbn>(
		profundidadeGlobal, capacidadeBucket));
	diretorio.push_back(std::make_shared<BucketIsbn>(
		profundidadeGlobal, capacidadeBucket));
}

std::size_t TabelaHashExtensivelIsbn::getProfundidadeGlobal() const {
	return profundidadeGlobal;
}

std::size_t TabelaHashExtensivelIsbn::getCapacidadeBucket() const {
	return capacidadeBucket;
}

std::size_t TabelaHashExtensivelIsbn::getTamanhoDiretorio() const {
	return diretorio.size();
}
