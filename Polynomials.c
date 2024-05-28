#include    <stdio.h>
#include    <stdlib.h>

typedef struct
{
    int coeff;
    int pow;
    struct Polynomials* next;
}Polynomials;

Polynomials* createPoly(int coeff, int pow){
    Polynomials* poly=(Polynomials*)malloc(sizeof(Polynomials));
    if(!poly)
        return NULL;
    poly->coeff=coeff;
    poly->pow=pow;
    poly->next=NULL;
    return poly;
}

int insert(Polynomials* poly,int coeff, int pow){
    while(poly->next!=NULL){
        if(poly->pow==pow){
            poly->coeff+=coeff;
            return 0;
        }
        poly=poly->next;
    }
    Polynomials* temp = createPoly(coeff,pow);
    poly->next=temp;
    return 0;
}



void polyadd(Polynomials* poly1, Polynomials* poly2, Polynomials* result){
    while(poly1->next&&poly2->next){
        if(poly1->pow > poly2->pow){
            result->coeff=poly1->coeff;
            result->pow=poly1->pow;
            poly1=poly1->next;
        }
        else if((poly1->pow < poly2->pow)){
            result->coeff=poly2->coeff;
            result->pow=poly2->pow;
            poly2=poly2->next;
        }
        else{
            result->coeff=poly1->coeff+poly2->coeff;
            result->pow=poly1->pow;
            poly1=poly1->next;
            poly2=poly2->next;
        }
        Polynomials* temp=createPoly(0,0);
        result->next=temp;
        result=result->next;
        result->next=NULL;
    }
    while(poly1->next||poly2->next){
        if(poly1->next){
            result->coeff=poly1->coeff;
            result->pow=poly1->pow;
            poly1=poly1->next;
        }
        if(poly2->next){
            result->coeff=poly2->coeff;
            result->pow=poly2->pow;
            poly2=poly2->next;
        }
        result->next=(Polynomials*)malloc(sizeof(Polynomials));
        result=result->next;
        result->next=NULL;
    }

    
    insert(result,poly2->coeff,poly2->pow);
    

}

int main(){
    Polynomials* poly1=createPoly(3,5);
    Polynomials* poly2=createPoly(9,1);
    Polynomials* result=createPoly(0,0);
    insert(poly1,2,2);
    insert(poly2,8,4);
    polyadd(poly1,poly2,result);
    while(result->next){
        printf("%dx^%d ",result->coeff,result->pow);
        result=result->next;
    }

    return 0;
}