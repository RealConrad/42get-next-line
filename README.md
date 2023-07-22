<h1 align="center">
    <p>
          📗 Get Next Line
    </p>
</h1>

<p align="center">
    <b><i>A C library that reads a single line from a file descriptor at a time, allocating memory for the line dynamically.</i></b>
</p>

<p align="center">
    This repository is coded in&nbsp&nbsp
    <a href="https://skillicons.dev">
        <img src="https://skillicons.dev/icons?i=c" />
    </a>
</p>

## Features
- Read lines from a file descriptor one line at a time.
- Stops reading at the first newline character ('\n') or the end of file (EOF).
- Dynamically alocate memory for the line, which must be freed by the caller.
- Handles multiple file descriptors simultaneously, without losing reading context (see bonus part).
- All functions have doxygen comments explaining their purpose in detail.
- Handles edge cases such as empty files, invalid file descriptors and memory allocaiton errors.

## Installation
1. Clone the repository.
```shell
% git clone https://github.com/RealConrad/42get-next-line.git
```
2. Remember to include `get_next_line.h` and/or `get_next-line_bonus.h` respectively in your c (source) files. 
3. Compile with `get_next_line.c` and `get_next_line_utils.c` and/or `get_next_line_bonus.c` and `get_next_line_utils_bonus.c` respectively.

## Examples
An example on how to use the library:  
**File: main.c**
```c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Error opening file");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```
Compiling and executing:
```shell
% gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 main.c get_next_line.c get_next_line_utils.c -o gnl_test
% ./gnl_test <filename>.txt
```


## License
[MIT](https://choosealicense.com/licenses/mit/)
