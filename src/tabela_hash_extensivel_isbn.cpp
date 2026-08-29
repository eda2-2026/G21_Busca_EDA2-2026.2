#include "tabela_hash_extensivel_isbn.h"

#include "normalizacao.h"
#include "funcao_hash.h"

#include <cctype>
#include <stdexcept>
#include <unordered_set>

BucketIsbn::BucketIsbn(std::size_t profundidadeLocal, std::size_t capacidade)
	: profundidadeLocal(profundidadeLocal), capacidade(capacidade) {
}

TabelaHashExtensivelIsbn::TabelaHashExtensivelIsbn(std::size_t capacidadeBucket)
	: profundidadeGlobal(1), capacidadeBucket(capacidadeBucket) {
	if (capacidadeBucket == 0) {
		throw std::invalid_argument("A capacidade do bucket deve ser maior que zero");
	}

	diretorio.push_back(std::make_shared<BucketIsbn>(profundidadeGlobal, capacidadeBucket));
	diretorio.push_back(std::make_shared<BucketIsbn>(profundidadeGlobal, capacidadeBucket));
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

bool TabelaHashExtensivelIsbn::isbnValido(const std::string &isbnNormalizado) {
	if (isbnNormalizado.empty()) {
		return false;
	}

	for (std::size_t i = 0; i < isbnNormalizado.size(); ++i) {
		unsigned char caractere = static_cast<unsigned char>(isbnNormalizado[i]);

		if (std::isdigit(caractere)) {
			continue;
		}

		if (caractere == 'X' && i + 1 == isbnNormalizado.size()) {
			continue;
		}

		return false;
	}

	return true;
}

std::size_t TabelaHashExtensivelIsbn::calcularIndice(std::uint64_t hash) const {
	std::uint64_t mascara = (1ULL << profundidadeGlobal) - 1ULL;
	return static_cast<std::size_t>(hash & mascara);
}

void TabelaHashExtensivelIsbn::duplicarDiretorio() {
	std::size_t tamanhoAnterior = diretorio.size();
	diretorio.reserve(tamanhoAnterior * 2);

	for (std::size_t indice = 0; indice < tamanhoAnterior; ++indice) {
		diretorio.push_back(diretorio[indice]);
	}

	++profundidadeGlobal;
}

void TabelaHashExtensivelIsbn::dividirBucket(const std::shared_ptr<BucketIsbn> &bucket) {
	std::size_t novaProfundidadeLocal = bucket->profundidadeLocal + 1;
	auto novoBucket = std::make_shared<BucketIsbn>(novaProfundidadeLocal, capacidadeBucket);
	bucket->profundidadeLocal = novaProfundidadeLocal;

	std::size_t bitDeDivisao = 1ULL << (novaProfundidadeLocal - 1);

	for (std::size_t indice = 0; indice < diretorio.size(); ++indice) {
		if (diretorio[indice] == bucket && (indice & bitDeDivisao) != 0) {
			diretorio[indice] = novoBucket;
		}
	}

	std::vector<Livro> livrosParaRedistribuir = std::move(bucket->livros);
	bucket->livros.clear();

	for (const Livro &livro : livrosParaRedistribuir) {
		std::size_t indice = calcularIndice(calcularHash(livro.getIsbn()));
		diretorio[indice]->livros.push_back(livro);
	}
}

bool TabelaHashExtensivelIsbn::inserir(const Livro &livro) {
	std::string isbnNormalizado = normalizarIsbn(livro.getIsbn());

	if (!isbnValido(isbnNormalizado)) {
		return false;
	}

	std::uint64_t hash = calcularHash(isbnNormalizado);
	Livro livroNormalizado(isbnNormalizado, livro.getTitulo(), livro.getAutor(), livro.getEditora(), livro.getAnoPublicacao());

	while (true) {
		auto bucket = diretorio[calcularIndice(hash)];

		for (const Livro &livroExistente : bucket->livros) {
			if (livroExistente.getIsbn() == isbnNormalizado) {
				return false;
			}
		}

		if (bucket->livros.size() < bucket->capacidade) {
			bucket->livros.push_back(livroNormalizado);
			return true;
		}

		if (profundidadeGlobal == 63 && bucket->profundidadeLocal == profundidadeGlobal) {
			bucket->livros.push_back(livroNormalizado);
			return true;
		}

		if (bucket->profundidadeLocal == profundidadeGlobal) {
			duplicarDiretorio();
		}

		dividirBucket(bucket);
	}
}

std::optional<Livro> TabelaHashExtensivelIsbn::buscar(const std::string &isbn) const {
	std::string isbnNormalizado = normalizarIsbn(isbn);

	if (!isbnValido(isbnNormalizado)) {
		return std::nullopt;
	}

	const auto &bucket = diretorio[calcularIndice(calcularHash(isbnNormalizado))];

	for (const Livro &livro : bucket->livros) {
		if (livro.getIsbn() == isbnNormalizado) {
			return livro;
		}
	}

	return std::nullopt;
}

bool TabelaHashExtensivelIsbn::atualizar(const Livro &livro) {
	std::string isbnNormalizado = normalizarIsbn(livro.getIsbn());

	if (!isbnValido(isbnNormalizado)) {
		return false;
	}

	auto &bucket = diretorio[calcularIndice(calcularHash(isbnNormalizado))];
	Livro livroNormalizado(isbnNormalizado, livro.getTitulo(), livro.getAutor(), livro.getEditora(), livro.getAnoPublicacao());

	for (Livro &livroExistente : bucket->livros) {
		if (livroExistente.getIsbn() == isbnNormalizado) {
			livroExistente = livroNormalizado;
			return true;
		}
	}

	return false;
}

bool TabelaHashExtensivelIsbn::remover(const std::string &isbn) {
	std::string isbnNormalizado = normalizarIsbn(isbn);

	if (!isbnValido(isbnNormalizado)) {
		return false;
	}

	auto &bucket = diretorio[calcularIndice(calcularHash(isbnNormalizado))];

	for (auto livro = bucket->livros.begin(); livro != bucket->livros.end(); ++livro) {
		if (livro->getIsbn() == isbnNormalizado) {
			bucket->livros.erase(livro);
			return true;
		}
	}

	return false;
}

std::vector<Livro> TabelaHashExtensivelIsbn::listarTodos() const {
	std::vector<Livro> livros;
	std::unordered_set<const BucketIsbn *> bucketsVisitados;

	for (const auto &bucket : diretorio) {
		if (!bucketsVisitados.insert(bucket.get()).second) {
			continue;
		}

		for (const Livro &livro : bucket->livros) {
			livros.push_back(livro);
		}
	}

	return livros;
}
