#include <stdio.h>

#define MAX_PRODUCTOS 5
#define MAX_RECURSOS 5
#define MAX_NOMBRE 20
#define MAX_RECURSOS_TOTALES 20

struct Recurso {
    char nombre[MAX_NOMBRE];
    int cantidad;
};

struct Producto {
    char nombre[MAX_NOMBRE];
    int tiempoFabricacionDias;
    int numRecursos;
    struct Recurso recursos[MAX_RECURSOS];
};

// === FUNCIONES AUXILIARES ===

int compararNombres(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}

void copiarTexto(char destino[], char origen[]) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

void limpiarBuffer() {
    while (getchar() != '\n');
}

void mostrarResumen(struct Producto productos[], int total) {
    printf("\nResumen de Productos:\n");
    for (int i = 0; i < total; i++) {
        int minutos = productos[i].tiempoFabricacionDias * 1440;
        printf("\nProducto %d:\n", i + 1);
        printf("Nombre: %s\n", productos[i].nombre);
        printf("Tiempo de fabricación: %d minutos (%.2f días)\n", minutos, (float)productos[i].tiempoFabricacionDias);
        printf("Requisitos:\n");
        for (int j = 0; j < productos[i].numRecursos; j++) {
            printf(" - %s: %d unidades\n", productos[i].recursos[j].nombre, productos[i].recursos[j].cantidad);
        }
    }
}

int recursoExiste(struct Recurso lista[], int total, char nombre[]) {
    for (int i = 0; i < total; i++) {
        if (compararNombres(lista[i].nombre, nombre)) {
            return i;
        }
    }
    return -1;
}

// === FUNCIÓN PRINCIPAL ===

int main() {
    struct Producto productos[MAX_PRODUCTOS];
    struct Producto plantillas[MAX_PRODUCTOS];
    struct Recurso recursosTotales[MAX_RECURSOS_TOTALES];

    int totalProductos = 0, totalPlantillas = 0, totalRecursosUsados = 0;
    int opcion;

    do {
        printf("\n--- MENÚ PRINCIPAL ---\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar un producto\n");
        printf("3. Eliminar un producto\n");
        printf("4. Ver resumen de productos\n");
        printf("5. Calcular producción según inventario\n");
        printf("6. Salir del programa\n");
        printf("Seleccione una opción: ");
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada no válida. Intente de nuevo.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        if (opcion == 1) {
            if (totalProductos >= MAX_PRODUCTOS) {
                printf("Límite de productos alcanzado.\n");
                continue;
            }

            printf("\nProducto %d:\n", totalProductos + 1);
            printf("Nombre del producto: ");
            scanf("%s", productos[totalProductos].nombre);

            int encontrado = -1;
            for (int j = 0; j < totalPlantillas; j++) {
                if (compararNombres(productos[totalProductos].nombre, plantillas[j].nombre)) {
                    encontrado = j;
                    break;
                }
            }

            if (encontrado != -1) {
                printf("Producto ya registrado antes. Se usarán sus datos guardados.\n");
                productos[totalProductos] = plantillas[encontrado];
            } else {
                int valido;
                do {
                    printf("Tiempo de fabricación (en días): ");
                    valido = scanf("%d", &productos[totalProductos].tiempoFabricacionDias);
                    limpiarBuffer();
                    if (valido != 1) printf("Entrada no válida. Ingrese solo números.\n");
                } while (valido != 1);

                do {
                    printf("¿Cuántos recursos necesita este producto?: ");
                    valido = scanf("%d", &productos[totalProductos].numRecursos);
                    limpiarBuffer();
                    if (valido != 1 || productos[totalProductos].numRecursos < 1 || productos[totalProductos].numRecursos > MAX_RECURSOS) {
                        printf("Número no válido. Debe ser entre 1 y %d.\n", MAX_RECURSOS);
                        valido = 0;
                    }
                } while (valido != 1);

                for (int j = 0; j < productos[totalProductos].numRecursos; j++) {
                    printf("Nombre del recurso %d: ", j + 1);
                    scanf("%s", productos[totalProductos].recursos[j].nombre);
                    do {
                        printf("Cantidad del recurso %d: ", j + 1);
                        valido = scanf("%d", &productos[totalProductos].recursos[j].cantidad);
                        limpiarBuffer();
                        if (valido != 1) printf("Entrada no válida. Ingrese solo números.\n");
                    } while (valido != 1);

                    if (recursoExiste(recursosTotales, totalRecursosUsados, productos[totalProductos].recursos[j].nombre) == -1) {
                        copiarTexto(recursosTotales[totalRecursosUsados].nombre, productos[totalProductos].recursos[j].nombre);
                        recursosTotales[totalRecursosUsados].cantidad = 0;
                        totalRecursosUsados++;
                    }
                }

                plantillas[totalPlantillas] = productos[totalProductos];
                totalPlantillas++;
            }

            totalProductos++;
        }

        else if (opcion == 2) {
            char nombreEditar[MAX_NOMBRE];
            printf("Ingrese el nombre del producto que desea editar: ");
            scanf("%s", nombreEditar);

            int encontrado = -1;
            for (int i = 0; i < totalProductos; i++) {
                if (compararNombres(productos[i].nombre, nombreEditar)) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {
                printf("Editando el producto %s\n", productos[encontrado].nombre);

                printf("Nuevo nombre: ");
                scanf("%s", productos[encontrado].nombre);

                printf("Nuevo tiempo de fabricación (días): ");
                scanf("%d", &productos[encontrado].tiempoFabricacionDias);

                printf("Nueva cantidad de tipos de recursos: ");
                scanf("%d", &productos[encontrado].numRecursos);

                for (int j = 0; j < productos[encontrado].numRecursos; j++) {
                    printf("Nombre del recurso %d: ", j + 1);
                    scanf("%s", productos[encontrado].recursos[j].nombre);
                    printf("Cantidad requerida: ");
                    scanf("%d", &productos[encontrado].recursos[j].cantidad);

                    if (recursoExiste(recursosTotales, totalRecursosUsados, productos[encontrado].recursos[j].nombre) == -1) {
                        copiarTexto(recursosTotales[totalRecursosUsados].nombre, productos[encontrado].recursos[j].nombre);
                        recursosTotales[totalRecursosUsados].cantidad = 0;
                        totalRecursosUsados++;
                    }
                }

                for (int k = 0; k < totalPlantillas; k++) {
                    if (compararNombres(plantillas[k].nombre, nombreEditar)) {
                        plantillas[k] = productos[encontrado];
                        break;
                    }
                }

                printf("Producto editado correctamente.\n");
            } else {
                printf("Producto no encontrado.\n");
            }
        }

        else if (opcion == 3) {
            char nombreEliminar[MAX_NOMBRE];
            printf("Ingrese el nombre del producto que desea eliminar: ");
            scanf("%s", nombreEliminar);
            int encontrado = -1;
            for (int i = 0; i < totalProductos; i++) {
                if (compararNombres(productos[i].nombre, nombreEliminar)) {
                    encontrado = i;
                    break;
                }
            }
            if (encontrado != -1) {
                for (int j = encontrado; j < totalProductos - 1; j++) {
                    productos[j] = productos[j + 1];
                }
                totalProductos--;
                printf("Producto eliminado exitosamente.\n");
            } else {
                printf("Producto no encontrado.\n");
            }
        }

        else if (opcion == 4) {
            if (totalProductos == 0) {
                printf("No hay productos registrados.\n");
            } else {
                mostrarResumen(productos, totalProductos);
            }
        }

        else if (opcion == 5) {
            if (totalProductos == 0) {
                printf("Primero debe ingresar productos.\n");
                continue;
            }
            printf("\nIngrese la cantidad disponible de cada recurso:\n");
            for (int i = 0; i < totalRecursosUsados; i++) {
                printf("%s: ", recursosTotales[i].nombre);
                scanf("%d", &recursosTotales[i].cantidad);
            }

            printf("\nCapacidad de producción:\n");
            for (int i = 0; i < totalProductos; i++) {
                int maxProducibles = 1000000;
                for (int j = 0; j < productos[i].numRecursos; j++) {
                    char* nombre = productos[i].recursos[j].nombre;
                    int requerido = productos[i].recursos[j].cantidad;
                    int disponible = 0;
                    int idx = recursoExiste(recursosTotales, totalRecursosUsados, nombre);
                    if (idx != -1) {
                        disponible = recursosTotales[idx].cantidad;
                    }
                    int posible = disponible / requerido;
                    if (posible < maxProducibles) {
                        maxProducibles = posible;
                    }
                }
                printf("%s: puede producirse %d veces\n", productos[i].nombre, maxProducibles);
            }
        }

        else if (opcion == 6) {
            printf("Saliendo del programa...\n");
        }

        else {
            printf("Opción inválida.\n");
        }

    } while (opcion != 6);

    return 0;
}