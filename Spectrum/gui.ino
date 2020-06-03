/* GUI for the handheld edition of the emulator 
 *  Gui for File selection
 *  Gui for hardware configuration
 *  - Change keymaps
 *  - Load a snapshot
 *  - Reset the emulator
 *  - define hardware emulation
 *  - define keymaps
 *  - volver el emulador
 *  Gui confirmacion
 */
/* Borrar la parte de la pantalla a utilizar
 *  Escribir un titulo de la "ventana"
 *  varias opciones a elegir
 *  scroll si son mas que las que caben en pantalla
 *  mover una barra o algo entre las opciones
 *  retornar si/no y el resultado en funcion de la seleccion
 */

// GENERIC FUNCTIONS:

 void gui_draw_window(int w,int h, char *title){
  int x,y,n,m;
  x=(320-w)/2;
  y=(240-h)/2;
  n=x+w-2;
  m=y+8;
  watch->eTFT->fillRect(x-2,y-2,w+4,h+4,watch->eTFT->color565(64,64,64));
  watch->eTFT->fillRect(x,  y,  w,  8,watch->eTFT->color565(0,0,0));
  watch->eTFT->fillRect(x+1,y+9,w-2,h-9,watch->eTFT->color565(255,255,255));
  watch->eTFT->drawRect(x,  y+8,w,  h-7,watch->eTFT->color565(0,0,0));

  watch->eTFT->setCursor(x+2, y+1);
  watch->eTFT->setTextColor(TFT_WHITE);  
  watch->eTFT->setTextSize(1);
  watch->eTFT->println(title);
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(0,0,255));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(0,0,255));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(0,0,255));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(0,0,255));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(0,255,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(0,255,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(0,255,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(0,255,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(255,255,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(255,255,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(255,255,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(255,255,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(255,0,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(255,0,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(255,0,0));
  watch->eTFT->drawLine(n,y,(n--)-8,m,watch->eTFT->color565(255,0,0));
 
 }

void gui_update_menu(int w,int h,int n,int s, char data[][25]){
  int c,x,y;
  x=(320-w)/2;
  y=(240-h)/2;

  watch->eTFT->setTextColor(TFT_BLACK);  
  watch->eTFT->setTextSize(1);
  for (c=1;c<=n;c++){
  watch->eTFT->fillRect(x+1,y+9*c,w-2,9,(c==s?TFT_CYAN:TFT_WHITE));
  watch->eTFT->setCursor(x+2, y+1+9*c);
  watch->eTFT->println(data[c-1]);
  }
} 
int gui_draw_menu(int w,  char *title, int n, char data[][25]){
  int ret=-1;
  int h,b;
  int s=1;
  h=9+9*(n>6?6:n);
  gui_draw_window(w,h,title);
  gui_update_menu(w,h,n,s,data);
  do {
    b=mirabotones();
    switch (b){
      case 4:
        if (s>1) {
          s--;
          gui_update_menu(w,h,n,s,data);
        }
        break;
      case 5:
        if (s<n) {
          s++;
          gui_update_menu(w,h,n,s,data);
        }
        break;
      case 3:
        ret=0;
        break;      
      case 1:
        ret=s;
        break;        
    }
  } while (ret == -1);
  return ret;
}

// SPECIFIC FUNCTIONS

void gui_Main_Menu(void){
  char options[6][25]={
    "Cambiar Mapa de teclado",
    "Cargar Snapshot",
    "Cargar Cinta",
    "Reset",
    "Tipo de Maquina",
    "Volver"
  };
  int r;
  r=gui_draw_menu(200,"Opciones",6,options);
  switch (r){
    case 1:
      emuopt.mappingindex++ ;       
      if (emuopt.mappingindex>3) emuopt.mappingindex=0;
      AS_printf("now mapping is "); AS_print(emuopt.mappingindex); AS_printf("\n"); 
      break;
    case 4:
      reset_spectrum(&spectrumZ80);
      break;
    case 2:
      Load_SNA(&spectrumZ80,"/manic.sna");
      //gui_Select_Snap();
      break;
/*
    case 3:
      gui_Select_Tape();
      break;
    case 5:
      gui_Select_Machine();
      break;
*/
  }
  watch->eTFT->fillScreen(TFT_BLACK);
  //watch->eTFT->fillRect(0,0,320,240,watch->eTFT->color565(0,0,0));
  for(r=0;r<(320*240);r++){ *(lastpix+r)=0; }      
} 
