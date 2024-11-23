// 11.22 ## 기본 틀 구성 O
// 11.23 ## github 연동 및, 4사분면 체크 및 막는 함수 만들기
// gitgub 연동 테스트 주석3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void manage();
void firstPlayer();
void printMap();
void mInTheP();
void randV();
void goToTop();
void goToUnder();
void goToLeft();
void goToRight();
int checkFour();
void compFour();
void makeWall(int xy);

int map[8][8]={0,};
int px = 0, py = 0;
int beforeXy;
int nowXy;

int main(){
    manage();
    return 0;
}

void manage(){
    int flag = 1;
    srand(time(NULL));
    firstPlayer();
    while (1)
    {
        printMap();
        randV();
        mInTheP();
        compFour();
    }
    
}

void firstPlayer(){
    px = rand() % 8;
    py = rand() % 8;
    map[px][py] = 1;
    beforeXy = checkFour();
}
void mInTheP(){
    map[px][py] = 1;
    nowXy = checkFour();
}
void randV(){
    int ran = rand() % 4;

    printf("ran: %d \n", ran);

    if (ran == 0)
        goToTop();
    else if(ran == 1)
        goToUnder();
    else if(ran ==2)
        goToLeft();
    else if(ran == 3)
        goToRight();
}
void goToTop(){
    if(px != 0){
        map[px][py] = 0;
        px -= 1;
        if(map[px][py] == 2)
        {   
            map[px+1][py] = 1;
            px += 1;
        }
        
    }
}
void goToUnder(){
    if(px != 7){
        map[px][py] = 0;
        px += 1;
        if(map[px][py] == 2)
        {   
            map[px-1][py] = 1;
            px -= 1;
        }
    }
}
void goToLeft(){
    if(py != 7){
        map[px][py] = 0;
        py += 1;
        if(map[px][py] == 2)
        {   
            map[px][py-1] = 1;
            py -= 1;
        }
    }
}
void goToRight(){
    if(py !=0){
        map[px][py] = 0;
        py -= 1;
        if(map[px][py] == 2)
        {   
            map[px][py+1] = 1;
            py += 1;
        }
    }
}
void printMap(){
    
    int i, j;
    
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(map[i][j] == 0 || map[i][j] ==2)
            {
                printf(" □ ");
            }
            else if(map[i][j] == 1)
            {
                printf(" ■ ");
            }
            
        }
        printf("\n");
    }

    printf("befor: %d, now: %d \n", beforeXy, nowXy);
    sleep(1);
    system("clear");
}
void compFour(){
    if(beforeXy != nowXy)
    {
        makeWall(beforeXy);
        beforeXy = nowXy;
    }
}
void makeWall(int xy){
    int i, j;

    if (xy == 1)
    {
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                map[i][j] = 2;
            }
        }
    }
    else if(xy == 2)
    {
        for(i=0; i<4; i++)
        {
            for(j=4; j<8; j++)
            {
                map[i][j] = 2;
            }
        }
    }
    else if (xy == 3)
    {
        for(i=4; i<8; i++)
        {
            for(j=0; j<4; j++)
            {
                map[i][j] = 2;
            }
        }
    }
    else if(xy == 4)
    {
        for(i=4; i<8; i++)
        {
            for(j=4; j<8; j++)
            {
                map[i][j] = 2;
            }
        }
    }
}
int checkFour(){

    if ((px >=0 && px <=3) && (py >= 0 && py <=3)){
        return 1;
    }
    else if ((px>=0 && px<=3) && (py>=4 && py <=7)){
        return 2;
    }
    else if ((px>=4 && px <=7) && (py>=0 && py<=3)){
        return 3;
    }
    else if ((px>=4 && px <=7) && (py>=4 && py <=7)){
        return 4;
    }
    else {
        return 0;
    }
    
}