#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <openssl/sha.h>  // header for sha family 

#define SIZE 512

/*

	Need to install the library before using this code
	for example in ubuntu: sudo apt-get install libssl-dev

	Need to specify linker "-lcrypto" when compiling with gcc
	i.e: gcc -Wall openssl_sha256_encrypt.c -o test -lcrypto

	# Perform sha256 encryption to input string

	# functions prototypes
	int SHA256_Init(SHA256_CTX *c);
	int SHA256_Update(SHA256_CTX *c, const void *data, size_t len);
	int SHA256_Final(unsigned char *md, SHA256_CTX *c);

	N.B: output is a array of unsigned char, length is 32

*/

// convert unsigned char[32] to char[64]
__attribute__((always_inline)) inline void uchar2hexchar( const unsigned char* source, char* result ) {

	if ( !source || !result ) return;
	unsigned int i = 0;
	for (; i < 32; i++) {
		sprintf(result, "%02x", source[i]);
		result += 2;
	}

}


int main() {

	char input[SIZE] = {0};
	unsigned char output[32]; 

	char ascii_output[65] = {0};	// last slot reserved for '\0'

	// init c
	SHA256_CTX c;
	SHA256_Init( &c );

	// type "exit" or "quit" to quit 
	while (1) {

		printf("input: ");
		scanf("%511s", input);
		fflush(stdin);

		// if exit
		if ( !strcmp(input, "exit") || !strcmp(input, "quit") )
			break;

		// start compute
		SHA256_Update( &c, input, strlen(input) );
		// get result and reset "c"
		SHA256_Final( output, &c );

		unsigned int i = 0;
		// print out the result as hex number
		printf("unsigned char:\n");
		for (; i < 32; i++) 
			printf("%02x", output[i]);

		printf("\n");

		// convert to char[]
		uchar2hexchar(output, ascii_output);
		printf("ascii:\n%s\n", ascii_output);

		memset(input, 0, SIZE);

	}


	return 0;
}
