#include "GameLife/include/Headings.h"
#include "GameLife/src/Services/OS.h"

// #define DEBUG

using namespace std;

class Field
{
    private:
        int ROWS;
        int COLS;
        double cellRare;

        char **field;
        
        char GetRandomCell()
        {
            int rare = rand() % 100;

            return rare < cellRare * 100 ? '#' : '-';
        }

    public:
        Field(int ROWS, int COLS, double cellRare = 0.25)
        {
            this->ROWS = ROWS;
            this->COLS = COLS;
            this->cellRare = cellRare;

            field = new char* [ROWS];
            for(int i = 0; i < ROWS; i++)
            {
                field[i] = new char[COLS];
            }
        }

        Field();

        ~Field()
        {
            for(int i = 0; i < ROWS; i++)
            {
                delete [] field[i];
                #ifdef DEBUG
                    cout << i << " Память очищена: " << &field[i] << endl;
                #endif
            }

            delete[] field;

            #ifdef DEBUG
                cout << " Память очищена: "<< &field << endl;
            #endif
        }

        void SetCell(int x, int y, char status) { field[x][y] = status; }
        char GetCell(int x, int y) { return field[x][y]; }

        char** GetField() { return field; }

        void ShowField()
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

        void GenerateField(bool isDead = true) 
        {
            for(int i = 0; i < ROWS; i++)
            {
                for(int j = 0; j < COLS; j++)
                {
                    field[i][j] = isDead ? '-' : '#';
                }
            }
        }

        void GenerateRandomField()
        {
            for(int i = 0; i < ROWS; i++)
            {
                for(int j = 0; j < COLS; j++)
                {
                    field[i][j] = GetRandomCell();
                }
            }
        }
};