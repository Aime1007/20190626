#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class student{
public:
    student(){}
    void set(int a,string b){
        num = a;
        name = b;
    }
    int get1(){
        return num;
    }
    string get2(){
        return name;    }
private:
    string name;
    int num;
};

class judge{
public:
    judge(){}
    void set(string a,int *p){
        name = a;
        for(int i=0; i<20; i++)
            score[i]=*(p+i);
    }
    string get1(){
        return name;
    }
    int get2(int z){
        return score[z];
    }
private:
    string name;
    int score[20];
};

void average(judge *jud,double *avg1){
    int scor[20][7];
    int sum[20]={0};
    for(int i=0; i<20; i++ )
        for(int j=0; j<7; j++ )
            scor[i][j] = (*(jud+j)).get2(i);
    int max,min;
    int sign_max=0,sign_min=0;
    for(int i=0; i<20; i++ ){
        max=0;
        min=1000;
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
    for(int i=0; i<20; i++ ){
        for(int j=0; j<7; j++ ){
            sum[i] += scor[i][j];
        }
        *(avg1+i) = 1.0*sum[i]/5;
    }
}
void sort(double *p,int *q){
    for(int i=0; i<19; i++)
        for(int j=0; j<19-i; j++ ){
            if( *(p+j)<=*(p+j+1) ){
                double t = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = t;
                int temp = *(q+j);
                *(q+j) = *(q+j+1);
                *(q+j+1) = temp;
            }
        }
}


int main() {
    student stu[20]; //对象数组 学生
    judge jud[7]; //对象数组 裁判
    double avg1[20]; //平均成绩
    int num[20];
    for(int i=0; i<20; i++ ){
        num[i] = i;
    }
    ifstream stuin("/Users/s20181106275/Desktop/project0626/20190626/190626in01.txt");
    ifstream judgein("/Users/s20181106275/Desktop/project0626/20190626/190626in02.txt");
    ofstream ljlout("/Users/s20181106275/Desktop/project0626/20190626/190626out.txt");
    
    if(stuin.is_open()){//文件读取学生学号姓名
        cout<<"file OK"<<endl;
        for(int i=0; i<20; i++){
            int a;
            string b;
            stuin >> a >> b;
            stu[i].set(a,b);
            
        }
        stuin.close();
    }
    
    if(judgein.is_open()){    //文件读取裁判姓名 给四个学生打的分数
        cout<<"file OK"<<endl;
        for(int i=0; i<7; i++) {  //每个裁判
            string a;
            judgein >> a;
            int score[20];
            for(int j=0; j<20; j++){
                int s;
                judgein >> s;
                score[j] = s;
            }
            jud[i].set(a,score);
        }
        judgein.close();
    }
    
    if (ljlout.is_open()){
        cout<<"file OK"<<endl;
        average(jud,avg1);
        sort(avg1,num);
        ljlout << std::left << setw(12) <<"排名";
        for(int i=0; i<20; i++ ){
            ljlout << std::left << setw(8) << i+1;
        }
        ljlout<<endl;
        ljlout << std::left << setw(12) <<"学号";
        for(int i=0; i<20; i++ ){
            ljlout << std::left << setw(8) << stu[num[i]].get1();
        }
        ljlout<<endl;
        ljlout << std::left << setw(12) <<"姓名";
        for(int i=0; i<20; i++ ){
            ljlout << std::left << setw(8) << stu[num[i]].get2();
        }
        ljlout<<endl;
        ljlout << std::left << setw(12) <<"得分";
        for(int i=0; i<20; i++ ){
            ljlout << std::left << setw(8) << avg1[i];
        }
        ljlout<<endl;
        for(int i=0; i<7; i++ ){
            ljlout << std::left << setw(9) <<jud[i].get1();
            for(int j=0; j<20; j++ ){
                ljlout << std::left << setw(8) << jud[i].get2(num[j]);
            }
            ljlout<<endl;
        }
        ljlout.close();
    }
    return 0;
}
