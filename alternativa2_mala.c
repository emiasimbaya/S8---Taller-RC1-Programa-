#include <stdio.h>

#define MAX_PRODUCTOS 5
#define MAX_NOMBRE 50

char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
int tiempos[MAX_PRODUCTOS];
int recursos[MAX_PRODUCTOS];
int cantidades[MAX_PRODUCTOS];
int totalProductos = 0;

// Comparar si dos cadenas son iguales
int esIgual(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') {
        return 1;
    }
    return 0;
}

// Copiar contenido de una cadena a otra
void copiarTexto(char destino[], char origen[]) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

// Ingreso de productos
void ingresarProductos() {
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        printf("\nIngrese nombre del producto %d: ", i + 1);
        scanf("%s", nombres[i]);
        printf("Ingrese tiempo de fabricación (min): ");
        scanf("%d", &tiempos[i]);
        printf("Ingrese recursos necesarios por unidad: ");
        scanf("%d", &recursos[i]);
        printf("Ingrese cantidad demandada: ");
        scanf("%d", &cantidades[i]);
        totalProductos++;
    }
}

// Mostrar productos
void mostrarProductos() {
    printf("\n--- Lista de Productos ---\n");
    for (int i = 0; i < totalProductos; i++) {
        printf("%d. %s - Tiempo: %d - Recursos: %d - Cantidad: %d\n",
               i + 1, nombres[i], tiempos[i], recursos[i], cantidades[i]);
    }
}

// Editar producto
void editarProducto() {
    char nombreBusqueda[MAX_NOMBRE];
    int encontrado = 0;

    printf("Ingrese el nombre del producto a editar: ");
    scanf("%s", nombreBusqueda);

    for (int i = 0; i < totalProductos; i++) {
        if (esIgual(nombres[i], nombreBusqueda)) {
            printf("Nuevo nombre: ");
            scanf("%s", nombres[i]);
            printf("Nuevo tiempo de fabricación: ");
            scanf("%d", &tiempos[i]);
            printf("Nuevos recursos por unidad: ");
            scanf("%d", &recursos[i]);
            printf("Nueva cantidad demandada: ");
            scanf("%d", &cantidades[i]);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}

// Eliminar producto
void eliminarProducto() {
    char nombreBusqueda[MAX_NOMBRE];
    int encontrado = 0;

    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombreBusqueda);

    for (int i = 0; i < totalProductos; i++) {
        if (esIgual(nombres[i], nombreBusqueda)) {
            for (int j = i; j < totalProductos - 1; j++) {
                copiarTexto(nombres[j], nombres[j + 1]);
                tiempos[j] = tiempos[j + 1];
                recursos[j] = recursos[j + 1];
                cantidades[j] = cantidades[j + 1];
            }
            totalProductos--;
            encontrado = 1;
            printf("Producto eliminado.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}

// Calcular tiempo y recursos totales
void calcularTotales() {
    int totalTiempo = 0;
    int totalRecursos = 0;

    for (int i = 0; i < totalProductos; i++) {
        totalTiempo += tiempos[i] * cantidades[i];
        totalRecursos += recursos[i] * cantidades[i];
    }

    printf("\nTiempo total requerido: %d minutos\n", totalTiempo);
    printf("Recursos totales necesarios: %d unidades\n", totalRecursos);
}

// Validar si se puede cumplir la demanda
void validarCapacidad() {
    int tiempoDisp, recursosDisp;
    int totalTiempo = 0, totalRecursos = 0;

    printf("Ingrese tiempo disponible: ");
    scanf("%d", &tiempoDisp);
    printf("Ingrese recursos disponibles: ");
    scanf("%d", &recursosDisp);

    for (int i = 0; i < totalProductos; i++) {
        totalTiempo += tiempos[i] * cantidades[i];
        totalRecursos += recursos[i] * cantidades[i];
    }

    if (totalTiempo <= tiempoDisp && totalRecursos <= recursosDisp) {
        printf("La fábrica PUEDE cumplir con la demanda.\n");
    } else {
        printf("La fábrica NO PUEDE cumplir con la demanda.\n");
    }
}

// Menú principal
int main() {
    int opcion;

    ingresarProductos();

    do {
        printf("\n--- Menú ---\n");
        printf("1. Mostrar productos\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Calcular tiempo y recursos\n");
        printf("5. Validar capacidad de producción\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            mostrarProductos();
        } else if (opcion == 2) {
            editarProducto();
        } else if (opcion == 3) {
            eliminarProducto();
        } else if (opcion == 4) {
            calcularTotales();
        } else if (opcion == 5) {
            validarCapacidad();
        } else if (opcion == 0) {
            printf("Saliendo del programa.\n");
        } else {
            printf("Opción inválida.\n");
        }
    } while (opcion != 0);

    return 0;
}