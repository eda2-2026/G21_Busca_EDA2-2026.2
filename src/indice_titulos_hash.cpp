#include "indice_titulos_hash.h"

#include "funcao_hash.h"
#include "normalizacao.h"

#include <algorithm>
#include <stdexcept>

IndiceTitulosHash::IndiceTitulosHash(std::size_t quantidadeBuckets)
	: quantidadeBuckets(quantidadeBuckets), buckets(quantidadeBuckets) {
	if (quantidadeBuckets == 0) {
		throw std::invalid_argument(
			"A quantidade de buckets deve ser maior que zero");
	}
}

bool IndiceTitulosHash::adicionar(const std::string &titulo,
								  const std::string &isbn) {
	const std::string tituloNormalizado = normalizarTitulo(titulo);
	const std::string isbnNormalizado = normalizarIsbn(isbn);

	if (tituloNormalizado.empty() || isbnNormalizado.empty()) {
		return false;
	}

	auto &bucket = buckets[calcularIndice(tituloNormalizado)];

	for (EntradaTitulo &entrada : bucket) {
		if (entrada.tituloNormalizado != tituloNormalizado) {
			continue;
		}

		const auto isbnExistente = std::find(
			entrada.isbns.begin(), entrada.isbns.end(), isbnNormalizado);

		if (isbnExistente != entrada.isbns.end()) {
			return false;
		}

		entrada.isbns.push_back(isbnNormalizado);
		return true;
	}

	bucket.push_back({tituloNormalizado, {isbnNormalizado}});
	return true;
}

std::vector<std::string> IndiceTitulosHash::buscar(
	const std::string &titulo) const {
	const std::string tituloNormalizado = normalizarTitulo(titulo);

	if (tituloNormalizado.empty()) {
		return {};
	}

	const auto &bucket = buckets[calcularIndice(tituloNormalizado)];

	for (const EntradaTitulo &entrada : bucket) {
		if (entrada.tituloNormalizado == tituloNormalizado) {
			return entrada.isbns;
		}
	}

	return {};
}

std::size_t IndiceTitulosHash::getQuantidadeBuckets() const {
	return quantidadeBuckets;
}

std::size_t IndiceTitulosHash::calcularIndice(
	const std::string &tituloNormalizado) const {
	return calcularHash(tituloNormalizado) % quantidadeBuckets;
}
