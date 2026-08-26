#include "funcao_hash.h"

std::uint64_t calcularHash(const std::string &chave) {
	constexpr std::uint64_t OFFSET_BASIS = 14695981039346656037ULL;
	constexpr std::uint64_t FNV_PRIME = 1099511628211ULL;

	std::uint64_t hash = OFFSET_BASIS;

	for (unsigned char caractere : chave) {
		hash ^= caractere;
		hash *= FNV_PRIME;
	}

	return hash;
}
