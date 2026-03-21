Este projeto foi criado como parte do currículo da 42 por zimbo e etelvina

Descrição
O Minishell é uma implementação simplificada de um shell inspirado no bash. O objetivo é criar um ambiente de linha de comando capaz de interpretar e executar comandos, gerenciar processos, redirecionamentos, pipes, variáveis de ambiente e sinais. Desenvolvido em C, o projeto proporciona um entendimento profundo sobre criação e gerenciamento de processos e descritores de arquivos.

Instruções
Compilação
bash
make        # compila o projeto
make clean  # remove arquivos objeto
make fclean # remove arquivos objeto e executável
make re     # recompila do zero
Execução
bash
./minishell
Exemplos de Uso
bash
minishell$ ls -la
minishell$ echo "hello world"
minishell$ cd /tmp
minishell$ pwd
minishell$ export TESTE=123
minishell$ env | grep TESTE
minishell$ cat << EOF
> linha 1
> linha 2
> EOF
minishell$ ps | grep minishell | wc -l
minishell$ exit 42
Recursos
Referências
Bash Reference Manual

The Linux Programming Interface

Minishell Subject

Uso de IA
A IA foi utilizada para esclarecimentos sobre algumas funcionalidades do bash e maior entendimento sobre como o bash funciona internamente quando recebe sinais, além da importância da IPC (Inter-Process Communication) para trabalhar com pipes.
