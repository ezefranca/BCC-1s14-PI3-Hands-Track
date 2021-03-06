#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

/**
 *  <#Description#>
 *
 *  @param mensagem <#mensagem description#>
 */
void erro(char *mensagem);
/**
 *  <#Description#>
 *
 *  @param mensagem <#mensagem description#>
 */
void aviso(char *mensagem);
/**
 *  <#Description#>
 *
 *  @param string <#string description#>
 *
 *  @return <#return value description#>
 */
double string_para_double(const char *string);
/**
 *  <#Description#>
 *
 *  @param string <#string description#>
 *
 *  @return <#return value description#>
 */
int string_para_int(const char *string);

/**
 *  <#Description#>
 *
 *  @param string <#string description#>
 *
 *  @return <#return value description#>
 */
int string_para_boolean(const char *string);
#endif
