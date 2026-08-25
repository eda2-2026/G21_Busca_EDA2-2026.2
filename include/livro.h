#ifndef LIVRO_H
#define LIVRO_H

#include <string>

using namespace std;

class Livro {

private:
	string isbn;
	string titulo;
	string autor;
	string editora;
	int anoPublicacao;
	bool disponivel;

public:
	Livro(const string &isbn, const string &titulo, const string &autor, const string &editora,
		  int anoPublicacao, bool disponivel = true);

	const string &getIsbn() const;
	const string &getTitulo() const;
	const string &getAutor() const;
	const string &getEditora() const;
	int getAnoPublicacao() const;
	bool getDisponivel() const;

	void setIsbn(const string &isbn);
	void setTitulo(const string &titulo);
	void setAutor(const string &autor);
	void setEditora(const string &editora);
	void setAnoPublicacao(int anoPublicacao);
	void setDisponivel(bool disponivel);
};

#endif