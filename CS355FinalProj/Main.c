#include <stdio.h>
//#include <Python.h>
main(int av, char* args[])
{
	FILE* file;
	
	int Done = 0;
	while (Done)
	{
		//Take Picture
		Py_Initialize();
		file = fopen("camera.py", "r");
		PyRun_SimpleFile(file, "camera.py");
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