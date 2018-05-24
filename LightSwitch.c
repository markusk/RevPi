/*!
 *
 * Project: LightSwitch
 *
 * Demo source code for usage of piControl driver
 *
 *   Copyright (C) 2016 : KUNBUS GmbH, Heerweg 15C, 73370 Denkendorf, Germany
 *
 * \file LightSwitch.c
 *
 * \brief Switch light if button is pressed.
 *
 *
 */

#include <piControlIf.h>
#include <piControl.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char ** argv)
{

	int  i = 0;
	int  iLastInputValue = 0;
	char *pchInput  = NULL;
	char *pchOutput = NULL;

	// structures containing variable information: Name, Offset, Bit, Length
	SPIVariable spiVariableIn  = {"", 0, 0, 0};
	SPIVariable spiVariableOut = {"", 0, 0, 0};

	// structures containing variable value: Offset, Bit, Value
	SPIValue sValueIn   = {0, 0, 0};
	SPIValue sValueOut  = {0, 0, 0};

	if(argc != 3)
	{
		printf("Usage: %s <PiCtory Input Pin> <PiCtory Output Pin>\n"
               "  i.e. %s Input_Pin_1 Output_Pin_1\n", argv[0], argv[0]);
		return 0;
	}

	pchInput  = argv[1];	// PiCtory input pin for Switch
	pchOutput = argv[2];	// PiCtory output pin for Light

	strncpy(spiVariableIn.strVarName,  pchInput,  sizeof(spiVariableIn.strVarName));
	strncpy(spiVariableOut.strVarName, pchOutput, sizeof(spiVariableOut.strVarName));

	i = piControlGetVariableInfo(&spiVariableIn);		// PiBridge - get variable info
	if(0 != i)											// handle error
	{
		fprintf(stderr, "Error: piControlGetVariableInfo() returned %d for variable '%s' \n",
			i, spiVariableIn.strVarName);
		return -1;
	}

    i = piControlGetVariableInfo(&spiVariableOut);		// PiBridge - get variable info
	if(0 != i)											// handle error
	{
		fprintf(stderr, "Error: piControlGetVariableInfo() returned %d for variable '%s' \n",
			i, spiVariableOut.strVarName);
		return -1;
	}

	sValueIn.i16uAddress  = spiVariableIn.i16uAddress;
	sValueIn.i8uBit       = spiVariableIn.i8uBit;
	sValueIn.i8uValue     = 0;

	sValueOut.i16uAddress = spiVariableOut.i16uAddress;
	sValueOut.i8uBit      = spiVariableOut.i8uBit;
	sValueOut.i8uValue    = 0;

	printf("%s is running waiting for switch '%s' \n", argv[0], pchInput);
	
	while(1)
	{
		i = piControlGetBitValue(&sValueIn);			// PiBridge - read input pin
		if(0 != i)										// handle error
		{
			fprintf(stderr, "Error: piControlGetBitValue() returned %d\n", i);
			return -1;
		}

		if(iLastInputValue != sValueIn.i8uValue)		// if button state changed
		{												// show the change
			printf("%-32s : %d \n", pchInput, sValueIn.i8uValue);
			if(0 == sValueIn.i8uValue)					// if button is released
			{
				if(1 == iLastInputValue)				// and was pressed before
				{										// switch light
					sValueOut.i8uValue = ~sValueOut.i8uValue;
														// PiBridge - set output pin
					i = piControlSetBitValue(&sValueOut);
					printf("%-32s : %s \n", pchOutput, sValueOut.i8uValue ? "On" : "Off");
					if(0 != i)
					{
						fprintf(stderr, "Error: piControlSetBitValue() returned %d\n", i);
						return -1;
					}
				}
			}
		}
		
		iLastInputValue = sValueIn.i8uValue;			// remember last input value
	}

	return 0;
}
