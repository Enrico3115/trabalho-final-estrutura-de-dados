/*
 * TRABALHO FINAL - ESTRUTURA DE DADOS
 * 1 SEMESTRE 2026
 *
 * Programa de gerenciamento de departamentos com pesquisa por
 * palavra-chave e por nome de departamento.
 *
 * Formato do arquivo de entrada (.txt):
 *   CODIGO DEPARTAMENTO PALAVRA1 PALAVRA2 PALAVRA3 PALAVRA4 PALAVRA5
 *
 * Exemplo:
 *   001 FINANCEIRO CAIXA FLUXO ENTRADA SAIDA DEBITO
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

// ==============================================
//  Constantes
// ==============================================
const int NUM_PALAVRAS = 5;

// ==============================================
//  Estrutura principal
// ==============================================
struct Departamento {
    std::string codigo;
    std::string nome;
    std::string palavras[NUM_PALAVRAS];
};

// ==============================================
//  Funcoes auxiliares
// ==============================================

// Converte string para maiusculas (comparacao case-insensitive)
std::string paraMaiusculo(const std::string& str) {
    std::string resultado = str;
    std::transform(resultado.begin(), resultado.end(),
                   resultado.begin(), ::toupper);
    return resultado;
}

// Remove espacos em branco das extremidades
std::string trim(const std::string& str) {
    size_t inicio = str.find_first_not_of(" \t\r\n");
    if (inicio == std::string::npos) return "";
    size_t fim = str.find_last_not_of(" \t\r\n");
    return str.substr(inicio, fim - inicio + 1);
}

// ==============================================
//  Importacao do arquivo
// ==============================================
bool importarArquivo(const std::string& caminho,
                     std::vector<Departamento>& departamentos) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        std::cerr << "\n  [ERRO] Nao foi possivel abrir o arquivo: "
                  << caminho << "\n";
        return false;
    }

    departamentos.clear();
    std::string linha;
    int numeroLinha = 0;

    while (std::getline(arquivo, linha)) {
        numeroLinha++;
        linha = trim(linha);
        if (linha.empty()) continue;

        std::istringstream ss(linha);
        Departamento dep;

        if (!(ss >> dep.codigo >> dep.nome)) {
            std::cerr << "  [AVISO] Linha " << numeroLinha
                      << " ignorada (formato invalido).\n";
            continue;
        }

        bool linhaValida = true;
        for (int i = 0; i < NUM_PALAVRAS; i++) {
            if (!(ss >> dep.palavras[i])) {
                std::cerr << "  [AVISO] Linha " << numeroLinha
                          << " ignorada (menos de " << NUM_PALAVRAS
                          << " palavras-chave).\n";
                linhaValida = false;
                break;
            }
        }

        if (linhaValida) {
            departamentos.push_back(dep);
        }
    }

    arquivo.close();
    return !departamentos.empty();
}

// ==============================================
//  Pesquisa 1: palavra-chave -> departamento
// ==============================================
void pesquisarPorPalavra(const std::vector<Departamento>& departamentos) {
    std::string busca;
    std::cout << "\n  Digite a palavra-chave: ";
    std::cin >> busca;
    busca = paraMaiusculo(trim(busca));

    bool encontrado = false;

    for (const auto& dep : departamentos) {
        for (int i = 0; i < NUM_PALAVRAS; i++) {
            if (paraMaiusculo(dep.palavras[i]) == busca) {
                std::cout << "\n  +---------------------------------------+\n";
                std::cout << "  |  Resultado da pesquisa                |\n";
                std::cout << "  +---------------------------------------+\n";
                std::cout << "  |  Palavra-chave : "
                          << std::left << std::setw(21) << busca << "|\n";
                std::cout << "  |  Departamento  : "
                          << std::setw(21) << dep.nome << "|\n";
                std::cout << "  |  Codigo        : "
                          << std::setw(21) << dep.codigo << "|\n";
                std::cout << "  +---------------------------------------+\n";
                encontrado = true;
                break;
            }
        }
        if (encontrado) break;
    }

    if (!encontrado) {
        std::cout << "\n  [!] Palavra-chave \"" << busca
                  << "\" nao encontrada em nenhum departamento.\n";
    }
}

// ==============================================
//  Pesquisa 2: departamento -> codigo + palavras-chave
// ==============================================
void pesquisarPorDepartamento(const std::vector<Departamento>& departamentos) {
    std::string busca;
    std::cout << "\n  Digite o nome do departamento: ";
    std::cin >> busca;
    busca = paraMaiusculo(trim(busca));

    bool encontrado = false;

    for (const auto& dep : departamentos) {
        if (paraMaiusculo(dep.nome) == busca) {
            std::cout << "\n  +---------------------------------------+\n";
            std::cout << "  |  Resultado da pesquisa                |\n";
            std::cout << "  +---------------------------------------+\n";
            std::cout << "  |  Departamento  : "
                      << std::left << std::setw(21) << dep.nome << "|\n";
            std::cout << "  |  Codigo        : "
                      << std::setw(21) << dep.codigo << "|\n";
            std::cout << "  +---------------------------------------+\n";
            std::cout << "  |  Palavras-chave:                      |\n";
            for (int i = 0; i < NUM_PALAVRAS; i++) {
                std::string item = "    " + std::to_string(i + 1) +
                                   ". " + dep.palavras[i];
                std::cout << "  |  " << std::left << std::setw(37) << item << "|\n";
            }
            std::cout << "  +---------------------------------------+\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "\n  [!] Departamento \"" << busca
                  << "\" nao encontrado.\n";
    }
}

// ==============================================
//  Lista todos os departamentos
// ==============================================
void listarDepartamentos(const std::vector<Departamento>& departamentos) {
    std::cout << "\n  +------+------------------+------------------------------------------+\n";
    std::cout << "  | Cod  | Departamento     | Palavras-chave                           |\n";
    std::cout << "  +------+------------------+------------------------------------------+\n";

    for (const auto& dep : departamentos) {
        std::string palavras;
        for (int i = 0; i < NUM_PALAVRAS; i++) {
            if (i > 0) palavras += ", ";
            palavras += dep.palavras[i];
        }
        std::cout << "  | " << std::left << std::setw(4) << dep.codigo
                  << " | " << std::setw(16) << dep.nome
                  << " | " << std::setw(40) << palavras << " |\n";
    }

    std::cout << "  +------+------------------+------------------------------------------+\n";
    std::cout << "  Total: " << departamentos.size() << " departamento(s) carregado(s).\n";
}

// ==============================================
//  Menu principal
// ==============================================
void exibirMenu() {
    std::cout << "\n  +=====================================+\n";
    std::cout << "  |     SISTEMA DE DEPARTAMENTOS        |\n";
    std::cout << "  +=====================================+\n";
    std::cout << "  |  1. Pesquisar por palavra-chave     |\n";
    std::cout << "  |  2. Pesquisar por departamento      |\n";
    std::cout << "  |  3. Listar todos os departamentos   |\n";
    std::cout << "  |  4. Importar novo arquivo           |\n";
    std::cout << "  |  0. Sair                            |\n";
    std::cout << "  +=====================================+\n";
    std::cout << "  Opcao: ";
}

// ==============================================
//  Ponto de entrada
// ==============================================
int main() {
    std::vector<Departamento> departamentos;
    std::string caminhoArquivo;

    std::cout << "\n  =====================================\n";
    std::cout << "   TRABALHO FINAL - ESTRUTURA DE DADOS\n";
    std::cout << "   1 Semestre 2026\n";
    std::cout << "  =====================================\n";

    std::cout << "\n  Informe o caminho do arquivo .txt: ";
    std::cin >> caminhoArquivo;

    if (!importarArquivo(caminhoArquivo, departamentos)) {
        std::cout << "\n  Programa encerrado. Nenhum dado foi carregado.\n";
        return 1;
    }

    std::cout << "\n  [OK] " << departamentos.size()
              << " departamento(s) importado(s) com sucesso!\n";

    int opcao;
    do {
        exibirMenu();
        std::cin >> opcao;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n  [!] Opcao invalida. Tente novamente.\n";
            continue;
        }

        switch (opcao) {
            case 1:
                pesquisarPorPalavra(departamentos);
                break;
            case 2:
                pesquisarPorDepartamento(departamentos);
                break;
            case 3:
                listarDepartamentos(departamentos);
                break;
            case 4:
                std::cout << "\n  Informe o caminho do novo arquivo .txt: ";
                std::cin >> caminhoArquivo;
                if (importarArquivo(caminhoArquivo, departamentos)) {
                    std::cout << "\n  [OK] " << departamentos.size()
                              << " departamento(s) importado(s) com sucesso!\n";
                }
                break;
            case 0:
                std::cout << "\n  Programa encerrado. Ate logo!\n\n";
                break;
            default:
                std::cout << "\n  [!] Opcao invalida. Tente novamente.\n";
        }
    } while (opcao != 0);

    return 0;
}
