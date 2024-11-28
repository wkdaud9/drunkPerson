#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
// 0: 맵, 1: 기본 저장 벽, 2: 사분면 막는 벽, 3: 펍, 4: 집, 5: 플레이어, 6: 임상, 7: 자경, 8: 스나이퍼, 9: 와이프 
// 좌표로 출력하기
void Manage();
void Start();

void PrintMap();
void MakeMap();
void MakePlayer();
void MakePub();
void MakeHome();

int CheckQ();
void CompQ();
void MakeWallQ(int bq);

void PlayerWalk();
void RandomWalk();
void PTop();
void PUnder();
void PLeft();
void PRight();

void TwoOrThree();
void TwoQ();
void MakeImsang();
void MakeJakyung();
void CheckOneLineIm(int j);
void CheckOneLineJa();
void Bang(int w);
//void ThreeQ();


int map[10][10] = {0,};
int px, py;
int pubX, pubY;
int homeX,homeY;
int beforeQ, nowQ, hQ;
int unitTime = 0;
int imX, imY;
int jaX, jaY;

int main(){
  Manage();
  while(1){}
  return 0;
}
void Manage(){
  int flag = 1;
  srand(time(NULL));
  Start();
  while(flag){
    PrintMap();
    PlayerWalk();
    CompQ();
    TwoOrThree();
  }
}
void Start(){
  MakeMap();
  MakePlayer();
  MakePub();
  MakeHome();
}
void PrintMap(){
  for(int i = 0; i<10; i++){
    for(int j =0; j<10; j++){
      if(map[i][j] == 1){
        printf(" ■");   // ■
      }
      else if(i == pubX && j == pubY){
        printf(" P");
      }
      else if(i == homeX && j == homeY){
        printf(" H");
      }
      else if(i == px && j == py){
        printf(" 5");
      }
      else if(i == imX && j == imY){
        printf(" I");
      }
      else if(i == jaX && j == jaY){
        printf(" J");
      }
      else if(map[i][j] == 0){
        printf(" 0");
      }
      else if(map[i][j] == 2){
        printf(" 2");
      }
    }
    printf("\n");
  }
  printf("Unit Time : %d \n", unitTime);
  usleep(800000);
  system("clear");
}
void MakeMap(){
  int wallX[25]={0,0,2,2,3,3,4,4,1,1,2,2,2,6,6,6,7,9,9,9,5,6,6,7,8};
  int wallY[25]={0,1,2,3,0,2,0,4,5,6,6,8,9,1,2,3,1,1,2,3,6,6,8,8,6};
  for(int i=0; i<25; i++){
    map[wallX[i]][wallY[i]] = 1;
  }
}
void MakePlayer(){
  int flag = 1;
  while(flag){
    px = rand() % 10;
    py = rand() % 10;
    beforeQ = CheckQ();
    if((beforeQ == 1 || beforeQ == 4) && map[px][py] != 1){
      flag = 0;
      }
    }
}
void MakePub(){
  pubX = px;
  pubY = py;
}
void MakeHome(){
  int flag = 1;
  while(flag){
    if(beforeQ == 1){
      homeX = rand() % (9-5+1) + 5;
      homeY = rand() % (9-5+1) + 5;
      hQ = 4;
    }
    else if(beforeQ == 4){
      homeX = rand() % 5;
      homeY = rand() % 5;
      hQ = 1;
    }
    if(map[homeX][homeY] != 1){
      flag = 0;
    }
  }
}
int CheckQ(){
  if ((px >=0 && px <=4) && (py >= 0 && py <=4)){
        return 1;
    }
    else if ((px>=0 && px<=4) && (py>=5 && py <=9)){
        return 2;
    }
    else if ((px>=5 && px <=9) && (py>=0 && py<=4)){
        return 3;
    }
    else if ((px>=5 && px <=9) && (py>=5 && py <=9)){
        return 4;
    }
    else {
        return 0;
    }
}
void PlayerWalk(){
  RandomWalk();
  nowQ = CheckQ();
  unitTime += 1;
}
void RandomWalk(){
  char key = getchar();
  if(key == 'w'){
    PTop();
  }
  else if(key == 's'){
    PUnder();
  }
  else if(key == 'd'){
    PLeft();
  }
  else if(key == 'a'){
    PRight();
  }
  printf("rand: %c \n", key); // 테스트용 지우기
}
void PTop(){
  if(px != 0){
        px -= 1;
        if(map[px][py] == 2 || map[px][py] == 1)
        {   
            px += 1;
        }
    }
}
void PUnder(){
  if(px != 9){
        px += 1;
        if(map[px][py] == 2 || map[px][py] == 1)
        {   
            px -= 1;
        }
    }
}
void PLeft(){
  if(py != 9){
        py += 1;
        if(map[px][py] == 2 || map[px][py] == 1)
        {   
            py -= 1;
        }
    }
}
void PRight(){
  if(py != 0){
        py -= 1;
        if(map[px][py] == 2 || map[px][py] == 1)
        {   
            py += 1;
        }
    }
}
void CompQ(){
  if(beforeQ != nowQ){
      MakeWallQ(beforeQ);
      beforeQ = nowQ;
  }
  if(nowQ == hQ){
    for(int i=1; i<=4; i++)
        {
            if(i != hQ)
            {
              MakeWallQ(i);
            }
        }
  }
}
void MakeWallQ(int bq){
  if (bq == 1)
    {
        for(int i=0; i<5; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(map[i][j] != 1){
                  map[i][j] = 2;
                }
            }
        }
    }
    else if(bq == 2)
    {
        for(int i=0; i<5; i++)
        {
            for(int j=5; j<10; j++)
            {
                if(map[i][j] != 1){
                  map[i][j] = 2;
                }
            }
        }
    }
    else if (bq == 3)
    {
        for(int i=5; i<10; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(map[i][j] != 1){
                  map[i][j] = 2;
                }
            }
        }
    }
    else if(bq == 4)
    {
        for(int i=5; i<10; i++)
        {
            for(int j=5; j<10; j++)
            {
                if(map[i][j] != 1){
                  map[i][j] = 2;
                }
            }
        }
    }
}
void TwoOrThree(){
  if(nowQ == 2){
    TwoQ();
  }
  // else if(nowQ == 3){
  //   ThreeQ();
  // }
}
void TwoQ(){
  static int twoUT = 0;
  static int jakyung = 0;
  twoUT += 1;
  if(twoUT == 10){
    MakeImsang();
  }
  if(twoUT <= 10){
    CheckOneLineIm(0);
  }
  if(twoUT == 20){
    MakeJakyung();
    jakyung = 1;
  }
}
void MakeImsang(){
  imX = rand() % 5;
  imY = rand() % (9-5+1) + 5;
}
void MakeJakyung(){
  jaX = rand() % 5;
  jaY = rand() % (9-5+1) + 5;
}
void CheckOneLineIm(int ja){ // 11.28일에 벽있으면 서로 못 보게 수정하기
  int cntX = 0;
  int cntY = 0;
  if(ja==0){
    if(px == imX){
      // for(int i = px; i<=imX; i++){
      //   if(map[px][i] == 1){
      //     cntX++;
      //   }
      // }
      //if(cntX == 0){
        Bang(5);
      //}
    }
    // else if(py == imY){
    //   for(int i = py; i<=imY; i++){
    //     if(map[i][py] == 1){
    //       cntY++;
    //     }
    //   }
      //if(cntY == 0){
        Bang(5);
      //}
//    }
  }
}
void CheckOneLineJa(){};
void Bang(int w){ 
  int r, acc;
  r = rand() % 100;
  if(w==5){
    if(r < 50){
      printf("술취한 사람이 임상의 총에 맞았습니다.. \n");
    }
    else{
      printf("임상이 술취한 사람에게 총을 쐈으나, 맞지 않았습니다.. \n");
    }
  }
  else if(w==7){
    if(r < 30){
      printf("자경이 임상의 총에 맞았습니다.. \n");
    }
    else{
      printf("임상이 자경에게 총을 쐈으나, 맞지 않았습니다.. \n");
    }
  }
}
