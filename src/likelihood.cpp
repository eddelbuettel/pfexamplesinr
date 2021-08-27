#include <RcppEigen.h>
#include "svol_sisr_hilb.h"
#include "resamplers.h"

// [[Rcpp::depends(RcppEigen)]]

// 1e3 particles, 5 bits 
#define NP 2
#define NB 5
#define debug_mode false


using Eigen::Map; 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using hilb_sys_resamp_T = pf::resamplers::sys_hilb_resampler<NP,1,NB,double>;
using svol_pfilter = svol_sisr_hilb<NP,NB, hilb_sys_resamp_T, double, debug_mode>; 

// helpful notes:
// 1. 
// parameters passed to svol_pfilter() ctor are in the following order: phi, beta, sigma
// 2.
// uProposal will be dimension (time X (particles + 1))
// first NP columns will be used for state sampling 
// last column will be used for resampling at each time point


// [[Rcpp::export]]
double approxLL(const Map<VectorXd> y, const Map<VectorXd> thetaProposal, const Map<MatrixXd> uProposal) {

  // construct particle filter object
  svol_pfilter pf(thetaProposal(0), thetaProposal(1), thetaProposal(2)); // order: phi, beta, sigma

  // iterate over the data 
  double log_like(0.0);
  Eigen::Matrix<double,1,1> yt;
  std::array<Eigen::Matrix<double,1,1>, NP> uStateTransition;
  Eigen::Matrix<double,1,1> uResample;
  for(int time = 0; time < y.rows(); ++time){
    
    // change types of inputs
    yt(0) = y(time);
    for(unsigned particle = 0; particle < NP; ++particle) {
      uStateTransition[particle] = uProposal.block(time,particle,1,1); 
    }
    uResample(0) = uProposal(time,NP);
    
    // std::cout << yt.transpose() << "\n";
    // for(unsigned int i = 0; i < NP; ++i)
    //   std::cout << uStateTransition[i] << ", ";
    // std::cout << "\n----------\n";
    
    // update particle filter and log-likelihood    
    pf.filter(yt, uStateTransition, uResample);
    log_like += pf.getLogCondLike();
  }
    
  //return es.eigenvalues();
  return log_like;
}

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.


/*** R
numTime <- 3
numParts <- 2 # make sure this agrees with NP
u <- matrix(rnorm(numTime*(numParts+1)), ncol = numParts+1)
params <- c(.9, 1, .1) #phi, beta, sigma
approxLL(rnorm(numTime), params, u)
*/
