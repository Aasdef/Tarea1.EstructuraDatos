#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Definición del TDA para representar un libro
typedef struct LibroNode {
    char titulo[51];
    char autor[51];
    char genero[51];
    char ISBN[51];
    char ubicacion[51];
    char estado[51];
    struct EstudianteNode* reservas;
    struct LibroNode* next;
} Libro;
// Definición del TDA para representar a un estudiante en la cola de reservas
typedef struct EstudianteNode {
    char nombre[51];
    struct EstudianteNode* next;
} Estudiante;

// Función para crear un nuevo libro y agregarlo a la biblioteca
Libro* registrarLibro(Libro* biblioteca, const char* titulo, const char* autor, const char* genero,const char* ISBN, const char* ubicacion) {
  Libro* nuevoLibro = (Libro*)malloc(sizeof(Libro));
  if (nuevoLibro == NULL) {
    printf("Error: no se pudo asignar memoria para el libro.\n");
    return biblioteca;
  }

// Inicializar el nuevo libro
  strcpy(nuevoLibro->titulo, titulo);
  strcpy(nuevoLibro->autor, autor);
  strcpy(nuevoLibro->genero, genero);
  strcpy(nuevoLibro->ISBN, ISBN);
  strcpy(nuevoLibro->ubicacion, ubicacion);
  strcpy(nuevoLibro->estado, "Disponible");
  nuevoLibro->reservas = NULL;
  nuevoLibro->next = NULL;

  // Agregar el nuevo libro a la lista de biblioteca
  if (biblioteca == NULL) {
    biblioteca = nuevoLibro;
  } else {
    Libro* current = biblioteca;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = nuevoLibro;
  }

  printf("Libro registrado con éxito.\n");
  return biblioteca;
}
// Función para mostrar los datos de un libro
void mostrarDatosLibro(Libro* biblioteca, const char* titulo, const char* autor) {
  Libro* current = biblioteca;
  while (current != NULL) {
    if (strcmp(current->titulo, titulo) == 0 && strcmp(current->autor, autor) == 0) {
      printf("Título: %s", current->titulo);
      printf("Autor: %s", current->autor);
      printf("Género: %s", current->genero);
      printf("ISBN: %s", current->ISBN);
      printf("Ubicación: %s", current->ubicacion);
      printf("Estado: %s\n", current->estado);

      Estudiante* reserva = current->reservas;
      if (reserva != NULL) {
        printf("Reservas:\n");
        while (reserva != NULL) {
          printf("- %s", reserva->nombre);
          reserva = reserva->next;
        }
      }

      return;
    }
    current = current->next;
  }
  printf("El libro no existe en la biblioteca.\n");
}

// Función para mostrar todos los libros
void mostrarTodosLosLibros(Libro* biblioteca) {
  Libro* current = biblioteca;
  if (current == NULL) {
    printf("No hay libros registrados en la biblioteca.\n");
  } 
  else {
    printf("Lista de libros:\n");
    int i = 1;
    while (current != NULL) {
      printf("%d. Título: %s", i, current->titulo);
      printf("   Autor: %s", current->autor);
      i++;
      current = current->next;
    }
  }
}
// Función para reservar un libro
void reservarLibro(Libro* biblioteca, const char* titulo, const char* autor, const char* nombre_estudiante) {
  Libro* current = biblioteca;
  while (current != NULL) {
    if (strcmp(current->titulo, titulo) == 0 && strcmp(current->autor, autor) == 0) {
      if (strcmp(current->estado, "Disponible") == 0) {
        strcpy(current->estado, "Reservado");
      }
// Agregar el estudiante a la cola de reservas
      Estudiante* nuevoEstudiante = (Estudiante*)malloc(sizeof(Estudiante));
      if (nuevoEstudiante == NULL) {
        printf("Error: no se pudo asignar memoria para el estudiante.\n");
        return;
      }
      strcpy(nuevoEstudiante->nombre, nombre_estudiante);
      nuevoEstudiante->next = NULL;

      Estudiante* reserva = current->reservas;
      if (reserva == NULL) {
        current->reservas = nuevoEstudiante;
      } else {
        while (reserva->next != NULL) {
          reserva = reserva->next;
        }
        reserva->next = nuevoEstudiante;
      }

      printf("El libro ha sido reservado por %s.\n", nombre_estudiante);
      return;
    }
    current = current->next;
  }
  printf("El libro no existe en la biblioteca.\n");
}

// Función para cancelar una reserva de libro
void cancelarReservaLibro(Libro* biblioteca, const char* titulo, const char* autor, const char* nombre_estudiante) {
  Libro* current = biblioteca;
  while (current != NULL) {
    if (strcmp(current->titulo, titulo) == 0 && strcmp(current->autor, autor) == 0) {
      Estudiante* reserva = current->reservas;
      Estudiante* anterior = NULL;
      while (reserva != NULL) {
        if (strcmp(reserva->nombre, nombre_estudiante) == 0) {
// Eliminar el estudiante de la cola de reservas
          if (anterior == NULL) {
            current->reservas = reserva->next;
          } else {
            anterior->next = reserva->next;
          }
          free(reserva);
          printf("La reserva del libro ha sido cancelada por %s.\n", nombre_estudiante);
          return;
        }
        anterior = reserva;
        reserva = reserva->next;
      }
      printf("%s no tiene una reserva para este libro.\n", nombre_estudiante);
      return;
    }
    current = current->next;
  }
  printf("El libro no existe en la biblioteca.\n");
}

// Función para retirar un libro
void retirarLibro(Libro* biblioteca, const char* titulo, const char* autor, const char* nombre_estudiante) {
  Libro* current = biblioteca;
  while (current != NULL) {
    if (strcmp(current->titulo, titulo) == 0 && strcmp(current->autor, autor) == 0) {
      if (strcmp(current->estado, "Disponible") == 0 || (strcmp(current->estado, "Reservado") == 0 && strcmp(current->reservas->nombre,nombre_estudiante) == 0)) {
        strcpy(current->estado, "Prestado");

// Eliminar al estudiante de la cola de reservas
        if (strcmp(current->estado, "Reservado") == 0) {
          Estudiante* reserva = current->reservas;
          current->reservas = current->reservas->next;
          free(reserva);
        }

        printf("El libro ha sido retirado por %s.\n", nombre_estudiante);
        return;
      }else {
      printf("El libro no puede ser retirado en este momento.\n");
      return;
      }
    }
    current = current->next;
  }
  printf("El libro no existe en la biblioteca.\n");
}

void devolverLibro(Libro* biblioteca, const char* titulo, const char* autor) {
  Libro* current = biblioteca;
  while (current != NULL) {
    if (strcmp(current->titulo, titulo) == 0 && strcmp(current->autor, autor) == 0) {
      if (strcmp(current->estado, "Prestado") == 0) {
        if (current->reservas != NULL) {
          strcpy(current->estado, "Reservado");
        } else {
          strcpy(current->estado, "Disponible");
        }
        printf("El libro ha sido devuelto.\n");
        return;
      } else {
        printf("El libro no se encuentra prestado.\n");
        return;
      }
    }
    current = current->next;
  }
  printf("El libro no existe en la biblioteca.\n");
}

// Función para mostrar libros prestados
void mostrarLibrosPrestados(Libro* biblioteca) {
  Libro* current = biblioteca;
  int count = 0;
  printf("Libros prestados:\n");
  while (current != NULL) {
    if (strcmp(current->estado, "Prestado") == 0) {
      printf("Título: %s", current->titulo);
      printf("Autor: %s", current->autor);
      printf("Prestado a: %s\n", current->reservas->nombre);
      count++;
    }
    current = current->next;
  }
  if (count == 0) {
  printf("No hay libros prestados en este momento.\n");
  }
}


// Función para importar libros desde un archivo CSV
void importarLibrosDesdeCSV(Libro** biblioteca, const char* nombre_archivo) {
  FILE* archivo = fopen(nombre_archivo, "r");
  if (archivo == NULL) {
    printf("No se pudo abrir el archivo.\n");
    return;
  }

  char linea[256];
  while (fgets(linea, sizeof(linea), archivo)) {
    char titulo[51], autor[51], genero[51],ISBN[51], ubicacion[51];
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],", titulo, autor, genero, ISBN, ubicacion);

// Agregar el libro a la biblioteca
    *biblioteca = registrarLibro(*biblioteca, titulo, autor, genero, ISBN, ubicacion);
  }

  fclose(archivo);
  printf("Libros importados desde el archivo CSV con éxito.\n");
}

// Función para exportar libros a un archivo CSV
void exportarLibrosACSV(Libro* biblioteca, const char* nombre_archivo) {
  FILE* archivo = fopen(nombre_archivo, "w");
  if (archivo == NULL) {
    printf("No se pudo crear el archivo.\n");
    return;
  }

  Libro* current = biblioteca;
  while (current != NULL) {
    fprintf(archivo, "%s,%s,%s,%s,%s,", current->titulo, current->autor, current->genero, current->ISBN, current->ubicacion);
    fprintf(archivo, "%s,", current->estado);

// Escribir la cola de reservas
    Estudiante* reserva = current->reservas;
    while (reserva != NULL) {
      fprintf(archivo, "%s", reserva->nombre);
      reserva = reserva->next;
      if (reserva != NULL) {
        fprintf(archivo, ",");
      }
    }
    fprintf(archivo, "\n");
    current = current->next;
  }

  fclose(archivo);
  printf("Libros exportados al archivo CSV con éxito.\n");
}

// Función para liberar la memoria de la biblioteca
void liberarMemoria(Libro* biblioteca) {
  while (biblioteca != NULL) {
    Libro* tempLibro = biblioteca;
    biblioteca = biblioteca->next;
// Liberar la memoria de la cola de reservas
    Estudiante* reserva = tempLibro->reservas;
    while (reserva != NULL) {
      Estudiante* tempEstudiante = reserva;
      reserva = reserva->next;
      free(tempEstudiante);
    }
    free(tempLibro);
  }
}

int main(){
  Libro* biblioteca = NULL;
  int opcion;

  do{
    printf("\nMenú de la biblioteca:\n");
    printf("1. Registrar libro\n");
    printf("2. Mostrar datos de libro\n");
    printf("3. Mostrar todos los libros\n");
    printf("4. Reservar libro\n");
    printf("5. Cancelar reserva de libro\n");
    printf("6. Retirar libro\n");
    printf("7. Devolver libro\n");
    printf("8. Mostrar libros prestados\n");
    printf("9. Importar libros desde un archivo CSV\n");
    printf("10. Exportar libros a un archivo CSV\n");
    printf("11. Salir\n");

    printf("Seleccione una opción: ");
    scanf("%d", &opcion);
    getchar();  // Limpiar el búfer de entrada   

    switch (opcion){
      case 1:{//REGISTRAR LIBRO EN LA BIBLIOTECA
        char titulo[50], autor[50], genero[50], ISBN[50], ubicacion[50];
        printf("Ingrese el título del libro (max 50 caracteres): ");
        fgets(titulo, sizeof(titulo), stdin);
        printf("Ingrese el autor del libro (max 50 caracteres): ");
        fgets(autor, sizeof(autor), stdin);
        printf("Ingrese el género del libro (max 50 caracteres): ");
        fgets(genero, sizeof(genero), stdin);
        printf("Ingrese el ISBN del libro (max 50 caracteres): ");
        fgets(ISBN, sizeof(ISBN), stdin);
        printf("Ingrese la ubicación del libro (max 50 caracteres): ");
        fgets(ubicacion, sizeof(ubicacion), stdin);
        biblioteca = registrarLibro(biblioteca, titulo, autor, genero, ISBN, ubicacion);
        break;  
      }
      case 2:{//MOSTRAR DATOS DE UN LIBRO
        char autorBuscar[51],tituloBuscar[51];
        printf("Ingrese el título del libro: ");
        fgets(tituloBuscar, sizeof(tituloBuscar), stdin);
        printf("Ingrese el autor del libro: ");
        fgets(autorBuscar, sizeof(autorBuscar), stdin);
        mostrarDatosLibro(biblioteca, tituloBuscar, autorBuscar);
        break;
      }
      case 3:{//MOSTRAR TODOS LOS LIBROS
        mostrarTodosLosLibros(biblioteca);
        break;
      }
      case 4: {//RESERVAR LIBRO
        char nombre_estudiante[51], titulo[51], autor[51];
        printf("Ingrese el título del libro: ");
        fgets(biblioteca->titulo, sizeof(biblioteca->titulo), stdin);
        printf("Ingrese el autor del libro: ");
        fgets(biblioteca->autor, sizeof(biblioteca->autor), stdin);
        printf("Ingrese el nombre del estudiante: ");
        fgets(nombre_estudiante, sizeof(nombre_estudiante), stdin);
        reservarLibro(biblioteca, biblioteca->titulo, biblioteca->autor, nombre_estudiante);
        break;
      }
      case 5:{//CANCELAR RESERVA LIBRO
        char nombre_estudiante[51], titulo[51],autor[51];
        printf("Ingrese el título del libro: ");
        fgets(biblioteca->titulo, sizeof(biblioteca->titulo), stdin);
        printf("Ingrese el autor del libro: ");
        fgets(biblioteca->autor, sizeof(biblioteca->autor), stdin);
        printf("Ingrese el nombre del estudiante: ");
        fgets(nombre_estudiante, sizeof(nombre_estudiante), stdin);
        cancelarReservaLibro(biblioteca, biblioteca->titulo, biblioteca->autor, nombre_estudiante);
        break;
      }  
      case 6:{//RETIRAR LIBRO
        char nombre_estudiante[51], titulo[51], autor[51];
        printf("Ingrese el título del libro: ");
        fgets(biblioteca->titulo, sizeof(biblioteca->titulo), stdin);
        printf("Ingrese el autor del libro: ");
        fgets(biblioteca->autor, sizeof(biblioteca->autor), stdin);
        printf("Ingrese el nombre del estudiante: ");
        fgets(nombre_estudiante, sizeof(nombre_estudiante), stdin);
        retirarLibro(biblioteca, biblioteca->titulo, biblioteca->autor, nombre_estudiante);
        break;
      }
      case 7:{//DEVOLVER LIBROS 
        char titulo[50], autor[50];
        printf("Ingrese el título del libro: ");
        fgets(biblioteca->titulo, sizeof(biblioteca->titulo), stdin);
        printf("Ingrese el autor del libro: ");
        fgets(biblioteca->autor, sizeof(biblioteca->autor), stdin);
        devolverLibro(biblioteca, titulo, autor);
        break;
      }
      case 8:{//MOSTRAR LIBROS PRESTADOS
        mostrarLibrosPrestados(biblioteca);
        break;
        
      }
      case 9:{//IMPORTAR DESDE CSV
        char nombre_archivo[50];
        printf("Ingrese el nombre del archivo CSV: ");
        fgets(nombre_archivo, sizeof(nombre_archivo), stdin);
        importarLibrosDesdeCSV(&biblioteca, nombre_archivo);
        break;
      }
      case 10:{//EXPORTAR DESDE CSV
        char nombre_archivo[50];
        printf("Ingrese el nombre del archivo CSV: ");
        fgets(nombre_archivo, sizeof(nombre_archivo), stdin);
        exportarLibrosACSV(biblioteca, nombre_archivo);
        break;
      }
      case 11:{//SALIDA
        printf("Saliendo de la aplicación.\n");
        break;
      }
      default:
        printf("Opción no válida. Por favor, seleccione una opción válida.\n");
      
    }
  }while (opcion != 11);
  // Liberar la memoria antes de salir
  liberarMemoria(biblioteca);
  return 0;
}