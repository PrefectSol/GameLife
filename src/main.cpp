#include "GameLife/include/Headings.h"
#include "Field.h"

// #define DEBUG

using namespace std;

class Startup
{
	private:
		int ROWS;
        int COLS;

		char** firstGen;
		char** nextGen;

		int countGen = 0;
		bool isChange = false;

		void SetCell(char** field, int x, int y, char status) { field[x][y] = status; }
        char GetCell(char** field,int x, int y) { return field[x][y]; }

		int GetNumberOfNeighbors(char** field, int x, int y)
		{
			int count = 0;
			for(int i = x - 1; i <= x + 1; i++)
			{
				for(int j = y - 1; j <= y + 1; j++)
				{
					if (i == x && j == y) { continue; }

					if (GetCell(field, i, j) == '#') { count++; }
				}
			}

			return count;
		}

		void ShowField(char** field)
        {
            GetOS() == Linux ? system("clear") : system("cls");

            for(int i = 0; i < ROWS; i++)
            {   
                for(int j = 0; j < COLS; j++)
                {
                    cout << field[i][j] << "  ";
                }

                cout << endl;
            }
        }

		void CopyField(char** fromF, char** inF)
		{
			for(int i = 0; i < ROWS; i++)
            {   
                for(int j = 0; j < COLS; j++)
                {
                    inF[i][j] = fromF[i][j];
                }
            }
		}

		void ScreenUpdate()
		{
			ShowField(firstGen);

			#ifdef __linux
				#include <unistd.h>
				sleep(1);
			#elif defined _WIN32
				#include <windows.h>
				Sleep(5000);
			#elif defined _WIN64
				#include <windows.h>
				Sleep(5000);
			#endif
		}

		bool FieldIsDead()
		{
			bool isDead = true;
			for(int i = 1; i < ROWS - 1; i++)
            {   
                for(int j = 1; j < COLS - 1; j++)
                {
                    if(firstGen[i][j] == '#') { return false; }
                }
            }

			return isDead;
		}

		void CheckChange()
		{
			isChange = true;
			for(int i = 1; i < ROWS - 1; i++)
            {   
                for(int j = 1; j < COLS - 1; j++)
                {
                    if(firstGen[i][j] != nextGen[i][j]) { isChange = false; }
                }
            }
		}

		void GameUpdate()
		{
			if(FieldIsDead())
			{
				ShowField(firstGen);
				cout << "The field is dead." << " Gen: " << countGen << endl;
			}
			else if (isChange)
			{
				ShowField(firstGen);
				cout << "The field does not change." << " Gen: " << countGen << endl;
			}
			else
			{
				Start();
			}
		}

	public:
		Startup(int ROWS, int COLS, Field& field)
		{
			this->ROWS = ROWS;
            this->COLS = COLS;
			
			firstGen = new char* [ROWS];
            for(int i = 0; i < ROWS; i++)
            {
                firstGen[i] = new char[COLS];
            }

			#ifdef DEBUG
				cout << "Created: " << &firstGen << endl;
			#endif // DEBUG
			
			nextGen = new char* [ROWS];
            for(int i = 0; i < ROWS; i++)
            {
                nextGen[i] = new char[COLS];
            }
			
			#ifdef DEBUG
				cout << "Created: " << &nextGen << endl;
			#endif // DEBUG
		
			CopyField(field.GetField(), firstGen);
			CopyField(firstGen, nextGen);

			Start();
		}

		~Startup()
        {
			for(int i = 0; i < ROWS; i++)
            {
                delete [] firstGen[i];
                #ifdef DEBUG
                    cout << i << " Deleted: " << &firstGen[i] << endl;
                #endif
            }

            delete[] firstGen;

            #ifdef DEBUG
                cout << " Deleted: "<< &firstGen << endl;
            #endif
		
			for(int i = 0; i < ROWS; i++)
            {
                delete [] nextGen[i];
                #ifdef DEBUG
                    cout << i << " Deleted: " << &nextGen[i] << endl;
                #endif
            }

            delete[] nextGen;

            #ifdef DEBUG
                cout << " Deleted: "<< &nextGen << endl;
            #endif
        }

	private:
		void Start()
		{
			ScreenUpdate();

			for(int x = 1; x < ROWS - 1; x++){
				for(int y = 1; y < COLS - 1; y++){
					int countNeighbors = GetNumberOfNeighbors(firstGen, x, y);

					if (GetCell(firstGen, x, y) == '-' && countNeighbors == 3)
					{
						SetCell(nextGen, x, y, '#');
					}
					
					else if (GetCell(firstGen, x, y) == '#' && (countNeighbors == 2 || countNeighbors == 3))
					{
						SetCell(nextGen, x, y, '#');
					}

					else if (GetCell(firstGen, x, y) == '#' && (countNeighbors < 2 || countNeighbors > 3))
					{
						SetCell(nextGen, x, y, '-');
					}
				}
			}
			
			CheckChange();

			CopyField(nextGen, firstGen);
			countGen++;
			
			GameUpdate();
		}
};

int main()
{
	srand(time(NULL));
	
	const int ROWS = 20;
	const int COLS = 20;
	const double cellRare = 0.5;

	Field field(ROWS, COLS, 0.2);

	// Field config =======

	field.GenerateRandomField();
	// field.GenerateField();

	// field.SetCell(3, 6, '#');
	// field.SetCell(3, 7, '#');
	// field.SetCell(4, 6, '#');

    // ====================

	Startup start(ROWS, COLS, field);

	return 0;
}