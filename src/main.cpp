#include <iostream>
#include "diffusion.h"
#include <algorithm>
#include <sstream>
#include <iterator>
#include <functional>
#include <fstream>
#include "TMath.h"
#include "TRandom.h"

// GSL
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

using namespace std;

// dispvector
Params testCTP();
void testGLD(Params theParams);
void testGTD(Params theParams);
void testGDV(Params theParams);
void testGDL(Params theParams);

// read event data
void testGTREL();
void testGEL();

// final
void testDiffusion(string out_filename);
void testPoisson();

# ifndef __CINT__

int main(int argc, char *argv[]){

    //cout << "running hierarchical debug" << endl;
    //cout << "displacement vector" << endl;
    
    //Params theParams = testCTP();
    //testGLD(theParams);
    //testGTD(theParams);
    //testGDV(theParams);
    //testGDL(theParams);
    
    //cout << "reading Event data" << endl;
    
    //testGTREL();
    //testGEL();
    
    cout << "joining everything together" << endl;
    
    testDiffusion("tracks-0_out.txt");
    
    //cout << "testing Poisson Statistics" << endl;
    
    //testPoisson();
    
	return 0;
	
}

# endif

Params testCTP(){
    
	double depthFrac = 0.3;
    double h = 1456;
    double v_d = 2.0;
    double sigma_Tcath = 0.59;
    double sigma_Lcath = 0.85;
    
    Params theParams = constructTheParams(depthFrac, h, v_d,
                                          sigma_Tcath, sigma_Lcath);
    
    cout << "depthFrac: " << theParams.depthFrac << endl;
    cout << "h: " << theParams.h << endl;
    cout << "v_d: " << theParams.v_d << endl;
    cout << "s_T: " << theParams.s_T << endl;
    cout << "s_L: " << theParams.s_L << endl;    
    
    return theParams;
}

void testGLD(Params theParams){
    
    int n = 10000;
    
    //theParams.s_L = theParams.s_T; // COMMENT OUT LATER
    
    ofstream myfile;
    myfile.open("./debug/testGLD.txt");
    
    TRandom *rnd = new TRandom(time(0));
    
    //~ const gsl_rng_type * T;
	//~ gsl_rng * rnd;
	
	//~ T = gsl_rng_default;
	//~ rnd = gsl_rng_alloc (T);
    
    cout << "testGLD --> writing to file" << endl;
    
    for(int i = 0; i < n ; i++){
        
        e_z currLD = getLdisplacement(theParams, rnd);
        myfile << currLD << "\n";
        
    }
    
    cout << "testGLD --> done" << endl;
    
    myfile.close();
    
    //~ gsl_rng_free (rnd);

    
}

void testGTD(Params theParams){
    
    //int n = 100000;
    int n = 10000;
    
    ofstream myfile;
    myfile.open("./debug/testGTD.txt");
    
    TRandom *rnd = new TRandom(time(0));
    
    //~ const gsl_rng_type * T;
	//~ gsl_rng * rnd;
	
	//~ T = gsl_rng_default;
	//~ rnd = gsl_rng_alloc (T);
    
    cout << "testGTD --> writing to file" << endl;
    
    for(int i = 0; i < n ; i++){
        
        e_xy currLT = getTdisplacement(theParams, rnd);
        myfile << currLT(0,0) << '\t' << currLT(0,1) << "\n";
        
    }
    
    cout << "testGTD --> done" << endl;
    
    myfile.close();
    
    //~ gsl_rng_free (rnd);

    
}

void testGDV(Params theParams){
    
    int n = 10000;

    ofstream myfile;
    myfile.open("./debug/testGDV.txt");
    
    TRandom *rnd = new TRandom(time(0));
    
    //~ const gsl_rng_type * T;
	//~ gsl_rng * rnd;
	
	//~ T = gsl_rng_default;
	//~ rnd = gsl_rng_alloc (T);
    
    cout << "testGDV --> writing to file" << endl;
    
    for(int i = 0; i < n ; i++){
        
        e_pos currDV = getDisplacementVector(theParams, rnd);
        myfile << currDV(0,0) << '\t' << currDV(0,1) << '\t';
        myfile << currDV(0,2) << '\n';
        
    }
    
    cout << "testGDV --> done" << endl;
    
    myfile.close();
    
    //~ gsl_rng_free (rnd);
    
}

void testGDL(Params theParams){
    
    int n = 10000;
    
    ofstream myfile;
    myfile.open("./debug/testGDL.txt");
    
    e_list DL = getDisplacementList(n, theParams);
    
    cout << "testGDL --> writing to file" << endl;
    
    for(int i = 0; i < n; i++){
        
        myfile << DL(i,0) << '\t' << DL(i,1) << '\t' << DL(i,2) << '\n';
        
    }
    
    cout << "testGDL --> done" << endl;
    
    myfile.close();
    

    
}

void testGTREL(){
    
    ifstream infile("./debug/b2bElec_1.out");
    e_list TREL = getThisRowEventList(infile);
    cout << "testGTREL --> TREL: " << TREL << endl;
    infile.close();
    
}

void testGEL(){
    
    string filename = "./debug/b2bElec_1.out";
    e_list GEL = getEventList(filename);
    
    ofstream myfile;
    myfile.open("./debug/testGEL.txt");
    
    cout << "testGEL --> writing to file" << endl;
    
    for(int i = 0 ; i < GEL.rows() ; i++){
        
        myfile << GEL(i,0) << '\t' << GEL(i,1) << '\t' << GEL(i,2) << '\n';
        
    }
    
    cout << "testGEL --> done" << endl;
    
    myfile.close();
}

void testDiffusion(string out_filename){
    
    string filename = "tracks-0.txt";
    
    e_list D = diffusion(filename, 0.01);
    
    ofstream myfile;
    myfile.open(out_filename);
    
    for(int i = 0 ; i < D.rows() ; i++){
        
        myfile << D(i,0) << '\t' << D(i,1) << '\t' << D(i,2) << '\n';
        
    }
    
    myfile.close();
}

void testPoisson(){
 
    int n = 200;
    
    string rootName = "./debug/poisson/testPoisson_";
    string extension = ".txt";
    
    for(int i = 0; i < n ; i++){
        
        string curr_name = rootName + std::to_string(i+1) + extension;
        testDiffusion(curr_name);
        
        cout << "testPoisson: produced " << curr_name << endl;
    }
    
}
