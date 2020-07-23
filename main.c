#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define direccionC "archivoC.txt"
#define direccionA "archivoA.txt"
#define direccionB "archivoB.txt"

#define MAX 1000

void crearDoc(){
    int i;
    FILE *fi;
    fi=fopen(direccionC,"w+");
    for(i=0;i<MAX;i++){
        fprintf(fi,"%.4d",rand()%MAX+1);
    }
    fclose(fi);
}
//dfsdfjsdnfvjds nvj  
void dividirMD(int elem, int cont){
    FILE *fa,*fb,*fc;
    char arrA[elem],arrB[elem];
    fc = fopen(direccionC,"r");
    fa = fopen(direccionA,"w+");
    fb = fopen(direccionB,"w+");
    rewind(fc);
    rewind(fa);
    rewind(fb);
    
    while(cont!=0){
        if(cont>=elem*2){
            fgets(arrA,elem+1,fc);
            fputs(arrA,fa);
            fgets(arrB,elem+1,fc);
            fputs(arrB,fb);
            cont-=elem*2;
        }
        if(cont<elem*2){
            fgets(arrA,elem+1,fc);
            fputs(arrA,fa);
            cont-=elem;
            fgets(arrB,cont+1,fc);
            fputs(arrB,fb);
            cont=0;
        
        }
    }
    
    fclose(fa);
    fclose(fb);
    fflush(stdin);
    fclose(fc);
    
}
void comparacionABMD(int elem, int cont){
    FILE *fa,*fb,*fc;

    int a=0,b=0,campo=elem/4,res;
    
    char arrA[4],arrB[4],resto[elem];
    
    fc = fopen(direccionC,"w+");
    fa = fopen(direccionA,"r+");
    fb = fopen(direccionB,"r+");
    
    fseek(fa,0,SEEK_END);
    fseek(fb,0,SEEK_END);
    int posA= ftell(fa);
    int posB= ftell(fb);
    fflush(fc);
    rewind(fa);
    rewind(fb);
    
    fgets(arrA,4+1,fa);
    fgets(arrB,4+1,fb);
    
    while(!feof(fb)){
        if(atoi(arrA)>atoi(arrB)){
            fputs(arrB,fc);
            fgets(arrB,4+1,fb);
            b++;
            posB-=4;
        }else if(atoi(arrA)<atoi(arrB) || atoi(arrA)==atoi(arrB)){
            fputs(arrA,fc);
            fgets(arrA,4+1,fa);
            a++;
            posA-=4;
        }
        

        if(a==campo){
            fputs(arrB,fc);
            b++;
            res=(a-b)*4;
            fgets(resto,res+1,fb);
            fputs(resto,fc);
            fgets(arrB,4+1,fb);
            a=0;
            b=0;
            posB-=res;
        }
        if(b==campo){
            fputs(arrA,fc);
            a++;
            res=(b-a)*4;
            fgets(resto,res+1,fa);
            fputs(resto,fc);
            fgets(arrA,4+1,fa);
            a=0;
            b=0;
            posA-=res;
        }
        fflush(stdin);
    }
    

    while(!feof(fa)){
        fputs(arrA,fc);
        fgets(arrA,4+1,fa);
    } 
    
    fflush(stdin);
    fclose(fa);
    fclose(fb);
    fclose(fc);
}


void MezclaDirecta(int elem){    
    int dato,n = 2;
    dato=pow(2,n);
    while((elem*4)>dato){
        dividirMD(dato,elem*4);
        comparacionABMD(dato,elem);
        n+=1;
        dato=pow(2,n);
    }

}
void comparacionABMN(int elem){
    FILE *fa,*fb,*fc;
    char arrA[4],arrB[4],arrC[4],arrD[4],residuo[elem];
    int posA, posB;
    fc = fopen(direccionC,"w+");
    fa = fopen(direccionA,"r+");
    fb = fopen(direccionB,"r+");
    rewind(fc);
    fseek(fa,0,SEEK_END);
    posA=ftell(fa);
    rewind(fa);
    fseek(fb,0,SEEK_END);
    posB=ftell(fb);
    rewind(fb);
    fgets(arrA,4+1,fa);
    fgets(arrB,4+1,fb);
    fgets(arrC,4+1,fa);
    fgets(arrD,4+1,fb);
    fseek(fa,-4,SEEK_CUR);
    fseek(fb,-4,SEEK_CUR);
    while(posA!=0 && posB!=0){
        if(atoi(arrA)<atoi(arrB)){
            fputs(arrA,fc);
            elem-=4;
            posA-=4;
            if(atoi(arrA)>atoi(arrC)){    
                fgets(arrA,4+1,fa);
                fgets(arrC,4+1,fa);
                fseek(fa,-4,SEEK_CUR);
                while(atoi(arrB)<=atoi(arrD) && posB!=0){
                    fputs(arrB,fc);
                    elem-=4;
                    posB-=4;
                    fgets(arrB,4+1,fb);
                    fgets(arrD,4+1,fb);
                    fseek(fb,-4,SEEK_CUR);
                    system("pause");
                }
            }
            if (atoi(arrA)<=atoi(arrC)){
                fgets(arrA,4+1,fa);
                fgets(arrC,4+1,fa);
                fseek(fa,-4,SEEK_CUR);
            }
            if(posB==0){
                fgets(residuo,posA,fa);
                fputs(residuo,fc);
                posA=0;     
            }
            if(posA==0){
                fgets(residuo,posB,fa);
                fputs(residuo,fc);
                posB=0;
            }

        }
        if(atoi(arrA)>atoi(arrB)){
            fputs(arrB,fc);
            elem-=4;
            posB-=4;
            if(atoi(arrB)>atoi(arrD)){    
                while(atoi(arrA)<=atoi(arrC) && posA!=0){
                    fputs(arrA,fc);
                    elem-=4;
                    posA-=4;
                    fgets(arrA,4+1,fa);
                    fgets(arrC,4+1,fa);
                    fseek(fa,-4,SEEK_CUR);
                         
                }
            }
            if(atoi(arrB)<=atoi(arrD)){
                fgets(arrB,4+1,fb);
                fgets(arrD,4+1,fb);
                fseek(fb,-4,SEEK_CUR);
                
            }  
        }
    }
    
    fflush(stdin);
    fclose(fa);
    fclose(fb);
    fclose(fc);
}
void dividirMN(int cont){
    FILE *fa,*fb,*fc;
    char arrA[4],arrB[4];
    fc = fopen(direccionC,"r");
    fa = fopen(direccionA,"w+");
    fb = fopen(direccionB,"w+");
    int cant = cont, seekC,posA, posB;
    rewind(fc);
    rewind(fa);
    rewind(fb);
    int i=0;
    fgets(arrA,4+1,fc);
    fgets(arrB,4+1,fc);
    
    while(cont!=0){
        
        if(i%2==0){
            if(atoi(arrA)>atoi(arrB)){
                i++;
            }
            fputs(arrA,fa);
            fseek(fc,-4,SEEK_CUR);
            fgets(arrA,4+1,fc);
            fgets(arrB,4+1,fc);
            cont-=4;
        }else{ 
            if(atoi(arrA)>atoi(arrB)){
                i++;
            }
            fputs(arrA,fb);
            fseek(fc,-4,SEEK_CUR);
            fgets(arrA,4+1,fc);
            fgets(arrB,4+1,fc);          
            cont-=4;
        }

    }
    fclose(fa);
    fclose(fb);
    fflush(stdin);
    fclose(fc);
}
void MezclaNatural(int elem){
    FILE *fb;
    crearDoc();
    fb= fopen(direccionB,"r+");
    do{
        dividirMN(elem*4);
        comparacionABMN(elem*4);    
    }while(ftell(fb)!=0);
    fclose(fb);



}


int main(){
    crearDoc();
    MezclaDirecta(MAX);
    //MezclaNatural(MAX);
    return 0;
}
