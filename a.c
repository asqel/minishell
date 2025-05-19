#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 1024

void handle_sigint(int signum) {
    (void)signum;
    write(STDOUT_FILENO, "\nSIGINT reçu\n", 13);
    // Rien d'autre ici : on veut juste interrompre le read()
}

int main(void) {
    char buffer[BUF_SIZE];
    ssize_t n;

    // Installer le gestionnaire de signal
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        write(STDOUT_FILENO, ">>> ", 4);
        n = read(STDIN_FILENO, buffer, BUF_SIZE - 1);

        if (n == -1) {
            if (errno == EINTR) {
                // Lecture interrompue par un signal
                write(STDOUT_FILENO, "Lecture interrompue par SIGINT\n", 32);
                continue;
            } else {
                perror("read");
                break;
            }
        } else if (n == 0) {
            // EOF (Ctrl+D)
            write(STDOUT_FILENO, "EOF reçu, sortie...\n", 21);
            break;
        }

        buffer[n] = '\0';
        printf("Vous avez tapé : %s", buffer);
    }

    return 0;
}

