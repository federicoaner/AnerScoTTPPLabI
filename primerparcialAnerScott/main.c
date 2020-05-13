#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define TAMTIP 4
#define TAMCOLOR 5


#define CANTHARCODE 8

#include "dataWarehouse.h"
#include "validacion.h"


typedef struct
{
    int dia;
    int mes;
    int anio;
} eFecha;

typedef struct{

int id; //PK
char descripcion[20];

}eTipo;

typedef struct{

int id; //PK
char descripcion[20];

}eColor;

typedef struct
{
    int id;
    char marca[20];
    int idTipo;
    int idColor;
    int rodado;
    int isEmpty;

} eBicicleta;

typedef struct
{
   int id; //PK
    char descripcion[20];
    float precio;

} eServicio;

typedef struct
{
    int id;
    int idBicicleta;
    int idTipo;
    int idServicio;
    eFecha fechaIngreso;

    int isEmpty;
} eTrabajo;


int menu();
void inicializarBicicletas(eBicicleta vec[],int tam);
void mostrarBicicleta(eBicicleta x, eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor );
void mostrarBicicletas (eBicicleta vec[],int tam, eTipo tiposB[], int tamTip,eColor tiposC[],int tamColor);
int buscarLibre(eBicicleta vec[], int tam);
void hardcodearBicicletas(eBicicleta vec[],int cant);
int cargarDescripcionTipoBicicleta(char descripcion[],int id, eTipo tiposB[], int tam );
void mostrarTiposBicicleta( eTipo tiposB[], int tam);
int altaBicicleta(int id,eBicicleta vec[], int tam,eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor);
int cargarDescripcionColorBicicleta(char descripcion[],int id, eColor tiposC[], int tam );
void mostrarColorBicicleta( eColor tiposC[], int tam);
int buscarBicicleta(int id,eBicicleta vec[],int tam);
void bajaBicicleta(eBicicleta vec[],int tam, eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor);
void ordenarBicicletas(eBicicleta vec[],int tam,eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor);
void modificarBicicleta(eBicicleta vec[],int tam, eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor);


int main()
{



    char seguir='s';
    char confirma;
    int proximoId=1000;


    eBicicleta listaB[TAM];
    eTipo tiposB[TAMTIP]={ {1,"Rutera"},{2,"Carrera"},{3,"Mountain"},{4,"Bmx"} };
    eColor tiposC[TAMCOLOR]={{1,"Gris"},{2,"Negro"},{3,"Blanco"},{4,"Azul"},{5,"Rojo"} };
     inicializarBicicletas(listaB ,TAM);

     hardcodearBicicletas(listaB,CANTHARCODE);//hardcodeo
     proximoId+=CANTHARCODE;

    ordenarBicicletas(listaB,TAM,tiposB,TAMTIP,tiposC,TAMCOLOR);



     do
    {
        switch(menu())
        {

        case 'a':

            altaBicicleta(proximoId,listaB,TAM,tiposB,TAMTIP,tiposC,TAMCOLOR);

            break;

        case 'b':
            modificarBicicleta(listaB,TAM,tiposB,TAMTIP,tiposC,TAMCOLOR);
            break;

        case 'c':
            bajaBicicleta(listaB,TAM,tiposB,TAMTIP,tiposC,TAMCOLOR);
            break;

        case 'd':
            mostrarBicicletas(listaB,TAM,tiposB,TAMTIP,tiposC,TAMCOLOR);

            break;

        case 'e':
        //sumarEdades(lista,TAM);

            break;

        case 'f':
           // ordenarClientes(lista,TAM);
            break;

        case 'g':
        // ordenarClientes(lista,TAM);
            break;

         case 'h':
        // ordenarClientes(lista,TAM);
            break;

           case 'i':
        // ordenarClientes(lista,TAM);
            break;



        case 'j':
            printf("Confirma salida?: ");
            fflush(stdin);
            scanf("%c",&confirma);
            if(confirma =='s')
            {
                seguir='n';
            }

            break;

        }
        system("pause");

    }
    while(seguir=='s');


    return 0;
}

int menu()
{
    char opcion;
    system("cls");
    printf("*********GESTION DE BICICLETAS**********\n\n");
    printf("a. Alta Bicicleta\n");
    printf("b. Modificar Bicicleta\n");
    printf("c. Baja Bicicleta\n");
    printf("d. Listar Bicicletas\n");
    printf("e. Listar Tipos\n");
    printf("f. Listar colores\n");
    printf("g. Listar Servicios\n");
    printf("h. Alta Servicios\n");
    printf("i. Listar Trabajos\n\n");
    printf("j. Salir\n\n");

    printf("Indique opcion: ");
    fflush(stdin);
    scanf("%s",&opcion);

    return opcion;

}

void inicializarBicicletas(eBicicleta vec[],int tam)
{

    for(int i=0; i<tam; i++)
    {
     vec[i].isEmpty=1;
    }

}

void mostrarBicicleta(eBicicleta x, eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor )
{
    char nombreTipo[20];
    char nombreColor[20];
    cargarDescripcionTipoBicicleta(nombreTipo,x.idTipo,tiposB,tamTip);
    cargarDescripcionColorBicicleta(nombreColor,x.idColor,tiposC,tamColor);
    printf(" %d     %15s         %d       %10s     %10s\n",x.id,x.marca ,x.rodado,nombreTipo,nombreColor);

}

void mostrarBicicletas (eBicicleta vec[],int tam, eTipo tiposB[], int tamTip,eColor tiposC[],int tamColor)
{
    system("cls");
    int flag=0;

    printf("************listado de Bicicletas***************\n ");
    printf("id               marca           rodado          tipo         color\n\n");

    for(int i=0; i<tam; i++)
    {
        if(vec[i].isEmpty==0)
        {
            mostrarBicicleta(vec[i],tiposB,tamTip,tiposC,tamColor);
            flag=1;
        }
    }

    if(flag==0)
    {
        printf("*****No hay Bicicletas para mostrar******\n");
    }
}

int buscarLibre(eBicicleta vec[], int tam)
{

    int indice=-1;


    for(int i=0; i<tam; i++)
    {

        if (vec[i].isEmpty==1)
        {
            indice=i;
            break;
        }
    }

    return indice;
}


void hardcodearBicicletas(eBicicleta vec[],int cant){

    for(int i=0;i<cant;i++){

    vec[i].id=ids[i];
    strcpy(vec[i].marca,marcasBicicletas[i]);
    vec[i].rodado=rodados[i];
    vec[i].idTipo=idsTiposdeBicicleta[i];
    vec[i].idColor=idsColordeBicicleta[i];

    vec[i].isEmpty=0;
    }
}

int cargarDescripcionTipoBicicleta(char descripcion[],int id, eTipo tiposB[], int tam ){ //

    int todoOk=0;

    for (int i=0;i<tam;i++){
        if(tiposB[i].id==id){
        strcpy(descripcion, tiposB[i].descripcion);
        todoOk=1;
        }
    }

    return todoOk;
}

void mostrarTiposBicicleta( eTipo tiposB[], int tam)
{

    printf("************Tipos***************\n ");
    printf("Id   Descripcion    \n\n");

    for(int i=0; i<tam; i++)
    {
        printf("  %d    %10s\n",tiposB[i].id,tiposB[i].descripcion);
    }

}

int altaBicicleta(int id,eBicicleta vec[], int tam,eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor)

{

        int todoOk=0;

    int indice = buscarLibre(vec, tam);
    //int id;
    //int existe;
    eBicicleta auxBicicleta;

    system("cls");
    printf("*********ALTA Bicicleta**************\n\n");

    if(indice == -1) //hay lugar?
    {
        printf("Sistema completo\n\n");
    }

    else  //si hay lugar vengo aca
    {


            auxBicicleta.id=id;



            utn_getCadena(auxBicicleta.marca,51,2,"Ingrese el marca: ","\nError. Reingrese el nombre\n");



            utn_getEntero(&auxBicicleta.rodado,2,"Ingrese Rodado: ","\n error Reingrese el Rodado\n",16,30);

            mostrarTiposBicicleta(tiposB, tamTip);
            printf("\nIngrese  Tipo de Bicicleta: ");
            scanf("%d",&auxBicicleta.idTipo);

            mostrarColorBicicleta(tiposC, tamColor);
            printf("\nIngrese  Color de Bicicleta: ");
            scanf("%d",&auxBicicleta.idColor);




            auxBicicleta.isEmpty=0;


            vec[indice] =auxBicicleta; //copio al vector el empleado nuevo
            todoOk=1;
         //else interior

    } //else exterior
 return todoOk;
} //fin funcion


int cargarDescripcionColorBicicleta(char descripcion[],int id, eColor tiposC[], int tam ){

    int todoOk=0;

    for (int i=0;i<tam;i++){
        if(tiposC[i].id==id){
        strcpy(descripcion, tiposC[i].descripcion);
        todoOk=1;
        }
    }
    return todoOk;
}

    void mostrarColorBicicleta( eColor tiposC[], int tam)
{

    printf("************Tipos***************\n ");
    printf("Id   Descripcion    \n\n");

    for(int i=0; i<tam; i++)
    {
        printf("  %d    %10s\n",tiposC[i].id,tiposC[i].descripcion);
    }

}

int buscarBicicleta(int id,eBicicleta vec[],int tam)
{
    int indice=-1;

    for(int i=0; i<tam; i++)
    {

        if (vec[i].id == id && vec[i].isEmpty == 0)  //ve si en esa lista de empleados el id q le mande esta ocupado
        {
            indice=i;
            break; //se frena una vez q lo encontramos
        }
    }

    return indice;

}



void bajaBicicleta(eBicicleta vec[],int tam, eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor)
{

    int indice;
    int id;
    char confirma;

    system("cls");
    printf("*********BAJA BICICLETA**************\n\n");


    printf("ingrese id: ");
    scanf("%d", &id);

    indice=buscarBicicleta(id,vec,tam);


    if(indice==-1) // el id  ya esta?
    {
        printf("no hay registro de una bicicleta con ese id: %d\n",id);
    }
    else
    {
        mostrarBicicleta(vec[indice],tiposB,tamTip,tiposC,tamColor);
        printf("confirma baja?: ");
        fflush(stdin);
        scanf("%c",&confirma);

        if(confirma=='s')
        {
            vec[indice].isEmpty=1;
            printf("se ha realizado la baja con exito\n\n");
        }
        else
        {
            printf("se ha cancelado la operacion\n\n");
        }
    }//else exterior
}

void ordenarBicicletas(eBicicleta vec[],int tam,eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor)

{

    eBicicleta auxBicicleta;
    for (int i=0; i<tam-1; i++)
    {
        for (int j=i+1; j<tam; j++)
        {
            if(vec[i].idTipo>vec[j].idTipo) // ordenar x nombre
                // if(vec[i].id>vec[j].id) //  ordenar por id
            {
                auxBicicleta=vec[i];
                vec[i]=vec[j];
                vec[j]=auxBicicleta;
            }
            else if(vec[i].idTipo>vec[j].idTipo && vec[i].rodado <vec[j].rodado) // ordenar x nombre
            {
                auxBicicleta=vec[i];
                vec[i]=vec[j];
                vec[j]=auxBicicleta;
            }
        }//for interior
    }//for exterior

}

void modificarBicicleta(eBicicleta vec[],int tam, eTipo tiposB[],int tamTip,eColor tiposC[],int tamColor)
{

    int indice;
    int id;
    char confirma;
    int nuevoRodado;

    system("cls");
    printf("*********MODIFICAR Bicicleta**************\n\n");


    printf("ingrese id: ");
    scanf("%d", &id);

    indice=buscarBicicleta(id,vec,tam);


    if(indice==-1) // el id  ya esta?
    {
        printf("no hay registro de una Bicicleta con ese id: %d\n",id);
    }
    else
    {

        mostrarBicicleta(vec[indice], tiposB,tamTip,tiposC,tamColor);


        printf("modifica rodado?: ");
        fflush(stdin);
        scanf("%c",&confirma);

        if(confirma=='s')
        {
            printf("ingrese nuevo rodado: ");
            scanf("%d",&nuevoRodado);
            vec[indice].rodado=nuevoRodado;
            printf("se ha actualizado el rodado con exito\n\n");
        }
        else
        {
            printf("se ha cancelado la operacion\n\n");
        }
    }//else exterior

} //fin funcion



