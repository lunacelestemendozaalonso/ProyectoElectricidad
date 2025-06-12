#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <C:\Program Files\MySQL\MySQL Server 9.2\include\mysql.h>

MYSQL *con;

void finish_with_error() {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void conectar() {
    con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() falló\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "12345", "electricidad", 3306, NULL, 0) == NULL) {
        finish_with_error();
    }
}

// ======================= PRODUCTOR =======================

// Insertar productor
void insertarProductor() {
    char nombre[100];
    printf("Nombre del productor: ");
    scanf(" %[^\n]", nombre);
    
    for (int i = 0; nombre[i]; i++) {
    if ((unsigned char)nombre[i] == 0xA0) {
        nombre[i] = ' ';
    }
    }


    char query[256];
    snprintf(query, sizeof(query),
        "INSERT INTO productor (nombre) VALUES ('%s')",
        nombre);

    if (mysql_query(con, query)) finish_with_error();
    printf("Productor insertado con éxito.\n");
}

// Consultar productores
void consultarProductores() {
    if (mysql_query(con, "SELECT * FROM productor")) finish_with_error();
    MYSQL_RES *res = mysql_store_result(con);
    MYSQL_ROW row;

    printf("\n%-5s %-30s\n", "ID", "Nombre");
    printf("--------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%-5s %-30s\n", row[0], row[1]);
    }
    mysql_free_result(res);
}

// Modificar productor (solo nombre)
void modificarProductor() {
    int id;
    char nombre[100];
    printf("ID del productor a modificar: ");
    scanf("%d", &id);
    getchar();
    printf("Nuevo nombre: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    char query[256];
    snprintf(query, sizeof(query),
        "UPDATE productor SET nombre = '%s' WHERE id_productor = %d",
        nombre, id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Productor actualizado.\n");
}

// Eliminar productor
void eliminarProductor() {
    int id;
    printf("ID del productor a eliminar: ");
    scanf("%d", &id);

    char query[128];
    snprintf(query, sizeof(query),
        "DELETE FROM productor WHERE id_productor = %d",
        id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Productor eliminado.\n");
}

// ======================= NUCLEAR =======================

// Insertar planta nuclear
void insertarNuclear() {
    char nombre[100];
    int potencia;
    printf("Nombre de la planta nuclear: ");
    scanf(" %[^\n]", nombre);
    printf("Potencia (MW): ");
    scanf("%d", &potencia);

    char query[256];
    snprintf(query, sizeof(query),
        "INSERT INTO nuclear (nombre, potencia) VALUES ('%s', %d)",
        nombre, potencia);

    if (mysql_query(con, query)) finish_with_error();
    printf("Planta nuclear insertada.\n");
}

// Consultar plantas nucleares
void consultarNucleares() {
    if (mysql_query(con, "SELECT * FROM nuclear")) finish_with_error();
    MYSQL_RES *res = mysql_store_result(con);
    MYSQL_ROW row;

    printf("\n%-5s %-30s %-10s\n", "ID", "Nombre", "Potencia");
    printf("----------------------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%-5s %-30s %-10s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(res);
}

// Modificar planta nuclear (solo potencia)
void modificarNuclear() {
    int id, potencia;
    printf("ID de la planta a modificar: ");
    scanf("%d", &id);
    printf("Nueva potencia (MW): ");
    scanf("%d", &potencia);

    char query[256];
    snprintf(query, sizeof(query),
        "UPDATE nuclear SET potencia = %d WHERE id_nuclear = %d",
        potencia, id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Potencia actualizada.\n");
}

// Eliminar planta nuclear
void eliminarNuclear() {
    int id;
    printf("ID de la planta a eliminar: ");
    scanf("%d", &id);

    char query[128];
    snprintf(query, sizeof(query),
        "DELETE FROM nuclear WHERE id_nuclear = %d",
        id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Planta nuclear eliminada.\n");
}

// ======================= SUMINISTRADOR =======================

// Insertar suministrador
void insertarSuministrador() {
    char nombre[100], contacto[50];
    printf("Nombre del suministrador: ");
    scanf(" %[^\n]", nombre);
    printf("Contacto (teléfono/email): ");
    scanf(" %[^\n]", contacto);

    char query[256];
    snprintf(query, sizeof(query),
        "INSERT INTO suministrador (nombre, contacto) VALUES ('%s', '%s')",
        nombre, contacto);

    if (mysql_query(con, query)) finish_with_error();
    printf("Suministrador insertado.\n");
}

// Consultar suministradores
void consultarSuministradores() {
    if (mysql_query(con, "SELECT * FROM suministrador")) finish_with_error();
    MYSQL_RES *res = mysql_store_result(con);
    MYSQL_ROW row;

    printf("\n%-5s %-30s %-20s\n", "ID", "Nombre", "Contacto");
    printf("------------------------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%-5s %-30s %-20s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(res);
}

// Modificar suministrador
void modificarSuministrador() {
    int id;
    char contacto[50];
    printf("ID del suministrador a modificar: ");
    scanf("%d", &id);
    getchar();
    printf("Nuevo contacto: ");
    fgets(contacto, sizeof(contacto), stdin);
    contacto[strcspn(contacto, "\n")] = 0;

    char query[256];
    snprintf(query, sizeof(query),
        "UPDATE suministrador SET contacto = '%s' WHERE id_suministrador = %d",
        contacto, id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Contacto actualizado.\n");
}

// Eliminar suministrador
void eliminarSuministrador() {
    int id;
    printf("ID del suministrador a eliminar: ");
    scanf("%d", &id);

    char query[128];
    snprintf(query, sizeof(query),
        "DELETE FROM suministrador WHERE id_suministrador = %d",
        id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Suministrador eliminado.\n");
}

// ======================= TRANSPORTISTA =======================

// Insertar transportista
void insertarTransportista() {
    char nombre[100], vehiculo[50];
    printf("Nombre del transportista: ");
    scanf(" %[^\n]", nombre);
    printf("Tipo de vehículo: ");
    scanf(" %[^\n]", vehiculo);

    char query[256];
    snprintf(query, sizeof(query),
        "INSERT INTO transportista (nombre, vehiculo) VALUES ('%s', '%s')",
        nombre, vehiculo);

    if (mysql_query(con, query)) finish_with_error();
    printf("Transportista insertado.\n");
}

// Consultar transportistas
void consultarTransportistas() {
    if (mysql_query(con, "SELECT * FROM transportista")) finish_with_error();
    MYSQL_RES *res = mysql_store_result(con);
    MYSQL_ROW row;

    printf("\n%-5s %-30s %-20s\n", "ID", "Nombre", "Vehículo");
    printf("------------------------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%-5s %-30s %-20s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(res);
}

// Modificar transportista
void modificarTransportista() {
    int id;
    char vehiculo[50];
    printf("ID del transportista a modificar: ");
    scanf("%d", &id);
    getchar();
    printf("Nuevo vehículo: ");
    fgets(vehiculo, sizeof(vehiculo), stdin);
    vehiculo[strcspn(vehiculo, "\n")] = 0;

    char query[256];
    snprintf(query, sizeof(query),
        "UPDATE transportista SET vehiculo = '%s' WHERE id_transportista = %d",
        vehiculo, id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Vehículo actualizado.\n");
}

// Eliminar transportista
void eliminarTransportista() {
    int id;
    printf("ID del transportista a eliminar: ");
    scanf("%d", &id);

    char query[128];
    snprintf(query, sizeof(query),
        "DELETE FROM transportista WHERE id_transportista = %d",
        id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Transportista eliminado.\n");
}

// ======================= COMPRA (relaciones) =======================

// Insertar compra
void insertarCompra() {
    int id_n, id_s, id_t;
    char fecha[12];
    float cantidad;

    printf("ID Nuclear: ");
    scanf("%d", &id_n);
    printf("ID Suministrador: ");
    scanf("%d", &id_s);
    printf("ID Transportista: ");
    scanf("%d", &id_t);
    printf("Fecha (YYYY-MM-DD): ");
    scanf(" %11s", fecha);
    printf("Cantidad (MW): ");
    scanf("%f", &cantidad);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO compra (id_nuclear, id_suministrador, id_transportista, fecha, cantidad) "
        "VALUES (%d, %d, %d, '%s', %.2f)",
        id_n, id_s, id_t, fecha, cantidad);

    if (mysql_query(con, query)) finish_with_error();
    printf("Compra registrada.\n");
}

// Consultar compras
void consultarCompras() {
    const char *q =
      "SELECT c.id_compra, n.nombre, s.nombre, t.nombre, c.fecha, c.cantidad "
      "FROM compra c "
      "JOIN nuclear n ON c.id_nuclear = n.id_nuclear "
      "JOIN suministrador s ON c.id_suministrador = s.id_suministrador "
      "JOIN transportista t ON c.id_transportista = t.id_transportista";
    if (mysql_query(con, q)) finish_with_error();
    MYSQL_RES *res = mysql_store_result(con);
    MYSQL_ROW row;

    printf("\n%-5s %-20s %-20s %-20s %-12s %-10s\n",
           "ID", "Nuclear", "Suministrador", "Transportista", "Fecha", "Cantidad");
    printf("--------------------------------------------------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%-5s %-20s %-20s %-20s %-12s %-10s\n",
               row[0], row[1], row[2], row[3], row[4], row[5]);
    }
    mysql_free_result(res);
}

// Modificar compra (cantidad y/o fecha)
void modificarCompra() {
    int id;
    char fecha[12];
    float cantidad;
    printf("ID de la compra a modificar: ");
    scanf("%d", &id);
    printf("Nueva fecha (YYYY-MM-DD): ");
    scanf(" %11s", fecha);
    printf("Nueva cantidad (MW): ");
    scanf("%f", &cantidad);

    char query[256];
    snprintf(query, sizeof(query),
        "UPDATE compra SET fecha = '%s', cantidad = %.2f WHERE id_compra = %d",
        fecha, cantidad, id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Compra actualizada.\n");
}

// Eliminar compra
void eliminarCompra() {
    int id;
    printf("ID de la compra a eliminar: ");
    scanf("%d", &id);

    char query[128];
    snprintf(query, sizeof(query),
        "DELETE FROM compra WHERE id_compra = %d",
        id);

    if (mysql_query(con, query)) finish_with_error();
    printf("Compra eliminada.\n");
}
// ======================= MENÚ  =======================
void menuProductor() {
    int o;
    do {
        printf("\n--- PRODUCTORES ---\n");
        printf("1. Insertar\n2. Consultar\n3. Modificar\n4. Eliminar\n0. Volver al menú principal\n");
        printf("Opción: "); scanf("%d", &o);
        switch (o) {
            case 1: insertarProductor(); break;
            case 2: consultarProductores(); break;
            case 3: modificarProductor(); break;
            case 4: eliminarProductor(); break;
            case 0: break;
            default: printf("Opción inválida.\n");
        }
    } while (o != 0);
}

// Menú Nuclear
void menuNuclear() {
    int o;
    do {
        printf("\n--- NUCLEARES ---\n");
        printf("1. Insertar\n2. Consultar\n3. Modificar\n4. Eliminar\n0. Volver al menú principal\n");
        printf("Opción: "); scanf("%d", &o);
        switch (o) {
            case 1: insertarNuclear(); break;
            case 2: consultarNucleares(); break;
            case 3: modificarNuclear(); break;
            case 4: eliminarNuclear(); break;
            case 0: break;
            default: printf("Opción inválida.\n");
        }
    } while (o != 0);
}

// Menú Suministrador
void menuSuministrador() {
    int o;
    do {
        printf("\n--- SUMINISTRADORES ---\n");
        printf("1. Insertar\n2. Consultar\n3. Modificar\n4. Eliminar\n0. Volver al menú principal\n");
        printf("Opción: "); scanf("%d", &o);
        switch (o) {
            case 1: insertarSuministrador(); break;
            case 2: consultarSuministradores(); break;
            case 3: modificarSuministrador(); break;
            case 4: eliminarSuministrador(); break;
            case 0: break;
            default: printf("Opción inválida.\n");
        }
    } while (o != 0);
}

// Menú Transportista
void menuTransportista() {
    int o;
    do {
        printf("\n--- TRANSPORTISTAS ---\n");
        printf("1. Insertar\n2. Consultar\n3. Modificar\n4. Eliminar\n0. Volver al menú principal\n");
        printf("Opción: "); scanf("%d", &o);
        switch (o) {
            case 1: insertarTransportista(); break;
            case 2: consultarTransportistas(); break;
            case 3: modificarTransportista(); break;
            case 4: eliminarTransportista(); break;
            case 0: break;
            default: printf("Opción inválida.\n");
        }
    } while (o != 0);
}

// Menú Compra
void menuCompra() {
    int o;
    do {
        printf("\n--- COMPRAS ---\n");
        printf("1. Insertar\n2. Consultar\n3. Modificar\n4. Eliminar\n0. Volver al menú principal\n");
        printf("Opción: "); scanf("%d", &o);
        switch (o) {
            case 1: insertarCompra(); break;
            case 2: consultarCompras(); break;
            case 3: modificarCompra(); break;
            case 4: eliminarCompra(); break;
            case 0: break;
            default: printf("Opción inválida.\n");
        }
    } while (o != 0);
}

// Menú Principal
void menuPrincipal() {
    int opc;
    do {
        printf("\n=== SISTEMA ELECTRICIDAD ===\n");
        printf("1. Productor\n2. Nuclear\n3. Suministrador\n4. Transportista\n5. Compra\n0. Salir\n");
        printf("Opción: "); scanf("%d", &opc);
        switch (opc) {
            case 1: menuProductor(); break;
            case 2: menuNuclear(); break;
            case 3: menuSuministrador(); break;
            case 4: menuTransportista(); break;
            case 5: menuCompra(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opción inválida.\n");
        }
    } while (opc != 0);
}

int main() {
    conectar();
    int opcion;

    do {
        printf("\n--- SISTEMA DE ENERGÍA ELÉCTRICA ---\n");
        printf("                      \n");
        printf("1. Productor\n");
        printf("2. Nuclear\n");
        printf("3. Suministrador\n");
        printf("4. Transportista\n");
        printf("5. Compra\n");
        printf("0. Salir\n");
        printf("                     \n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer de entrada
        switch (opcion) {
        case 1: menuProductor(); break;
        case 2: menuNuclear(); break;
        case 3: menuSuministrador(); break;
        case 4: menuTransportista(); break;
        case 5: menuCompra(); break;
        case 0: printf("Saliendo...\n");
        break;
        default: printf("Opción inválida.\n");
     }

    } while (opcion != 0);

    mysql_close(con);
    return 0;
}