#include "indice_titulos_hash.h"

#include "funcao_hash.h"

#include <stdexcept>

IndiceTitulosHash::IndiceTitulosHash(std::size_t quantidadeBuckets)
	: quantidadeBuckets(quantidadeBuckets), buckets(quantidadeBuckets) {
	if (quantidadeBuckets == 0) {
		throw std::invalid_argument(
			"A quantidade de buckets deve ser maior que zero");
	}
}

std::size_t IndiceTitulosHash::getQuantidadeBuckets() const {
	return quantidadeBuckets;
}

std::size_t IndiceTitulosHash::calcularIndice(
	const std::string &tituloNormalizado) const {
	return calcularHash(tituloNormalizado) % quantidadeBuckets;
}
