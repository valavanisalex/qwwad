#!/bin/sh
# Define output file

OUT=O-F.r

# Initialise files

rm -f $OUT

# Calculate conduction band barrier height for GaAs/Ga(1-x)Al(x)As
# Use V=0.67*1247*x, keep x=0.2

V=167.0985

# Calculate bulk effective mass of electron in Ga(1-x)Al(x)As
# Use MB=0.067+0.083*x, keep x=0.2

MB=0.0836

# Define well widths here

LW1=60
LW2=50

# perform numerical solution
#
# First generate structure definition `s.r' file
echo 200 0.2 0.0 > s.r
echo $LW1 0.0 0.0 >> s.r
echo 60 0.2 0.0 >> s.r
echo $LW2 0.0 0.0 >> s.r
echo 200 0.2 0.0 >> s.r

find_heterostructure --nz 2281		# generate alloy concentration as a function of z
efxv			# generate potential data

# Loop over electric field 

for F in 0 1 2 3 4 5 6 7 8 9 10 11 12 15 20 25 30 40
do
{

 # Add electric field to potential
 find_poisson_potential --field $F --centred --uncharged
 paste v.r v_p.r | awk '{print $1, $2+$4}' > v_t.r

 efss --nst-max 2 --v-file v_t.r # calculate ground and first excited states

 # Calculate overlap integral between two states and write to file

 ovl=` paste wf_e1.r wf_e2.r | awk '
 function abs(value)
 {
     return (value<0 ? -value : value);
 }
 BEGIN {dz=0.25e-10; sum=0}
 {
     sum+=abs($2)*abs($4);
 }
 END {print sum * dz}'`

 echo $F $ovl >> $OUT

# ovl wf_e1.r wf_e2.r | awk '{printf("\t%f\n",$4)}' >> $OUT
}
done