//Paulina Vara Figueroa

#include <stdio.h> //entrada y salida del programa
#include <stdlib.h> //system() y num aleatorios
#include <time.h> // para la hora del sistema

#define SIZE 200000 //Tamaño del arreglo a ordenar
#define SIZE2 150000//75% DE SIZE / Para dimensión de la cubeta
#define INC 5 // Número de incrementos en shell sort
#define RANGO 1000 //Rango para numeros aleatorios + 1 Llenado inicial del arreglo

int bc[SIZE2][10]; //Matriz de bucket sort

//Funciones de Apoyo
void generarNumeros(int mat[], int dim)
{
	int i;
	srand(25);
	for (i = 0; i < SIZE; i++) //Llenado del arreglo
		mat[i] = rand() % RANGO;
}

void imprimeArreglo(int arr[], int dim)
{
	int i;
	for (i = 0; i < dim; i++) //Mostrar el arreglo
		printf("%d, ", arr[i]);
	printf("\n\n");
}
void devolverCubeta(int arr[], int dim) //AYUDA EN BUCKETSORT
{
	int m, i, k;
	m = 0;
	for (i = 0; i < 10; i++)
	{
		for (k = 0; (k < dim && bc[k][i] != -1); k++)
		{
			arr[m] = bc[k][i];
			m++;
		}
	}
}
void limpiarCubeta(int j[], int dim) //AYUDA EN BUCKETSORT
{
	int i, k;
	for (i = 0; i < dim; i++)
	{
		for (k = 0; k < 10; k++)
			bc[i][k] = -1;
	}
	for (i = 0; i < 10; i++)
		j[i] = 0;
}
int particion(int arr[], int linf, int lsup)
{
	int a /*valor del pivote*/, abajo, temp, arriba;
	a = arr[linf];
	arriba = lsup;
	abajo = linf;
	while (abajo < arriba)
	{
		while (arr[abajo] <= a && abajo < lsup)
			abajo += 1;
		while (arr[arriba] > a)
			arriba -= 1;
		if (abajo < arriba)
		{
			temp = arr[abajo];
			arr[abajo] = arr[arriba];
			arr[arriba] = temp;
		}
	}
	arr[linf] = arr[arriba];
	arr[arriba] = a;
	return arriba;
}
void guardarEnCubeta(int arr[], int cont[], int caso, int i)//AYUDA EN BUCKET SORT
{
	int a, pos;
	int k, j;
	a = arr[i];
	switch (caso)
	{
	case 1:
		pos = a % 10;
		break;
	case 2:
		pos = ((a % 100) - (a % 10)) / 10;
		break;
	case 3:
		if (a >= 100)
			pos = (a - (a % 100)) / 100;
		else
			pos = 0;
		break;
	}
	bc[cont[pos]][pos] = a;
	cont[pos]++;
}

//Funciones de ordenamiento
void burbuja(int arr[], int dim)
{
	int i, j, temp;
	for (i = 0; i < dim; i++)//1
	{
		for (j = i + 1; j < dim; j++)//2
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}//if
		}//f2
	}//f1
	//printf("\tBUBBLE SORT\n\n");
	//imprimeArreglo(arr, dim);
}
void selection_sort(int arr[], int dim)
{
	int i, j, j2 = 0, temp2 = 5000;
	for (i = 0; i < dim; i++)//1
	{
		temp2 = arr[i];
		for (j = i + 1; j < dim; j++)//2
		{
			if (temp2 > arr[j])
			{
				temp2 = arr[j];
				j2 = j;
			}//if
		}//f2

		if (temp2 != arr[i])
		{
			arr[j2] = arr[i];
			arr[i] = temp2;
		}//if
	}//f1
	//printf("\tSELECTION SORT\n\n");
	//imprimeArreglo(arr, dim);
}
void insert_sort(int arr[], int dim)
{
	int y, i, k;
	for (k = 1; k < dim; k++)
	{
		y = arr[k];
		for (i = k - 1; i >= 0 && y < arr[i]; i--)
			arr[i + 1] = arr[i];
		arr[i + 1] = y;
	}
	//printf("\tINSERT SORT\n\n");
	//imprimeArreglo(arr, dim);
}
void shell_sort(int arr[], int dim, int inc[], int numinc)//(int arr[], int dim)
{
	int y, span/*incremento actual*/, j, k, incr/*contador de incrementos*/;
	for (incr = numinc-1; incr > 0; incr--)
	{
		span = inc[incr];
		for (j = span; j < dim; j++)
		{
			y = arr[j];
			for (k = j - span; k >= 0 && y < arr[k]; k -= span)
				arr[k + span] = arr[k];
			arr[k + span] = y;
		}
	}
	//printf("\tSHELL SORT\n\n");
	//imprimeArreglo(arr, dim);
}
void bucket_sort(int arr[], int dim)
{
	int i, j[10], pos;

	//INICIALIZAR CUBETA Y CONTADOR
	limpiarCubeta(j, SIZE2);

	//GUARDAR POR UNIDADES EN CUBETA - 1
	for (i = 0; i < dim; i++)
		guardarEnCubeta(arr, j, 1, i);

	devolverCubeta(arr, dim);
	limpiarCubeta(j, SIZE2);

	//GUARDAR POR DECENAS EN CUBETA - 2
	for (i = 0; i < dim; i++)
		guardarEnCubeta(arr, j, 2, i);

	devolverCubeta(arr, dim);
	limpiarCubeta(j, SIZE2);

	//GUARDAR POR CENTENAS EN CUBETA - 3
	for (i = 0; i < dim; i++)
		guardarEnCubeta(arr, j, 3, i);

	devolverCubeta(arr, dim);
	//printf("\tBUCKET SORT\n\n");
	//imprimeArreglo(arr, dim);
}
void cuentaDeDistribuciones(int arr[], int dim)
{
	int cont[RANGO] = { 0 }, i, j = 0, cont2 = 0;
	for (i = 0; i < dim; i++)
	{
		cont[arr[i]]++;
	}
	cont2 = 0;
	i = 0;
	for (i = 0; i < RANGO; i++)
	{
		cont2 += cont[i];
		while (j < cont2)
		{
			arr[j] = i;
			j++;
		}
	}
	//printf("\tCUENTA DE DISTRIBUCIONES\n\n");
	//imprimeArreglo(arr, dim);
}
void quick(int arr[], int linf, int lsup)
{
	int j;
	if (linf >= lsup)
		return;
	j = particion(arr, linf, lsup);
	quick(arr, linf, j - 1);//Recursividad al lado izquierdo del arreglo
	quick(arr, j + 1, lsup);//Recursividad al lado derecho del arreglo
}


int main()
{
	int arreglo[SIZE], inicio, fin, tiemp[6], orden[6], incremento[INC], i, j, k[6] = { 0 };

	//---------------------------------------------------ORDENAMIENTOS--------------------------------------------------------
	printf("\n\n\tEvaluacion de algoritmos de ordenamiento con %d numeros\n\n\n",SIZE);

	generarNumeros(arreglo,SIZE);
	printf("\t\tIniciando algoritmo Bubble Sort.......");
	inicio = time(0);
	burbuja(arreglo,SIZE);
	fin = time(0);
	printf("Terminado\n\n");
	orden[0] = tiemp[0]=fin-inicio;

	generarNumeros(arreglo,SIZE);
	printf("\t\tIniciando algoritmo Selection Sort....");
	inicio = time(0);
	selection_sort(arreglo,SIZE);
	fin = time(0);
	printf("Terminado\n\n");
	orden[1] = tiemp[1]=fin-inicio;

	generarNumeros(arreglo,SIZE);
	printf("\t\tIniciando algoritmo Insert Sort.......");
	inicio = time(0);
	insert_sort(arreglo, SIZE);
	fin = time(0);
	printf("Terminado\n\n");
	orden[2] = tiemp[2]=fin-inicio;
	
	generarNumeros(arreglo, SIZE);
	printf("\t\tIniciando algoritmo Shell Sort........");
	inicio = time(0);
	for (i = 0; i < INC; i++)
		incremento[i] = i + 1;
	shell_sort(arreglo, SIZE, incremento, INC);
	fin = time(0);
	printf("Terminado\n\n");
	orden[3] = tiemp[3] = fin - inicio;

	generarNumeros(arreglo, SIZE);
	printf("\t\tIniciando algoritmo Bucket Sort.......");
	inicio = time(0);
	bucket_sort(arreglo, SIZE);
	fin = time(0);
	printf("Terminado\n\n");
	orden[4] = tiemp[4] = fin - inicio;

	generarNumeros(arreglo, SIZE);
	printf("\t\tIniciando algoritmo Quick Sort........");
	inicio = time(0);
	quick(arreglo, 0, SIZE - 1);
	fin = time(0);
	printf("Terminado\n\n");
	orden[5] = tiemp[5] = fin - inicio;

	//IMPRESIÓN EN ORDEN DE TIEMPO DE LOS ALGORITMOS DE ORDENAMIENTO
	cuentaDeDistribuciones(orden, 6);
	i = 0;
	printf("    ---------------------------------------------------------------\n");
	printf("\n\tRESULTADO DE LA EVALUACION POR TIEMPO DE LOS ALGORITMOS\n");
	printf("\n\n\t     Algoritmo de Ordenamiento   |     Tiempo (s)\n");
	while (i < 6)
	{
		for (j = 0; j < 6; j++)
		{
			if ((orden[i] == tiemp[j]) && k[j] == 0)
			{
				printf("\n\t\t%d.    ", i+1);
				switch (j)
				{
				case 0:
					printf("Bubble Sort        | %5d segundos", tiemp[0]);
					break;
				case 1:
					printf("Selection Sort     | %5d segundos", tiemp[1]);
					break;
				case 2:
					printf("Insert Sort        | %5d segundos", tiemp[2]);
					break;
				case 3:
					printf("Shell Sort         | %5d segundos", tiemp[3]);
					break;
				case 4:
					printf("Bucket Sort        | %5d segundos", tiemp[4]);
					break;
				case 5:
					printf("Quick Sort         | %5d segundos", tiemp[5]);
					break;
				}
				k[j] = 1;
				j = 6;
			}
		}
		i++;
	}
	printf("\n\n\n");
	system("pause");
	return 0;
}