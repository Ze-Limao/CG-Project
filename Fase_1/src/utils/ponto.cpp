#include "ponto.hpp"

struct ponto{
    float x, y, z;
};

Ponto newEmptyPonto(){
    return newPonto(0.0f, 0.0f, 0.0f);
}

Ponto newPonto(float x, float y, float z){
    Ponto r = (Ponto)malloc(sizeof(struct ponto));
    if(r != NULL){
        r->x = x; r->y = y; r->z = z;
    }
    return r;
}

Ponto newPontoEsferico(float a, float b, float radius){
    float z = radius * cosf(b) * cosf(a);
    float x = radius * cosf(b) * sinf(a);
    float y = radius * sinf(b);
    
    return newPonto(x, y, z);
}

float getX(Ponto p){
    if(p){
        return p->x;
    }
    return 0.0f;
}

float getY(Ponto p){
    if(p){
        return p->y;
    }
    return 0.0f;
}

float getZ(Ponto p){
    if(p){
        return p->z;
    }
    return 0.0f;
}

float distanceToOrigin(Ponto p){
    float dx = getX(p);
    float dy = getY(p);
    float dz = getZ(p);
    return sqrtf(dx*dx + dy*dy + dz*dz);
}

float distance(Ponto p1, Ponto p2){
    float dx = getX(p2) - getX(p1);
    float dy = getY(p2) - getY(p1);
    float dz = getZ(p2) - getZ(p1);
    return sqrtf(dx*dx + dy*dy + dz*dz);
}

Ponto dupPonto(Ponto ponto){
    return newPonto(ponto->x, ponto->y, ponto->z);
}

void deletePonto(Ponto p){
    free(p);
}