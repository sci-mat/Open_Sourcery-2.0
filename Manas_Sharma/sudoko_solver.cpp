#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool issafe(vector<vector<char>>&board, int a,int i, int j){
    char ch = a + '0';
    for(int b=0; b<9; b++){
        if(board[i][b] == ch ){
            return false;
        }
        
    }
    for(int b=0; b<9; b++){
        if(board[b][j] == ch){
            return false;
        }
    }
    int st , end;
    st = i/3 *3;
    end = j/3 *3;

    for(int x =st; x < st+3; x++){
        for(int y=end; y<end+3; y++){
            
            if(board[x][y] == ch){
                return false;
            }
        }
    }
   
    return true;
}


bool isBoardFilled( vector<vector<char>>& board) {
    for(auto& row : board){
        for(char c : row){
            if(c == '.') return false;
        }
    }
    return true;
}




void  solvesudoko(vector<vector<char>>&board, int i , int j){
    //base case
    if(i==9){
        return ;
    }
    if(j==9){
        solvesudoko(board, i+1 , 0);
        return ;
    }
    
    
    if(board[i][j] == '.'){
            for(int a=1; a<=9; a++){
                if(issafe(board, a, i,j)){
                    char ch = a + '0';
                    board[i][j] = ch ;
                    solvesudoko(board, i , j+1);
                    
                    if(isBoardFilled(board)) return ;
                    
                    board[i][j] = '.';
                }
            }
        }else{
            solvesudoko(board, i , j+1);
        }
    
}

int main(){
    vector<vector<char>> board = {
    {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
    {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
    {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
    {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
    {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
    {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
    {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
    {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
    {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
};

    solvesudoko(board, 0, 0);

    for(auto a : board){
        for(auto b:a){
            cout << b<< ' ';
        }
        cout << endl;
    }
    return 0;
}