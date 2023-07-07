#include <iostream>
#include <random>
#include <chrono>
using std::cin;
using std::cout;
using std::endl;
int minematrix[50][50], N, mine, k;

void Nummine() 
{
    int d=0;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0, N-1);

    cout << "\nNhap so luong min: ";

    while (true){
        cin >> mine;
        if(std::cin.fail() || cin.peek() != '\n' || mine > (N*N - 1) || mine < 1 ){
            cout << "\nSo luong min phai la so nguyen, lon hon 0 va nho hon kich thuoc bai min.\nVui long nhap lai: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } 
        else
            break;
    }

    while (d != mine) {
        int row = dis(gen);
        int col = dis(gen);
        if (minematrix[row][col] != -1) {
            minematrix[row][col] = -1;
            d++;
        }
    }
}

void CreatMinematrix() 
{
    cout << "\n      MINE DETECTION";
        cout << "\nNhap kich thuoc cua bai min: ";

        while (true){
            cin >> N;     
            if(std::cin.fail() || cin.peek() != '\n' || N<2){//cin.fail() kiểm tra đầu vào có đúng với kiểu dữ liệu ban đầu không, nếu không sẽ trả về true
                cout << "\nKich thuoc bai min phai la so nguyen va lon hon 1."  << endl << "Vui long nhap lai: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            } 
            else
                break;
        }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            minematrix[i][j] = -2;
    }
}

void ExportMinematrix() 
{
    cout << "      START" << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            cout << "|_|" << " ";
        cout << endl;
    }
}

void Minecount(int row, int col) // so luong min xung quanh vi tri [i][j]
{
    int res = 0;
    if(minematrix[row][col] != -1){

        if(minematrix[row][col-1] == -1) // ben trai
            res++;
        if(minematrix[row][col+1] == -1) // ben phai
            res++;
        if(minematrix[row-1][col-1] == -1) // ben trai tren
            res++;
        if(minematrix[row-1][col] == -1) // ben tren
            res++;
        if(minematrix[row-1][col+1] == -1) // ben phai tren
            res++;
        if(minematrix[row+1][col-1] == -1) // ben trai duoi
            res++;
        if(minematrix[row+1][col] == -1) // ben duoi
            res++;
        if(minematrix[row+1][col+1] == -1) // ben phai duoi
            res++;

        minematrix[row][col] = res;
    }
}

void NewMinematrix(int row, int col) // ma tran min moi
{
    Minecount(row,col);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(minematrix[i][j] == -1 || minematrix[i][j] == -2)
                cout << "|_|" << " ";
            else
                cout << " " << minematrix[i][j] << "  ";
        }
        cout << endl;
    }
}

void ExportMinematrix2()
{
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            Minecount(i,j);
            if(minematrix[i][j]  == -1)
                cout << "X" << " ";
            else
                cout << minematrix[i][j] << " ";
        }
        cout << endl;
    }
} 

void Demining()
{
    int row, col, count = 0;
    while( (N*N - count) != mine){
        cout << "\nChon o de di: ";
        cin >> row >> col;

        if(minematrix[row][col] == -1){
            cout << "\nBan da dinh min." << endl;
            ExportMinematrix2();
            cout << "       GAME OVER" << endl;
            return;
        }
        else if(minematrix[row][col] != -2)
            cout << "\nBan da di o nay roi.";
        else{
            count++;
            NewMinematrix(row,col);
        }
    }

    cout << "\nChuc mung ban do min thanh cong." << endl;
    ExportMinematrix2();
    cout << "       YOU WIN" << endl;
}

void Resert()
{
    // resert du lieu
    for(int i = 0; i < N; i++){
       for(int j = 0; j < N; j++){
            minematrix[i][j] = 0;
        }
    }
    N = 0; 
    mine = 0;
}
int main()
{
    do{
        CreatMinematrix();
        Nummine();
        ExportMinematrix();
        Demining();

        cout << "\n1.Choi lai     2.Thoat game";
        cout << "\nChon: ";
        cin >> k;
        Resert();

    } while(k == 1);

    return 0;
}