#include <stdio.h>

int FindString(char ** strings, int num_strings, char * string){
	
	
	int num_found = 0;
	for(int i = 0; i < num_strings; i++)
	{
		char * p0 = strings[i];
		char * p1 = string;
		while(*p0 !='\0')
		{
			while(*p0 != *p1 || *p0 == '\0') p0++;
			while(*p0 == *p1 && *p0 != '\0') { p0++; p1++; }
			if(*p1 == '\0') num_found += 1;
			p1 = string;
		}
	}
	return num_found;
	
}

void main(int argc, char **argv)
{
	char * strings[] = {
		"hej jnd lodmald odn p apådmlaaw",
		"ksek f sää WÄ FLSMlaELKF",
		"abjda döe åand la jdnaj"
		"destern sortenr strunterso laserja"
	};
	
	char * string = "la";
	int num_strings = sizeof(strings) / sizeof(char *);
	int num_found = FindString(strings, num_strings, string);
	printf("Den innehåller: %i sonna.\n", num_found);
	
	return 0;
}
