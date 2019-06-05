#!/bin/sh
## mini_mouli_6.sh for 42sh in /home/Thery/Desktop/PSU_2016_42sh
## 
## Made by Thery Fouchter
## Login   <thery.fouchter@epitech.eu>
## 
## Started on  Wed Jan 18 01:40:59 2017 Thery Fouchter
## Last update Mon Jun  5 16:06:02 2017 Thery Fouchter
##

## =============================================================================
## CONFIG
## =============================================================================

color='y'
verbose='y'
timeout='1s'
logs_txt='logs/logs.txt'
logs_42sh='logs/logs_42sh'
logs_tcsh='logs/logs_tcsh'

## =============================================================================
## HELP
## =============================================================================

help_me () {
    echo -e "Cette mini moulinette$c_red n'est pas parfaite$c_nc et risque de ne pas vous envoyer exactement les bons resultats!"
    echo -e "Elle compare des commandes envoyee sur votre ./42sh puis au tcsh lui meme."
    echo -e "Je vous conseille de$c_red l'utiliser sur votre Blinux$c_nc ainsi qu en la$c_red lancant depuis le tcsh$c_nc lui meme (pour l environnement)"
    echo -e ""
    echo -e "-> Lister les tests avec l'argument $c_green./mouli list$c_nc"
    echo -e "-> Supprimer le dossier temporairement crée 'logs' avec l'argument$c_green ./mouli clean$c_nc"
    echo -e "-> Lancer un test en particulier avec l'argument$c_green ./mouli debug [START] [END]$c_nc"
    echo -e ""
    echo -e "Jetez un oeil au$c_green dossier logs$c_nc qui sera cree pour l occasion avec 3 fichiers logs importants:"
    echo -e "-$c_green logs.txt$c_nc -> recapitule tout ce que vous devez savoir sur ce qu il s est passe"
    echo -e "-$c_green logs.42sh$c_nc -> seulement le 42sh"
    echo -e "-$c_green logs.tcsh$c_nc -> seulement le tcsh"
    echo -e ""
    echo -e "De plus, la mouli cree des fichiers .c qui sont au prealable compiles."
    echo -e "Ils effectuent des programmes pas tres gentils qui crashent ou return une valeur precise."
    echo -e "$c_red"
    echo -e "Je ne suis pas responsable si vous pushez le dossier logs avec des fichiers .c qui ne sont pas a la norme ;)$c_nc"
    echo -e "Cree par Fouchter Thery (thery.fouchter@epitech.eu)"
}

## =============================================================================
## SCRIPT
## =============================================================================

debug='0'
debug_max='9999'
test_number='0'
test_ok='0'
test_ko='0'
test_crash='0'
list='0'
no_env='0'
if [ $color = 'y' ]
then
    c_red='\033[0;31m'
    c_green='\033[0;32m'
    c_nc='\033[0m'
else
    c_red=''
    c_green=''
    c_nc=''
fi

init () {
    if [ ! -f ./42sh ]
    then
	while true
	do
	    read -p './42sh not found, execute make re ? [y/n] ' answer
	    if [ "$answer" = 'y' ] || [ "$answer" = 'Y' ]
	    then
		make re
		break
	    fi
	    break
	done
    fi
    if [ ! -f ./42sh ]
    then
	echo './42sh not found.'
	exit
    fi
    mkdir -p logs
    echo 'minishell1' > $logs_42sh
    echo 'minishell1' > $logs_tcsh
    echo 'Therynosaure Alpha' > $logs_txt
    echo "int main(void){char *str;str=0;*str=42;}" > logs/segfault_core.c
    echo "#include <sys/prctl.h>" > logs/segfault.c
    echo "int main(void){char *str;prctl(PR_SET_DUMPABLE,0);str=0;*str=42;}" >> logs/segfault.c
    echo "int main(void){int i=0;int a=42/i;}" > logs/float.c
    echo "#include <unistd.h>" > logs/hello.c
    echo "int main(void){write(1,\"Hello World !\",13);char c=10;write(1,&c,1);return(0);}" >> logs/hello.c
    echo "int main(void){return(42);}" > logs/42.c
    echo 'Hello World !' > logs/hello_world
    rm -f tmp
    rm -f tutu
    gcc -o segfault_core logs/segfault_core.c
    gcc -o segfault logs/segfault.c
    gcc -o float logs/float.c
    gcc -o hello logs/hello.c
    gcc -o 42 logs/42.c
    mv -t logs segfault segfault_core float hello 42
    cp -n logs/hello logs/hello_nw
    chmod 000 logs/hello_nw
    title '---------------- start ----------------'
}

finish () {
    title '---------------- done ! ---------------'
    rm -f tmp
    rm -f tutu
    if [ $debug -eq 0 ] && [ $verbose = 'y' ] && [ $list -ne 1 ]
    then
	echo "Passed: $((test_ok * 100 / test_number))% ($test_ok / $test_number)"
	echo "Crashed: $((test_crash * 100 / test_number))% ($test_crash / $test_number)"
    fi
    if [ $debug -ne 0 ] && [ $verbose = 'y' ] && [ $list -ne 1 ]
    then
	if [ $debug_max -gt $test_number ]
	then
	    debug_max=$test_number
	fi
	test_number=$((debug_max - debug + 1))
	echo "Passed: $((test_ok * 100 / test_number))% ($test_ok / $test_number)"
	echo "Crashed: $((test_crash * 100 / test_number))% ($test_crash / $test_number)"
    fi
}

title () {
    echo '==========================================================' >> $logs_txt
    echo '==========================================================' >> $logs_42sh
    echo '==========================================================' >> $logs_tcsh
}

log_diff () {
    diff -I '_=*' logs/tmp1 logs/tmp2 > logs/tmp_diff
    res_diff=$?
    log
    if [ $verbose = 'y' ] && [ $res_diff -ne 0 ]
    then
	echo -e '/------Diff-------\'
	echo -e '|      42sh       |'
	echo -e '<<<<<<<<<<<<<<<<<<<'
	cat logs/tmp_diff | head
	echo -e '>>>>>>>>>>>>>>>>>>>'
	echo -e '|      tcsh       |'
	echo -e '\-----------------/'
	echo ''
    fi
}

log_grep () {
    cat logs/tmp1 | grep $1 > logs/tmp1
    cat logs/tmp2 | grep $1 > logs/tmp2
    diff logs/tmp1 logs/tmp2
    res_diff=$?
    log
}

log () {
    if [ $res_diff -ne 0 ]
    then
	out='Output : KO'
    else
	out='Output : OK'
    fi
    if [ $ret1 -eq $ret2 ]
    then
	ret="Return : OK ($ret1)"
    else
	ret="Return : KO ($ret1 / $ret2)"
    fi
    if [ $res_diff -ne 0 ] || [ ! $ret1 -eq $ret2 ]
    then
	echo $out >> $logs_txt
	echo $ret >> $logs_txt
	echo '-------------------------> OUTPUT : ./42sh <-------------------------' >> $logs_txt
	cat logs/tmp1 >> $logs_txt
	echo '-------------------------> OUTPUT : tcsh   <-------------------------' >> $logs_txt
	cat logs/tmp2 >> $logs_txt
	echo '-------------------------> OUTPUT : diff   <-------------------------' >> $logs_txt
	diff -I '_=*' logs/tmp1 logs/tmp2 >> $logs_txt 2>&1
    else
	echo 'OK' >> $logs_txt
    fi
    if [ $verbose = 'y' ]
    then
	if [ $res_diff -ne 0 ] || [ $ret1 -ne $ret2 ]
	then
	    if [ $ret1 -gt 128 ]
	    then
		test_crash=$((test_crash + 1))
	    fi
	    test_ko=$((test_ko + 1))
	    echo -ne "[$c_red KO $c_nc] "
	else
	    test_ok=$((test_ok + 1))
	    echo -ne "[$c_green OK $c_nc] "
	fi
	echo -ne 'Output :'
	if [ $res_diff -ne 0 ]
	then
	    echo -ne "$c_red KO $c_nc "
	else
	    echo -ne "$c_green OK $c_nc "
	fi
	echo -ne 'Return :'
	if [ $ret1 -eq $ret2 ]
	then
	    echo -e "$c_green OK $c_nc ($ret1)"
	else
	    if [ $ret1 -eq '124' ]
	    then
		echo -ne "$c_red TIMEOUT ($timeout) $c_nc"
	    else
		echo -ne "$c_red KO $c_nc"
	    fi
	    echo -e " ($ret1 / $ret2)"
	fi
	echo ''
    fi
    echo $out >> $logs_42sh
    echo $ret >> $logs_42sh
    echo $out >> $logs_tcsh
    echo $ret >> $logs_tcsh
    cat logs/tmp1 >> $logs_42sh
    cat logs/tmp2 >> $logs_tcsh
    echo '' >> $logs_42sh
    echo '' >> $logs_tcsh
    echo '' >> $logs_txt
}

exec_test () {
    test_number=$((test_number + 1))
    if [ $list -eq 1 ]
    then
	echo "{$test_number} $1 $2"
    else
	if [ $debug -eq 0 ] || [ $test_number -ge $debug ] && [ $test_number -le $debug_max ]
	then
	    title
	    if [ $verbose = 'y' ]
	    then
		echo "{$test_number} $1 $2"
	    fi
	    echo "{$test_number} $1 $2" >> $logs_txt
	    echo "{$test_number} $1 $2" >> $logs_42sh
	    echo "{$test_number} $1 $2" >> $logs_tcsh
	    title
	    IFS='%'
	    if [ $no_env -eq 0 ]
	    then
		echo -e $2 | timeout $timeout ./42sh > logs/tmp1 2>&1
		ret1=$?
		echo -e $2 | timeout $timeout tcsh > logs/tmp2 2>&1
		ret2=$?
	    else
		echo -e $2 | timeout $timeout env -i ./42sh > logs/tmp1 2>&1
		ret1=$?
		echo -e $2 | timeout $timeout env -i tcsh > logs/tmp2 2>&1
		ret2=$?
	    fi
	    unset IFS
	    log_diff
	fi
    fi
}

## =============================================================================
## PARSING
## =============================================================================

if [ $# -eq 2 ] && [ $1 = 'debug' ]
then
    if [[ $2 =~ ^-?[0-9]+$ ]]
    then
	debug=$2
    else
	echo 'Invalid debug value: Must be a number.'
	exit
    fi
else
    if [ $# -eq 3 ] && [ $1 = 'debug' ]
    then
	if [[ $2 =~ ^-?[0-9]+$ ]] && [[ $3 =~ ^-?[0-9]+$ ]]
	then
	    debug=$2
	    debug_max=$3
	else
	    echo 'Invalid debug value: Must be a number.'
	    exit
	fi
    else
	if [ $# -eq 1 ] && [ $1 = 'list' ]
	then
	    list='1'
	else
	    if [ $# -eq 1 ] && [ $1 = 'clean' ]
	    then
		echo "Removing 'logs' folder."
		rm -rf logs
		echo "Removing 'salut tutu tmp tmp2 damn' files."
		rm -f salut tutu tmp tmp2 damn
		exit
	    else
		if [ $# -ge 1 ]
		then
		    if [ $1 = 'h' ] || [ $1 = 'help' ] || [ $1 = '-h' ] || [ $1 = '-help' ] || [ $1 = '--help' ]
		    then
			help_me
		    else
			echo 'Maybe try -h option ?'
		    fi
		    exit
		fi
	    fi
	fi
    fi
fi
if [ ! -d logs ]
then
    init
    echo "Created 'logs' folder, launch again to start!"
    echo "Don't forget that you can execute ./mouli -h for additional infos!"
    exit
fi

## =============================================================================
## TESTS
## =============================================================================

init

exec_test '---_empty_---' ''
exec_test '---_filled_spaces_---' '                '
exec_test '---_filled_tabs_---' '			'
exec_test '---_simple_command_---' 'pwd'
exec_test '---_multiple_args_---' 'ls -la'
exec_test '---_multiple_args_---' 'ls -l -a'
exec_test '---_invalid_arg_---' 'ls -w'
exec_test '---_invalid_command_---' 'hello'
exec_test '---_simple_command_with_spaces---' '    pwd     '
exec_test '---_multiple_args_with_spaces---' '  ls    -l       -a     '
exec_test '---_multiple_args_with_tabs---' '	ls		-l	-a	'
exec_test '---_multiple_args_with_tabs_and_spaces---' '  	ls	  	  -l	 -a  	 '
exec_test '---_basic_exec_---' 'logs/hello'
exec_test '---_spe_basic_exec_---' './logs/hello'
exec_test '---_spe_basic_exec_---' 'logs/../logs/hello'
exec_test '---_spe_basic_exec_---' './logs/../logs/hello'
exec_test '---_error_path_exec_---' '/ls'
exec_test '---_error_folder_exec_---' 'bin/ls'
exec_test '---_path_exec_---' '/bin/ls'
exec_test '---_segfault_core_exec_---' 'logs/segfault_core'
exec_test '---_segfault_exec_---' 'logs/segfault'
exec_test '---_no_rights_exec_---' 'logs/hello_nw'
exec_test '---_floating_exec_---' 'logs/float'
exec_test '---_error_exec_---' './hello'
exec_test '---_basic_return_---' 'logs/42'
exec_test '---_basic_cd_---' 'cd logs ; pwd'
exec_test '---_basic_spe_cd_---' 'cd . ; pwd'
exec_test '---_basic_spe_cd_---' 'cd .. ; pwd'
exec_test '---_empty_cd_---' 'cd ; pwd'
exec_test '---_path_cd_---' 'cd / ; pwd'
exec_test '---_path_cd_---' 'cd /bin ; pwd'
exec_test '---_old_cd_---' 'cd logs ; pwd ; cd - ; pwd'
exec_test '---_old_cd_---' 'cd ; pwd ; cd - ; pwd'
exec_test '---_cd_error---' 'cd a b ; pwd'
exec_test '---_cd_error---' 'cd /root ; pwd'
exec_test '---_advanced_cd_---' 'cd -- logs ; pwd ; cd -- - ; pwd'
exec_test '---_advanced_cd_---' 'cd -- ; pwd ; cd - -- ; pwd'
exec_test '---_advanced_error_cd_---' 'cd - logs ; pwd'
exec_test '---_advanced_error_cd_---' 'cd -- - ; pwd'
exec_test '---_advanced_error_cd_---' 'cd -- logs - ; pwd'
exec_test '---_advanced_error_cd_---' 'cd /bin/ls ; pwd'
exec_test '---_basic_env_---' 'env'
exec_test '---_basic_setenv_---' 'setenv'
exec_test '---_basic_setenv_2_---' 'setenv one ; env'
exec_test '---_basic_setenv_3_---' 'setenv one two ; env'
exec_test '---_error_setenv_---' 'setenv one two three ; env'
exec_test '---_error_setenv_---' 'setenv one=two three ; env'
exec_test '---_check_setenv_---' 'setenv one_two three ; env'
exec_test '---_error_setenv_2_---' 'setenv 42onetwo three ; env'
exec_test '---_check_setenv_2_---' 'setenv one42two three ; env'
exec_test '---_basic_unsetenv_---' 'setenv hello ; unsetenv hello ; env'
exec_test '---_basic_unsetenv_---' 'setenv hello ; unsetenv hello ; env'
exec_test '---_multiple_unsetenv_---' 'setenv hello ; setenv world ; unsetenv hello world ; env'
exec_test '---_error_unsetenv_---' 'unsetenv ; env'
no_env=1
exec_test '---_check_no_env_---' 'pwd'
no_env=0
exec_test '---_error_arg_---' '/usr/bin ; pwd'
exec_test '---_check_basic_cmd_---' 'ls -l nothing'
exec_test '---_simple_pipe_---' 'ls | cat -e'
exec_test '---_double_pipe_---' 'ls | cat -e | cat -e'
exec_test '---_simple_invalid_cat_---' 'cat john_snow | wc -l'
exec_test '---_simple_redirect_---' 'echo hello_world > salut ; cat salut ; rm salut'
exec_test '---_simple_redirect_2_---' 'wc -l < logs/hello_world'
exec_test '---_simple_redirect_3_---' 'grep -i LO < logs/hello_world'
exec_test '---_strange_redirect_---' '< logs/hello_world wc -l'
exec_test '---_strange_redirect_2_---' 'wc < logs/hello_world -l'
exec_test '---_strange_redirect_3_---' 'grep -i < logs/hello_world LO'
exec_test '---_strange_redirect_4_---' '<logs/hello_world cat -e'
exec_test '---_strange_redirect_5_---' 'cat -e<logs/hello_world'
exec_test '---_strange_redirect_6_---' 'cat -e< logs/hello_world'
exec_test '---_pipe_and_redirect_---' 'grep -i < logs/hello_world LO | cat -e'
exec_test '---_pipe_and_builtin_---' 'env | grep PWD'
exec_test '---_glued_pipe_---' 'ls|cat -e'
exec_test '---_evil_long_pipe_---' 'man gcc | grep -i implies'
exec_test '---_satan_is_here_---' 'man gcc | cat -e | cat -e | cat -e | cat -e'
exec_test '---_pdf_test_---' 'mkdir tmp_dir ; cd tmp_dir ; ls -a ; ls | cat | wc -c > tutu ; cat tutu ; cd .. ; rm tmp_dir/tutu ; rmdir tmp_dir'
exec_test '---_simple_append_redirect_---' 'echo hello>>tmp ; echo _ >>tmp;echo world>> tmp;cat -e tmp ; rm tmp'
exec_test '---_ambiguous_input_redirect_---' 'ls | cat -e > tmp < logs/hello_world'
rm -f tmp
exec_test '---_ambiguous_output_redirect_---' 'ls | cat -e > tmp > tmp2'
rm -f tmp
exec_test '---_invalid_null_cmd_---' 'ls | | cat -e'
exec_test '---_not_existing_left_redirect_---' 'cat -e < damn'
exec_test '---_invalid_redirect_---' 'cat -e <> damn'
exec_test '---_invalid_redirect_---' 'cat -e >< damn'
exec_test '---_ambiguous_input_redirect_2_---' 'ls | < cat -e'
exec_test '---_ambiguous_input_redirect_3_---' 'ls | cat -e < file'
exec_test '---_missing_redirect_name_---' 'cat -e <  < end'
exec_test '---_exit_value_before_other_cmd_---' 'exit 45|cat /etc/resolv.conf'
exec_test '---_triple_invalid_pipe_---' 'toto | titi | tata'
exec_test '---_invalid_and_valid_pipes_---' 'toto | ls | tata | cat -e | cat -e'
exec_test '---_alone_cat_in_ls_---' 'cat -e | ls'
exec_test '---_creating_file_in_instruction_---' 'rm -f tmp ; ls > tmp ; cat tmp'
exec_test '---_left_redirect_then_pipe_---' 'cat -e < logs/hello_world | cat -e'
exec_test '---_unsetenv_with_input_---' 'unsetenv PATH ; cat ./logs/hello_world'
exec_test '---_tr_test_---' 'tr "[A-Z]" "[a-z]" < /etc/passwd'
exec_test '---_tr_test_big_1_---' 'man gcc | grep e | grep o | tr A-Z a-z | tr a b'
exec_test '---_tr_test_big_2_---' 'man gcc | grep e | grep o | tr A-Z a-z | tr a b | tr b c | tr c d | tr d e | tr e f | tr f g | tr g h | tr h i | tr i j | tr j k | tr k l | tr l m | tr m n | tr n o | tr o p | tr p q | tr q r | tr r s | tr s t | tr t u | tr u v | tr v w | tr w x | tr x y | tr y z'
exec_test '---_tr_test_big_3_---' 'man gcc | tr A-Z a-z | tr a b | tr b c | tr c d | tr d e | tr e f | tr f g | tr g h | tr h i | tr i j | tr j k | tr k l | tr l m | tr m n | tr n o | tr o p | tr p q | tr q r | tr r s | tr s t | tr t u | tr u v | tr v w | tr w x | tr x y | tr y z | tr A B | tr B C | tr C D | tr D E | tr E F | tr F G | tr G H | tr H I | tr I J | tr J K | tr K L | tr L M | tr M N | tr N O | tr O P | tr P Q | tr Q R | tr R S | tr S T | tr T U | tr U V | tr V W | tr W X | tr X Y | tr Y Z | tr Z z | tr 0 1 | tr 1 2 | tr 2 3 | tr 3 4 | tr 4 5 | tr 5 6 | tr 6 7 | tr 7 8 | tr 8 9 | tr 9 z'
exec_test '---_globbing_---' 'ls -l *.c src/*.c'
exec_test '---_and_test_1_---' 'ls && echo OK'
exec_test '---_and_test_1_---' 'ls nothing && echo KO'
exec_test '---_and_test_2_---' 'ls && echo OK1 && echo OK2'
exec_test '---_and_test_3_---' 'ls && echo OK1 && echo OK2 ; echo OK3'
exec_test '---_inv_and_---' 'ls && && echo KO'
exec_test '---_or_test_1_---' 'ls || echo KO'
exec_test '---_or_test_2_---' 'ls nothing || echo OK'
exec_test '---_or_test_3_---' 'ls nothing || echo OK ; echo OK2'
exec_test '---_inv_or_---' 'ls || || echo KO'
exec_test '---_inv_and_or_---' 'ls && || echo KO'
exec_test '---_advanced_and_or_1_---' 'ls -l && ls && ls nothing && ls include || echo OK'
exec_test '---_advanced_and_or_2_---' 'ls no || ls nope || ls really && echo hell_no || echo yes'
exec_test '---_advanced_and_or_3_---' 'ls no || ls && ls nope && echo OK || echo NOPE'
exec_test '---_advanced_and_or_4_---' 'ls && ( ls no || ls nope && ls || echo OK || echo KO )'
exec_test '---_advanced_and_or_5_---' 'ls && ( ls no || ls nope && ls || echo OK || echo KO ) && ( echo HERE ; echo test )'
exec_test '---_advanced_and_or_6_---' 'ls && ( ls no || ls nope && ls || echo OK || echo KO ) && ( echo NOT ; echo HERE )'
exec_test '---_advanced_and_or_7_---' 'test 1 && echo OK || echo KO'
exec_test '---_advanced_and_or_8_---' 'test 1 && echo OK1 && echo OK2 || echo KO && echo KO2'
exec_test '---_advanced_and_or_9_---' 'test && echo KO && echo KO2 || echo OK'
exec_test '---_advanced_and_or_10_---' 'test 1 || echo OK || echo KO || echo OK2 || echo KO2'
exec_test '---_advanced_and_or_11_---' 'ls && ( ls no || ls nope && ls || echo OK || echo KO ) && ( echo NOT ; echo HERE )'
exec_test '---_parenthesis_1_---' '(echo OK)'
exec_test '---_parenthesis_2_---' 'ls && (echo OK)'
exec_test '---_parenthesis_3_---' 'ls && (echo OK1 ; echo OK2)'
exec_test '---_parenthesis_4_---' 'ls nothing || (echo OK1 ; echo OK2)'
exec_test '---_parenthesis_5_---' 'echo OK0 && ls nothing || (echo OK1 ; echo OK2)'
exec_test '---_parenthesis_6_---' '(echo OK0 && ls nothing) || (echo OK1 && echo OK2)'
exec_test '---_parenthesis_7_---' '(echo OK0 && ls nothing) && (echo OK1 && echo OK2)'
exec_test '---_parenthesis_8_---' '(echo OK0 && ls nothing) && (echo OK1 || echo OK2)'
exec_test '---_parenthesis_9_---' '(echo OK0 && ls nothing) && (echo OK1 || echo OK2) && echo OK3'
exec_test '---_parenthesis_multipipe_1_---' '(echo 1 && echo 2) | cat -e'
exec_test '---_parenthesis_multipipe_2_---' 'ls | (cat && cat -e)'
exec_test '---_parenthesis_redirect_---' '(echo one ; echo two) > tmp && cat tmp && rm tmp'
exec_test '---_inv_parenthesis_1_---' '(ls'
exec_test '---_inv_parenthesis_2_---' '(((ls))'
exec_test '---_inv_parenthesis_3_---' 'ls)'
exec_test '---_inv_parenthesis_4_---' 'ls ()'
exec_test '---_inv_parenthesis_5_---' '((ls()))'
exec_test '---_and_or_test_---' 'ls /nope || ls -l && ls /nope_again || ls'
exec_test '---_simple_repeat_---' 'repeat 2 ls'
exec_test '---_double_repeat_---' 'repeat 2 repeat 2 ls'
exec_test '---_inv_repeat_1_---' 'repeat'
exec_test '---_inv_repeat_2_---' 'repeat 2'
exec_test '---_inv_repeat_3_---' 'repeat 0 ls'
exec_test '---_inv_repeat_4_---' 'repeat 5a ls'
exec_test '---_broken_pipe_---' 'ls -lR / | cat | cat | cat | cat | cat | cat | cat | cat | cat | head -30'
exec_test '---_tricky_1_---' 'find . | head -n 1'
exec_test '---_basic_foreach_1_---' 'foreach i (a b c)\necho $i\nend'
exec_test '---_basic_foreach_2_---' 'foreach i (a b c)\necho hello ; echo "$i"\nend'
exec_test '---_one_line_if_1_---' 'set foo=bar ; if ( $foo == foo ) echo KO || echo OK'
exec_test '---_one_line_if_2_---' 'set foo=bar ; if ( $foo == bar ) echo OK || echo KO'
exec_test '---_one_line_if_3_---' 'set foo=bar ; if ( $foo != bar ) echo KO || echo OK'
exec_test '---_inv_if_1_---' 'set foo=bar ; if ( $foo == bar )'
exec_test '---_inv_if_2_---' 'set foo=bar ; if ( $foo == bar )'
exec_test '---_inv_if_3_---' 'set foo=bar ; if ( $foo == bar ) then echo KO'
exec_test '---_inv_if_4_---' 'if'
exec_test '---_inv_if_5_---' 'if ( $foo == you_know_nothing ) then echo KO'
exec_test '---_multiple_line_if_1_---' 'if ( foo == bar ) then\necho KO\nelse\necho OK\nendif'
exec_test '---_multiple_line_if_2_---' 'if ( foo != bar ) then\necho OK\nelse\necho KO\nendif'
exec_test '---_multiple_line_if_3_---' 'if ( foo == bar ) then\necho KO\nelse echo OK'
exec_test '---_multiple_line_if_4_---' 'if ( foo == bar ) then\necho KO_1\nelse if ( foo != bar ) then\necho OK\nelse\n echo KO_2\nendif'
exec_test '---_inv_multiple_line_if_1_---' 'if ( foo == bar ) then\necho KO_1\nelse if ( foo != bar ) then wtf\necho OK\nelse\n echo KO_2\nendif'
exec_test '---_inv_multiple_line_if_2_---' 'if ( foo == bar ) then\necho KO_1\nelse if ( foo != bar )\necho OK\nelse\n echo KO_2\nendif'
exec_test '---_inv_multiple_line_if_3_---' 'if ( foo == bar ) then\necho KO_1\nelse'
exec_test '---_inv_multiple_line_if_5_---' 'else \n echo KO \n endif'
exec_test '---_if_condition_1_---' 'if (4 < 12) echo OK'
exec_test '---_if_condition_2_---' 'if (4 <= 12) echo OK'
exec_test '---_if_condition_3_---' 'if (4 <= 4) echo OK'
exec_test '---_if_condition_4_---' 'if (4 >= 4) echo OK'
exec_test '---_if_condition_5_---' 'if (12 >= 4) echo OK'
exec_test '---_if_condition_6_---' 'if (12 >=) echo OK'
exec_test '---_if_condition_7_---' 'if ( < 4 ) echo OK'
exec_test '---_if_condition_8_---' 'set a=4 ; set b=12\nif ($a < $b ) echo OK'
exec_test '---_if_inv_condition_1_---' 'if ($a < 12) echo KO'
exec_test '---_if_inv_condition_2_---' 'if (4  12) echo KO'
exec_test '---_if_inv_condition_3_---' 'if ( == ) echo OK'
exec_test '---_if_inv_condition_4_---' 'set a=foo \n if ($a < 12) echo OK'
exec_test '---_inhibitor_test_1_---' 'set foo=bar ; echo "$foo -->`pwd`<--"'
exec_test '---_var_interpreter_1_---' 'echo $PATH'
exec_test '---_var_interpreter_2_---' 'echo ${PATH}'
exec_test '---_var_interpreter_3_---' 'echo $NOTHING'
exec_test '---_var_interpreter_4_---' 'echo ${NOTHING}'
exec_test '---_var_interpreter_5_---' 'echo "Hello -> $PATH <-"'
exec_test '---_var_interpreter_6_---' 'echo "Hello ->$PATH<-"'
exec_test '---_var_interpreter_7_---' 'set a=2 ; echo $a'
exec_test '---_var_interpreter_8_---' 'set foo=bar ; echo $foo'
exec_test '---_var_interpreter_9_---' 'set foo = bar ; echo $foo'
exec_test '---_var_interpreter_10_---' 'set foo = bar bar = foo ; echo $foo $bar'
exec_test '---_var_interpreter_11_---' 'set foo=bar bar=foo ; echo $foo $bar'
exec_test '---_var_interpreter_12_---' 'set foo bar ; echo "> $foo <" "> $bar <"'
exec_test '---_var_interpreter_13_---' 'set foo bar ; echo ">$foo<" ">$bar<"'
exec_test '---_var_interpreter_14_---' 'set a = k ; echo "bon${a}jour"'
exec_test '---_var_interpreter_15_---' 'echo $?'
exec_test '---_var_interpreter_16_---' 'ls $'
exec_test '---_alias_1_---' 'which pwd'
exec_test '---_alias_2_---' 'alias pwd "ls -la" \n pwd'
exec_test '---_alias_3_---' 'alias pwd caca \n pwd \n alias caca ls \n pwd'
exec_test '---_alias_loop_---' 'alias a b \n a \n alias b c \n a \n alias c a \n a \n alias c ls \n a'
exec_test '---_alias_5_---' 'alias a ; alias b; a'
exec_test '---_alias_6_---' 'alias ls ls -l -a  \n ls '
exec_test '---_alias_7_---' 'alias ok ok ; ok'
exec_test '---_alias_8_---' 'alias a ; a'
exec_test '---_or_test_4---' 'ls /random || echo Display'
exec_test '---_or_test_4_---' 'ls /random || echo Display'
exec_test '---_or_test_5_---' 'toto || toto'
exec_test '---_or_test_6_---' 'echo Bonjour || toto'
exec_test '---_advanced_or_and_test_1_---' 'ls /random || echo display && echo Test'
exec_test '---_advanced_or_and_test_2_---' 'echo 42 || ls /rrr && echo r || ls /'
exec_test '---_or_test_7_---' 'ls /random || echo display || ls /random || echo redisplay'
exec_test '---_alias_2_---' 'alias pwd "ls -la" ; pwd'
exec_test '---_alias_3_---' 'alias pwd caca ; pwd ; alias caca ls ; pwd'
exec_test '---_alias_loop_---' 'alias a b ; a ; alias b c ; a ; alias c a ; a ; alias c ls ; a'
exec_test '---_alias_2_---' 'alias a ; a'
exec_test '---_echo_1_---' 'echo mdr thery le sang'
exec_test '---_echo_2_---' 'echo "baptiste le gros pd'
exec_test '---_echo_3_---' 'echo "baptiste" le gros pd'
exec_test '---_echo_4_---' 'echo mon pwd est `pwd`'
exec_test '---_echo_5_---' 'echo cou\nmdr `ls`'
exec_test '---_echo_6_---' 'echo "cou\\nmdr `ls`"'
exec_test '---_echo_7_---' 'echo pwd : `ls | cat -e`'
exec_test '---_echo_8_---' 'echo'
exec_test '---_echo_9_---' 'echo HOME\\mdr\"'
exec_test '---_echo_10_---' 'echo "HOME\\mdr\""'
exec_test '---_echo_11_---' 'echo "HOME\ mdr\^\\"'
exec_test '---_echo_12_---' 'echo HOME\ mdr\^\\m'
exec_test '---_echo_13_---' 'echo HOME\ \"\`mdr\^\\m'
exec_test '---_quotes_1_---' 'ls HOME\\mdr\"'
exec_test '---_quotes_2_---' 'ls "HOME\\mdr\""'
exec_test '---_quotes_3_---' 'ls "HOME\ mdr\^\\"'
exec_test '---_quotes_4_---' 'ls HOME\ mdr\^\\j'
exec_test '---_quotes_5_---' 'ls HOME\ \"\`mdr\^\\m'
exec_test '---_inhibitor_1_---' 'echo /home/student/coucou'
exec_test '---_inhibitor_2_---' 'echo "/home/student/coucou"'
nexec_test '---_inhibitor_3_---' 'echo "/home/""student""/""coucou"'
exec_test '---_inhibitor_4_---' 'echo "/home/""student\""/"\"coucou"'
exec_test '---_inhibitor_4_---' 'echo "/home/""student\\""/"\"coucou"'
exec_test '---_inhibitor_5_---' 'echo "/home/student\\\"/coucou"'
exec_test '---_inhibitor_6_---' 'echo /home/student\\\"/coucou'
exec_test '---_inhibitor_7_---' 'echo /home/student\\"/coucou'
exec_test '---_inhibitor_8_---' 'echo /home/student\\\""/coucou'
exec_test '---_inhibitor_9_---' 'echo /home/student\\\"/coucou"'
exec_test '---_inhibitor_10_---' 'echo /home/student\\""/coucou'
exec_test '---_inhibitor_11_---' 'echo /ho\"me/\"student\"/coucou'
exec_test '---_inhibitor_12_---' 'echo /home/"student\"/cou"cou'
exec_test '---_inhibitor_13_---' 'echo /home/"student\\"/cou"cou'

finish
