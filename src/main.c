#include "init.h"
#include "comum.h"
#include "terminate.h"

//Global
int _vizinhos = 100;
/**
 *  <#Description#>
 *
 *  @param n  <#n description#>
 *  @param x  <#x description#>
 *  @param fx <#fx description#>
 */
void interpolacao(int n, double *x, double *fx){
     double somax = 0;//inicializando os valores dos somatorios.
     double somax2 = 0;
     double somaf = 0;
     double somaxf = 0;
     
     for(int i=1;i<=10;i++){//Somatorios de x, x², f(x) e x*f(x)
      somax = somax + x[i];
      somax2 = somax2 + x[i]* x[i];
      somaf = somaf + fx[i];
      somaxf = somaxf + x[i]* fx[i];
    }              

    //calculo dos valores de a e b da regressão linear.
    double a = (somaf * somax2 - somax * somaxf)/(n * somax2 - somax *somax);
    double b = (n * somaxf - somax * somaf)/(n * somax2 - somax * somax);

    //printf ("\nA curva que melhor ajusta os 10 dados fornecidos eh \ng(x)= %f + %f*x\n\n", a, b);
    double c = (a * 42) + b;
    printf("%f, %f = %f\n",a, b, c);
}

  void testeRGB(Rgb *cores){
    cores->r = 200;
   // printf("---------------------------------%d\n",cores->r);
  }

  void remove_fundo(unsigned char ***atual, unsigned char ***primeiro, unsigned char ***matriz){

    int r , g , b;

	//printf("luminus %s %d", pegar_configuracao("LUMINUS", "camera", config), string_para_int(pegar_configuracao("LUMINUS", "camera", config)));
    for (int y = _vizinhos; y < altura - _vizinhos; y++){
      for (int x = _vizinhos; x < largura - _vizinhos; x++){
  // for(int y = 0; y < altura; y++){
  //   for(int x = 0; x < largura; x++) {
        r = abs(atual[y][x][0] -  primeiro[y][x][0]);
        g = abs(atual[y][x][1] -  primeiro[y][x][1]);
        b = abs(atual[y][x][2] -  primeiro[y][x][2]);

	  //Verificação da luminosidade.
        if ((r + g + b) > game->luminus)
        {
          matriz[y][x][0] = 255;
          matriz[y][x][1] = 255;
          matriz[y][x][2] = 255;
        }

        else
        {
          matriz[y][x][0] = 0;
          matriz[y][x][1] = 0;
          matriz[y][x][2] = 0;
        }   
      }
    }

  }
/**
 *  <#Description#>
 *
 *  @return <#return value description#>
 */
  int main() {

    inicializar_allegro();

    unsigned char ***matriz = camera_aloca_matriz(cam);
    unsigned char ***matriz_pb = camera_aloca_matriz(cam);
    unsigned char ***matriz_verde = camera_aloca_matriz(cam);

    unsigned char ***primeiro = camera_aloca_matriz(cam);
    //unsigned char ***matriz2 = camera_aloca_matriz(cam);
    //ALLEGRO_COLOR cor = al_map_rgb_f(0, 0, 1);

    ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);
    ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, largura, altura);
    ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, largura, 0, largura, altura);

    //ALLEGRO_COLOR vermelho = al_map_rgb_f(255, 0, 0);

    Rgb *cores_rgb = malloc(sizeof(Rgb));
    Hsv *cores_hsv = malloc(sizeof(Hsv));


    int desenhar = 0;
    int terminar = 0;
    int amostragem = 0;
    double x[10]; 
    double fx[10];

    //int atualiza = 0;

    camera_atualiza(cam);

    for(int y = 0; y < altura; y++){
      for(int x = 0; x < largura; x++) {
        primeiro[y][x][0] = cam->quadro[y][x][0];
        primeiro[y][x][1] = cam->quadro[y][x][1];
        primeiro[y][x][2] = cam->quadro[y][x][2];
      }
    }

    //tela_sprite();

    while(1) {
      ALLEGRO_EVENT event;

      al_wait_for_event(queue, &event);

      switch(event.type) {
        case ALLEGRO_EVENT_TIMER:
        desenhar = 1;
        break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        terminar = 1;
        break;
        default:
        printf("evento desconhecido\n");
      }

      if(terminar)
        break;

      if(desenhar && al_is_event_queue_empty(queue)) {

        desenhar = 0;
        camera_atualiza(cam);
        remove_fundo(cam->quadro, primeiro, matriz);
            /**********/
            /**********/
            //limiarizacao(fundo, altura, largura);
            //otsu_binarizacao(fundo, fundo, altura, largura);
        normalizacao_preto_e_branco(matriz, altura, largura);
        otsu_binarizacao(matriz, matriz_pb, altura, largura);
            //filtro_borda(cam->quadro, matriz_pb, altura, largura);
            //filtro_laplaciano(cam->quadro, matriz, altura, largura);
        filtro_borda(matriz_pb, matriz_pb, altura, largura);
            //limiarizacao(matriz_pb, altura, largura);
            //filtro_mediana(matriz, matriz, altura, largura);
            //filtro_mediana(matriz, matriz, altura, largura);
            // laplaciano(matriz, matriz, altura, largura);
            //filtro_media(matriz, matriz, altura, largura);
        matriz_copia(matriz_pb, matriz_verde, altura, largura);
        poligono *f = fecho(matriz_verde,altura, largura);
        camera_copia(cam, matriz_pb, esquerda);
        camera_copia(cam, matriz_verde, direita);
            //al_draw_circle(300, 300, 10, vermelho, 10);
            //fecho(matriz_pb, altura, largura);
            //------------------
            //Teste
        ALLEGRO_COLOR azul = al_map_rgb_f(0, 0, 255);
        ALLEGRO_COLOR verde = al_map_rgb_f(0, 255, 0);
        ALLEGRO_COLOR preto = al_map_rgb_f(0, 0, 0);

        al_draw_filled_rectangle(1, 1, largura, altura, verde);
        al_draw_rectangle(_vizinhos, _vizinhos, (largura - _vizinhos),(altura - _vizinhos) , preto, 3);

        for (int i = _vizinhos; i < altura - _vizinhos; i++){
          for (int j = _vizinhos; j < largura - _vizinhos; j++){
                    // removedor_ruidos(matriz, _vizinhos, i, j);
            if(matriz_verde[i][j][0] == 255 && matriz_verde[i][j][1] == 255 && matriz_verde[i][j][2] == 255)
            {
              al_draw_filled_circle(j, i, 2, azul);

            }
          }
        }

                //pontos_extremo(f, menor_x, maior_x, menor_y, maior_y);
        /*
        Tesoura, 20000 - 36000

        Pedra,   15000 - 45000

        Papel, 40000 - 120000
        */
        if(amostragem < 10){
          fx[amostragem] = area_do_fecho(f);
          x[amostragem] = f->n;
        }else{
          interpolacao(10, x, fx);
          pontos_extremo(f);
            amostragem = -1;
        }
        amostragem++;



       // printf("\nArea do fecho: %2f Pontos %d\n", area_do_fecho(f), f->n);
        print_poligono(f);
            //camera_copia(cam, fundo, direita);
            /**********/

        al_flip_display();
        free(f);
      }
    }

    al_destroy_bitmap(direita);

    al_destroy_bitmap(esquerda);

    camera_libera_matriz(cam, matriz);

		/**********/

    finalizar_allegro();

    return EXIT_SUCCESS;
  }