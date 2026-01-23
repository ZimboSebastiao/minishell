# Minishell

<div align="center">

![Minishell](https://img.shields.io/badge/42-São_Paulo-0056D2?style=for-the-badge&logo=42&logoColor=white)
![Language](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=black)
![License](https://img.shields.io/badge/License-MIT-32CD32?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Inprocess-orange?style=for-the-badge)
![Version](https://img.shields.io/badge/Version-1.0.0-blue?style=for-the-badge)

</div>

<div align="center">

![GitHub repo size](https://img.shields.io/github/repo-size/ZimboSebastiao/minishell?style=flat-square&color=0056D2)
![GitHub last commit](https://img.shields.io/github/last-commit/ZimboSebastiao/minishell?style=flat-square&color=32CD32)
![GitHub issues](https://img.shields.io/github/issues/ZimboSebastiao/minishell?style=flat-square&color=orange)
</div>

## Sobre o Projeto

**Minishell** é um projeto que se baseia em um interpretador de comandos shell que interage com o Sistema Operacional, automatiza tarefas repetitivas, gerencia arquivos e executa comandos diretamente do kernel.

## Funcionalidades

### Funcionalidades Obrigatórias
- [x] Exibir um **prompt** enquanto aguarda um novo comando.
- [x] Ter um **histórico** funcional.
- [x] Pesquisar e iniciar o executável correto (com base na variável **PATH** ou usando um
caminho relativo ou absoluto).
- [x] Usar no máximo **uma variável global** para indicar um sinal recebido. Considere
as implicações: essa abordagem garante que seu manipulador de sinal não acessará
suas estruturas de dados principais.
- [x] Não interpretar aspas não fechadas ou caracteres especiais que não são necessários
pelo enunciado, como **\ (barra invertida)** ou **; (ponto e vírgula)**.
- [x] Lidar com **’ (aspas simples)**, que deve impedir o shell de interpretar os metacarac-
teres na sequência entre aspas.
- [x] Lidar com **" (aspas duplas)**, que deve impedir o shell de interpretar os metacarac-
teres na sequência entre aspas, exceto para **$ (sinal de dólar)**.
- [x] Implementar os seguintes **redirecionamentos**:
	- [x] **<** deve redirecionar a entrada.
	- [x]  **>** deve redirecionar a saída.
	- [x] **<<** deve receber um delimitador, então ler a entrada até que uma linha contendo
	o delimitador seja encontrada. No entanto, não precisa atualizar o histórico
	- [x] **>>** deve redirecionar a saída no modo de anexação.
- [x] Implementar **pipes** (caractere |). A saída de cada comando no pipeline é conectada
à entrada do próximo comando via um pipe.
- [x] Lidar com **variáveis de ambiente** ($ seguido de uma sequência de caracteres),
que devem ser expandidas para seus valores.
- [x] Lidar com **$?** que deve expandir para o status de saída do pipeline em primeiro
plano mais recentemente executado.
- [x] Lidar com **ctrl-C, ctrl-D e ctrl-\*** que devem se comportar como em bash.
- [x] No modo **interativo**:
	- [x] **ctrl-C** exibe um novo prompt em uma nova linha.
	- [x] **ctrl-D** sai do shell.
	- [x] **ctrl-\*** não faz nada.
- [x] Seu shell deve implementar os seguintes comandos **built-in**:
	- [x] **echo** com a opção **-n**.
	- [x] **cd** com apenas um caminho relativo ou absoluto.
	- [x] **pwd** sem opções.
	- [x] **export** sem opções.
	- [x] **unset** sem opções.
	- [x] **env** sem opções ou argumentos.
	- [x] **exit** sem opções.

## 🔧 Instalação e Compilação

### 🚀 Compilação Rápida

#### Clone o repositório

```bash
git clone https://github.com/ZimboSebastiao/minishell.git
cd minishell
```
#### Compile tudo

```bash
make
```

###  Comandos do Makefile

| Comando | Descrição |
|---------|-----------|
| `make` ou `make all` | Compila cliente e servidor |
| `make clean` | Remove arquivos objeto |
| `make fclean` | Remove objetos e executáveis |
| `make re` | Recompila completamente |




<div align="center">

### 📞 Contato

[![Email](https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:gloriasebastiao7@gmail.com)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/zimbo-sebasti%C3%A3o-3397a1195/)

### 🌟 Dê uma estrela!

Se este projeto foi útil para você, considere dar uma estrela ⭐

[![GitHub stars](https://img.shields.io/github/stars/ZimboSebastiao/minishell?style=social)](https://github.com/ZimboSebastiao/minishell)

---

**minishell** • Projeto 42 São Paulo • Desenvolvido com 💙

</div>