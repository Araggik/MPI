#include <iostream>
#include "mpi.h"
#include <iomanip>

using namespace std;

//Task 6
void My_scatter(void *sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
	int rank,size;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	MPI_Status status;
	MPI_Request req;
	if (rank == root)
	{
		for (int i=0;i<size;i++)
		{			
			char* sbuf = static_cast<char*>(sendbuf);
		    if(i!=root) MPI_Send(sbuf+i*sendcount, sendcount, sendtype, i, 0, comm);
			else
			{
				char* rbuf = static_cast<char*>(recvbuf);
				for (int j = 0; j < recvcount; j++)
				{
					rbuf[j] = sbuf[i*sendcount+j];
				}
			}
		}
	}
	else
	{
		MPI_Recv(recvbuf, recvcount, recvtype, root, 0, comm, &status);
	}
}

int main(int argc, char** argv)
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	//Task1
	/*
	char msg[13] = "Hello otherA";
	char rmsg[13] ="hi";
	if (rank == 0)
	{
		MPI_Send(&msg, 13, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		cout << "I'm rank " << rank << " Send msg: " <<msg;
	}
	else if (rank == 1){
		MPI_Recv(&rmsg, 13, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		rmsg[11] = 'B';
		cout << "I'm rank " << rank << " Recieve msg: " << rmsg;
	}*/
	


	//Task2
	
	/*it msg = 0;
	int n = 2;
	for (int i = 0; i < n; i++)
	{
		if (rank == 1)
		{
			MPI_Send(&msg, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
			MPI_Recv(&msg, 1, MPI_INT, (size-2)+(size+1)%2, 0, MPI_COMM_WORLD, &status);
			msg++;
			cout << "I'm rank " << rank << " Recieve msg: " << msg << " " <<endl;

		}
		else if (rank == (size - 2) + (size + 1) % 2 )
		{
			MPI_Recv(&msg, 1, MPI_INT, rank - 2, 0, MPI_COMM_WORLD, &status);
			msg++;
			cout << "I'm rank " << rank << " Recieve msg: " << msg << " "<<endl;
			MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		}
		else if (rank % 2 != 0)
		{
			MPI_Recv(&msg, 1, MPI_INT, rank - 2, 0, MPI_COMM_WORLD, &status);
			msg++;
			cout << "I'm rank " << rank << " Recieve msg: " << msg << " "<<endl;
			MPI_Send(&msg, 1, MPI_INT, rank + 2, 0, MPI_COMM_WORLD);
		}
	}*/
	


	//Task3
	/*char msg[6] = "Hello";
	int count_msg = 100000;
	double start, end;
	if (rank == 0)
	{
		start = MPI_Wtime();
		for (int i = 1; i <= count_msg; i++)
			MPI_Send(&msg, 6, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		end= MPI_Wtime();
		cout << "avg time for MPI_Send: " << (end - start)/count_msg<<" ";

		start = MPI_Wtime();
		for (int i = 1; i <= count_msg; i++)
			MPI_Ssend(&msg, 6, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		end = MPI_Wtime();
		cout << "avg time for MPI_Ssend: " << (end - start) / count_msg;
	}
	else
	{
		for (int i = 1; i <= count_msg; i++)
			MPI_Recv(&msg, 6, MPI_CHAR, 0, 0, MPI_COMM_WORLD,&status);

		for (int i = 1; i <= count_msg; i++)
			MPI_Recv(&msg, 6, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
	}*/


	//Task4
	//char msg[6] = "Hello";
	//int count_msg = 100000;
	//double start, end;
	//if (rank == 0)
	//{
	//	int b_size=count_msg * (sizeof(char) * 6 + MPI_BSEND_OVERHEAD);
	//	void* buf=malloc(b_size);
	//	MPI_Buffer_attach(buf, b_size);

	//	start = MPI_Wtime();
	//	for (int i = 1; i <= count_msg; i++)
	//		MPI_Bsend(&msg, 6, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
	//	end= MPI_Wtime();

	//	MPI_Buffer_detach(&buf, &b_size);
	//	free(buf);
	//	cout << "avg time for MPI_Bsend: " << (end - start)/count_msg<<" ";		
	//}
	//else
	//{
	//	for (int i = 1; i <= count_msg; i++)
	//		MPI_Recv(&msg, 6, MPI_CHAR, 0, 0, MPI_COMM_WORLD,&status);
	//}


	//Task5
	/*int count_msg = 100000;
	int* msg = new int[count_msg];
	MPI_Request* reqs = new MPI_Request[count_msg];
	MPI_Status* statuses = new MPI_Status[count_msg];
	double start, end;
	for (int i = 0; i < count_msg; i++)
	{
		msg[i] = 0;
	}
	if (rank == 0)
	{		
		start = MPI_Wtime();
		for (int i = 0; i < count_msg; i++)
		{
			MPI_Isend(&msg[i], 1, MPI_INT, 1, i, MPI_COMM_WORLD, &reqs[i]);
		}
		MPI_Waitall(count_msg, reqs,statuses);
		end= MPI_Wtime();
		cout << "avg time for MPI_Isend: " << (end - start)/count_msg<<" ";
	}
	else
	{
		for (int i = 0; i < count_msg; i++)
		{
			MPI_Irecv(&msg[i], 1, MPI_INT, 0, i, MPI_COMM_WORLD, &reqs[i]);
		}
		MPI_Waitall(count_msg, reqs, statuses);
	}
	delete[] reqs;
	delete[] statuses;
	delete[] msg;*/

	//Task6	
	/*char sbuf[7] = "ABCDEF";
	char rbuf[3]="AB";
	double start, end;

	start = MPI_Wtime();
	MPI_Scatter(&sbuf, 2, MPI_CHAR, &rbuf, 2, MPI_CHAR, 1, MPI_COMM_WORLD);
	end = MPI_Wtime();
	cout << "I'm rank " << rank << " rbuf:" << rbuf << " time MPI_Scatter:" <<end - start<<" ";

	start = MPI_Wtime();
	My_scatter(&sbuf, 2, MPI_CHAR, &rbuf, 2, MPI_CHAR, 1, MPI_COMM_WORLD);	
	end = MPI_Wtime();
	cout << "I'm rank " << rank << " rbuf:" << rbuf << " time My_Scatter:" << end - start<< " ";*/
	
    //Task7

	MPI_Finalize();
}


