# Bash like shell implementation
## System programming 2020 fall - programming assignment 3
### Ahn, Junho (20175097) 2020 NOV 17
### github: https://github.com/ahn9807/Minish

# Environment
* linux 5.4.0-53-generic in vmware funsion of machintosh
* gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)

# Functionality
## Built in functions
### help
help prints the help documetation of minish. 

    junho:/home/junho/Desktop/HW3$ help
    MINISH Help
    These shell commands are defined internally.  Type `help' to see this list

    quit, pwd, cd ,help, path, status(not working correctly), cap

### quit
quit quitting the minish shell.

    junho:/home/junho/Desktop/HW3$ quit

### pwd
pwd prints current directories.

    junho:/home/junho/Desktop/HW3$ pwd
    /home/junho/Desktop/HW3

### cd
cd changes current directories.

    junho:/home/junho/Desktop/HW3$ pwd
    /home/junho/Desktop/HW3
    junho:/home/junho/Desktop/HW3$ cd ..

### path
path prints current path variable. with two arguments, we can set path variables.

    junho:/home/junho/Desktop$ path
    PATH :/home/junho/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

### cap
cap makes current shell into bash shell with printing "Green one is not zelda"

    junho:/home/junho/Desktop$ cap
    Green one is not zelda
    junho@junho-virtual-machine:~/Desktop$ 

## Piping
We can redirect standard-output to standard-in of another program using piping. Some elf programe such as grep or wc takes input of STDIN of system /dev/..., and execute itself by taking input from that. So we can implemented piping by using pipe() system call and dup2() at stdin and stdout. 

    junho:/home/junho/Desktop/HW3$ ls -al | grep exec
    -rw-rw-r-- 1 junho junho   1790 Nov 17 19:39 exec_builtin.c
    -rw-rw-r-- 1 junho junho    150 Nov 16 02:10 exec_builtin.h
    -rw-rw-r-- 1 junho junho   1164 Nov 17 19:29 exec_commend.c
    -rw-rw-r-- 1 junho junho     86 Nov 16 11:58 exec_commend.h
    -rw-rw-r-- 1 junho junho    606 Nov 17 19:23 exec_external.c
    -rw-rw-r-- 1 junho junho     93 Nov 16 02:10 exec_external.h
    -rw-rw-r-- 1 junho junho   1761 Nov 17 19:40 exec_piped.c
    -rw-rw-r-- 1 junho junho    105 Nov 16 11:47 exec_piped.h
    -rw-rw-r-- 1 junho junho   1266 Nov 17 19:17 exec_redirected.c
    -rw-rw-r-- 1 junho junho    212 Nov 17 00:55 exec_redirected.h

## Redirection
Basically, linux prints results of execution to default system I/O devices such as monitor or files. But we can redirect this by intercepting the stdin or files to another files. 

    junho:/home/junho/Desktop/HW3$ wc /etc/passwd > out.txt
    junho:/home/junho/Desktop/HW3$ cat out.txt
    46   81 2738 /etc/passwd

## External Programes
Minish can run external programes by searching path variables at another process by fork() system-call. 

    junho:/home/junho/Desktop/HW3$ ssh
    usage: ssh [-46AaCfGgKkMNnqsTtVvXxYy] [-B bind_interface]
            [-b bind_address] [-c cipher_spec] [-D [bind_address:]port]
            [-E log_file] [-e escape_char] [-F configfile] [-I pkcs11]
            [-i identity_file] [-J [user@]host[:port]] [-L address]
            [-l login_name] [-m mac_spec] [-O ctl_cmd] [-o option] [-p port]
            [-Q query_option] [-R address] [-S ctl_path] [-W host:port]
            [-w local_tun[:remote_tun]] destination [command]

# Way of implementations
## shell.c
As an entry point of shell.c, infinite loop keeps minish run until quit commend is given. Also, shell.c allocate memories for queue and some other unallocated memories. Shell.c also register signal handler.

## minish_io.c / parser.c
minish_io.c and parser.c take part of I/O and string parser in minish. Minish_io.c takes input and makes output shell prompt screen. Parser.c has various kinds of important parser including parse_space and parser_input. parse_input is the most important part of the parser.c. parse_input parse the input string and decide witch 

## exec_commend.c exec_builtin.c exec_piped.c exec_redirected.c 
exec_commend.c get input as an argument of itself. With aid of parser.c, exec_commend parse the argument and call appropriate function to execute builtin, piped, redirected commend. 

## queue.c
This is help script for implementing background and foreground job scheduling. Queue is implemented in linked list fasioned. 

## signal_handler.c
signal_halder.c register appropriate actions for each siganls. 

# Conclusion
We can make bash like shell in c with aid of systemcall. Actually, shell such as zsh or bash is a just a programe that runs systemcall to execute any other programe user friendly in TUI environments. Some features such as auto complete or history is not implemented in this project. I want to extend my shell to have more real bash like strucuture if I have time.

Overall architecture structure is designed by myself. 
