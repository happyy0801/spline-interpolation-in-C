#include "stdio.h"

//spline interpolation


//ax^3 + bx^2 + cx + d
struct ThreeEq 
{
  float x3,x2,x1,x0;
};

const int dot = 600;//최대 x의 점 개수(10min)

float time[] = {0.f,60.f,120.f,150.f,180.f,200.f};//처음 값은 무조건 0이어야 함, 최소 3개
float temp[] = {30.f,150.f,200.f,120.f,80.f,90.f};

int count = sizeof(time) / sizeof(float);//사용자로부터 입력 받은 점의 개수



float* TimeAxis(float arr[]) { //축의 좌표를 1마다 생성
  static float tAxis[dot];
  for(int i = (int) arr[0]; i < (int) arr[count - 1]; i++) {
    tAxis[i] = (int) arr[0] + i;
  }
  return tAxis; //float* Axis = TimeAxis(time);로 저장 
}

void cal (float TAxis[], float time[], float temp[]) 
{//배열의 크기가 3인 입력(세 점)을 받아 하나의 3차방정식 계수를 반환 2번 작업
  
  struct ThreeEq tes;
  //처음 구간
  tes.x3 = ( (temp[1] - temp[2])/(time[1] - time[2]) - (temp[0] - temp[1])/(time[0] - time[1]) ) / (-3*time[1]*time[1]*(time[0]-time[2])/(time[1]-time[2]) - (time[0]*time[0]+time[0]*time[1]+time[1]*time[1]) - (time[0]-time[1])*(time[1]*time[1]+time[1]*time[2]+time[2]*time[2])/(time[1]-time[2]) + 3*time[0]*(time[0]+time[1]) + 3*time[1]*(time[0]-time[1])*(time[1]+time[2])/(time[1]-time[2]));
  
  tes.x2 = -3*tes.x3*time[0];
  
  tes.x1 = (temp[0]-temp[1])/(time[0]-time[1]) - tes.x3*(time[0]*time[0]+time[0]*time[1]+time[1]*time[1]) + 3*tes.x3*time[0]*(time[0]+time[1]);
  
  tes.x0 = temp[0] - tes.x1*time[0] +2*tes.x3*time[0]*time[0]*time[0];
  

  for(int i=(int) time[0]; i < (int) time[1]; i++) 
  { //각 구간 사이 1씩
    TAxis[i] = tes.x3*i*i*i + tes.x2*i*i + tes.x1*i + tes.x0;
  }

  //두번째 구간
  tes.x3 = -tes.x3*(time[0]-time[1])/(time[1]-time[2]);
  
  tes.x2 = -3*tes.x3*time[2];
  
  tes.x1 = (temp[1]-temp[2])/(time[1]-time[2]) - tes.x3*(time[1]*time[1]+time[1]*time[2]+time[2]*time[2]) + 3*tes.x3*time[2]*(time[1]+time[2]);
  
  tes.x0 = temp[2] - tes.x1*time[2] +2*tes.x3*time[2]*time[2]*time[2];

  for(int i=(int) time[1]; i < (int) time[2]; i++) 
  { //각 구간 사이 1씩
    TAxis[i] = tes.x3*i*i*i + tes.x2*i*i + tes.x1*i + tes.x0;
  }
  
}

void TempAxis (float TAxis[], float heat[], float time[],float temp[])//입력받은 좌표를 3개씩 나눠주는 함수
{
  float temp1[3]={0};
  float temp2[3]={0};
  for(int i=0;i<count-2;i++) //입력받은 좌표 개수
  {
    for(int j=0;j<3;j++)//처음 좌표부터 3개씩 
    {
      temp1[j] = time[i+j];
      temp2[j] = temp[i+j];
    }
    
    cal(TAxis,temp1,temp2);

    
  }
  
  for(int w=0;w<dot;w++)
  {
    heat[w] = TAxis[w];
  }

}






int main(void) {





  

float heat[dot]={0};
float TAxis[dot]={0};
  
  float* Axis = TimeAxis(time);

  //for(int i=0; i<600; i++) printf("%f ", Axis[i]);


  TempAxis(TAxis,heat,time,temp);
  for(int i=0;i<dot;i++) printf("%f, %d\n",heat[i],i);


  
  return 0;
}
