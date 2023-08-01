#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>

// Estructura de Pelicula.
struct Pelicula{
	int codigo;
	char titulo[32];
	char actores[52];
	char director[52];
	char genero[22];
	int duracion;
	float precio;
	int cant_alquilada;
	int cant_recibida;
	int stock;
}pelicula;

// Funcion para desactivar Maximizar
void desactivarMaximizar(){
	HWND consoleWindow;
	consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE,GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

// Funcion Gotoxy
void gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;
	SetConsoleCursorPosition(hcon,dwPos);
}

// Funcion Menu principal.
void menuPrincipal(){

	system("cls");
	char opcion = 's';
	int opMenu = 0;

	gotoxy(27,8);printf("===========================================\n");
	gotoxy(27,9);printf("\t==> ADMINISTRACION VIDEO CLUB <==\n");
	gotoxy(27,10);printf("===========================================");


	while(opcion == 's'){
		gotoxy(27,12);printf("\t[1]- Ingresar nueva pelicula \n");
		gotoxy(27,13);	printf("\t[2]- Editar una pelicula \n");
		gotoxy(27,14);	printf("\t[3]- Borrar una pelicula \n");
		gotoxy(27,15);	printf("\t[4]- Filtrar peliculas por clave \n");
		gotoxy(27,16);	printf("\t[5]- Listado general de peliculas \n");
		gotoxy(27,17);	printf("\t[6]- Listado particular \n");
		gotoxy(27,18);	printf("\t[7]- Consulta particular \n");
		gotoxy(27,19);	printf("\t[8]- Alquiler pelicula \n");
		gotoxy(27,20);	printf("\t[9]- Salir \n");
		gotoxy(27,21);	printf("\tIngrese su opcion: [ ] \n");
		gotoxy(52,21);	scanf("%i", &opMenu);
	
			if(opMenu>0 && opMenu<10){
				switch(opMenu){
				case 1: {
					altaPelicula();
					break;
				}
				case 2: {
					editarPelicula();
					break;
				}
				case 3: {
					borrarPelicula();
					break;
				}
				case 4: {
					listarPelicula();
					break;
				}
				case 5: {
					listadoGeneral();
					break;
				}
				case 6: {
					listadoParticular();
					break;
				}
				case 7: {
					consultaParticular();
					break;
				}
				case 8: {
					alquilerPelicula();
					break;
				}
				case 9: {
					system("cls");
					gotoxy(27,15);printf("GRACIAS POR USAR NUESTRO PROGRAMA, HASTA LUEGO! \n\n\n\t\t\tEXEQUIEL VAZQUEZ - MISAEL SENDRA - FERNANDO SARMIENTO");
					gotoxy(0,27);exit (0);
					break;
				}
	
			}
			} else {
				system("cls");
				printf("Por favor ingrese una opcion correcta \n");
			}

	printf("Continuar (S/N) \n");
	scanf(" %c", &opcion);
	switch(opcion){
    case 's': {
        system("cls");
    	gotoxy(27,8);printf("===========================================\n");
		gotoxy(27,9);printf("\t==> ADMINISTRACION VIDEO CLUB <==\n");
		gotoxy(27,10);printf("===========================================");
        break;
    }
    }
	}
}

// Funcion para buscar un codigo que ya existe
int buscarCodigo(const int codigo){
	FILE* archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    struct Pelicula pelicula;

    while (fread(&pelicula, sizeof(struct Pelicula), 1, archivo) == 1) {
        if (pelicula.codigo == codigo) {
            fclose(archivo);
            return 1; // El codigo ya existe
        }
    }

    fclose(archivo);
    return 0; // El codigo no existe
}

// Función para buscar una película por su título
int buscarPeliculaPorTitulo(const char* titulo) {
    FILE* archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    struct Pelicula pelicula;

    while (fread(&pelicula, sizeof(struct Pelicula), 1, archivo) == 1) {
        if (strcmp(pelicula.titulo, titulo) == 0) {
            fclose(archivo);
            return 1; // La película ya existe
        }
    }

    fclose(archivo);
    return 0; // La película no existe
}

// Funcion para encontrar si son solo letras
bool esSoloLetras(const char *cadena) {
    bool contiene_letras = false;

    for (int i = 0; cadena[i] != '\0'; i++) {
        if (isalpha(cadena[i])) {
            contiene_letras = true;
        } else if (!isspace(cadena[i])) {
            return false; // Se encontró un carácter no permitido
        }
    }

    return contiene_letras;
}

// Funcion para encontrar si son solo numeros
bool esSoloNumeros(const char *cadena) {
    bool contiene_numeros = false;
    bool punto_encontrado = false;

    for (int i = 0; cadena[i] != '\0'; i++) {
        if (isdigit(cadena[i])) {
            contiene_numeros = true;
        } else if (cadena[i] == '.' && !punto_encontrado) {
            punto_encontrado = true;
        } else {
            return false; // Se encontró un carácter no permitido
        }
    }

    return contiene_numeros;
}

// Funcion alquiler pelicula
void alquilerPelicula(){
system("cls");

    FILE *archivo;
    archivo = fopen("peliculas.dat", "rb+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }

    struct Pelicula pelicula;
    int cod;
    int existe=0;
    long int posicionEdicion;

    printf("Ingrese CODIGO de pelicula buscada: ");
    scanf("%i", &cod);

     while (fread(&pelicula, sizeof(struct Pelicula), 1, archivo) == 1){
	    if (cod==pelicula.codigo){

        printf("| TITULO: %-20s |\n| STOCK: %i |\n",pelicula.titulo, pelicula.stock);

	    existe=1;
	    break;
		}
	}
	
	if(existe==1){
		
		// VALIDACION STOCK
	    char stockStr[10];
	    int stock;
	
	    do {
	        printf("Ingrese unidades ALQUILADAS: ");
	        fflush(stdin);
	        fgets(stockStr, sizeof(stockStr), stdin);
	        stockStr[strcspn(stockStr, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final
	
	        if (!esSoloNumeros(stockStr)) {
	            printf("Debe contener solo NUMEROS. Por favor, ingrese un valor valido.\n");
	        } else	{
	            stock = atoi(stockStr); // Convertir la cadena a entero
	            if (stock <= 0) {
	                printf("Debe ser un numero entero positivo. Por favor, ingrese un valor valido.\n");
	            }
	        }
	    } while (!esSoloNumeros(stockStr) || stock <= 0);
	
	    pelicula.stock = stock; // le asigna el valor de precio al atributo de la estructura Pelicula
		
		if (pelicula.cant_alquilada > pelicula.stock) {
	    	printf("No hay suficientes unidades en stock para completar el alquiler.\n");
		} else {
		    pelicula.stock -= pelicula.cant_alquilada;
		
		    // Guardar la posición actual en el archivo
		    posicionEdicion = ftell(archivo);
		
		    // Regresar a la posición inicial de la película para sobrescribir los datos
		    fseek(archivo, posicionEdicion - sizeof(struct Pelicula), SEEK_SET);
		
		    // Escribir la película editada directamente en el archivo
		    fwrite(&pelicula, sizeof(struct Pelicula), 1, archivo);
		
		    printf("ALQUILER INGRESADO CORRECTAMENTE! \n");
		    printf("STOCK ACTUALIZADO: %i \n", pelicula.stock);
		}
	}
    
	if(existe==0)
	printf("Pelicula no existe con ese codigo \nPor favor ingrese un codigo valido \n");
	
	fclose(archivo);
 
}

// Funcion [1] dar de alta una pelicula.
void altaPelicula() {
    system("cls");
    
    FILE *archivo;
    archivo = fopen("peliculas.dat", "ab");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    struct Pelicula pelicula;

    printf("\n\t\t\t==> DAR DE ALTA NUEVA PELICULA <==\n\n\n");
    printf("\t\t================================================\n\n\n");

    char codigo[10]; // Variable auxiliar para validar el código
    printf("Ingrese el codigo de la pelicula: ");
    scanf("%s", codigo);

    if (buscarCodigo(atoi(codigo))) { // convierte un string a su equivalente en enteros
        printf("El codigo ya existe, por favor ingrese otro\n");
        fclose(archivo);
        return; // Salir de la función sin guardar el código
    }

    // Validar que solo se ingresen números en el código de la película
    for (int i = 0; codigo[i] != '\0'; i++) {
        if (!isdigit(codigo[i])) {
            printf("El codigo debe contener solo numeros. Por favor, intente nuevamente.\n");
            fclose(archivo);
            return; // Salir de la función si se encuentra un carácter no numérico
        }
    }

    pelicula.codigo = atoi(codigo); // le asigna el valor convertido a entero que fue ingresado por el usuario a pelicula.codigo

    do {
        printf("Ingrese el titulo de la pelicula: ");
        fflush(stdin);
        fgets(pelicula.titulo, sizeof(pelicula.titulo), stdin);
        pelicula.titulo[strcspn(pelicula.titulo, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        // Verificar la longitud del título
        if (strlen(pelicula.titulo) > 30) {
            printf("El titulo de la pelicula excede los 30 caracteres. Por favor, ingrese un titulo mas corto.\n");
        }

        if (buscarPeliculaPorTitulo(pelicula.titulo)) { // Verificar si el título ya existe en el registro
            printf("El titulo de la pelicula ya existe. Por favor, ingrese un nuevo título.\n");
            fclose(archivo);
            return; // Salir de la función sin guardar la película
        }
    } while (strlen(pelicula.titulo) > 30 || buscarPeliculaPorTitulo(pelicula.titulo));

    // Validar que solo se ingresen letras y espacios en ACTORES
    do {
        printf("Ingrese los actores de la pelicula: ");
        fflush(stdin);
        fgets(pelicula.actores, sizeof(pelicula.actores), stdin);
        pelicula.actores[strcspn(pelicula.actores, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        // Verificar la longitud de los actores
        if (strlen(pelicula.actores) > 50) {
            printf("Los actores de la pelicula exceden los 50 caracteres. Por favor, ingrese actores mas cortos.\n");
        }

        if (!esSoloLetras(pelicula.actores)) {
            printf("Los actores de la pelicula deben contener solo letras y espacios. Por favor, ingrese actores validos.\n");
        }
    } while (strlen(pelicula.actores) > 50 || !esSoloLetras(pelicula.actores));

    // Validar que solo se ingresen letras y espacios en DIRECTOR
    do {
        printf("Ingrese el director de la pelicula: ");
        fflush(stdin);
        fgets(pelicula.director, sizeof(pelicula.director), stdin);
        pelicula.director[strcspn(pelicula.director, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        // Verificar la longitud de los actores
        if (strlen(pelicula.director) > 50) {
            printf("El director de la pelicula exceden los 50 caracteres. Por favor, ingrese director mas corto.\n");
        }

        if (!esSoloLetras(pelicula.director)) {
            printf("El director de la pelicula deben contener solo letras y espacios. Por favor, ingrese director valido.\n");
        }
    } while (strlen(pelicula.director) > 50 || !esSoloLetras(pelicula.director));

    // Validar que solo se ingresen letras y espacios en GENERO
    do {
        printf("Ingrese el genero de la pelicula: ");
        fflush(stdin);
        fgets(pelicula.genero, sizeof(pelicula.genero), stdin);
        pelicula.genero[strcspn(pelicula.genero, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        // Verificar la longitud de genero
        if (strlen(pelicula.genero) > 20) {
            printf("El genero de la pelicula exceden los 50 caracteres. Por favor, ingrese genero mas corto.\n");
        }

        if (!esSoloLetras(pelicula.genero)) {
            printf("El genero de la pelicula deben contener solo letras y espacios. Por favor, ingrese genero valido.\n");
        }
    } while (strlen(pelicula.genero) > 20 || !esSoloLetras(pelicula.genero));


    // VALIDACION DURACION
    char duracionStr[10];
    int duracion;

    do {
        printf("Ingrese la duracion de la pelicula: ");
        fflush(stdin);
        fgets(duracionStr, sizeof(duracionStr), stdin);
        duracionStr[strcspn(duracionStr, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        if (!esSoloNumeros(duracionStr)) {
            printf("La duracion de la pelicula debe contener solo NUMEROS. Por favor, ingrese un valor valido.\n");
        } else {
            duracion = atoi(duracionStr); // Convertir la cadena a entero
            if (duracion <= 0) {
                printf("La duracion de la pelicula debe ser un numero entero positivo. Por favor, ingrese un valor valido.\n");
            }
        }
    } while (!esSoloNumeros(duracionStr) || duracion <= 0);

    pelicula.duracion = duracion;


    // VALIDACION PRECIO
    char precioStr[10];
    int precio;

    do {
        printf("Ingrese el precio de la pelicula: ");
        fflush(stdin);
        fgets(precioStr, sizeof(precioStr), stdin);
        precioStr[strcspn(precioStr, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        if (!esSoloNumeros(precioStr)) {
            printf("El precio de la pelicula debe contener solo NUMEROS. Por favor, ingrese un valor valido.\n");
        } else {
            precio = atoi(precioStr); // Convertir la cadena a entero
            if (precio <= 0) {
                printf("El precio de la pelicula debe ser un numero entero positivo. Por favor, ingrese un valor valido.\n");
            }
        }
    } while (!esSoloNumeros(precioStr) || precio <= 0);

    pelicula.precio = precio; // le asigna el valor de precio al atributo de la estructura Pelicula


	// VALIDACION CANTIDAD STOCK
    char cantidadStr[10];
    int cantidad;

    do {
        printf("Ingrese la cantidad recibida de la pelicula: ");
        fflush(stdin);
        fgets(cantidadStr, sizeof(cantidadStr), stdin);
        cantidadStr[strcspn(cantidadStr, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        if (!esSoloNumeros(cantidadStr)) {
            printf("La cantidad de la pelicula debe contener solo NUMEROS. Por favor, ingrese un valor valido.\n");
        } else {
            cantidad = atoi(cantidadStr); // Convertir la cadena a entero
            if (cantidad <= 0) {
                printf("La cantidad de la pelicula debe ser un numero entero positivo. Por favor, ingrese un valor valido.\n");
            }
        }
    } while (!esSoloNumeros(cantidadStr) || cantidad <= 0);

    pelicula.cant_recibida = cantidad;
    pelicula.stock = pelicula.cant_recibida;

    fwrite(&pelicula, sizeof(struct Pelicula), 1, archivo);

    printf("PELICULA INSERTADA CORRECTAMENTE!\n");

    fclose(archivo);
}

// Funcion [2] editar una pelicula.
void editarPelicula(){
	system("cls");
	FILE *archivo;
    archivo = fopen("peliculas.dat", "rb+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit (1);
    }

    struct Pelicula pelicula;

    int encontrado = 0;
    char peliculaBuscada[30];

    printf("\n\t\t\t==> EDITAR UNA PELICULA <==\n");
	printf("\t\t===========================================\n\n\n");

    printf("Ingrese CODIGO de la pelicula a editar: ");
    int cod;
    scanf("%i",&cod);

    int existe=0;
    long int posicionEdicion;

    while (fread(&pelicula, sizeof(struct Pelicula), 1, archivo) == 1){
    if (cod==pelicula.codigo){
    existe=1;
	printf("| CODIGO: %-8d \n| TITULO: %-20s \n| ACTORES: %-20s \n| DIRECTOR: %-20s \n| GENERO: %-10s \n| DURACION: %-8d \n| PRECIO ALQUILER: %-8.2f \n| CANTIDAD: %-8d \n",pelicula.codigo,
	pelicula.titulo,
	pelicula.actores,
	pelicula.director,
	pelicula.genero,
	pelicula.duracion,
	pelicula.precio,
	pelicula.cant_recibida);


	    do {
        printf("Ingrese el titulo de la pelicula: ");
        fflush(stdin);
        fgets(pelicula.titulo, sizeof(pelicula.titulo), stdin);
        pelicula.titulo[strcspn(pelicula.titulo, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        // Verificar la longitud del título
        if (strlen(pelicula.titulo) > 30) {
            printf("El titulo de la pelicula excede los 30 caracteres. Por favor, ingrese un titulo mas corto.\n");
        }

        if (buscarPeliculaPorTitulo(pelicula.titulo)) { // Verificar si el título ya existe en la base de datos
            printf("El titulo de la pelicula ya existe. Por favor, ingrese un nuevo título.\n");
            fclose(archivo);
            return; // Salir de la función sin guardar la película
        }
    } while (strlen(pelicula.titulo) > 30 || buscarPeliculaPorTitulo(pelicula.titulo));

		// Validar que solo se ingresen letras y espacios en ACTORES
    do {
        printf("Ingrese los actores de la pelicula: ");
        fflush(stdin);
        fgets(pelicula.actores, sizeof(pelicula.actores), stdin);

        // Verificar la longitud de los actores
        if (strlen(pelicula.actores) > 50) {
            printf("Los actores de la pelicula exceden los 50 caracteres. Por favor, ingrese actores mas cortos.\n");
        }

        if (!esSoloLetras(pelicula.actores)) {
            printf("Los actores de la pelicula deben contener solo letras y espacios. Por favor, ingrese actores validos.\n");
        }
    } while (strlen(pelicula.actores) > 50 || !esSoloLetras(pelicula.actores));


		// Validar que solo se ingresen letras y espacios en DIRECTOR
    do {
        printf("Ingrese el director de la pelicula: ");
        fflush(stdin);
        fgets(pelicula.director, sizeof(pelicula.director), stdin);

        // Verificar la longitud de los actores
        if (strlen(pelicula.director) > 50) {
            printf("El director de la pelicula exceden los 50 caracteres. Por favor, ingrese director mas corto.\n");
        }

        if (!esSoloLetras(pelicula.director)) {
            printf("El director de la pelicula deben contener solo letras y espacios. Por favor, ingrese director valido.\n");
        }
    } while (strlen(pelicula.director) > 50 || !esSoloLetras(pelicula.director));


		// Validar que solo se ingresen letras y espacios en GENERO
    do {
        printf("Ingrese el genero de la pelicula: ");
        fflush(stdin);
        fgets(pelicula.genero, sizeof(pelicula.genero), stdin);

        // Verificar la longitud de genero
        if (strlen(pelicula.genero) > 20) {
            printf("El genero de la pelicula exceden los 50 caracteres. Por favor, ingrese genero mas corto.\n");
        }

        if (!esSoloLetras(pelicula.genero)) {
            printf("El genero de la pelicula deben contener solo letras y espacios. Por favor, ingrese genero valido.\n");
        }
    } while (strlen(pelicula.genero) > 20 || !esSoloLetras(pelicula.genero));


		// VALIDACION DURACION
    char duracionStr[10];
    int duracion;

    do {
        printf("Ingrese la duracion de la pelicula: ");
        fflush(stdin);
        fgets(duracionStr, sizeof(duracionStr), stdin);
        duracionStr[strcspn(duracionStr, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        if (!esSoloNumeros(duracionStr)) {
            printf("La duracion de la pelicula debe contener solo NUMEROS. Por favor, ingrese un valor valido.\n");
        } else {
            duracion = atoi(duracionStr); // Convertir la cadena a entero
            if (duracion <= 0) {
                printf("La duracion de la pelicula debe ser un numero entero positivo. Por favor, ingrese un valor valido.\n");
            }
        }
    } while (!esSoloNumeros(duracionStr) || duracion <= 0);

    pelicula.duracion = duracion;

		// VALIDACION PRECIO
    char precioStr[10];
    int precio;

    do {
        printf("Ingrese el precio de la pelicula: ");
        fflush(stdin);
        fgets(precioStr, sizeof(precioStr), stdin);
        precioStr[strcspn(precioStr, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        if (!esSoloNumeros(precioStr)) {
            printf("El precio de la pelicula debe contener solo NUMEROS. Por favor, ingrese un valor valido.\n");
        } else {
            precio = atoi(precioStr); // Convertir la cadena a entero
            if (precio <= 0) {
                printf("El precio de la pelicula debe ser un numero entero positivo. Por favor, ingrese un valor valido.\n");
            }
        }
    } while (!esSoloNumeros(precioStr) || precio <= 0);

    pelicula.precio = precio; // le asigna el valor de precio al atributo de la estructura Pelicula


            // Guardar la posición actual en el archivo
            posicionEdicion = ftell(archivo);

            // Regresar a la posición inicial de la película para sobrescribir los datos
            fseek(archivo, posicionEdicion - sizeof(struct Pelicula), SEEK_SET);

            // Escribir la película editada directamente en el archivo
            fwrite(&pelicula, sizeof(struct Pelicula), 1, archivo);

            printf("PELICULA EDITADA CORRECTAMENTE! \n");
            break;
        }
    }

    fclose(archivo);

    if (existe == 0) {
        printf("No existe una pelicula con ese codigo \nPor favor ingrese un codigo valido \n");
    }
}

// Funcion [3] borrar una pelicula.
void borrarPelicula() {
    system("cls");

    FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    FILE *nuevoArchivo;
    nuevoArchivo = fopen("peliculas.tmp", "wb");
    if (nuevoArchivo == NULL) {
        fclose(archivo);
        printf("Error al abrir el archivo temporal\n");
        exit(1);
    }

    struct Pelicula pelicula;
    int encontrado = 0;
    char nombreBorrar[32];
    int continua = 1;
    int op = 0;

    printf("\n\t\t\t==> BORRAR UNA PELICULA <==\n");
    printf("\t\t==========================================\n\n\n");

    while (continua == 1) {
        printf("Ingrese el titulo de la pelicula a BORRAR: ");
        fflush(stdin);
        fgets(nombreBorrar, sizeof(pelicula.titulo), stdin);
        nombreBorrar[strcspn(nombreBorrar, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

        // Validar que el usuario ingresó una cadena válida no vacía
        if (strlen(nombreBorrar) == 0) {
            printf("ERROR | Por favor ingrese una pelicula que se encuentre en la base de datos\n");
            continue;
        }

        encontrado = 0; // Reiniciar el indicador de encontrado

        fseek(archivo, 0, SEEK_SET); // Reposicionar el puntero del archivo al inicio del archivo
        while (fread(&pelicula, sizeof(struct Pelicula), 1, archivo) == 1) {
            if (strcmp(pelicula.titulo, nombreBorrar) == 0) {
                encontrado = 1;
            } else {
                fwrite(&pelicula, sizeof(struct Pelicula), 1, nuevoArchivo);
            }
        }

        if (encontrado == 0) {
            printf("LA PELICULA NO EXISTE!\n");
            printf("[1]- Ir al menu principal\n");
            printf("[2]- Continuar\n");
            scanf("%i", &op);
            if (op == 1) {
                menuPrincipal();
            } else {
                continue;
            }
        }

        break; // Salir del bucle while
    }

    fflush(nuevoArchivo); // Asegurarse de que todos los datos se hayan escrito en el archivo temporal
    fclose(nuevoArchivo);
    fclose(archivo);

    if (encontrado == 1) {
        printf("LA PELICULA HA SIDO BORRADA CORRECTAMENTE! \n");
    }

    remove("peliculas.dat");
    rename("peliculas.tmp", "peliculas.dat");
}

// Funcion [4] filtrar las peliculas según clave.
void listarPelicula(){
	system("cls");

	FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    printf("\n\t\t\t==> FILTRAR PELICULAS <==\n");
	printf("\t\t========================================\n\n\n");

	char opcion = 's';
    int opListar = 0;

    while(opcion == 's'){
		printf("[1]- Filtrar por precio de alquiler \n");
		printf("[2]- Filtrar por duracion de la pelicula \n");
		printf("[3]- Filtrar por cantidad de stock \n");
		printf("Ingrese una opcion: [ ] \n");
		scanf("%i", &opListar);

		if(opListar >0 && opListar < 4){
				switch(opListar){
				case 1: {
					listarPrecio();
					break;
				}
				case 2: {
					listarDuracion();
					break;
				}
				case 3: {
					listarCantidad();
					break;
				}
			}
			}
			else {
				printf("Por favor ingrese una opcion correcta \n");
			}


		printf("Continuar... (s/n) \n");
		scanf(" %c", &opcion);
	}

	fclose(archivo);
}

// Funcion [4]-1 filtrar por precio (minimos y maximos).
void listarPrecio(){
	system("cls");

	FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit (1);
    }

    printf("\n\t\t\t==> LISTAR PELICULAS POR PRECIO <==\n");
	printf("\t\t================================================\n\n\n");

	struct Pelicula pelicula[100];
	int num_peliculas = 0;

	while(fread(&pelicula[num_peliculas], sizeof(struct Pelicula), 1, archivo) == 1){
		num_peliculas++;
	}

	fclose(archivo);

	char opcion = 's';
	int opMenu = 0;

	while(opcion=='s'){
	printf("[1]- Listar de menor a mayor \n");
	printf("[2]- Listar de mayor a menor \n");
	printf("[3]- Salir al menu principal \n");
	scanf("%i", &opMenu);

	if(opMenu >0 && opMenu < 4){
		switch(opMenu){
			case 1:{
				// ordenamiento por burbuja para ordenar de menor a mayor
				for(int i = 0; i < num_peliculas -1; i++){
					for (int j = 0; j < num_peliculas - i - 1; j++){
						if (pelicula[j].precio > pelicula[j + 1].precio){
							struct Pelicula aux = pelicula[j];
							pelicula[j] = pelicula[j + 1];
							pelicula[j + 1] = aux;
						}
					}
				}

				system("cls");
				printf("Peliculas ordenadas por precio de alquiler (de menor a mayor):\n");
				for (int i = 0; i < num_peliculas; i++) {
				    printf("%s - precio: $ %.2f\n", pelicula[i].titulo, pelicula[i].precio);
				}
				break;
			}
			case 2:{
				// ordenamiento por burbuja para ordenar de mayor a menor
				for(int i = 0; i < num_peliculas -1; i++){
					for (int j = 0; j < num_peliculas - i - 1; j++){
						if (pelicula[j].precio < pelicula[j + 1].precio){
							struct Pelicula aux = pelicula[j + 1];
							pelicula[j + 1] = pelicula[j];
							pelicula[j] = aux;
						}
					}
				}

				system("cls");
				printf("Peliculas ordenadas por precio de alquiler (de mayor a menor):\n");
				for (int i = 0; i < num_peliculas; i++) {
				    printf("%s - precio: $ %f\n", pelicula[i].titulo, pelicula[i].precio);
				}
				break;
			}
			case 3:{
				menuPrincipal();
				break;
			}
		} // cierre del switch
	} // cierre del if
else {
	printf("Por favor ingrese una opcion correcta \n");
	}


}
}

// Funcion [4]-2 filtrar por duracion (minimos y maximos).
void listarDuracion(){
	system("cls");

	FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit (1);
    }

    printf("\n\t\t\t==> LISTAR PELICULAS POR DURACION <==\n");
	printf("\t\t================================================\n\n\n");

	struct Pelicula pelicula[100];
	int num_peliculas = 0;

	while(fread(&pelicula[num_peliculas], sizeof(struct Pelicula), 1, archivo) == 1){
		num_peliculas++;
	}

	fclose(archivo);

	char opcion = 's';
	int opMenu = 0;

	while(opcion=='s'){
	printf("[1]- Listar de menor a mayor \n");
	printf("[2]- Listar de mayor a menor \n");
	printf("[3]- Salir al menu principal \n");
	scanf("%i", &opMenu);

	if(opMenu >0 && opMenu < 4){
		switch(opMenu){
			case 1:{
				// ordenamiento por burbuja para ordenar de menor a mayor
				for(int i = 0; i < num_peliculas -1; i++){
					for (int j = 0; j < num_peliculas - i - 1; j++){
						if (pelicula[j].duracion > pelicula[j + 1].duracion){
							struct Pelicula aux = pelicula[j];
							pelicula[j] = pelicula[j + 1];
							pelicula[j + 1] = aux;
						}
					}
				}

				system("cls");
				printf("Peliculas ordenadas por duracion (de menor a mayor):\n");
				for (int i = 0; i < num_peliculas; i++) {
				    printf("%s - %i minutos\n", pelicula[i].titulo, pelicula[i].duracion);
				}
				break;
			}
			case 2:{
				// ordenamiento por burbuja para ordenar de mayor a menor
				for(int i = 0; i < num_peliculas -1; i++){
					for (int j = 0; j < num_peliculas - i - 1; j++){
						if (pelicula[j].duracion < pelicula[j + 1].duracion){
							struct Pelicula aux = pelicula[j + 1];
							pelicula[j + 1] = pelicula[j];
							pelicula[j] = aux;
						}
					}
				}

				system("cls");
				printf("Peliculas ordenadas por duracion (de mayor a menor):\n");
				for (int i = 0; i < num_peliculas; i++) {
				    printf("%s - %i minutos\n", pelicula[i].titulo, pelicula[i].duracion);
				}
				break;
			}
			case 3:{
				menuPrincipal();
				break;
			}
		} // cierre del switch
	} // cierre del if
else {
	printf("Por favor ingrese una opcion correcta \n");
	}


}
	}

// Funcion [4]-3 filtrar por stock (minimos y maximos).
void listarCantidad(){
	system("cls");

	FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit (1);
    }

    printf("\n\t\t\t==> LISTAR PELICULAS POR STOCK <==\n");
	printf("\t\t================================================\n\n\n");

	struct Pelicula pelicula[100];
	int num_peliculas = 0;

	while(fread(&pelicula[num_peliculas], sizeof(struct Pelicula), 1, archivo) == 1){
		num_peliculas++;
	}

	fclose(archivo);

	char opcion = 's';
	int opMenu = 0;

	while(opcion=='s'){
	printf("[1]- Listar de menor a mayor \n");
	printf("[2]- Listar de mayor a menor \n");
	printf("[3]- Salir al menu principal \n");
	scanf("%i", &opMenu);

	if(opMenu >0 && opMenu < 4){
		switch(opMenu){
			case 1:{
				// ordenamiento por burbuja para ordenar de menor a mayor
				for(int i = 0; i < num_peliculas -1; i++){
					for (int j = 0; j < num_peliculas - i - 1; j++){
						if (pelicula[j].cant_recibida > pelicula[j + 1].cant_recibida){
							struct Pelicula aux = pelicula[j];
							pelicula[j] = pelicula[j + 1];
							pelicula[j + 1] = aux;
						}
					}
				}

				system("cls");
				printf("Peliculas ordenadas por duracion (de menor a mayor):\n");
				for (int i = 0; i < num_peliculas; i++) {
				    printf("%s - stock: %i\n", pelicula[i].titulo, pelicula[i].cant_recibida);
				}
				break;
			}
			case 2:{
				// ordenamiento por burbuja para ordenar de mayor a menor
				for(int i = 0; i < num_peliculas -1; i++){
					for (int j = 0; j < num_peliculas - i - 1; j++){
						if (pelicula[j].cant_recibida < pelicula[j + 1].cant_recibida){
							struct Pelicula aux = pelicula[j + 1];
							pelicula[j + 1] = pelicula[j];
							pelicula[j] = aux;
						}
					}
				}

				system("cls");
				printf("Peliculas ordenadas por duracion (de mayor a menor):\n");
				for (int i = 0; i < num_peliculas; i++) {
				    printf("%s - stock: %i\n", pelicula[i].titulo, pelicula[i].cant_recibida);
				}
				break;
			}
			case 3:{
				menuPrincipal();
				break;
			}
		} // cierre del switch
	} // cierre del if
	else {
		printf("Por favor ingrese una opcion correcta \n");
		}
	}
}

// Funcion [5] listar todas las peliculas.
void listadoGeneral() {
    system("cls");

    FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }

    struct Pelicula pelicula[100];
    int num_peliculas = 0;

    while (fread(&pelicula[num_peliculas], sizeof(struct Pelicula), 1, archivo) == 1) {
        num_peliculas++;
       
    }

    fclose(archivo);

    gotoxy(30,1);printf("==> LISTADO DE PELICULAS REGISTRADAS <==\n");
    printf(" ==================================================================================================\n");
    printf(" CODIGO   TITULO      ACTORES      DIRECTOR       GENERO       DURACION      PRECIO          STOCK \n");
    printf(" --------------------------------------------------------------------------------------------------\n");
	int fila=5;
    for (int i = 0; i < num_peliculas; i++) {
       gotoxy(3,fila); printf("%i",pelicula[i].codigo);
       gotoxy(9,fila); printf("%s",pelicula[i].titulo);
       gotoxy(21,fila); printf("%s",pelicula[i].actores);
       gotoxy(34,fila); printf("%s",pelicula[i].director);
       gotoxy(49,fila); printf("%s",pelicula[i].genero);
       gotoxy(65,fila); printf("%i",pelicula[i].duracion);
       gotoxy(76,fila); printf("%.2f",pelicula[i].precio);
       gotoxy(93,fila); printf("%i",pelicula[i].stock);
	   fila++;
	    }

    printf(" \n ==================================================================================================\n");
}

// Funcion [6] Listado particular.
void listadoParticular(){
	system("cls");

    FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }

    struct Pelicula pelicula;
    int cod;
    int existe=0;

    printf("Ingrese CODIGO de pelicula buscada: ");
    scanf("%i", &cod);

    fread(&pelicula,sizeof(struct Pelicula),1,archivo);

    while(!feof(archivo)){
	    if (cod==pelicula.codigo){

        printf("| TITULO: %-20s \n| ACTORES: %-20s \n| DIRECTOR: %-20s \n| GENERO: %-10s \n| DURACION: %-8d \n| PRECIO ALQUILER: %-8.2f \n| CANTIDAD: %-8d \n",pelicula.titulo,
		pelicula.actores,
		pelicula.director,
		pelicula.genero,
		pelicula.duracion,
		pelicula.precio,
		pelicula.stock);

	    existe=1;
	    break;
		}

		fread(&pelicula,sizeof(struct Pelicula),1,archivo);
	}

	if(existe==0)
		printf("Pelicula no existe con ese codigo \n Por favor ingrese un codigo valido \n");

    fclose(archivo);
}

// Funcion [7] consulta particular.
void consultaParticular(){
	menuConsultas();
}

// Funcion [7]-1 consultar strings.
void consultarString(int campo){
	system("cls");

	FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    struct Pelicula pelicula;

    char strBuscado[50] = "";
    int encontrado = 0;

    printf("Ingrese el valor buscado:");
    fflush(stdin);
    fgets(strBuscado, 50, stdin);
    strBuscado[strcspn(strBuscado, "\n")] = '\0'; // Eliminar el carácter de nueva línea al final

    while(fread(&pelicula, sizeof(struct Pelicula),1,archivo)==1){
    	int valor = 0;
    	switch(campo){
    		case 1:
    			valor = strcmp(strBuscado, pelicula.titulo); // si las cadenas coinciden se le asigna 0 a valor..
    			break;
			case 2:
				valor = strcmp(strBuscado, pelicula.actores);
				break;
			case 3:
				valor = strcmp(strBuscado, pelicula.director);
				break;
			case 4:
				valor = strcmp(strBuscado, pelicula.genero);
				break;
		}
		if(valor == 0){ // si valor es 0 las cadenas son iguales
            encontrado = 1;
            printf("| CODIGO: %-8d \n| TITULO: %-20s \n| ACTORES: %-20s \n| DIRECTOR: %-20s \n| GENERO: %-10s \n| DURACION: %-8d \n| PRECIO ALQUILER: %-8.2f \n| CANTIDAD: %-8d \n",
            pelicula.codigo,
            pelicula.titulo,
            pelicula.actores,
            pelicula.director,
            pelicula.genero,
            pelicula.duracion,
            pelicula.precio,
            pelicula.stock);
        }
	}
		if(!encontrado) {
	    printf("Pelicula no encontrada\n");
	}

    fclose(archivo);
}

// Funcion [7]-2 consultar numeros.
void consultarNumero(int campo){
    system("cls");

    FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    struct Pelicula pelicula;
    int numBuscado=0;
    int encontrado = 0;

    printf("Ingrese un valor: ");
    scanf("%i", &numBuscado);

    while (fread(&pelicula, sizeof(struct Pelicula), 1, archivo) == 1) {
        int valor = 0;
        switch(campo) {
            case 1:
                valor = pelicula.duracion;
                break;
            case 2:
                valor = pelicula.precio;
                break;
            case 3:
                valor = pelicula.stock;
                break;
        }
        if(valor == numBuscado){
            encontrado = 1;
            printf("| %-8d | %-20s | %-20s | %-20s | %-10s | %-8d | %-8.2f | %-8d |\n",
            pelicula.codigo,
            pelicula.titulo,
            pelicula.actores,
            pelicula.director,
            pelicula.genero,
            pelicula.duracion,
            pelicula.precio,
            pelicula.stock);
        }
    }

    if(!encontrado){
        printf("Pelicula no encontrada\n");
    }

    fclose(archivo);
}

//Funcion Menu de consultas.
void menuConsultas(){
	system("cls");

	FILE *archivo;
    archivo = fopen("peliculas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    printf("\n\t\t\t==> CONSULTAR PELICULAS <==\n");
	printf("\t\t========================================\n\n\n");

	char opcion = 's';
    int opListar = 0;

    while(opcion == 's'){
		printf("\t[1]- Consultar por titulo \n");
		printf("\t[2]- Consultar por actores \n");
		printf("\t[3]- Consultar por director \n");
		printf("\t[4]- Consultar por genero \n");
		printf("\t[5]- Consultar por duracion \n");
		printf("\t[6]- Consultar por precio \n");
		printf("\t[7]- Consultar por cantidad \n");
		printf("\t[8]- Ir al menu principal \n");
		printf("\tIngrese una opcion: [ ] \n");
		scanf("%i", &opListar);

		if(opListar >0 && opListar < 9){
				switch(opListar){
				case 1: {
					consultarString(1); // titulo
					break;
				}
				case 2: {
					consultarString(2); // actores
					break;
				}
				case 3: {
					consultarString(3); // director
					break;
				}
				case 4: {
					consultarString(4); // genero
					break;
				}
				case 5: {
					consultarNumero(1); // duracion
					break;
				}
				case 6:{
					consultarNumero(2); // precio
					break;
				}
				case 7:{
					consultarNumero(3); // cantidad
					break;
				}
				case 8: {
					menuPrincipal();
					break;
				}
			}
			}
			else {
				printf("Por favor ingrese una opcion correcta \n");
			}


		printf("Continuar... (s/n) \n");
		scanf(" %c", &opcion);
	}

	fclose(archivo);
}

int main(){

// crea el registro desde cero por única vez y después se comenta el código.

//	FILE *archivo;
//	    archivo = fopen("peliculas.dat", "wb");
//	    if (archivo == NULL) {
//	        gotoxy(27,15);printf("Error al abrir el archivo\n");
//	        gotoxy(0,27);exit (1);
//	    } else {
//    	gotoxy(27,15);printf("Base de datos Peliculas creado correctamente \n");
//		}
//		system("pause");
//		fclose(archivo);

	//APARIENCIA
	system("mode con: cols=130 lines=30");
	system("COLOR 30");
	system("title ADMIN-VIDEOCLUB");
	desactivarMaximizar();
	
	//llamar al menu principal
	menuPrincipal();

	return 0;
}
