// 11.22 ## 기본 틀 구성 O
// 11.23 ## github 연동 및, 4사분면 체크 및 막는 함수 만들기 O
// 11.24 ##-1 주석 추가 및 집 구현 o
// 11.24 ##-2 집과 플레이어 만나면 프로그램 종료 o

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void manage();  // 모든 실행 맡아서 하는 부함수
void firstPlayer(); // 플레이어 처음 위치(랜덤 값)
void printMap();    // 맵을 출력하는 함수
void mInTheP(); // 플레이어 위치를 맵안에 표시하는 함수
void randV();   // 랜덤값으로 플레이어가 갈 방향 정하는 함수
void goToTop(); // 플레이어를 위로 한 칸 보내는 함수
void goToUnder();   // 플레이어를 아래로 한 칸 보내는 함수
void goToLeft();    // 플레이어를 왼쪽으로 한 칸 보내는 함수
void goToRight();   // 플레이어를 오른쪽으로 한 칸 보내는 함수
int checkFour();    // 현재 플레이어의 사분면 위치를 체크하는 함수
void compFour();    // 이전 플레이어 사분면 위치와 현재 플레이어 사분면 위치 비교 함수
void makeWall(int xy);  // 벽을 만들어서, 사분면을 막는 역할
void makeHome();    // 초기 집 위치 생성(플레이어와 대각선 사분면
void compHome();    // 플레이어가 집이 있는 사분면에 들어왔는지 체크 후 makeWall 함수 호출
int matchHP();     // 플레이어가 집에 도착했는지 확인

int map[8][8]={0,}; // 기본 맵(8*8)
int px = 0, py = 0; // 플레이어 x좌표, y좌표
int beforeXy;   // 플레이어 이전 사분면 위치
int nowXy;  // 플레이어 현재 사분면 위치
int hx, hy; // 집 x좌표, y좌표
int hFour;   // 집 사분면 위치

int main(){
    manage();
    return 0;
}

void manage(){
    int flag = 1;
    srand(time(NULL));
    firstPlayer();
    makeHome();

    while (flag)
    {
        printMap();
        randV();
        mInTheP();
        compFour();
        compHome();
        flag = matchHP();
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
            //if(map[i][j] == 0 || map[i][j] ==2)
            //{
                //printf(" □ ");
                printf("%d  ", map[i][j]);
            //}
            //else if(map[i][j] == 1)
            //{
            //    printf(" ■ ");
            //}
            //else if(map[i][j] == 3)
            //{
            //    printf(" H ");
            //}
            
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
void makeHome(){
    int pFour = checkFour();

    if(pFour == 1)
    {
        hx = rand () % (7-4+1)+4;
        hy = rand () % (7-4+1)+4;
        hFour = 4;
    }
    else if(pFour == 2)
    {
        hx = rand () % (7-4+1)+4;
        hy = rand () % 4;
        hFour = 3;
    }
    else if(pFour == 3)
    {
        hx = rand () % 4;
        hy = rand () % (7-4+1)+4;
        hFour = 2;
    }
    else if(pFour == 4)
    {
        hy = rand () % 4;
        hx = rand () % 4;
        hFour = 1;
    }

    map[hx][hy] = 3;   
}
void compHome(){

    int i;

    if(nowXy == hFour)
    {
        for(i=1; i<=4; i++)
        {
            if(i != hFour)
            {
                 makeWall(i);
            }
        }
    }
}
int matchHP(){
    
    if(px == hx && py == hy){
        return 0;
    }
    else{
        return 1;
    }
}