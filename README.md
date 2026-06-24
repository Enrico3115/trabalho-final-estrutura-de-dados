# Sistema de Departamentos
**Trabalho Final — Estrutura de Dados | 1º Semestre 2026**

---

## Descrição

Programa em C++ que importa um arquivo `.txt` contendo departamentos e suas palavras-chave, armazena as informações em uma estrutura de dados e permite duas modalidades de pesquisa: por palavra-chave e por nome de departamento.

---

## Estrutura do Projeto

```
.
|-- departamentos.cpp   # Código-fonte principal
|-- departamentos.txt   # Arquivo de dados (gerado a partir do .docx fornecido)
|-- README.md           # Este arquivo
```

---

## Formato do Arquivo de Entrada

O arquivo `.txt` deve conter uma linha por departamento, com os campos separados por espaço:

```
CÓDIGO DEPARTAMENTO PALAVRA1 PALAVRA2 PALAVRA3 PALAVRA4 PALAVRA5
```

**Regras:**
- Exatamente 5 palavras-chave por departamento
- Sem palavras-chave repetidas entre departamentos
- Sem palavras compostas (apenas palavras simples)
- Sem acentos ou caracteres especiais

**Exemplo:**

```
001 FINANCEIRO INVESTIMENTO RENDA GASTOS DESPESAS LUCRO
002 CONTABILIDADE BALANCO BALANCETE RAZAO ENTRADA SAIDA
003 PESSOAL SALARIO VAGAS CONTRATACAO DESLIGAMENTO PROMOCAO
```

---

## Compilação

Requisitos: compilador C++ com suporte ao padrao C++17 (g++ ou equivalente).

```bash
g++ -std=c++17 -o departamentos departamentos.cpp
```

---

## Execução

```bash
./departamentos
```

Ao iniciar, o programa solicita o caminho do arquivo `.txt`:

```
=====================================
 TRABALHO FINAL - ESTRUTURA DE DADOS
 1 Semestre 2026
=====================================

  Informe o caminho do arquivo .txt: departamentos.txt
```

---

## Menu de Opções

```
+=====================================+
|     SISTEMA DE DEPARTAMENTOS        |
+=====================================+
|  1. Pesquisar por palavra-chave     |
|  2. Pesquisar por departamento      |
|  3. Listar todos os departamentos   |
|  4. Importar novo arquivo           |
|  0. Sair                            |
+=====================================+
```

### Opção 1 — Pesquisar por palavra-chave

Informa uma palavra-chave e exibe o departamento correspondente.

```
  Digite a palavra-chave: SALARIO

  +---------------------------------------+
  |  Resultado da pesquisa                |
  +---------------------------------------+
  |  Palavra-chave : SALARIO              |
  |  Departamento  : PESSOAL              |
  |  Codigo        : 003                  |
  +---------------------------------------+
```

### Opção 2 — Pesquisar por departamento

Informa o nome do departamento e exibe o código e as 5 palavras-chave.

```
  Digite o nome do departamento: ESTOQUE

  +---------------------------------------+
  |  Resultado da pesquisa                |
  +---------------------------------------+
  |  Departamento  : ESTOQUE              |
  |  Codigo        : 005                  |
  +---------------------------------------+
  |  Palavras-chave:                      |
  |      1. SALDO                         |
  |      2. MAXIMO                        |
  |      3. MINIMO                        |
  |      4. MEDIO                         |
  |      5. PERDA                         |
  +---------------------------------------+
```

### Opção 3 — Listar todos os departamentos

Exibe uma tabela com todos os departamentos carregados, seus códigos e palavras-chave.

### Opção 4 — Importar novo arquivo

Permite carregar um novo arquivo `.txt` sem encerrar o programa.

### Opção 0 — Sair

Encerra o programa.

---

## Estrutura de Dados Utilizada

```cpp
// Representa um departamento com seu código, nome e palavras-chave
struct Departamento {
    string codigo;              // Ex: "001"
    string nome;                // Ex: "FINANCEIRO"
    string palavras[5];         // Exatamente 5 palavras-chave
};

// Lista dinâmica de departamentos (cresce conforme o arquivo)
vector<Departamento> departamentos;
```

A escolha do `vector` permite que o programa carregue qualquer quantidade de departamentos sem limite fixo definido em código.

---

## Observações

- A pesquisa **nao diferencia maiúsculas de minúsculas**: digitar `salario`, `Salario` ou `SALARIO` produz o mesmo resultado.
- Linhas vazias ou mal formatadas no arquivo `.txt` sao ignoradas com aviso no terminal.
- O arquivo de dados não deve conter acentos, pois terminais sem suporte a UTF-8 exibiriam caracteres incorretos.
