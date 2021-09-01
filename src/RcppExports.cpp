// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// svolApproxLL
double svolApproxLL(Eigen::Map<Eigen::VectorXd> y, Eigen::Map<Eigen::VectorXd> thetaProposal, Eigen::Map<Eigen::VectorXd> uProposal);
RcppExport SEXP _pfexamplesinr_svolApproxLL(SEXP ySEXP, SEXP thetaProposalSEXP, SEXP uProposalSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::Map<Eigen::VectorXd> >::type y(ySEXP);
    Rcpp::traits::input_parameter< Eigen::Map<Eigen::VectorXd> >::type thetaProposal(thetaProposalSEXP);
    Rcpp::traits::input_parameter< Eigen::Map<Eigen::VectorXd> >::type uProposal(uProposalSEXP);
    rcpp_result_gen = Rcpp::wrap(svolApproxLL(y, thetaProposal, uProposal));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_pfexamplesinr_svolApproxLL", (DL_FUNC) &_pfexamplesinr_svolApproxLL, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_pfexamplesinr(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
