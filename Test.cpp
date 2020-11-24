#include <iostream>
#include "mpi.h"
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	//Factorial
	double fact2, fact4, fact8,
		polufact5_6, polufact5_7, polufact9_10,
		polufact9_11, polufact13_14, polufact13_15, polufact9_12;
	int nums1[] = { 0,1,2,3 }, nums2[] = { 4,5,6,7 };

	MPI_Group group1, group2, group_world;
	MPI_Comm comm1, comm2;
	//Получение группы из коммуникатора MPI_COMM_WORLD
	MPI_Comm_group(MPI_COMM_WORLD, &group_world);
	//Создание групп на основе группы group_world
	MPI_Group_incl(group_world, 4, nums1, &group1);
	MPI_Group_incl(group_world, 4, nums2, &group2);
	//Создание коммуникаторов на основе MPI_COMM_WORLD для групп
	MPI_Comm_create(MPI_COMM_WORLD, group1, &comm1);
	MPI_Comm_create(MPI_COMM_WORLD, group2, &comm2);

	if (rank == 0)
	{
		fact2 = 1 * 2;
		MPI_Send(&fact2, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);

		double fact3 = fact2 * 3;
		MPI_Bcast(&fact4, 1, MPI_DOUBLE, 1, comm1);

		double fact5 = fact4 * 5;
		MPI_Bcast(&fact8, 1, MPI_DOUBLE, 3, MPI_COMM_WORLD);

		double fact9 = fact8 * 9;
		cout << " 2!= " << fixed << setprecision(0) << fact2 << endl;
		cout << " 3!= " << fixed << setprecision(0) << fact3 << endl;
		cout << " 5!= " << fixed << setprecision(0) << fact5 << endl;
		cout << " 9!= " << fixed << setprecision(0) << fact9 << endl;
	}
	else if (rank == 1)
	{
		double polufact34 = 3 * 4;
		MPI_Recv(&fact2, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);

		fact4 = fact2 * polufact34;
		MPI_Bcast(&fact4, 1, MPI_DOUBLE, 1, comm1);
		MPI_Recv(&polufact5_6, 1, MPI_DOUBLE, 2, 1, MPI_COMM_WORLD, &status);

		double fact6 = fact4 * polufact5_6;
		MPI_Bcast(&fact8, 1, MPI_DOUBLE, 3, MPI_COMM_WORLD);
		MPI_Recv(&polufact9_10, 1, MPI_DOUBLE, 4, 1, MPI_COMM_WORLD, &status);

		double fact10 = fact8 * polufact9_10;
		cout << " 4!= " << fixed << setprecision(0) << fact4 << endl;
		cout << " 6!= " << fixed << setprecision(0) << fact6 << endl;
		cout << "10!= " << fixed << setprecision(0) << fact10 << endl;
	}
	else if (rank == 2)
	{
		polufact5_6 = 5 * 6;
		MPI_Send(&polufact5_6, 1, MPI_DOUBLE, 3, 1, MPI_COMM_WORLD);

		polufact5_7 = polufact5_6 * 7;
		MPI_Bcast(&fact4, 1, MPI_DOUBLE, 1, comm1);
		MPI_Send(&polufact5_6, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);

		double fact7 = fact4 * polufact5_7;
		MPI_Bcast(&fact8, 1, MPI_DOUBLE, 3, MPI_COMM_WORLD);
		MPI_Recv(&polufact9_11, 1, MPI_DOUBLE, 4, 1, MPI_COMM_WORLD, &status);

		double fact11 = fact8 * polufact9_11;
		cout << " 7!= " << fixed << setprecision(0) << fact7 << endl;
		cout << "11!= " << fixed << setprecision(0) << fact11 << endl;
	}
	else if (rank == 3)
	{
		double polufact78 = 7 * 8;
		MPI_Recv(&polufact5_6, 1, MPI_DOUBLE, 2, 1, MPI_COMM_WORLD, &status);

		double polufact5_8 = polufact5_6 * polufact78;
		MPI_Bcast(&fact4, 1, MPI_DOUBLE, 1, comm1);

		fact8 = fact4 * polufact5_8;
		MPI_Bcast(&fact8, 1, MPI_DOUBLE, 3, MPI_COMM_WORLD);
		MPI_Recv(&polufact9_12, 1, MPI_DOUBLE, 4, 1, MPI_COMM_WORLD, &status);

		double fact12 = fact8 * polufact9_12;
		cout << " 8!= " << fixed << setprecision(0) << fact8 << endl;
		cout << "11!= " << fixed << setprecision(0) << fact12 << endl;
	}
	else if (rank == 4)
	{
		polufact9_10 = 9 * 10;
		MPI_Send(&polufact9_10, 1, MPI_DOUBLE, 5, 1, MPI_COMM_WORLD);

		polufact9_11 = polufact9_10 * 11;
		MPI_Bcast(&polufact9_12, 1, MPI_DOUBLE, 1, comm2);

		double polufact9_13 = polufact9_12 * 13;
		MPI_Bcast(&fact8, 1, MPI_DOUBLE, 3, MPI_COMM_WORLD);
		MPI_Send(&polufact9_10, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
		MPI_Send(&polufact9_11, 1, MPI_DOUBLE, 2, 1, MPI_COMM_WORLD);

		double fact13 = fact8 * polufact9_13;
		cout << "13!= " << fixed << setprecision(0) << fact13 << endl;
	}
	else if (rank == 5)
	{
		double polufact11_12 = 11 * 12;
		MPI_Recv(&polufact9_10, 1, MPI_DOUBLE, 4, 1, MPI_COMM_WORLD, &status);

		polufact9_12 = polufact9_10 * polufact11_12;
		MPI_Bcast(&polufact9_12, 1, MPI_DOUBLE, 1, comm2);
		MPI_Recv(&polufact13_14, 1, MPI_DOUBLE, 6, 1, MPI_COMM_WORLD, &status);

		double polufact9_14 = polufact9_12 * polufact13_14;
		MPI_Bcast(&fact8, 1, MPI_DOUBLE, 3, MPI_COMM_WORLD);
		MPI_Send(&polufact9_12, 1, MPI_DOUBLE, 3, 1, MPI_COMM_WORLD);

		double fact14 = fact8 * polufact9_14;
		cout << "14!= " << fixed << setprecision(0) << fact14 << endl;
	}
	else if (rank == 6)
	{
		polufact13_14 = 13 * 14;
		MPI_Send(&polufact13_14, 1, MPI_DOUBLE, 7, 1, MPI_COMM_WORLD);

		polufact13_15 = polufact13_14 * 15;
		MPI_Bcast(&polufact9_12, 1, MPI_DOUBLE, 1, comm2);
		//MPI_Send(&polufact13_15, 1, MPI_DOUBLE, 5, 1, MPI_COMM_WORLD);	

		double polufact9_15 = polufact9_12 * polufact13_15;
		MPI_Bcast(&fact8, 1, MPI_DOUBLE, 3, MPI_COMM_WORLD);

		double fact15 = fact8 * polufact9_15;
		cout << "14!= " << fixed << setprecision(0) << fact15 << endl;
	}
	else if (rank == 7)
	{
		double polufact15_16 = 15 * 16;
		MPI_Recv(&polufact13_14, 1, MPI_DOUBLE, 6, 1, MPI_COMM_WORLD, &status);

		double polufact13_16 = polufact13_14 * polufact15_16;
		MPI_Bcast(&polufact9_12, 1, MPI_DOUBLE, 1, comm2);

		double polufact9_16 = polufact9_12 * polufact13_16;
		MPI_Bcast(&fact8, 1, MPI_DOUBLE, 3, MPI_COMM_WORLD);

		double fact16 = fact8 * polufact9_16;
		cout << "16!= " << fixed << setprecision(0) << fact16 << endl;
	}


	MPI_Finalize();
}