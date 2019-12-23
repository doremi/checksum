#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

uint32_t checksum_32(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (!fd) {
        perror("open");
        return 0;
    }

    struct stat st;
    fstat(fd, &st);
    off_t len = st.st_size;
    uint8_t *file_ptr = (uint8_t*)mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
    if (file_ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 0;
    }

    uint32_t sum = 0;
    while (len > 0) {
        sum += *file_ptr++;
        --len;
    }
    munmap(file_ptr, len);
    close(fd);

    return sum;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(2);
    }

    uint32_t result = checksum_32(argv[1]);
    printf("%08x  %s\n", result, argv[1]);
    return 0;
}
