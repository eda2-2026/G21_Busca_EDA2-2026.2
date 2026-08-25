#include "livro.h"

using namespace std;

Livro::Livro(const string &isbn, const string &titulo, const string &autor, const string &editora,
			 int anoPublicacao, bool disponivel)
	: isbn(isbn), titulo(titulo), autor(autor), editora(editora), anoPublicacao(anoPublicacao), disponivel(disponivel) {
}

const string &Livro::getIsbn() const {
	return isbn;
}

const string &Livro::getTitulo() const {
	return titulo;
}

const string &Livro::getAutor() const {
	return autor;
}

const string &Livro::getEditora() const {
	return editora;
}

int Livro::getAnoPublicacao() const {
	return anoPublicacao;
}

bool Livro::getDisponivel() const {
	return disponivel;
}

void Livro::setIsbn(const string &isbn) {
	this->isbn = isbn;
}

void Livro::setTitulo(const string &titulo) {
	this->titulo = titulo;
}

void Livro::setAutor(const string &autor) {
	this->autor = autor;
}

void Livro::setEditora(const string &editora) {
	this->editora = editora;
}

void Livro::setAnoPublicacao(int anoPublicacao) {
	this->anoPublicacao = anoPublicacao;
}

void Livro::setDisponivel(bool disponivel) {
	this->disponivel = disponivel;
}