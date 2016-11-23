#include <stdio.h>
//#include <Python.h

//gcc  $(python - config --includes --libs) main.c
main(int av, char* args[])
{
	FILE* file;
	
	int Done = 0;
	while (Done)
	{
		//Take Picture
		Py_Initialize();
		file = fopen("Sensorss.py", "r");
		PyRun_SimpleFile(file, "Sensorss.py");
		Py_Finalize();

		//Prompt for Continue
		printf("Picture Taken, Continue(y/n)? ");
		int iTest = getchar();

		//Process Result
		if (iTest == 'n')
		{
			Done = 1;
		}
		putchar(iTest);
		printf("\n");
	}
	
}