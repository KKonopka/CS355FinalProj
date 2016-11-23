#include <stdio.h>
//#include <Python.h>
main(int av, char* args[])
{
	FILE* file;
	Py_Initialize();
	file = fopen("camera.py", "r");
	PyRun_SimpleFile(file, "camera.py");
	Py_Finalize();
}