#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

char servicio[3][10]={"50Mb","100Mb","300Mb"};
struct TVenta{
    int servicioID; //numerado con ciclo iterativo
    char *servCntrtd;//algun valor del arreglo servicio
    float precio; //2000 - 5000
    bool bonfccion; //40% de descuento si es true, false sin descuento
};
typedef struct TVenta TVnt;
struct Nodo
{
    TVnt *Venta;
    struct Nodo *Siguiente;
};
typedef struct Nodo Tnd;

TVnt * CreateSale(int iD);
Tnd * CreateNode(TVnt * venta);
void InsertNode(Tnd **start, TVnt * venta);
int GetWithBonus50(Tnd * list);
int GetNoBonus100(Tnd * list);
float MakeDiscount(TVnt * vent);
float GetWithBonus(Tnd * list);
float GetNoBonus(Tnd * list);
int GetAverage(Tnd * list, int cantVent);
void ShowSale (TVnt * vent);
void ShowSales(Tnd * list, int cantMostrar);
void FreeList(Tnd * list);

int main(){
    srand((int)time(NULL));
    //rand() % (100 - 10 + 1) + 10;
    int Nventas = rand() % (100 - 50 + 1) + 50;

    Tnd * Ventas = NULL;
    for (int i = 0; i < Nventas; i++){
        InsertNode(&Ventas,CreateSale(i));
    }
    printf("cantidad de servicios: %d\n", Nventas);
    printf("1) Cantidad de servicios con bonfcación y de 50Mb: %d\n", GetWithBonus50(Ventas));
    printf("2) Cantidad de servicios sin bonfcación y de 100Mb: %d\n", GetNoBonus100(Ventas));
    printf("3) Monto total de la venta con bonfcación: $%2.lf\n",GetWithBonus(Ventas));
    printf("4) Monto total de la venta sin bonfcación: $%2.lf\n", GetNoBonus(Ventas));
    printf("5) Promedio de venta Totales: %d\n", GetAverage(Ventas,Nventas));
    printf("Ingrese la cantidad de ventas que desea ver\n0 para ver todas\n");
    int cantAMostrar = 0;
    scanf("%d",&cantAMostrar);
    fflush(stdin);
    getchar();
    ShowSales(Ventas,cantAMostrar);
    FreeList(Ventas);
    return 0;
}

TVnt * CreateSale(int iD){
    //reserva de memoria, char/struct TVnt
    TVnt * Venta = (TVnt *) malloc(sizeof(TVnt));
    char *buff = (char *) malloc(20 * sizeof(char));

    Venta->servicioID = iD+1;

    //tipo de servicio
    strcpy(buff,servicio[rand()%3]);
    Venta->servCntrtd = (char *) malloc(sizeof(char) * (strlen(buff)+1));
    strcpy(Venta->servCntrtd,buff);
    free(buff);

    Venta->precio = rand() % (5000 - 2000 + 1) + 2000;
    Venta->bonfccion = rand()%2;
    
    return Venta;
}

Tnd * CreateNode(TVnt * venta){
    Tnd * nuevo = (Tnd *) malloc(sizeof(Tnd));
    nuevo->Venta = venta;
    nuevo->Siguiente = NULL;

    return nuevo;
}

void InsertNode(Tnd **start, TVnt * venta){
    Tnd * nuevo = CreateNode(venta);
    if(*start != NULL){
        nuevo->Siguiente = *start;
    }else{
        nuevo->Siguiente = NULL;
    }
    *start = nuevo;
}

int GetWithBonus50(Tnd * list){
    int counter = 0;
    while(list != NULL){
        if(list->Venta->bonfccion && strcmp(list->Venta->servCntrtd,servicio[0])){
            counter++;
        }
        list = list->Siguiente;
    }
    return counter;
}
int GetNoBonus100(Tnd * list){
    int counter = 0;
    while(list != NULL){
        if(!(list->Venta->bonfccion) && strcmp(list->Venta->servCntrtd,servicio[1])){
            counter++;
        }
        list = list->Siguiente;
    }
    return counter;
}
float MakeDiscount(TVnt * vent){
    float precioFinal = 0;
    if(vent->bonfccion){
        float descuento = (float)(vent->precio * 40/100);
        precioFinal = vent->precio - descuento;
    }else{
        precioFinal = vent->precio;
    }
    return precioFinal;
}
float GetWithBonus(Tnd * list){
    float total = 0;
    while (list != NULL)
    {
        float precio = MakeDiscount(list->Venta);
        total += precio;
        list = list->Siguiente;
    }
    return total;
}
float GetNoBonus(Tnd * list){
    float total = 0;
    while (list != NULL)
    {
        if(!(list->Venta->bonfccion)){
            total += list->Venta->precio;
        }
        list = list->Siguiente;
    }
    return total;
}
int GetAverage(Tnd * list, int cantVent){
    float withBonus = GetWithBonus(list);
    float noBonus = GetNoBonus(list);
    int promedio = (int)((withBonus+noBonus)/cantVent);
    return promedio;
}
void ShowSale (TVnt * vent){
    printf("ID %d\n", vent->servicioID);
    printf("Servicio contratado: %s\n", vent->servCntrtd);
    printf("Precio : %2.lf\n", MakeDiscount(vent));
    if(vent->bonfccion){
        printf("Bonificación: Si");
    }else{
        printf("Bonificación: NO");
    }
}

void ShowSales(Tnd * list, int cantMostrar){
    int i = 0;
    if(cantMostrar > 0){
        while(list != NULL && i < cantMostrar){
            ShowSale(list->Venta);
            printf("\n\n");
            i++;
            list = list->Siguiente;
        }
    }
    if(cantMostrar == 0){
        while(list != NULL){
            ShowSale(list->Venta);
            printf("\n\n");
            list = list->Siguiente;
        }
    }
}
void FreeList(Tnd * list){
    Tnd * aux;
    while(list != NULL){
        aux = list;
        free(list->Venta->servCntrtd);
        list = list->Siguiente;
        free(aux);
    }
}