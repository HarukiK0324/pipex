/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:21:04 by haruki            #+#    #+#             */
/*   Updated: 2025/02/14 16:32:29 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Child process: Executing 'ls -l'\n");
        char *args[] = {"ls", "-l", NULL};
        char *env[] = {NULL};
        if (execve("/bin/ls", args, env) == -1) {
            perror("execve failed");
            exit(EXIT_FAILURE);  //execve fails
        }
    } else {
        printf("Parent process: Waiting for child to complete\n");
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child did not terminate normally\n");
        }
    }

    return 0;
}
