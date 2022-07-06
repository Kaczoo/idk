#include <stdio.h>

# define new_line 10
# define space 32
# define hash 35


# define read \
ins[j] = fgetc(src); \
if (ins[j] == 32) \
{ \
    j--; \
}


# define read_mem_addr \
for (int j = 0; j < 3; j++) \
{ \
    read; \
} \
line += (ins[1] - 48)*10 + ins[2] - 48;


# define read_reg \
for (int j = 0; j < 2; j++) \
{ \
    read; \
} \
if (ins[1] == '1') \
{ \
    line += 256; \
}


# define read_const \
for (int j = 0; j < 3; j++) \
{ \
    read; \
} \
line += (ins[0] - 48)*100 + (ins[1] - 48)*10 + ins[2] - 48;


# define arithm_templ \
fgetc(src); \
read_reg; \
fgetc(src); \
ins[0] = fgetc(src); \
fseek(src, -1, SEEK_CUR); \
if (ins[0] == 'R') \
{ \
    line += 512; \
    fgetc(src); \
    fgetc(src); \
} \
else \
{ \
    read_const; \
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

    int c = 0;
    short line;
    int ins[3] = {};

    for (int i = 0; c != -1 && ins[0] != -1 && ins[1] != -1 && ins[2] != -1; i++)
    {
	for (int j = 0; j < 3; j++)
	{
	    read;
	}
	if (ins[0] == 'M' && ins[1] == 'W' && ins[2] == 'I')
	{
	    read_reg;

	    fgetc(src);

	    ins[0] = fgetc(src);
	    fseek(src, -1, SEEK_CUR);
	    if (ins[0] == 64)
	    {
		line += 512;
		read_mem_addr;
	    }
	    else
	    {
		read_const;
	    }
	}
	else if (ins[0] == 'M' && ins[1] == 'W' && ins[2] == 'O')
	{
	    line += 1024;

	    read_reg;

	    read_mem_addr;
	}
	else if (ins[0] == 'J' && ins[1] == 'M' && ins[2] == 'P')
	{
	    line +=  2048;
	    
	    read_mem_addr;
	}
	else if (ins[0] == 'J' && ins[1] == 'E' && ins[2] == 'Z')
	{
	    line += 3072;

	    read_reg;

	    read_mem_addr;
	}
	else if (ins[0] == 'A' && ins[1] == 'D' && ins[2] == 'D')
	{
	    line += 4096;

            arithm_templ;
	}
	else if (ins[0] == 'S' && ins[1] == 'U' && ins[2] == 'B')
	{
	    line += 5120;

	    arithm_templ;
	}
	else if (ins[0] == 'A' && ins[1] == 'N' && ins[2] == 'D')
	{
	    line += 6144;

	    arithm_templ;
	}
	else if (ins[0] == 'I' && ins[1] == 'O' && ins[2] == 'R')
	{
	    line += 7168;

	    arithm_templ;
	}
	else
	{
	    printf("read manual first retard");
	}

	if (line < 4096)
	    printf("0");
	if (line < 256)
	    printf("0");
	if (line < 16)
	    printf("0");
	printf("%x\n", line);
	line = 0;

	if(fgetc(src) != 10)
	    printf("endlines\n");
	if(fgetc(src) == -1)
	    break;
	fseek(src, -1, SEEK_CUR);
    }
    return 0;
}
