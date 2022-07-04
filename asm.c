#include <stdio.h>

# define new_line 10
# define space 32
# define hash 35

# ifndef EOF
    # define EOF -1
# endif


# define read \
ins[j] = fgetc(src);\
if (ins[j] == 32)\
    i--;\


# define read_mem_addr \
for (int j = 0; j < 3; j++)\
{\
    read;\
}\
line[i] += (ins[1] - 48)*10 + ins[2] - 48;


# define read_reg \
for (int j = 0; j < 2; j++)\
{\
    read;\
}\
if (ins[1] == '1')\
    line[i] += 256;


# define read_const \
for (int j = 0; j < 3; j++)\
{\
    read;\
}\
line[i] += (ins[0] - 48)*100 + (ins[1] - 48)*10 + ins[2] - 48


# define arithm_templ \
read_reg;\
ins[0] = fgetc(src);\
src--;\
if (ins[0] == 'R')\
{\
    line[i] += 256;\
}\
else\
{\
    read_const;\
}



int main(int argc, char** argv)
{
    char hexOutput = 1;
    if (argc > 2)
    {
	if (argv[2][0] == 'b')
	    hexOutput = 0;
    }

    FILE* src;
    src = fopen(argv[1], "r");

    char c = 0;
    short line[64] = {};
    char ins[3] = {};

    for (int i = 0; c != -1; i++)
    {
	for (int j = 0; j < 3; j++)
	{
	    read;
	}
	if (ins[0] == 'M' && ins[1] == 'W' && ins[2] == 'I')
	{
	    read_reg;

	    ins[0] = fgetc(src);
	    src--;
	    if (ins[0] == '@')
	    {
		line[i] += 512;
		read_mem_addr;
	    }
	    else
	    {
		read_const;
	    }
	}
	else if (ins[0] == 'M' && ins[1] == 'W' && ins[2] == 'O')
	{
	    line[i] += 1024;

	    read_reg;

	    read_mem_addr;
	}
	else if (ins[0] == 'J' && ins[1] == 'M' && ins[2] == 'P')
	{
	    line[i] +=  2048;
	    
	    read_mem_addr;
	}
	else if (ins[0] == 'J' && ins[1] == 'E' && ins[2] == 'Z')
	{
	    line[i] += 3072;

	    read_reg;

	    read_mem_addr;
	}
	else if (ins[0] == 'A' && ins[1] == 'D' && ins[2] == 'D')
	{
	    line[i] += 4096;

            arithm_templ;
	}
	else if (ins[0] == 'S' && ins[1] == 'U' && ins[2] == 'B')
	{
	    line[i] += 5120;

	    arithm_templ;
	}
	else if (ins[0] == 'A' && ins[1] == 'N' && ins[2] == 'D')
	{
	    line[i] += 6144;

	    arithm_templ;
	}
	else if (ins[0] == 'I' && ins[1] == 'O' && ins[2] == 'R')
	{
	    line[i] += 7168;

	    arithm_templ;
	}
	else
	{
	    printf("read manual first retard");
	}
    }
    return 0;
}
