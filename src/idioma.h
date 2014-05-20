#ifndef IDIOMA_H
#define IDIOMA_H

typedef struct _elemento_string {
 	char *string;
 	char *var;
 	struct _elemento_string *proximo;
} elemento_string;

typedef struct {
	elemento_string **hash;
} IDIOMA;
 
IDIOMA *idioma;

void carregar_idioma(const char *arquivo);

char *pegar_idioma(const char *key, IDIOMA *idioma);

void destroi_idioma(IDIOMA *language);


#endif