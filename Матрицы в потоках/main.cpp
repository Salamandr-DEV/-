#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

void Print(const vector<vector<int>> C)
{
	for (auto & row : C)
	{
		for (auto & elem : row)
		{
			cout << elem << " ";
		}
		cout << endl;
	}
}

void Multiply(const vector<vector<int>> A, const vector<vector<int>> B, vector<vector<int>> &C)
{
	int temp = 0;

	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < B[0].size(); j++)
		{
			temp = 0;
			for (int k = 0; k < A[0].size(); k++)
			{
				C[i][j] = A[i][k] * B[k][j];
				temp = temp + C[i][j];
			}
			C[i][j] = temp;
		}
	}
}

void Multiply2(const vector<vector<int>> A, const vector<vector<int>> B, vector<vector<int>> &C)
{
	int temp = 0;

	thread T1([=, &C, &temp]()
	{
		for (int i = 0; i < A.size() / 2; i++)
		{
			for (int j = 0; j < B[0].size(); j++)
			{
				temp = 0;
				for (int k = 0; k < A[0].size(); k++)
				{
					C[i][j] = A[i][k] * B[k][j];
					temp = temp + C[i][j];
				}
				C[i][j] = temp;
			}
		}
	});

	int temp_2 = 0;

	thread T2([=, &C, &temp_2]()
	{
		for (int i = A.size() / 2; i < A.size(); i++)
		{
			for (int j = 0; j < B[0].size(); j++)
			{
				temp_2 = 0;
				for (int k = 0; k < A[0].size(); k++)
				{
					C[i][j] = A[i][k] * B[k][j];
					temp_2 = temp_2 + C[i][j];
				}
				C[i][j] = temp_2;
			}
		}
	});

	T1.join();
	T2.join();
}



int main()
{
	int rows, cols;

	cout << "rows - ";
	cin >> rows;
	cout << "cols - ";
	cin >> cols;

	vector<vector<int>> A, B, C;

	A.resize(rows);
	for (auto & row : A)
	{
		row.resize(cols);
		for (auto & elem : row)
		{
			elem = rand() % 10;
			//cout << elem << " ";
		}
		//cout << endl;
	}

	//cout << " ==================================================== " << endl;

	B.resize(cols);
	for (auto & row : B)
	{
		row.resize(rows);
		for (auto & elem : row)
		{
			elem = rand() % 10;
			//cout << elem << " ";
		}
		//cout << endl;
	}

	//cout << " ==================================================== " << endl;

	C.resize(rows);
	for (auto & row : C)
	{
		row.resize(rows);
	}

	auto start = std::chrono::high_resolution_clock::now();

	Multiply2(A, B, C);

	auto finish = std::chrono::high_resolution_clock::now();

	auto t = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

	cout << "t = " << t << endl;

	//Print(C);

	system("pause");
	return 0;
}