#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "station.h"


/* Creeaza o gara cu un numar fix de peroane.
 * 
 * platforms_no: numarul de peroane ale garii
 *
 * return: gara creata
 */
TrainStation* open_train_station(int platforms_no) {
    int i;
    TrainStation* station =(TrainStation*) malloc(sizeof(TrainStation));
    station->platforms_no=platforms_no;
    station->platforms=(Train**) malloc(platforms_no*sizeof(Train*));
    for(i=0; i<station->platforms_no; i++)
            *(station->platforms+i)=NULL;
    return station;
}


/* Elibereaza memoria alocata pentru gara.
 *
 * station: gara existenta
 */
void close_train_station(TrainStation *station) {
    int i;
    TrainCar* aux;
    TrainCar* auxx;
    if(station){
    for(i=0; i<station->platforms_no; i++){
        if(station->platforms[i])
            if(station->platforms[i]->train_cars){
                aux=station->platforms[i]->train_cars;
                while(aux!=NULL){
                    auxx=aux;
                    aux=aux->next;
                    free(auxx);
        }
    }}
    for(i=0; i<station->platforms_no; i++)
        if(station->platforms[i]!=NULL)
            free(station->platforms[i]);
    free(station->platforms);
    free(station);
    }
}


/* Afiseaza trenurile stationate in gara.
 *
 * station: gara existenta
 * f: fisierul in care se face afisarea
 */
void show_existing_trains(TrainStation *station, FILE *f) {
    if(station){
    int i;
    for(i=0; i<station->platforms_no; i++){
        fprintf(f,"%d: ",i);
        if(*(station->platforms+i)){
            TrainCar* aux=station->platforms[i]->train_cars;
        fprintf(f,"(%d)",station->platforms[i]->locomotive_power);
        while(aux!=NULL){
            fprintf(f,"-|%d|",aux->weight);
            aux=aux->next;
        }
        }
        fprintf(f,"\n");
    }}

}


/* Adauga o locomotiva pe un peron.
 * 
 * station: gara existenta
 * platform: peronul pe care se adauga locomotiva
 * locomotive_power: puterea de tractiune a locomotivei
 */
void arrive_train(TrainStation *station, int platform, int locomotive_power) {
    if(station){
    if((platform>=0)&&(platform<station->platforms_no)) {
        if(station->platforms[platform]==NULL){
        station->platforms[platform]=(Train*) malloc(sizeof(Train));
        station->platforms[platform]->locomotive_power=locomotive_power;
        station->platforms[platform]->train_cars=NULL;}
}}
}


/* Elibereaza un peron.
 * 
 * station: gara existenta
 * platform: peronul de pe care pleaca trenul
 */
void leave_train(TrainStation *station, int platform) {
    if(station){
        if((platform<0)||(platform>=station->platforms_no))
        return; 
            if(!(station->platforms[platform]))
        return;
    //if(station->platforms[platform]->train_cars)
    TrainCar* auxx=NULL;
    TrainCar* aux=station->platforms[platform]->train_cars;
    if(aux==NULL)
    {free(station->platforms[platform]);
    station->platforms[platform]=NULL;}
    else{ 
    while(aux!=NULL){
        auxx=aux;
            aux=aux->next;
        free(auxx);
    }
    free(station->platforms[platform]);
    
    }
    station->platforms[platform]=NULL;
}
}
/* Adauga un vagon la capatul unui tren.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 * weight: greutatea vagonului adaugat
 */
 void add_train_car(TrainStation *station, int platform, int weight) {
    if((platform>=0)&&(platform<station->platforms_no)) 
        if(station->platforms[platform]!=NULL){ 
            if(station->platforms[platform]->train_cars){
                TrainCar* aux=station->platforms[platform]->train_cars;
                while(aux->next!=NULL)
                    aux=aux->next;
                TrainCar* auxx=(TrainCar*) malloc(sizeof(TrainCar));
                auxx->weight=weight;
                auxx->next=NULL;
                aux->next=auxx;
                }
            else{
                station->platforms[platform]->train_cars=(TrainCar*) malloc(sizeof(TrainCar));
                station->platforms[platform]->train_cars->weight=weight;
                station->platforms[platform]->train_cars->next=NULL;
            }
}
 }

/* Scoate vagoanele de o anumita greutate dintr-un tren.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 * weight: greutatea vagonului scos
 */

int contains(TrainStation *station, int platform, int weight){
    if((platform>=0)&&(platform<station->platforms_no)) 
        if(station->platforms[platform]!=NULL){ 
            if(station->platforms[platform]->train_cars){
                TrainCar* aux=station->platforms[platform]->train_cars;
                while(aux!=NULL){
                    if(aux->weight==weight)
                        return 1;
                    aux=aux->next;
                }
                return 0;
            }
            }
    return 0;
}
TrainCar* deleteonce(TrainStation *station, int platform, int weight){
     if((platform>=0)&&(platform<station->platforms_no)) 
        if(station->platforms[platform]!=NULL){ 
            if(station->platforms[platform]->train_cars){
                TrainCar* aux=station->platforms[platform]->train_cars;
                TrainCar* prev;
                if(aux->weight==weight){
                    station->platforms[platform]->train_cars=station->platforms[platform]->train_cars->next;
                    free(aux);
                }
                else{
                    prev=aux;
                    aux=aux->next;
                    while((aux!=NULL)&&(aux->weight!=weight)){
                        prev=aux;
                        aux=aux->next;
                    }
                    if(aux!=NULL){
                        prev->next=aux->next;
                        free(aux);
                    }
                }
            }
        }
    return station->platforms[platform]->train_cars;
}


void remove_train_cars(TrainStation *station, int platform, int weight) {
if((platform>=0)&&(platform<station->platforms_no)) 
        if(station->platforms[platform]!=NULL){ 
            if(station->platforms[platform]->train_cars){
                while(contains(station,platform,weight)){
                    station->platforms[platform]->train_cars=deleteonce(station,platform,weight);
                }
            }
        }
}
/* Muta o secventa de vagoane dintr-un tren in altul.
 * 
 * station: gara existenta
 * platform_a: peronul pe care se afla trenul de unde se scot vagoanele
 * pos_a: pozitia primului vagon din secventa
 * cars_no: lungimea secventei
 * platform_b: peronul pe care se afla trenul unde se adauga vagoanele
 * pos_b: pozitia unde se adauga secventa de vagoane
 */

int length(TrainStation* station, int platform){
    if(!(station->platforms[platform]->train_cars))
        return 0;
    int k=0;
    TrainCar* aux=station->platforms[platform]->train_cars;
    while(aux){
        k++;
        aux=aux->next;
    }
    return k;
}
TrainCar* removee(TrainStation* station, int platform, int pos){
    TrainCar* aux=station->platforms[platform]->train_cars;
    TrainCar* prev;
    if(pos>1){
    for(int i=1; i<pos; i++){
        prev=aux;
        aux=aux->next;
    }
    prev->next=aux->next;
    return aux;
    }
    if(pos==1){
    station->platforms[platform]->train_cars=station->platforms[platform]->train_cars->next;
    return aux;
    }

}
void insert(TrainStation* station, int platform, int pos, TrainCar* car){
    if(pos==1){
    car->next=station->platforms[platform]->train_cars;
    station->platforms[platform]->train_cars=car;}
    else{
        TrainCar* aux;
        TrainCar* prev;
        aux=station->platforms[platform]->train_cars;
        for(int i=1; i<pos; i++){
            prev=aux;
            aux=aux->next;
        }
        car->next=aux;
        prev->next=car;
    }


}

void move_train_cars(TrainStation *station, int platform_a, int pos_a, 
                                int cars_no, int platform_b, int pos_b) {
     TrainCar* r;
    if((platform_a>=0)&&(platform_a<station->platforms_no))
        if((platform_b>=0)&&(platform_b<station->platforms_no))
            if((pos_a>=1)&&(pos_a<=length(station,platform_a)))
                if((pos_b>=1)&&(pos_b<=length(station,platform_b)+1))
                    if((pos_a+cars_no-1>0)&&(pos_a+cars_no-1<=length(station,platform_a)))
                        {
                            for(int i=0; i<cars_no; i++){
                                r=removee(station,platform_a,pos_a);
                                r->next=NULL;
                                insert(station,platform_b,pos_b+i,r);
                            }
                        }
    
}
/* Gaseste trenul cel mai rapid.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_express_train(TrainStation *station) {
    int rapid=0,q;
    int viteza;
    for(int i=0; i<station->platforms_no; i++){
        if(station->platforms[i]){
            if(station->platforms[i]->train_cars){
                viteza=station->platforms[i]->locomotive_power;
                TrainCar* curr=station->platforms[i]->train_cars;
                while(curr!=NULL){
                    viteza=viteza-curr->weight;
                    curr=curr->next;
                    }
                if(viteza>rapid){
                    rapid=viteza;
                    q=i;
                }}
                else{
                    viteza=station->platforms[i]->locomotive_power;
                    if(viteza>rapid){
                    rapid=viteza;
                    q=i;
                }
                }
                
                }}
    return q;
}


/* Gaseste trenul supraincarcat.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_overload_train(TrainStation *station) {
    int rapid=0,q;
    int viteza;
    for(int i=0; i<station->platforms_no; i++){
        if(station->platforms[i]){
            if(station->platforms[i]->train_cars){
                viteza=station->platforms[i]->locomotive_power;
                TrainCar* curr=station->platforms[i]->train_cars;
                while(curr!=NULL){
                    viteza=viteza-curr->weight;
                    curr=curr->next;
                    }
                    if(viteza<0)
                    return i;
                }
                }}
            return -1;

}


/* Gaseste trenul cu incarcatura optima.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_optimal_train(TrainStation *station) {
    int rapid=100000000,q;
    int viteza;
    for(int i=0; i<station->platforms_no; i++){
        if(station->platforms[i]){
            if(station->platforms[i]->train_cars){
                viteza=station->platforms[i]->locomotive_power;
                TrainCar* curr=station->platforms[i]->train_cars;
                while(curr!=NULL){
                    viteza=viteza-curr->weight;
                    curr=curr->next;
                    }
                if(viteza<rapid){ 
                    rapid=viteza;
                    q=i;
                }}
                else{
                    viteza=station->platforms[i]->locomotive_power;
                    if(viteza<rapid){
                    rapid=viteza;
                    q=i;
                }
                }
                
                }}
    return q;
}


/* Gaseste trenul cu incarcatura nedistribuita bine.
 * 
 * station: gara existenta
 * cars_no: lungimea secventei de vagoane
 *
 * return: peronul pe care se afla trenul
 */
int find_heaviest_sequence_train(TrainStation *station, int cars_no, TrainCar **start_car) {
    int maxx=-1;
    int r;
    int s,x;
    int max;
    int q=-1;
    int contor=-1;
    TrainCar* cautat;
    for(int i=0; i<station->platforms_no; i++){
            if((station->platforms[i])&&(length(station,i)<cars_no))
                max=-1;
            else if((station->platforms[i])&&(length(station,i)>=cars_no)){
                x=length(station,i);
                TrainCar* curr=station->platforms[i]->train_cars;
                max=0;
                for(int j=0; j<=x-cars_no; j++){
                TrainCar* aux=curr;

                s=0;
                for(int k=1; k<=cars_no; k++){
                    s=s+aux->weight;
                    if(aux->next)
                        aux=aux->next;}
                if(s>max){
                    max=s;
                    cautat=curr;
                    }
                curr=curr->next;
            }}
    if(max>maxx)
    {maxx=max;
    *start_car=cautat;
    contor=i;}
    }
    if(contor==-1)
    *start_car=NULL;
    return contor;
}


/* Ordoneaza vagoanele dintr-un tren in ordinea descrescatoare a greutatilor.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 */
void order_train(TrainStation *station, int platform) {

    if(station){
        if(station->platforms[platform])
        if(station->platforms[platform]->train_cars)
        if(length(station,platform)>1){
            int sort;
            do{
                sort=1;
                TrainCar* curr=station->platforms[platform]->train_cars;
                TrainCar* nxt=curr->next;

                if(curr->weight<nxt->weight){
                    curr->next=nxt->next;
                    nxt->next=curr;
                    station->platforms[platform]->train_cars=nxt;
                    sort=0;
                }
                curr=station->platforms[platform]->train_cars->next;
                nxt=curr->next;
                TrainCar* aux=station->platforms[platform]->train_cars;;
                while(curr->next!=NULL){
                    if(curr->weight <  nxt->weight){

                        curr->next=nxt->next;
                        aux->next=nxt;
                        nxt->next=curr;
                        sort=0;
                    }
                   aux=aux->next;
                   curr=aux->next;
                   nxt=curr->next;
                    

                }

            }while(!sort);

        }}
}


/* Scoate un vagon din trenul supraincarcat.
 * 
 * station: gara existenta
 */
void fix_overload_train(TrainStation *station) {
   if(station){
       int overload=find_overload_train(station);
      
       if(overload==-1)
            return;
        else{
            TrainCar* aux=station->platforms[overload]->train_cars;
            TrainCar* curr=aux;
            int power=station->platforms[overload]->locomotive_power;
            int incarcatura=0;
            while(curr!=NULL){
                incarcatura=incarcatura+curr->weight;
                curr=curr->next;
            }
            curr=aux;
            int min=1000;
            while(curr!=NULL){
                if((incarcatura - curr->weight <= power ) && (curr->weight < min)){
                    min=curr->weight;
                }
                curr=curr->next;
            }
            deleteonce(station,overload,min);
        }
   }
   
   }