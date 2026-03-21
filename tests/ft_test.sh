#!/bin/bash

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Contadores
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}  TESTE COMPLETO DO MINISHELL  ${NC}"
echo -e "${BLUE}================================${NC}\n"

# Compila o minishell
echo -e "${YELLOW}Compilando minishell...${NC}"
make re > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Erro na compilação!${NC}"
    exit 1
fi
echo -e "${GREEN}✅ Compilação OK${NC}\n"

# Função para executar teste e verificar resultado
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_pattern="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${CYAN}▶ Teste $TOTAL_TESTS: ${test_name}${NC}"
    echo "   Comando: $command"
    
    # Executa o comando no minishell e captura output e exit code
    output=$(echo "$command" | ./minishell 2>&1)
    exit_code=$?
    
    # Mostra o output (limitado para não poluir)
    echo "   Output:"
    echo "$output" | sed 's/^/     /' | head -10
    if [ $(echo "$output" | wc -l) -gt 10 ]; then
        echo "     ... (mais $(($(echo "$output" | wc -l) - 10)) linhas)"
    fi
    
    # Verifica se o teste passou baseado no expected_pattern
    if [ -n "$expected_pattern" ]; then
        if echo "$output" | grep -q "$expected_pattern"; then
            echo -e "   ${GREEN}✅ PASSOU${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "   ${RED}❌ FALHOU (padrão esperado: '$expected_pattern' não encontrado)${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    elif [ $exit_code -eq 0 ]; then
        echo -e "   ${GREEN}✅ PASSOU${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "   ${RED}❌ FALHOU (exit code: $exit_code)${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
}

# Função para comparar com bash
compare_with_bash() {
    local test_name="$1"
    local command="$2"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${CYAN}▶ Teste $TOTAL_TESTS: ${test_name}${NC}"
    echo "   Comando: $command"
    
    # Executa no bash
    bash_output=$(echo "$command" | bash 2>&1)
    bash_exit=$?
    
    # Executa no minishell
    minishell_output=$(echo "$command" | ./minishell 2>&1)
    minishell_exit=$?
    
    # Compara os outputs (primeiras 3 linhas)
    bash_sample=$(echo "$bash_output" | head -3)
    minishell_sample=$(echo "$minishell_output" | head -3)
    
    echo "   Bash:     $bash_sample"
    echo "   Minishell: $minishell_sample"
    
    # Verifica se são iguais
    if [ "$bash_sample" = "$minishell_sample" ] && [ $bash_exit -eq $minishell_exit ]; then
        echo -e "   ${GREEN}✅ PASSOU (output e exit code iguais)${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "   ${RED}❌ FALHOU${NC}"
        if [ "$bash_sample" != "$minishell_sample" ]; then
            echo -e "   ${RED}     - Output diferente${NC}"
        fi
        if [ $bash_exit -ne $minishell_exit ]; then
            echo -e "   ${RED}     - Exit code diferente (bash: $bash_exit, minishell: $minishell_exit)${NC}"
        fi
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
}

echo -e "${BLUE}1. COMPILAÇÃO E NORMINETTE${NC}"
echo -n "make -n (verificar flags -Wall -Wextra -Werror): "
if make -n | grep -q -E "\-(Werror|Wall|Wextra)"; then
    echo -e "${GREEN}✅ OK${NC}"
else
    echo -e "${RED}❌ Flags não encontradas${NC}"
fi

echo -n "Verificar relink: "
make > /dev/null 2>&1
make > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ OK${NC}"
else
    echo -e "${RED}❌ Falha no relink${NC}"
fi
echo ""

echo -e "${BLUE}2. COMMANDOS SIMPLES${NC}"
run_test "Comando absoluto" "/bin/ls" "minishell"
run_test "Comando vazio" "" ""
run_test "Apenas espaços" "     " ""
run_test "Comando com argumentos" "/bin/ls -la" "total"

echo -e "${BLUE}3. GLOBAL VARIABLES${NC}"
echo -n "Verificar número de variáveis globais (máx 1): "
global_count=$(grep -r "extern int g_signal" --include="*.c" . 2>/dev/null | wc -l)
if [ "$global_count" -le 1 ]; then
    echo -e "${GREEN}✅ OK ($global_count variável(eis))${NC}"
else
    echo -e "${RED}❌ Muitas variáveis globais ($global_count)${NC}"
fi
echo ""

echo -e "${BLUE}4. ARGUMENTOS E HISTÓRICO${NC}"
run_test "Argumentos múltiplos" "ls -la -l -a" "total"
run_test "Comandos diferentes" "pwd" "/home"
run_test "Comandos diferentes" "whoami" "$USER"
run_test "Comandos diferentes" "date" "202"

echo -e "${BLUE}5. ECHO${NC}"
run_test "echo sem argumentos" "echo" ""
run_test "echo com argumentos" "echo hello world" "hello world"
run_test "echo -n" "echo -n hello" "hello"
run_test "echo -nnnnnn" "echo -nnnnnn test" "test"
run_test "echo com -n no meio" "echo hello -n world" "hello -n world"

echo -e "${BLUE}6. EXIT${NC}"
run_test "exit sem argumentos" "exit" ""
echo "Relaunch minishell..."
run_test "exit com argumento" "exit 42" ""
run_test "exit com argumento inválido" "exit abc" "numeric argument required"

echo -e "${BLUE}7. RETURN VALUE${NC}"
compare_with_bash "Exit code de comando válido" "/bin/ls; echo \$?"
compare_with_bash "Exit code de comando inválido" "/bin/ls arquivo_inexistente 2>/dev/null; echo \$?"
compare_with_bash "Múltiplos exit codes" "expr 1 + 1 >/dev/null; echo \$?; expr 2 + 2 >/dev/null; echo \$?"

echo -e "${BLUE}8. SIGNALS${NC}"
echo "⚠️  Testes de signal precisam ser executados manualmente:"
echo "   ./minishell"
echo "   Testar: Ctrl-C, Ctrl-\, Ctrl-D nos cenários descritos"
read -p "   Pressione Enter quando concluir os testes manuais..." dummy
echo ""

echo -e "${BLUE}9. DOUBLE QUOTES${NC}"
run_test "Double quotes com espaços" "echo \"hello world with spaces\"" "hello world with spaces"
run_test "Double quotes com redirecionamento" "echo \"cat lol.c | cat > lol.c\"" "cat lol.c | cat > lol.c"
run_test "Double quotes com variáveis" "echo \"HOME=\$HOME\"" "HOME=/home"

echo -e "${BLUE}10. SIMPLE QUOTES${NC}"
run_test "Simple quotes" "echo 'hello world'" "hello world"
run_test "Simple quotes com variáveis" "echo '\$HOME'" "\$HOME"
run_test "Simple quotes com pipes" "echo '|' '>' '<'" "| > <"
run_test "Simple quotes vazio" "echo ''" ""
run_test "Escape em quotes" "echo '\\USER'" "\\USER"

echo -e "${BLUE}11. ENV${NC}"
run_test "env" "env" "HOME="

echo -e "${BLUE}12. EXPORT${NC}"
run_test "export sem argumentos" "export" "declare -x"
run_test "export nova variável" "export TESTE=123; env | grep TESTE || echo 'FAIL'" "TESTE=123"
run_test "export substituir" "export TESTE=456; env | grep TESTE || echo 'FAIL'" "TESTE=456"

echo -e "${BLUE}13. UNSET${NC}"
run_test "unset variável" "export TESTE=123; unset TESTE; env | grep TESTE || echo 'OK'" "OK"

echo -e "${BLUE}14. CD${NC}"
run_test "cd sem argumentos" "cd; pwd" "/home"
run_test "cd para diretório" "cd /tmp; pwd" "/tmp"
run_test "cd com .." "cd ..; pwd" "/home"
run_test "cd inválido" "cd /diretorio_inexistente " "No such file"

echo -e "${BLUE}15. PWD${NC}"
run_test "pwd" "pwd" "/minishell"
run_test "pwd após cd" "cd /tmp; pwd" "/tmp"

echo -e "${BLUE}16. RELATIVE PATH${NC}"
run_test "Path relativo" "cd /tmp; ls -la ./" "total"
run_test "Path complexo" "cd /usr; ls -la ../bin" "total"

echo -e "${BLUE}17. ENVIRONMENT PATH${NC}"
run_test "Comando sem path" "ls" "minishell"
run_test "Unset PATH" "unset PATH 2>/dev/null; ls 2>&1 || echo 'OK'" "OK"
run_test "PATH múltiplo" "export PATH=/bin:/usr/bin 2>/dev/null; ls" "minishell"

echo -e "${BLUE}18. REDIRECTION${NC}"
run_test "Redirecionamento output" "echo hello > test.txt; cat test.txt" "hello"
run_test "Redirecionamento append" "echo world >> test.txt; cat test.txt" "hello"
run_test "Redirecionamento input" "cat < test.txt" "hello"
run_test "Heredoc" "cat << EOF
line1
line2
EOF" "line1"
run_test "Múltiplos redirecionamentos" "echo test > out1.txt > out2.txt; ls -la out*.txt 2>/dev/null | wc -l" "2"

echo -e "${BLUE}19. PIPES${NC}"
run_test "Pipe simples" "ls -la | grep .c" "main.c"
run_test "Pipe múltiplo" "ls -la | grep .c | wc -l" "[0-9]"
run_test "Pipe com erro" "ls arquivo_inexistente 2>&1 | grep bla | wc -l" "0"
run_test "Pipe com redirecionamento" "ls -la | grep .c > output.txt; cat output.txt" "main.c"

echo -e "${BLUE}20. GO CRAZY${NC}"
run_test "Comando inválido" "dsbksdgbsk 2>&1" "command not found"
run_test "Comando longo" "echo a b c d e f g h i j k l m n o p q r s t u v w x y z" "a b c d e f g h i j k l m n o p q r s t u v w x y z"
run_test "Múltiplos comandos" "pwd; ls; echo done" "done"

echo -e "${BLUE}21. ENVIRONMENT VARIABLES${NC}"
run_test "Expansão \$" "echo \$HOME" "/home"
run_test "Expansão em double quotes" "echo \"\$HOME\"" "/home"
run_test "Escape de \$" "echo \\\$HOME" "\$HOME"
run_test "Variável inexistente" "echo \$VARIAVEL_INEXISTENTE" ""

echo -e "${BLUE}22. CLEANUP${NC}"
echo "Removendo arquivos temporários..."
rm -f test.txt out1.txt out2.txt output.txt "arquivo teste.txt" 2>/dev/null
echo -e "${GREEN}✅ Arquivos removidos${NC}\n"

# RESUMO FINAL
echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}         RESUMO FINAL           ${NC}"
echo -e "${BLUE}================================${NC}"
echo -e "Total de testes: ${CYAN}$TOTAL_TESTS${NC}"
echo -e "${GREEN}Passaram: $PASSED_TESTS${NC}"
echo -e "${RED}Falharam: $FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}🎉 PARABÉNS! TODOS OS TESTES PASSARAM! 🎉${NC}"
else
    echo -e "\n${YELLOW}⚠️  Alguns testes falharam. Verifique os outputs acima.${NC}"
fi

echo -e "\n${YELLOW}Nota: Testes de signal precisam ser validados manualmente${NC}"