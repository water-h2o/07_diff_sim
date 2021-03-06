#ifndef DIFFUSION_H
#define DIFFUSION_H

#include <Eigen/Dense>
#include <vector> // used only for string vectors
#include <string>
#include "TMath.h"
#include "TRandom.h"

// GSL
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

// === TYPEDEFS ========================================================

// ------ diffusion ----------------------------------------------------
typedef double sigma_T;
typedef double sigma_L;

// ------ electron -----------------------------------------------------
typedef Eigen::RowVector3d e_pos; // row vector with x,y,z (mm)
typedef double               e_z;
typedef Eigen::RowVector2d  e_xy;
typedef Eigen::MatrixXd   e_list; // <n_electrons>-row vector, where 
                                  // each row is an e_pos
// ------ other --------------------------------------------------------
typedef std::vector<std::string> a_sentence;

// === STRUCTS =========================================================

struct diffParameters{
	
	double  depthFrac;
	double  h;
	double  v_d;
	sigma_T s_T;
	sigma_L s_L;
	
};
typedef struct diffParameters Params;

// === MAIN FUNCTION ===================================================

e_list diffusion(std::string filename,
                      double depthFrac, // (0 == top, 1 == cathode)
                      double h = 1456,            // mm
                      double v_d = 2.0,           // mm/us
                      double sigma_Tcath = 0.59,  // mm
                      double sigma_Lcath = 0.85); // us

// === HIGH LEVEL TOOLS ================================================

// ------ input --------------------------------------------------------

e_list getEventList(std::string filename);

// ------ displacement vector ------------------------------------------

e_list getDisplacementList(int n_electrons,
                        Params theParams);

e_pos getDisplacementVector(Params theParams,
                          TRandom* );
                          
//~ e_pos getDisplacementVector(Params theParams,
                          //~ gsl_rng* );
                          
// === MID LEVEL TOOLS =================================================

// ------ reading input ------------------------------------------------

int getEventListRows(std::string filename);

e_list getThisRowEventList(std::ifstream& stream);

// ------ diffusion function -------------------------------------------

e_xy getTdisplacement(Params theParams, // 2D ROOT RNG on pdf
                    TRandom* ); 

//~ e_xy getTdisplacement(Params theParams,
                    //~ gsl_rng* );

e_z  getLdisplacement(Params theParams, // 1D ROOT RNG on pdf
                    TRandom* ); 
                    
//~ e_z getLdisplacement(Params theParams,
                   //~ gsl_rng* );

// === LOW LEVEL TOOLS =================================================

// ------ operations ---------------------------------------------------

void split(const std::string& s, 
                         char c, 
                  a_sentence& v);

//~ e_list cat2currList(e_list curr_deposition,
                    //~ e_list eventListSoFar);

e_pos cat2displacement(e_xy Tdisplacement,
                        e_z Ldisplacement);

e_list displace(e_list eventList,
                e_list displacementList);

// ------ converters ---------------------------------------------------



// ------ prepare parameters -------------------------------------------

Params constructTheParams(double depthFrac,
                          double h = 1456,            // mm
                          double v_d = 2.0,           // mm/us
                          double sigma_Tcath = 0.59,  // mm
                          double sigma_Lcath = 0.85); // us

sigma_T getSigma_T(double depthFrac, // transverse diffusion coefficient
                   double sigma_Tcath = 0.59);

sigma_L getSigma_L(double depthFrac, // longitudinal diffusion coeff
                   double v_d = 2.0,
                   double sigma_Lcath = 0.85);

// === ERROR RETURNS ===================================================

// ERRORS GO HERE

#endif // DIFFUSION_H 
