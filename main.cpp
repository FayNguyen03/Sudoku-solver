#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include <vector>
using namespace std;
#define empty 0
bool isUsedBox(int ** grid, int boxBeginrow, int boxBegincol,int num,int n);
bool isUsedRow(int ** grid, int row, int num,int n);
bool isUsedCol(int ** grid, int col,int num,int n);
bool isEmpty(int **grid,int &row, int &col, int n);
bool SolveSudoku(int **grid, int n);
bool isGridSafe(int ** grid, int row,int col,int num,int n);

/*Check for entries have no values*/

bool isEmpty(int **grid,int &row, int &col, int n){
    for(row=0;row<n;row++)
        for(col=0;col<n;col++){
            if (grid[row][col]==empty)
                {
                return true;}

        }
    return false;

}

/*Solving the sudoku with the backtracking algorithm*/
bool SolveSudoku(int **grid,int n)
{
    int row, col;
    if (!isEmpty(grid,row,col,n))//&row assignd the value of empty row
       return true;

    for(int i=1;i<=n;i++){
        if(isGridSafe(grid,row,col,i,n)) {
                grid[row][col]=i;
                if(SolveSudoku(grid,n))return true;
                else grid[row][col]=empty;}
    }
    return false;
}


/*Check the num used or not in row*/
bool isUsedRow(int **grid,int row, int num,int n){
    for(int i=0;i<n;i++){
        if(grid[row][i]==num){
            return true;
            break;
        }

    }
    return false;
}

/*Check the num used or not in col*/
bool isUsedCol(int **grid,int col, int num,int n){
    for(int i=0;i<n;i++){
        if(grid[i][col]==num){
            return true;
            break;
        }

    }
    return false;

}

/*Check the num used or not in box*/
bool isUsedBox(int **grid,int boxBeginrow,int boxBegincol, int num, int n){
    int j,k;
    switch (n){
        case 4:
            j=k=2;
            break;
        case 6:
            j=2;
            k=3;
            break;
        case 9:
            j=k=3;
            break;

    }
    for(int row=0;row<j;row++)
        for(int col=0;col<k;col++){
        if(grid[row+boxBeginrow][col+boxBegincol]==num)
            return true;
        }
    return false;

    }


bool isGridSafe(int ** grid, int row,int col,int num,int n){
    int j,k;
    switch (n){
        case 4:
            j=2;
            k=2;
            break;
        case 6:
            j=2;
            k=3;
            break;
        case 9:
            j=3;
            k=3;
            break;
    }
    return(!isUsedBox(grid,row -row%j, col-col%k,num,n) && !isUsedRow(grid,row,num,n) && !isUsedCol(grid,col,num,n));
}


/*Print the final result*/
void PrintFinal(int **FinalGrid, int n)
{
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cout << FinalGrid[i][j] << "\t";
        }
        cout << endl << endl ;
    }
}
int main(){
    int N;
    char t,ch;
    cout <<"SUDOKU NxN. Choose N:" << endl << "1/ 4x4" << endl << "2/ 6x6" <<  endl <<  "3/ 9x9" << endl << "Any other key to exit" << endl;
    cin >> t;
    switch(t){
        case '1':
            N=4;
            break;
        case '2':
            N=6;
            break;
        case '3':
            N=9;
            break;
        default:
            cout << "Exit =====> ";
            exit(0);
    }
    int **grid=new int*[N];/*create a 2-D array*/
    for(int i=0;i<N;i++) grid[i]=new int [N];
    for(int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            grid[i][j]=0;
    cout << "\n\n\n";
    PrintFinal(grid,N);
    input:
    cout << "Assigned values: (Press n to finish entering the data)\n";
    int row, col, num;
    do{
        cout<< "Number:";
        cin >> num;
        do{
            cout << "Row - Col:";
            cin >> row >> col;
            if(row<1 || row >N || num<0 || num >N || col<1 || col >N)
                cout << "Invalid!";
            else
                grid[row-1][col-1]=num;
            cout << "\nContinue? (y/n)";
            cin >> ch;
        }while(ch=='y' || ch=='Y');
        cout << "Another number?(y/n)";
        cin >> ch;
    }while(ch =='y'|| ch=='Y');
    PrintFinal(grid,N);
    cout << endl <<"Need any changes?(y/n)" << endl;
    cin >> ch;
    if(ch=='y'|| ch== 'Y') goto input;
    if(SolveSudoku(grid,N))
        PrintFinal(grid,N);
    else
        cout <<"Can't solve the problem!\n";
    system("Pause");
    return 0;

}
