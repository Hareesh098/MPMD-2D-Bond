#include<stdio.h>
#include<stdlib.h>
#include"globalExtern.h"
void ApplyForce(){
 int n;
 double fx, fy;
 fx = 0.00000; fy = -0.001;
 for(n = 1; n <= nAtom; n ++){
 ay[n] += fy; 
 if(atomType[n] == 4 || atomType[n] == 5){
 ax[n] += fx;
} } }
