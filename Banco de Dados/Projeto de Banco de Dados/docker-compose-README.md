# 🐘 Ambiente Prático — TCC00335 Projeto de Bancos de Dados

Este repositório contém os **mini-projetos práticos** de cada aula, complementando o material teórico já organizado em `Aula_1/README.md`, `Aula_2/README.md`, etc.

A partir da Aula 2, cada pasta `Aula_N/` ganha um arquivo **`EXERCICIO.md`** com o enunciado prático daquela aula (a Aula 1 é só apresentação da disciplina, então não tem exercício).

## 📦 Pré-requisitos

- [Docker](https://docs.docker.com/get-docker/) instalado
- [Docker Compose](https://docs.docker.com/compose/) (v2, já incluso no Docker Desktop)
- Um cliente SQL de sua preferência (o `psql` via terminal do container já é suficiente; o pgAdmin também sobe junto)

## 🚀 Subindo o ambiente

Na raiz do repositório:

```bash
docker compose up -d
```

Isso sobe dois serviços:

| Serviço   | Acesso                                  | Credenciais                          |
|-----------|------------------------------------------|---------------------------------------|
| PostgreSQL 16 | `localhost:5432` (host) / `postgres:5432` (rede docker) | usuário `aluno` / senha `pbd2026` / banco `projeto_bd` |
| pgAdmin 4 | http://localhost:8080                    | `aluno@uff.br` / `pbd2026`            |

Extensões (`pageinspect`, `pgstattuple`, `postgres_fdw`) já são habilitadas automaticamente na primeira subida via `scripts-init/00_extensoes.sql`.

## 🖥️ Conectando via terminal (mais rápido para os exercícios)

```bash
docker exec -it pbd_postgres psql -U aluno -d projeto_bd
```

## 📂 Como rodar o script de uma aula específica

Cada `Aula_N/scripts/` tem um ou mais arquivos `.sql` (e às vezes um `.sh`) que preparam os dados daquele exercício. Como os scripts em `scripts-init/` só rodam na **primeira** criação do volume, o script de cada aula deve ser executado manualmente, assim vocês podem repetir o exercício quantas vezes quiserem:

```bash
docker exec -i pbd_postgres psql -U aluno -d projeto_bd < Aula_3/scripts/setup.sql
```

## ♻️ Resetando o banco do zero

Se quiser voltar ao estado inicial (apagando tudo que foi criado nos exercícios):

```bash
docker compose down -v
docker compose up -d
```

`-v` remove o volume `pbd_data`, então **todos os dados são perdidos** — use com cuidado.

## 🌐 Exceção: Aula 7 (Fragmentação Horizontal)

Como a Aula 7 trata de **bancos de dados distribuídos**, ela usa um compose complementar com múltiplos containers PostgreSQL simulando nós diferentes. Veja `Aula_7/EXERCICIO.md` e `Aula_7/docker-compose.aula7.yml` para instruções específicas — ele roda **em paralelo** ao compose padrão (portas diferentes), então não precisa derrubar o ambiente principal.

## 🧭 Índice de exercícios

| Aula | Tema | Exercício |
|------|------|-----------|
| 1 | Apresentação da disciplina | — (sem exercício) |
| 2 | Arquitetura Física e Buffer Pool | [`Aula_2/EXERCICIO.md`](./Aula_2/EXERCICIO.md) |
| 3 | Índices e Estruturas de Índices | [`Aula_3/EXERCICIO.md`](./Aula_3/EXERCICIO.md) |
| 4 | Índice Hash | [`Aula_4/EXERCICIO.md`](./Aula_4/EXERCICIO.md) |
| 5 | Árvores B e B+ | [`Aula_5/EXERCICIO.md`](./Aula_5/EXERCICIO.md) |
| 6 | Índices no PostgreSQL | [`Aula_6/EXERCICIO.md`](./Aula_6/EXERCICIO.md) |
| 7 | Fragmentação Horizontal (FHP/FHD) | [`Aula_7/EXERCICIO.md`](./Aula_7/EXERCICIO.md) |
| 8 | Particionamento Avançado | [`Aula_8/EXERCICIO.md`](./Aula_8/EXERCICIO.md) |

---

## 👨🏾‍🏫 Autor & Informações Acadêmicas

Organizado por **João Victor Labre**

Graduando em Sistemas de Informação — Universidade Federal Fluminense (UFF)

---

## 📧 Contact

<div align="center">
    <a href="https://github.com/LabreCoder">
        <img alt="GitHub" src="https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white"/>
    </a>     
    <a href="https://www.linkedin.com/in/joão-victor-labre">
        <img alt="LinkedIn" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=LinkedIn&logoColor=white"/>
    </a>     
    <a href="mailto:jvlabremachado@gmail.com">
        <img alt="Email" src="https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=Gmail&logoColor=white"/>
    </a>
</div>