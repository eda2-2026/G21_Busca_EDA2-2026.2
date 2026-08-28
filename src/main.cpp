#include <iostream>

#include "catalogo.h"
#include "menu.h"

int main() {  
      
    Catalogo catalogo;
    Menu menu(catalogo);
    
    menu.executar();

    return 0;
}