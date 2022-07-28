#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

char Servicio[3][10]={"50Mb","100Mb","300Mb"};
struct Tventa{
    int servicioID; //numerado en ciclo iterativo
    char * srvContrtdo; //Algun valor del arreglo
    float precio; //entre 2000 - 5000
    bool bonus; //40% de descuento si es true
    int empresa; // 1 - Telecom, 2 - Claro, 3 - Movistar
};
typedef struct Tventa Tvnt;

struct Nodo{
    Tvnt * Venta;
    struct Nodo * Next;
};
typedef struct Nodo nodo;
//Funciones
char * ReserveWord(int cantResev);
char * CopyWord();
Tvnt * BookStructure();
Tvnt * CreateSale(int iD);
nodo * CreateNodo(Tvnt * Venta);
void InsertNode(nodo ** start, Tvnt * venta);
bool GetTelecom(Tvnt * vent);
bool Get50Mb(Tvnt * vent);
bool Get100Mb(Tvnt * vent);
int GetWithBonus50(nodo * nod);
int GetWithBonus100(nodo * nod);
float GetNoBonusPrice(nodo * nod);
float MakeDiscount (Tvnt * vent);
float GetWithBonus(nodo * nod);
int GetAverage(nodo * nod, int totServ);
void ShowDataTelecom(nodo * nod, int totServ);
void Showsale(Tvnt * vent);
int GetAllTelecom(nodo * nod);
int GetWithBonusTel(nodo * nod);
int GetNoBonusTel(nodo * nod);
void ShowAllDataTel(nodo * nod, int cant, int op);
//main
int main(){
    srand(time(NULL));
    int totServ = rand() % (100 - 50 + 1) + 50;
    nodo * Ventas = NULL;
    for(int i = 0; i < totServ; i++){
        InsertNode(&Ventas, CreateSale(i));
    }
    ShowDataTelecom(Ventas,totServ);
    int cant = 0;
    int op = 0;
    do{
        do{
            printf("\nCuantas ventas quieres ver?: ");
            scanf("%d",&cant);
            fflush(stdin);
            getchar();
            if(!(cant < GetAllTelecom(Ventas))){
                printf("Ingrese valores validos\n");
            }
        }while(!(cant < GetAllTelecom(Ventas)));

        do{
            printf("\n1) Con Beneficios\n2) Sin Beneficios\n");
            scanf("%d",&op);
            fflush(stdin);
            getchar();
            if(!(op == 1 || op == 2)){
                printf("Ingrese valores validos\n");
            }
        }while(!(op == 1 || op == 2));
        ShowAllDataTel(Ventas, cant, op);
    }while((op == 1 || op == 2 || (cant < GetAllTelecom(Ventas))));
    return 0;
}

char * ReserveWord(int cantResev){
    char * word = (char *) malloc(sizeof(char) * cantResev);
    return word;
}
char * CopyWord(){
    char * buff = ReserveWord(20);
    strcpy(buff, Servicio[rand()%3]);
    return buff;
}
Tvnt * BookStructure(){
    Tvnt * vent = (Tvnt *) malloc(sizeof(Tvnt));
    return vent;
}
Tvnt * CreateSale(int iD){
    Tvnt * Venta = BookStructure();
    Venta->servicioID = iD+1;
    char * buff = CopyWord();
    Venta->srvContrtdo = ReserveWord(strlen(buff)+1);
    strcpy(Venta->srvContrtdo, buff);
    Venta->precio = rand() % (5000 - 2000 + 1) + 2000;
    Venta->bonus = rand()%2;
    Venta->empresa = rand() % (3 - 1 + 1) + 1;

    return Venta;
}
nodo * CreateNodo(Tvnt * Venta){
    nodo * nNodo = (nodo *) malloc(sizeof(nodo));
    nNodo->Venta = Venta;
    nNodo->Next = NULL;
    return nNodo;
}
void InsertNode(nodo ** start, Tvnt * venta){
    nodo * nNodo = CreateNodo(venta);
    if(*start != NULL){
        nNodo->Next = *start;
    }else{
        nNodo->Next = NULL;
    }
    *start = nNodo;
}
bool GetTelecom(Tvnt * vent){
    if(vent->empresa == 1){
        return true;
    }
    return false;
}
bool Get50Mb(Tvnt * vent){
    if(strcmp(vent->srvContrtdo,Servicio[0])){
        return true;
    }
    return false;
}
bool Get100Mb(Tvnt * vent){
    if(strcmp(vent->srvContrtdo,Servicio[1])){
        return true;
    }
    return false;
}
int GetWithBonus50(nodo * nod){
    int counter = 0;
    while(nod != NULL){
        if(GetTelecom(nod->Venta) && Get50Mb(nod->Venta) && (nod->Venta->bonus)){
            counter++;
        }
        nod = nod->Next;
    }
    return counter;
}
int GetWithBonus100(nodo * nod){
    int counter = 0;
    while(nod != NULL){
        if(GetTelecom(nod->Venta) && Get100Mb(nod->Venta) && !(nod->Venta->bonus)){
            counter++;
        }
        nod = nod->Next;
    }
    return counter;
}
float GetNoBonusPrice(nodo * nod){
    float total = 0;
    while(nod != NULL){
        if(GetTelecom(nod->Venta) && !(nod->Venta->bonus)){
            total += nod->Venta->precio;
        }
        nod = nod->Next;
    }
    return total;
}
float MakeDiscount (Tvnt * vent){
    float discount = 0;
    if(vent->bonus){
        discount = (float)(vent->precio - ((vent->precio * 40) / 100));
    }else{
        discount = vent->precio;
    }
    return discount;
}
float GetWithBonus(nodo * nod){
    float total = 0;
    while(nod != NULL){
        if(GetTelecom(nod->Venta)){
            total += MakeDiscount(nod->Venta);
        }
        nod = nod->Next;
    }
    return total;
}
int GetAverage(nodo * nod, int totServ){
    int average =(int) ((GetWithBonus(nod) + GetNoBonusPrice(nod)) / totServ);
    return average;
}
void Showsale(Tvnt * vent){
    printf("\nID %d\n", vent->servicioID);
    printf("Servicio contratado: %s\n", vent->srvContrtdo);
    printf("Precio: $%2.lf\n", MakeDiscount(vent));
    if(vent->bonus){
        printf("Bonificación: SI\n");
    }else{
        printf("Bonificación: NO\n");
    }
    if(vent->empresa == 1){
        printf("Empresa: Telecom\n");
    }
    if(vent->empresa == 2){
        printf("Empresa: Claro\n");
    }
    if(vent->empresa == 3){
        printf("Empresa: Movistar\n");
    }
    printf("\n");
}
int GetAllTelecom(nodo * nod){
    int cantTel = 0;
    while (nod != NULL)
    {
        if(GetTelecom(nod->Venta)){
            cantTel++;
        }
        nod = nod->Next;
    }
    return cantTel;
}
int GetWithBonusTel(nodo * nod){
    int cantBonus = 0;
    while (nod != NULL)
    {
        if(GetTelecom(nod->Venta) && nod->Venta->bonus){
            cantBonus++;
        }
        nod = nod->Next;
    }
    return cantBonus;
}
int GetNoBonusTel(nodo * nod){
    int cantNoBonus = 0;
    while (nod != NULL)
    {
        if(GetTelecom(nod->Venta) && !(nod->Venta->bonus)){
            cantNoBonus++;
        }
        nod = nod->Next;
    }
    return cantNoBonus;
}
void ShowDataTelecom(nodo * nod, int totServ){
    printf("Datos de Telecom\n");
    printf("Cantidad de ventas de Telecom: %d\n", GetAllTelecom(nod));
    printf("Cantidad con Beneficios: %d\n", GetWithBonusTel(nod));
    printf("Cantidad sin Beneficios: %d\n", GetNoBonusTel(nod));
    printf("Servicios con Bonificación y de 50Mb: %d\n",GetWithBonus50(nod));
    printf("Servicios sin Bonificación y de 100Mb: %d\n",GetWithBonus100(nod));
    printf("Monto total sin bonificación: %2.lf\n",GetNoBonusPrice(nod));
    printf("Monto total con bonificación: %2.lf\n",GetWithBonus(nod));
    printf("Promedio total de ventas: %d\n", GetAverage(nod,totServ));
}
void ShowAllDataTel(nodo * nod, int cant, int op){
    int i = 0;
    if(op == 1){
        while(nod != NULL && i < cant){
            if(GetTelecom(nod->Venta) && nod->Venta->bonus){
                Showsale(nod->Venta);
                i++;
            }
            nod = nod->Next;
        }
    }
    if(op == 2){
        while(nod != NULL && i < cant){
            if(GetTelecom(nod->Venta) && !(nod->Venta->bonus)){
                Showsale(nod->Venta);
                i++;
            }
            nod = nod->Next;
        }
    }
}