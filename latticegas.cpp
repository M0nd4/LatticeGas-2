#include <iostream>
#include <Eigen/Dense>
#include <math.h>

using namespace std;
using namespace Eigen;

int _lattsize=100;

int latrand() {
	double x = double(rand())/double(RAND_MAX);
	return int( _lattsize*x );
}

int pmrand() {
	double x = double(rand())/double(RAND_MAX);
	if( x >= 0.5 )	return  1;
	else		return -1;
}

int nrand(int N) {
    double x = double(rand())/double(RAND_MAX);
    return int( N*x );
}

class prt {
public:
	Vector3d pos;
	int type;
};



void rdist(prt *pprt, int Nprt) {

	for(int i=0;i<Nprt;i++) {

	pprt[i].pos(0) = latrand();
	pprt[i].pos(1) = latrand();
	pprt[i].pos(2) = 0;		// latrand();

		for(int j=0;j<i;j++) {

			while(pprt[i].pos==pprt[j].pos) {
			pprt[i].pos(0) = latrand();
			pprt[i].pos(1) = latrand();
			pprt[i].pos(2) = 0;		// latrand();
			}	// while i=j
		}		// for j
	}			// for i
}

void write(prt *pprt, int Nprt) {

	for(int i=0;i<Nprt;i++) {
	cout<<pprt[i].pos(0)<<" ; "<<pprt[i].pos(1)<<" ; "<<pprt[i].pos(2)<<"\n";
	}

}

Vector3d nextstep(Vector3d currpos) {
    if( pmrand() == 1 ) { 			
		if( pmrand() == 1 ) { 
                currpos(0)+=1;
                if(currpos(0)>_lattsize) { currpos(0)-=_lattsize; }
                if(currpos(0)<0) { currpos(0)+=_lattsize; }
                } 		
            else {
                currpos(0)-=1;
                if(currpos(0)>_lattsize) { currpos(0)-=_lattsize; }
                if(currpos(0)<0) { currpos(0)+=_lattsize; }
                }	
	        }
	    else { 			
		    if( pmrand() == 1 ) { 
                currpos(1)+=1;
                if(currpos(1)>_lattsize) { currpos(1)-=_lattsize; }
                if(currpos(1)<0) { currpos(1)+=_lattsize; }
                } 		
            else {
                currpos(1)-=1;
                if(currpos(1)>_lattsize) { currpos(1)-=_lattsize; }
                if(currpos(1)<0) { currpos(1)+=_lattsize; }
                }	
            }	  
    return currpos;
}

/*Vector3d nextstepi(prt *pprt, int i) {
    if( pmrand() == 1 ) { 			
		if( pmrand() == 1 ) { 
                pprt[i].pos(0)+=1;
                if(pprt[i].pos(0)>_lattsize) { pprt[i].pos(0)-=_lattsize; }
                if(pprt[i].pos(0)<0) { pprt[i].pos(0)+=_lattsize; }
                } 		
            else {
                pprt[i].pos(0)-=1;
                if(pprt[i].pos(0)>_lattsize) { pprt[i].pos(0)-=_lattsize; }
                if(pprt[i].pos(0)<0) { pprt[i].pos(0)+=_lattsize; }
                }	
	        }
	    else { 			
		    if( pmrand() == 1 ) { 
                pprt[i].pos(1)+=1;
                if(pprt[i].pos(1)>_lattsize) { pprt[i].pos(1)-=_lattsize; }
                if(pprt[i].pos(1)<0) { pprt[i].pos(1)+=_lattsize; }
                } 		
            else {
                pprt[i].pos(1)-=1;
                if(pprt[i].pos(1)>_lattsize) { pprt[i].pos(1)-=_lattsize; }
                if(pprt[i].pos(1)<0) { pprt[i].pos(1)+=_lattsize; }
                }	
            }	  
    return pprt[i].pos;
}*/

bool coll(prt *pprt, Vector3d nextpos, int N, int mov) {
    Vector3d currpos = pprt[mov].pos;
    for(int i=0;i<N;i++) {
        if(i==mov) {}
        else {
            if( nextpos == pprt[i].pos )
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

void allstep(prt *pprt, int N) {
    for(int i=0;i<N;i++) {
        Vector3d nextpos = nextstep(pprt[i].pos);
        if( coll(pprt,nextpos,N,i) == 1 ) {}
        else { pprt[i].pos = nextpos; }
    }
    return;
}

int main() {
	const int N=2;
	prt p[N];

	rdist(p,N);
	
    //nstep(p,N,1);
    
    p[0].pos(0)=20;
    p[0].pos(1)=20;

    p[1].pos(0)=20;
    p[1].pos(1)=21;

    for(int i=0;i<1000;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<"particle: "<<j<<" ";
            cout<<p[j].pos(0)<<", "<<p[j].pos(1)<<"\n";
            allstep(p,N);
        }
        cout<<"\n";
    }
        
    return 0;
}

