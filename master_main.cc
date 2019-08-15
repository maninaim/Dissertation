
// program to do master transformation for power spectrum 

#include <string>
#include "stdio.h"
//#include "OptMedian.h"

#include "xcomplex.h"

//#include "paramfile.h"
//#include "simparams.h"
//#include "lsconstants.h"
//#include "planck_rng.h"
#include "healpix_map.h"
#include "healpix_data_io.h"
#include "healpix_map_fitsio.h"
#include <alm.h>
#include <alm_fitsio.h>
#include <alm_healpix_tools.h>
//#include "alm_fitsio.h"
//#include "healpix_base.h"
#include <powspec.h>
#include <powspec_fitsio.h>
#include <alm_powspec_tools.h>
#include "MatMask.h"
//#include "fitshandle.h"

using namespace std;

int main( int argc, char *argv[] )
{
	
	 int k;
    double Min, Max;
    //fitsstruct Header, HD1;
    char Cmd[512];
    Cmd[0] = '\0';
    //for (k =0; k < argc; k++) sprintf(Cmd, "%s %s", Cmd, argv[k]);

	char Name_Imag_In[512] = "cmb_9yr.fits"; /* input file image */
	//char SignalPowSpec_FileName [512];

	bool Verbose=false;
	float SigmaNoise=0.;
	 
	bool NormALM = false;
	float  ZeroPadding=0.;
	int Lmax = 0.;
	bool OptS_PS = false;
	bool CFIMA= false;

	char MaskMatrix_FileName;
	char Mask_FileName[512] = "wmap_temperature_kq75_analysis_mask_r9_9yr_v5.fits";
	bool UseMask = false;         
	int MaskIter = 20;

	bool OptMat = false;
	bool OptMask = false;
	bool InputPowSpec = false;

	//printf("\n I've writeen my first Cpp program!\n");
	
	Healpix_Map<double> tgt_map, mask_map;

	//string infile = string(Name_Imag_In);
	
	read_Healpix_map_from_fits( Name_Imag_In, tgt_map, 1, 2 );
	
	int nside =  tgt_map.Nside();
	int nlmax  = 2*nside;
	int nmmax = nlmax;
	printf("\n Nside is %d\n", tgt_map.Nside() );
	
	arr<double> weight;
	weight.alloc(2*nside);
	weight.fill(1);
	
	if( tgt_map.Scheme() == NEST ) tgt_map.swap_scheme();
	
	Alm<xcomplex<double> > alm( nlmax, nmmax );
	
	map2alm_iter(  tgt_map, alm, 1,  weight );
	
	PowSpec mySpec(1,nlmax);
	extract_powspec(alm,mySpec);
	
	fitshandle myCl;
	myCl.create("PowSpectrum.fits");
	
	write_powspec_to_fits(myCl,mySpec,1);
	
	return  1;
	
	
	
	
	
	
	
}
