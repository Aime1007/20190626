#include <iostream>
#include <fstream>
using namespace std;

class student{
public:
    student(){}
    void set(int a,string b){
        num = a;
        name = b;
    }
    friend void sort(double *p,student *q,string *r,int *z);
private:
    string name;
    int num;
};

class judge{
public:
    judge(){}
    void set(string a,int *p){
        name = a;
        for(int i=0; i<4; i++)
            score[i]=*(p+i);
    }
    string get1(){
        return name;
    }
    int get2(int z){
        return score[z];
    }
    friend void average(judge *jud,double *avg1);
private:
    string name;
    int score[4];
};

void average(judge *jud,double *avg1);
void sort(double *p,student *q,string *r);

int main() {
    student stu[4]; //对象数组 学生
    judge jud[7]; //对象数组 裁判
    double avg1[4];
    string nam[4];
    int num[4]={0,1,2,3};
    ifstream stuin("/Users/s20181106275/Desktop/project0626/20190626/190626in01.txt");
    ifstream judgein("/Users/s20181106275/Desktop/project0626/20190626/190626in02.txt");
    ofstream ljlout("/Users/s20181106275/Desktop/project0626/20190626/190626out.txt");
    
    if(stuin.is_open()) //文件读取学生学号姓名
    {
        cout<<"file OK"<<endl;
        for(int i=0; i<4; i++)
        {
            int a;
            string b;
            stuin >> a >> b;
            stu[i].set(a,b);
            
        }
        stuin.close();
    }
    
    if(judgein.is_open()) //文件读取裁判姓名 给四个学生打的分数
    {
        cout<<"file OK"<<endl;
        for(int i=0; i<7; i++) //每个裁判
        {
            string a;
            judgein >> a;
            int score[4];
            for(int j=0; j<4; j++)
            {
                int s;
                judgein >> s;
                score[j] = s;
            }
            jud[i].set(a,score);
        }
        judgein.close();
    }
    if (ljlout.is_open())
    {
        cout<<"file OK"<<endl;
        average(jud,avg1);
        sort(avg1,stu,nam,num);
        for(int i=0; i<4; i++ ){
            ljlout << nam[i] <<" "<< avg1[i] <<endl;
            for(int j=0; j<7; j++){
                ljlout << jud[j].get1() <<" "<< jud[j].get2(num[i])<<" ";
            }
            ljlout<<endl;
        }
        
        ljlout.close();
    }
    return 0;
}
void average(judge *jud,double *avg1){
    int scor[4][7];
    //double avg[4];
    int sum[4]={0,0,0,0};
    for(int i=0; i<4; i++ )
        for(int j=0; j<7; j++ ){
            scor[i][j] = (*(jud+j)).score[i];
        }
    int max,min;
    int sign_max=0,sign_min=0;
    for(int i=0; i<4; i++ ){
        max=0,min=1000;
        for(int j=0; j<7; j++ ){
            if( scor[i][j]>max ){
                max = scor[i][j];
                sign_max = j;
            }
            if( scor[i][j]<min ){
                min = scor[i][j];
                sign_min = j;
            }
        }
        scor[i][sign_max]=0; scor[i][sign_min] =0;
    }
    for(int i=0; i<4; i++ ){
        for(int j=0; j<7; j++ ){
            sum[i] += scor[i][j];
        }
        *(avg1+i) = 1.0*sum[i]/5;
    }
}
void sort(double *p,student *q,string *r,int *z){
    for(int i=0; i<3; i++)
        for(int j=0; j<3-i; j++ ){
            if( *(p+j)>*(p+j+1) ){
                double t = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = t;
                string temp = (*(q+j)).name;
                (*(q+j)).name = (*(q+j+1)).name;
                (*(q+j+1)).name = temp;
                int v = *(z+j);
                *(z+j) = *(z+j+1);
                *(z+j+1) = v;
            }
        }
    for(int i=0; i<4; i++){
        *(r+i) = (*(q+i)).name;
    }
}
