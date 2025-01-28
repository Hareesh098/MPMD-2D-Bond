#include<stdio.h>
#include<math.h>
#include"globalExtern.h"
void ComputePairForce(){
double dr[NDIM+1], fcVal, rr, ri, r, uVal;
int n, i,j;
uVal = 0.0;  uSumPair = 0.0 ; 
virSumPair = 0.0; virSumPairxx = 0.; virSumPairyy = 0.; virSumPairxy = 0.;

for(n = 1 ; n <= nAtom ; n ++){
 ax[n] = 0.;
 ay[n] = 0.;
}

RadiusIJ = 0.0;
gamman = 1.0;
double vr[NDIM+1], fdVal, rrinv;
rrinv = 0.0; fdVal = 0.0; 

for(i=1;i<=nAtom;i++){
 for(j=i+1;j<=nAtom;j++){
 if(atomRadius[i] > 0.0 &&  atomRadius[j] > 0.0){
  dr[1] = rx[i] - rx[j];
   if(dr[1] >= regionH[1]) 
    dr[1] -= region[1];
   else if(dr[1] < -regionH[1]) 
    dr[1] += region[1];

  dr[2] = ry[i] - ry[j];
   if(dr[2] >= regionH[2]){
    dr[1] -= shearDisplacement;
    if(dr[1] < -regionH[1]) dr[1] += region[1];
    dr[2] -= region[2];
  }else if(dr[2] < -regionH[2]){
   dr[1] += shearDisplacement;
    if(dr[1] >= regionH[1]) dr[1] -= region[1];
   dr[2] += region[2];
  }

  rr = Sqr(dr[1]) + Sqr(dr[2]);
  RadiusIJ = atomRadius[i] + atomRadius[j];
  SqrRadiusIJ = Sqr(RadiusIJ);
  if(rr < SqrRadiusIJ){
   r = sqrt(rr);
   ri = 1.0/r;
   rrinv = 1.0/rr;
   vr[1] = vx[i] - vx[j];
   vr[2] = vy[i] - vy[j];
   RadiusIJInv = 1.0/RadiusIJ;
   uVal = Sqr(1.0 - r * RadiusIJInv);
   fcVal = 1.0 * RadiusIJInv * (1.0 - r * RadiusIJInv) *ri;
   fdVal = -gamman * (vr[1]*dr[1] + vr[2]*dr[2]) * rrinv; //disc-disc drag

   discDragx[i] +=  fdVal * dr[1]; //disc-disc drag
   discDragy[i] +=  fdVal * dr[2]; //disc-disc drag
   discDragx[j] += -fdVal * dr[1]; //disc-disc drag
   discDragy[j] += -fdVal * dr[2]; //disc-disc drag

   ax[i] += (fcVal + fdVal) * dr[1];
   ay[i] += (fcVal + fdVal) * dr[2];
   ax[j] += -(fcVal + fdVal) * dr[1];
   ay[j] += -(fcVal + fdVal) * dr[2];


  //In the following, for stress/virial term (fcVal + fdVal) is used since the total pair force = Hookean Interaction + relative velocity drag
  uSumPair +=  0.5 * uVal;
  virSumPair += 0.5 * (fcVal + fdVal) * rr; 
  virSumPairxx += 0.5 * (fcVal + fdVal) * dr[1] * dr[1];
  virSumPairyy += 0.5 * (fcVal + fdVal) * dr[2] * dr[2];
  virSumPairxy += 0.5 * (fcVal + fdVal) * dr[1] * dr[2];
  } } } }

}



