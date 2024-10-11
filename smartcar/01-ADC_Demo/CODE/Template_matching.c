#include "Template_matching.h"

double Template_matching_match(unsigned char input[19][19])
{
	int R1=0,R2=0,R3=0;
	for(int i=19-1;i>=0;i--)
	 	for(int j=19-1;j>=0;j--)
	{
		R1+=input[i][j]*circle_temple_bin[i][j];
		R2+=input[i][j]*input[i][j];
		R3+=circle_temple_bin[i][j]*circle_temple_bin[i][j];
	  R2=R2*R3;
	}
	
	return (R1/sqrt(R2));
}
