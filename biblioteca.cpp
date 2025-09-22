#include "Biblioteca.h"
#include <iostream>

void Biblioteca::adicionarLivro(const Livro& livro) {
    livros.push_back(livro);
    std::cout << "Livro '" << livro.getTitulo() << "' adicionado.\n";
}

void Biblioteca::listarLivros() const {
    if (livros.empty()) {
        std::cout << "Nenhum livro na biblioteca.\n";
        return;
    }
    std::cout << "--- Livros na Biblioteca ---\n";
    for (const auto& livro : livros) {
        std::cout << "Titulo: " << livro.getTitulo()
                  << ", Autor: " << livro.getAutor()
                  << ", ISBN: " << livro.getISBN()
                  << ", Status: " << (livro.isDisponivel() ? "Disponivel" : "Emprestado")
                  << std::endl;
    }
}

Livro* Biblioteca::buscarLivro(const std::string& isbn) {
    for (auto& livro : livros) {
        if (livro.getISBN() == isbn) {
            return &livro;
        }
    }
    return nullptr;
}

void Biblioteca::removerLivro(const std::string& isbn) {
    auto it = std::remove_if(livros.begin(), livros.end(),
                             [&](const Livro& l) { return l.getISBN() == isbn; });
    if (it != livros.end()) {
        livros.erase(it, livros.end());
        std::cout << "Livro com ISBN " << isbn << " removido.\n";
    } else {
        std::cout << "Livro com ISBN " << isbn << " nao encontrado.\n";
    }
}

void Biblioteca::adicionarMembro(const Membro& membro) {
    membros.push_back(membro);
    std::cout << "Membro '" << membro.getNome() << "' adicionado.\n";
}

void Biblioteca::listarMembros() const {
    if (membros.empty()) {
        std::cout << "Nenhum membro registrado.\n";
        return;
    }
    std::cout << "--- Membros da Biblioteca ---\n";
    for (const auto& membro : membros) {
        std::cout << "Nome: " << membro.getNome() << ", ID: " << membro.getIdMembro();
        const auto& livrosEmprestados = membro.getLivrosEmprestados();
        if (!livrosEmprestados.empty()) {
            std::cout << ", Livros emprestados: ";
            for (const auto& livro : livrosEmprestados) {
                std::cout << "'" << livro->getTitulo() << "' ";
            }
        }
        std::cout << std::endl;
    }
}

Membro* Biblioteca::buscarMembro(const std::string& idMembro) {
    for (auto& membro : membros) {
        if (membro.getIdMembro() == idMembro) {
            return &membro;
        }
    }
    return nullptr;
}

void Biblioteca::removerMembro(const std::string& idMembro) {
    auto it = std::remove_if(membros.begin(), membros.end(),
                             [&](const Membro& m) { return m.getIdMembro() == idMembro; });
    if (it != membros.end()) {
        membros.erase(it, membros.end());
        std::cout << "Membro com ID " << idMembro << " removido.\n";
    } else {
        std::cout << "Membro com ID " << idMembro << " nao encontrado.\n";
    }
}

void Biblioteca::emprestarLivro(const std::string& isbn, const std::string& idMembro) {
    Livro* livro = buscarLivro(isbn);
    Membro* membro = buscarMembro(idMembro);

    if (livro && membro) {
        if (livro->isDisponivel()) {
            livro->setDisponivel(false);
            membro->emprestarLivro(livro);
            std::cout << "'" << livro->getTitulo() << "' emprestado para '" << membro->getNome() << "'.\n";
        } else {
            std::cout << "O livro '" << livro->getTitulo() << "' ja esta emprestado.\n";
        }
    } else {
        std::cout << "Livro ou membro nao encontrado.\n";
    }
}

void Biblioteca::devolverLivro(const std::string& isbn, const std::string& idMembro) {
    Livro* livro = buscarLivro(isbn);
    Membro* membro = buscarMembro(idMembro);

    if (livro && membro) {
        livro->setDisponivel(true);
        membro->devolverLivro(livro);
        std::cout << "'" << livro->getTitulo() << "' devolvido por '" << membro->getNome() << "'.\n";
    } else {
        std::cout << "Livro ou membro nao encontrado.\n";
    }
}
