#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<direct.h>
#include<tgmath.h>
#include<complex.h>
#include<math.h>
#pragma warning(disable : 4996)

int main(void){//f(주파수)=n일때 t의 값을 t1에서 t2(t 1개=0.1초(푸리에 변환을 위한 작은묶음)/t 변화량=샘플레이트)까지 올려가면서 t1부터 t2까지의 변환값의 실수부 구하기
    char samplename[100];
    char outputname[100];
    double xcolumn=0.1;//x좌표/linecount/4410으로 증가
    int currentfrequency=20;//20-4000까지//y좌표축
    double t=0;//s단위
    double t1=t+0.1;
    double integralsum=0;//t부터 t1까지의 적분 합
    double amplitude;
    int tgaesu=0;//단위함수 t의 개수
    long long line=0;//읽어올 줄 번호/1-44100-->나중 노래의 x좌표 
    long long linecount=0;
    double complex ipi=M_PI*I;
    double complex eipi=cexp(ipi);//e^ipi-->(e^ipi)^-2*진동수*double t
    double complex fft1t;//적분 전 식에 넣은 값
    int songseconds=0;//노래길이
    char onlyamp[256];//진폭만
    printf("what is name of the sample(ex.test.dat)");
    scanf("%s",&samplename);
    printf("what is the output file name(ex.testoutput.txt)");
    scanf("%s",&outputname);
    printf("what is the length of song-in seconds\n");
    scanf("%d",&songseconds);
    printf("song length is %d\n",songseconds);
    hwnd=GetForegroundWindow();
    hdc=GetWindowDC(hwnd);
    FILE *wr;
    wr=fopen(outputname,"w+");
    if(wr==NULL){
            puts("ERROR");
    } 
    while (currentfrequency<4020)//주파수마다 아래 동작을 시행
    {
        FILE *fp =fopen(samplename,"r");
        while (tgaesu<songseconds*10)//단위함수 t의 개수가 초와 일치할때까지 
        {
            while(t<t1-0.000002){//단위함수(t) 안에서 리만적분
                //줄 읽어오는 반복함수용
                line++;
                //printf broken
                if(fp==NULL){
                    
                }
                else{
                    char buf[256]; 
                    while(fgets(buf, sizeof buf, fp) != NULL){
                        if(linecount==(line-1)){
                            linecount++;
                            //printf("%s",buf);//buf의 진폭만
                            strncpy(onlyamp,buf+17,25);
                            amplitude=atof(onlyamp);
                            fft1t=cpow(eipi,-2*currentfrequency*t);
                            integralsum=integralsum+(amplitude*creal(fft1t));
                            //printf("%lld",linecount);
                            //printf("%.20f\n",amplitude);
                            //buf에서 뒷부분만 추출-->decimal로변환-->적분돌리기-->
                            break;
                        }
                        else{
                            //printf("%s\n",buf);
                            linecount++;
                            strncpy(onlyamp,buf+17,25);
                            amplitude=atof(onlyamp);
                            fft1t=cpow(eipi,-2*currentfrequency*t);
                            integralsum=integralsum+(amplitude*creal(fft1t));
                            //printf("%.20f\n",amplitude);
                        }
                    }
                }
                t=t+0.00002267573; 
                
                
                //line+1번째 줄 읽기
                //줄을 읽어오기(col 19부터 40까지)/푸리에변환식에 집어넣기
            }
            //printf("%lld ",line);
            //printf("%.20f\n",integralsum);//0.1초단위
            fprintf(wr, "%f %d %.20f\n",xcolumn,currentfrequency,integralsum);
            integralsum=0;
            t=0;
            xcolumn=xcolumn+0.1;
            tgaesu++;//t개수 올리기
        }
        tgaesu=0;
        line=0;//주파수 대역 바뀌면서 초기화
        linecount=0;
        currentfrequency=currentfrequency+20;
        xcolumn=0.1;
        fclose(fp);
    }
    
    printf("DONE");//end of the code 
}
