/*JJGoFo
*Programa de encriptado por terminal o archivo de texto; El mensaje se guarda en "Mensaje Encriptado.txt";
*El encriptado por terminal se realiza en el programa;
*Encriptado por archivo se lee desde el archivo "Mensaje Por Encriptar.txt";
*En caso de no existir "Mensaje Por Encriptar.txt" debera crearse manualmente,
 de lo contrario devolvera error pues no hay nada que encriptar
*Todos los archivos se generan en la misma ruta del ejecutable


NOTA:AL USAR getche() Y MEMORIA DINAMICA PARA LA OBTENCION DE CADENAS DE TAMAÑO INDEFINIDO SEGUN LA ENTRADA
DEL USUARIO ES POSIBLE QUE FUNCIONES COMO BORRAR EN LA TERMINAL O EL REUSAR EL PROGRAMA EN UNA MISMA EJECUCION
PUEDA FALLAR, ESTO SEGUNDO NO ES TAN COMUN, DE CUALQUIER FORMA EL PROGRAMA SIGUE FUNCIONANDO PARA 
ENCRIPTAR/DESENCRIPTAR AUN SI EL PROGRAMA SE CIERRA Y VUELVE A ABRIR 
*/

//antes de leer este codigo, recuerden que todas las cadenas tienen en su ultimo bloque '\0' que es un 
//terminador de linea, no traten de modificar ese ultimo bloque pq el programa se rompe
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define enter 13
void encriptar();
void desencriptar();
void encriptarArchivo();
long int Bin_Dec(char Bin[]);
int Dec_Bin(int num);
int Dec_Aleatorio( );

int main( )
{
    //Todo el main solo es para implementar las funciones en un menu
    system("color 8e"); //Definimos el color de la terminal
    char opcion;
    do{
    system("cls");
    printf("\tPROGRAMA DE ENCRIPCION/DESENCRIPCION\n");
    printf("Ingrese la opcion a realizar\n\t1)Encriptar\n\t2)Desencriptar\n\t3)Encriptar por archivo\n\t4)Salir\n");
    fflush(stdin);
    scanf(" %c",&opcion);
    switch (opcion)
    {
    case '1':
        system("cls");
        encriptar( );
        printf("\n");
        system("pause");
        break;
    case '2':
        system("cls");
        desencriptar( );
        printf("\n");
        system("pause");
        break;
    case '3':
        system("cls");
        encriptarArchivo( );
        printf("\n");
        system("pause");
        break;
    case '4':
        system("cls");
        return 0;
        break;
    default:

        system("pause");
        break;
    }}while (opcion!=4);    
}

void encriptar( ){
    printf("Ingrese el mensaje a Encriptar: \n");
//este primer bloque permite crear una cadena de texto de cualquier tamaño segun lo que se escriba
//usa memoria dinamica, asi no tenemos que definir el tamaño de la cadena
    char *texto=NULL;
    int contador=0;
    char caracter;
    texto==(char*)malloc(1*sizeof(char));
    do
    {
        fflush(stdin);
        caracter=getche();
        if(caracter!=enter){
        contador++;
        texto=(char*)realloc(texto,contador*sizeof(char));
        texto[contador-1]=caracter;
        }
        else break;
    } while (1);
//este bloque pedira una llave para encriptarlo en codigo ascii, esto luego se los explico xd
    system("cls");
    int llave;
    llave=Dec_Aleatorio( );
//este bloque encripta el mensaje deseado con el primer for
//el segundo for sirve para imprimir el mensaje encriptado    
    for (int i = 0; i < contador; i++)
    {
        texto[i]=texto[i]+llave;
    }
    texto[contador]='\0';
    printf("Su mensaje encriptado es:\n");
    for (int i = 0; i < contador; i++)
    {
        printf("%c",texto[i]);
    }
    int llaveBin=Dec_Bin(llave);
    printf("\n\tRECUERDE SU LLAVE\nSu llave en binario es: %d\n",llaveBin);
//en este bloque escribiremos el mensaje encriptado en un archivo de texto llamado "Mensaje Encriptado.txt"
    FILE *archivo;
    archivo=fopen("Mensaje Encriptado.txt","w");
    if (archivo==NULL) //es importante declarar esto por si no se puede crear el archivo, ya sea pq no se tienen permisos o no hay espacio en el disco o asi
    {
        printf("No se puede crear el archivo\n");
    }
    else{        
            fprintf(archivo,texto);
            printf("\nSu encriptado se ha creado con exito\n\n");
            }
    free(texto);
    fclose(archivo);    
}

void desencriptar(){
    //abrimos el archivo previamente creado para leerlo y desencriptarlo
    FILE *archivo;
    archivo=fopen("Mensaje Encriptado.txt","r");
    char llaveCadena[20];
    printf("\nIngrese la llave binaria para desencriptar: \n");
    scanf("%s",&llaveCadena);    
    long int llave= Bin_Dec(llaveCadena);
    if (archivo==NULL)
    {
        printf("No se puede abrir el archivo\n");
    }
    else{
        //Obtenemos el texto del archivo
            char caracter;
            char *texto=NULL;
            texto=(char *)malloc(1*sizeof(char));
            int contador=0;
            do
            {
                caracter=fgetc(archivo);
                if (feof(archivo)) break;
                else{
                contador++;
                texto=(char *)realloc(texto,contador*sizeof(char));
                texto[contador-1]=caracter;
                }
            } while (1);
            
        //Hacemos la desencripcion con la llave dada
            for (int i = 0; i<contador; i++)
            {
                texto[i]=texto[i]-llave;
            }
            printf("La cadena desencriptada es:\n");
            for (int i = 0; i < contador; i++)
            {
                printf("%c",texto[i]);
            }
            free(texto);
    }
        
        fclose(archivo);
}

void encriptarArchivo(){
    FILE *archivo;
    archivo=fopen("Mensaje Por Encriptar.txt","r");
    int llave;  
    if (archivo==NULL)
    {
        printf("No se puede abrir el archivo\nAsegure que este existe y esta bajo el nombre de Mensaje Por Encriptar.txt\n");
    }
    else{
        //Obtenemos el texto del archivo
            char caracter;
            char *texto=NULL;
            texto=(char *)malloc(1*sizeof(char));
            int contador=0;
            do
            {
                caracter=fgetc(archivo);
                if (feof(archivo)) break;
                else{
                contador++;
                texto=(char *)realloc(texto,contador*sizeof(char));
                texto[contador-1]=caracter;
                }
            } while (1);
            texto[contador]='\0';
            fclose(archivo);
        //encriptamos y lo escribimos sobre mensaje encriptado.txt
         llave=Dec_Aleatorio();  
          for (int i = 0; i<contador; i++)
            {
                texto[i]=texto[i]+llave;
            }
            printf("La cadena encriptada es:\n");
            for (int i = 0; i < contador; i++)
            {
                printf("%c",texto[i]);
            }
            FILE *archivo;
            int llaveBin=Dec_Bin(llave);
            printf("\n\tRECUERDE SU LLAVE\nSu llave en binario es: %d\n",llaveBin);
            archivo=fopen("Mensaje Encriptado.txt","w");
            fprintf(archivo,texto);
            printf("\nSu encriptado se ha creado con exito\n\n");
            fclose(archivo);
            free(texto);
            
            FILE *archivoAux;
            archivoAux=fopen("Mensaje Por Encriptar.txt","w");
            if(archivoAux==NULL)
            printf("No se ha podido borrar el contenido del archivo por encriptar");
            else{
            fprintf(archivo,"");
            fclose(archivoAux);
            }
            }
            }

long int Bin_Dec(char Bin[100]){
    char *endptr;
    long int decimal=0;
    decimal= strtol(Bin,&endptr,2);   
    return decimal;
}

int Dec_Bin(int num){
    int base=2,total=0,coeficiente=1;
    while(num!=0)
    {
        if (num<0) break;
        else{
        total=total+coeficiente*(num%2);
        num=num/2;
        coeficiente*=10;
        }
    }
    return total;
}

int Dec_Aleatorio( ){
int min=1, max=133;
srand(time(0));
return min + rand() % (max + 1 - min);
}
