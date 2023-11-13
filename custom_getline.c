#include "shell.h"
#define BUFFER_SIZE 1024
static char static_buffer[BUFFER_SIZE];
static size_t static_buffer_index;
static size_t static_buffer_size;
/**
 * _getline - a function to read input from stream
 * @lineptr: A pointer to the buffer that stores the line
 * @n: Pointer to the size of the buffer
 * @stream: File stream to read from
 * Return: The number of characters read or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i;
	/*char *new_ptr;*/
	/*ssize_t read_bytes;*/

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;/*Invalid argument*/
		return (-1);
	}
	/*if a buffer is not allocated allocate a buffer*/
	if (*lineptr == NULL || *n == 0)
	{
		*n = BUFFER_SIZE;/*initial size*/
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			perror("Erro allocating memory");
			return (-1);
		}
	}
	i = 0;
	/*copy characters from the static buffer*/
	while (static_buffer_index < static_buffer_size ||
			read_into_buffer(stream) > 0)
	{
		expand_buffer(lineptr, n, i + 1);
		(*lineptr)[i++] = static_buffer[static_buffer_index++];
		if (static_buffer[static_buffer_index - 1] == '\n')
		{
			/*reset static buffer*/
			static_buffer_index = static_buffer_size = 0;
			(*lineptr)[i] = '\0';/*NULL-terminate the string*/
			return (i);/*return the number of characters read*/
		}
	}
	return (-1);
}

/**
 * read_into_buffer -  a function to read into the buffer
 * @stream: input file
 * Return: bytes read from buffer
 */
ssize_t read_into_buffer(FILE *stream)
{
	ssize_t read_bytes;

	read_bytes = read(fileno(stream), static_buffer, BUFFER_SIZE);
	if (read_bytes > 0)
	{
		static_buffer_index = 0;
		static_buffer_size = (size_t)read_bytes;
	}
	return (read_bytes);
}

/**
 * expand_buffer - a function to handle the reallocation of the
 * buffer when needed
 * @lineptr: pointer to buffer
 * @n: size
 * @required_size: required size
 */
void expand_buffer(char **lineptr, size_t *n, size_t required_size)
{
	char *new_ptr;

	while (required_size >= *n - 1)
	{
		*n *= 2;
		new_ptr = realloc(*lineptr, *n);
		if (!new_ptr)
		{
			perror("Error reallocating memory");
			free(*lineptr);
			*lineptr = NULL;
			exit(EXIT_FAILURE);
		}
		*lineptr = new_ptr;
	}
}
