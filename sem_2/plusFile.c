#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s PATH_IN text\n", argv[0]);
        fprintf(stderr, "or if u wanna to use file in current dir:\n");
        fprintf(stderr, "Usage: %s FileIN text\n\n", argv[0]);
        return -1;
    }

    const char *input_filename = argv[1];

    int FileIN = open(input_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (FileIN == -1) {
        perror("OutERR");
        return -1;
    }

    for (int i = 2; i < argc; i++) {
        write(FileIN, argv[i], strlen(argv[i]));
        write(FileIN, "\n", 1);
    }

    close(FileIN);

    int FileNext = open(input_filename, O_RDONLY);
    if (FileNext == -1) {
        perror("ReadERR");
        return -1;
    }

    char *buf = malloc(256);
    read(FileNext, buf, 5);
    buf[5] = '\0';
    printf("%s", buf);
    
    free(buf);
    close(FileNext);
    return 0;
}
