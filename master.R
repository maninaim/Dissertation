# post process from MASTER 
install.packages(FITSio)
install.packages(astro)
library(FITSio)
library(astro)

x <- read.fitsim( "PowSpectrum.fits" ,hdu=2)
xx <- x$table
l <- as.numeric(1:length(xx))

xx <- xx * ( l-1 ) * l / pi # / (2*pi)

k <- l-1

idx <- 1:500

plot( k[idx], xx[idx]*10^3, xlab=expression(paste("Multipole moment,",l)), ylab=expression( paste("Power spectrum ", C[l]*l*(l+1)/2*pi," " , m * K^2 )), type="l", col="blue", main="Reconstruced power spectrum WMAP 9 year" )

