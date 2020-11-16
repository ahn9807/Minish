all:
	gcc -g shell.c exec_builtin.c exec_external.c exec_piped.c exec_commend.c queue.c minish_io.c parser.c signal_handler.c exec_redirected.c -o minish
clean:
	rm -rf minish