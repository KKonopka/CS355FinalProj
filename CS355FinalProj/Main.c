#include <stdio.h>
#include <Python.h>
#include <my_global.h>
#include <mysql.h>

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


		//Process Picture
		FILE *fp = fopen("image.jpg", "rb");
		if (fp == NULL)
		{
			fprintf(stderr, "cannot open image file\n");
			exit(1);
		}
		fseek(fp, 0, SEEK_END);
		if (ferror(fp)) {
			fprintf(stderr, "fseek() failed\n");
			int r = fclose(fp);
			if (r == EOF) {
				fprintf(stderr, "cannot close file handler\n");
			}
			exit(1);
		}
		int flen = ftell(fp);
		if (flen == -1) {
			perror("error occurred");
			int r = fclose(fp);
			if (r == EOF) {
				fprintf(stderr, "cannot close file handler\n");
			}
			exit(1);
		}
		fseek(fp, 0, SEEK_SET);
		if (ferror(fp)) {

			fprintf(stderr, "fseek() failed\n");
			int r = fclose(fp);

			if (r == EOF) {
				fprintf(stderr, "cannot close file handler\n");
			}

			exit(1);
		}

		char data[flen + 1];
		int size = fread(data, 1, flen, fp);

		if (ferror(fp)) {

			fprintf(stderr, "fread() failed\n");
			int r = fclose(fp);

			if (r == EOF) {
				fprintf(stderr, "cannot close file handler\n");
			}

			exit(1);
		}

		int r = fclose(fp);

		if (r == EOF) {
			fprintf(stderr, "cannot close file handler\n");
		}

		MYSQL *con = mysql_init(NULL);

		if (con == NULL)
		{
			fprintf(stderr, "mysql_init() failed\n");
			exit(1);
		}
		if (mysql_real_connect(con, "localhost", "root", "pass*",
			"imagedb", 0, NULL, 0) == NULL)
		{
			finish_with_error(con);
		}

		char chunk[(2 * size) + 1];
		mysql_real_escape_string(con, chunk, data, size);

		char *st = "INSERT INTO images(img) VALUES('%s')";
		size_t st_len = strlen(st);

		char query[st_len + 2 * size + 1];
		int len = snprintf(query, st_len + 2 * size + 1, st, chunk);

		if (mysql_real_query(con, query, len))
		{
			fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
			exit(1);
		}

		mysql_close(con);
		exit(0);

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