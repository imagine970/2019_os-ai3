#include <iostream>

using namespace std;
//��������

#define MapSize 100
#define LINE 1//���� ����
#define SKEW 1.41//б ����


//�����ͼ��ṹ��
struct A_map{
    int Map_symbol;//1Ϊ��ͨ  2ΪΧǽ  3Ϊ��� 4Ϊ�ص�
    int x;//���� x
    int y;//���� y
    //�����ҵ�g(n)���Կ�����start��current�����ѵ�cost��h(n)��current��end�Ļ��ѡ�  ������Ȼ�Ǹо��Ƕ���ģ���������Ӧ��������ɡ���������
    float already_Cost;//ʵ���߹���·���Ļ���
    float expect_Cost;//���ƻ��� �㷨ʹ���Ǹ�ʲôŶ����Ϊ�򵥣���ͼȫ�����ֳ��˿�״���򵥣��򵥡�
    float Cost;//�ܻ���
    int Visit_symbol;//1���Ѿ����� 2��û���� 3��׼������  
    //struct A_map *next;
};

//����-����������ͼ֮��� expect_Cost   return  int  �����پ��룿����
//��������� xy
int GetExpect_Cost(int x1,int y1,int x2,int y2){
    int x=x2-x1;
    int y=y2-y1;
    if(x<0) x=-x;
    if(y<0) y=-y;
    return x+y;
}

//�����Χ��8����ͼ��  ���뵱ǰ����
int * GetExpect_Map(A_map currentMap,A_map maps[]){
    static int Map_Index[8];
    int index=0;
    int i;
    //���Է������
    //cout<<currentMap.x<<","<<currentMap.y<<"   "<<currentMap.Map_symbol<<" |";
    for(i=0;i<MapSize;i++){
        if(currentMap.x-1<=maps[i].x&&maps[i].x<=currentMap.x+1&&currentMap.y-1<=maps[i].y&&maps[i].y<=currentMap.y+1){//д������
            if(maps[i].Visit_symbol==2){//�����1 ����δ�����ʡ���ôҪ�������ʡ�
                maps[i].Visit_symbol=3;//׼������
                Map_Index[index++]=i;//��¼�±�
            }
        }
    }
    return Map_Index;
}

//��ʼ����ͼ
void MapInit(A_map maps[],int goods[]){
    int i,j=0;
    //int index=0;
    for(i=0;i<MapSize;i++){
        maps[i].Map_symbol=1;//map 1��ƽ��
        maps[i].x=i%10;
        maps[i].Visit_symbol=2;//2��û���ʵ�
        if(i%10==0&&i!=0){
            j++;
        }
        maps[i].y=j;
    }
    maps[goods[0]].already_Cost=0;
    maps[goods[0]].expect_Cost=0;
    maps[goods[0]].Cost=0;
    i=0;
    for(i;i<9;i++){
        if(i==0){//��ʼ�� ��ʼ�����ѷ��ʵ�
            maps[goods[i]].Map_symbol=3;
            maps[goods[i]].Visit_symbol=1;
        }else if(i==8){//������   �������ǿɷ��ʵġ�
            maps[goods[i]].Map_symbol=4;
            maps[goods[i]].Visit_symbol=2;
        }else{//�ϰ��� �ѷ��ʵ�(�����ٷ���)��
            maps[goods[i]].Map_symbol=2;
            maps[goods[i]].Visit_symbol=1;
        }
    }
}

//�Աȵ�ͼ��Ĵ���
int CompareToMap(A_map maps[],int Expect_Index[]){
    int index=0;
    int record_index=0;//��¼��С�±�
    float areadyCost=maps[Expect_Index[index]].already_Cost;
    float expectCost=maps[Expect_Index[index]].expect_Cost;
    float cost=maps[Expect_Index[index]].Cost;
    //�Աȴ�С
    index=1;
    record_index=index;
    while(Expect_Index[index]!='\0'){
        if(cost>maps[Expect_Index[index]].Cost){//>�Ա�cost
            cost=maps[Expect_Index[index]].Cost;
            record_index=index;
        }else if(cost==maps[Expect_Index[index]].Cost){//=cost��ͬ
            if(expectCost>maps[Expect_Index[index]].expect_Cost){//>�Ա� expect
                expectCost=maps[Expect_Index[index]].expect_Cost;
                record_index=index;
            }else if(expectCost==maps[Expect_Index[index]].expect_Cost){//= expect��ͬ
                if(areadyCost>maps[Expect_Index[index]].already_Cost){//>�Ա� areadycost
                    areadyCost=maps[Expect_Index[index]].already_Cost;
                    record_index=index;
                }
            }
        }
        index++;
    }
    return record_index;
}


//ѭ���������ߵ�· �������һ����map
int ReckonTheExpect(int Expect_Index[],A_map maps[],A_map EndPoint,A_map *currentMap){
    //Ҫ�ȳ�ʼ��float���͵ı���Ҫ��Ȼ�����һ��-3242232+008
    int index=0;//��һ��Ҫ�ߵ��±�
    int AlreadyCost=currentMap->already_Cost;//��¼����㵽��ǰ�����ġ�
    int MHD_distance=0;
    //�Ǿ��ȼ������İ�
    //cout<<"   Cost:"<<maps[Expect_Index[index]].Cost<<"\n";
    while(Expect_Index[index]!='\0'){
        //�ȼ����������� ����
        MHD_distance=GetExpect_Cost(maps[Expect_Index[index]].x,maps[Expect_Index[index]].y,EndPoint.x,EndPoint.y);
        maps[Expect_Index[index]].expect_Cost=MHD_distance;
        if(maps[Expect_Index[index]].x==currentMap->x||maps[Expect_Index[index]].y==currentMap->y){//��������
            maps[Expect_Index[index]].already_Cost=AlreadyCost+LINE;//�����1      
        }else{
            maps[Expect_Index[index]].already_Cost=AlreadyCost+SKEW;//�����1.41
        }
    //  maps[Expect_Index[index]].expect_Cost=MHD_distance;

        maps[Expect_Index[index]].Cost=maps[Expect_Index[index]].already_Cost+maps[Expect_Index[index]].expect_Cost;

        cout<<"MHD_distance:"<<MHD_distance<<" Expect_Index[index]:"<< Expect_Index[index]<<"   Cost:"<<maps[Expect_Index[index]].Cost<<"\n";
        index++;
    }
    //������������·�ӣ����Ұ�����һ���ڵ������
    cout<<"���·�ӣ�"<<Expect_Index[CompareToMap(maps,Expect_Index)]<<"  ��ͼ���λ��("<<maps[Expect_Index[CompareToMap(maps,Expect_Index)]].x<<","<<maps[Expect_Index[CompareToMap(maps,Expect_Index)]].y<<")\n";
    return Expect_Index[CompareToMap(maps,Expect_Index)]; 
}



//��ӡ��ͼ----------------------------------------------------------����  ��������------------------------------------------------------

void PrintMap(A_map everyMap[]){
    for(int i=0;i<MapSize;i++){
        if(i%10==0){
            cout<<"\n";
        }
        cout<<everyMap[i].Map_symbol<<"-"<<"("<<everyMap[i].x<<","<<everyMap[i].y<<") ";
    }
    cout<<"\n------------------------------- map is already ok  ----------------------------\n\n";  
}

//��ӡ�����̬
void PrintMap2(A_map everyMap[]){
    for(int i=0;i<MapSize;i++){
        if(i%10==0){
            cout<<"\n";
        }
        cout<<everyMap[i].Visit_symbol<<"-"<<"("<<everyMap[i].x<<","<<everyMap[i].y<<") ";
    }
    cout<<"\n------------------------------- ExpectMap is already ok  ----------------------------\n\n";    
}

//��ӡ�����ߵ�·��
void PrintExpect(int *expect_Point){
    int h=0;
    while(*(expect_Point+h)!='\0'){
        cout<<"index: "<<*(expect_Point+h++)<<" \n";
    }
    cout<<"   count:"<<h<<"\n";
    cout<<"\n------------------------------- printExpect is already ok  ----------------------------\n\n";
}

//--------------------------------------------------------���� ��������--------------------------------------------------------------------



//��·���������������Ҹı�symbol
void NextStep(A_map *currentMap,A_map maps[],int nextStep,int Expect_Index[]){
    //ǰ���λ�ü��
    cout<<"ǰһλ�ã�("<<currentMap->x<<","<<currentMap->y<<")\n";
    int index=0;
    if(currentMap->Visit_symbol==3){//��3����1
        currentMap->Visit_symbol=1;
    }   
    //currentMap->next=&maps[nextStep];//��ǰ·��ָ����һ��ѡ����·
    while(Expect_Index[index]!='\0'){
        maps[Expect_Index[index]].Visit_symbol=1;
        index++;
    }
    PrintMap2(maps);//��ͼ��һ��Ҫ���ķ�Χ��� 

}




main(){

    cout<<"������������ʼ����ͼ\n";   

    A_map currentMap;

    A_map everyMap[MapSize];//����һ��10*10�ĵ�ͼ 100��map

    int goods[]={12,41,42,43,44,45,46,47,76};//��¼  ��㣬�ϰ�����������֣��յ����������

    int *expect_Point;//����ָ����һ����ָ��
    //����·��-����-��ʼ
    int keepStep[50];
    //keepStep����������
    int keepStep_index=0;
    //����·��-����-����
    int nextStep=0;//��һ�� maps����ֵ �ļ�¼
    //int init_i=0;//��ʼ��ѭ������
    /*���Խṹ���Ƿ���� 
    eveyMap[0].Map_symbol=1;
    cout<<"eveyMap[0].Map_symbol: "<<eveyMap[0].Map_symbol;
    */
    /*
    ��ͼ����-�ο�
    1 1 1 1 1 1 1 1 1 1
    1 1 3 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1
    1 2 2 2 2 2 2 2 1 1
    1 1 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 4 1 1 1
    1 1 1 1 1 1 1 1 1 1
    1 1 1 1 1 1 1 1 1 1
    1-(0,0) 1-(1,0) 1-(2,0) 1-(3,0) 1-(4,0) 1-(5,0) 1-(6,0) 1-(7,0) 1-(8,0) 1-(9,0)
    1-(0,1) 1-(1,1) 3-(2,1) 1-(3,1) 1-(4,1) 1-(5,1) 1-(6,1) 1-(7,1) 1-(8,1) 1-(9,1)
    1-(0,2) 1-(1,2) 1-(2,2) 1-(3,2) 1-(4,2) 1-(5,2) 1-(6,2) 1-(7,2) 1-(8,2) 1-(9,2)
    1-(0,3) 1-(1,3) 1-(2,3) 1-(3,3) 1-(4,3) 1-(5,3) 1-(6,3) 1-(7,3) 1-(8,3) 1-(9,3)
    1-(0,4) 2-(1,4) 2-(2,4) 2-(3,4) 2-(4,4) 2-(5,4) 2-(6,4) 2-(7,4) 1-(8,4) 1-(9,4)
    1-(0,5) 1-(1,5) 1-(2,5) 1-(3,5) 1-(4,5) 1-(5,5) 1-(6,5) 1-(7,5) 1-(8,5) 1-(9,5)
    1-(0,6) 1-(1,6) 1-(2,6) 1-(3,6) 1-(4,6) 1-(5,6) 1-(6,6) 1-(7,6) 1-(8,6) 1-(9,6)
    1-(0,7) 1-(1,7) 1-(2,7) 1-(3,7) 1-(4,7) 1-(5,7) 4-(6,7) 1-(7,7) 1-(8,7) 1-(9,7)
    1-(0,8) 1-(1,8) 1-(2,8) 1-(3,8) 1-(4,8) 1-(5,8) 1-(6,8) 1-(7,8) 1-(8,8) 1-(9,8)
    1-(0,9) 1-(1,9) 1-(2,9) 1-(3,9) 1-(4,9) 1-(5,9) 1-(6,9) 1-(7,9) 1-(8,9) 1-(9,9)
    */
    //goodsԪ�ؼ���-----------���õ�����ɲ�֪��Ϊʲô���뺯������ĳ��Ȼ���4����sizeof����ָ��ĵ�ַ����
    //printf("%d",sizeof(goods)/sizeof(int));

    MapInit(everyMap,goods);//��ͼ��ʼ��
    PrintMap(everyMap); //��ͼ��ʼ������

    currentMap=everyMap[goods[0]];//��ǰλ�ó�ʼ������ʼ���Ļ�����ͼ�ĵ�ǰλ�þ������

//����Ҫѭ���壬����ĺ������������˵�������Կ���
    while(nextStep!=goods[sizeof(goods)/sizeof(int)-1]){
            expect_Point=GetExpect_Map(currentMap,everyMap);//Ѱ����һ��Ȧ��Ҫ���ģ�׼���ߵ�·
            nextStep=ReckonTheExpect(expect_Point,everyMap,everyMap[goods[sizeof(goods)/sizeof(int)-1]],&currentMap);
            cout<<"1  next-Step:"<<nextStep<<"\n";
            keepStep[keepStep_index++]=nextStep;//����·��
            NextStep(&currentMap,everyMap,nextStep,expect_Point);
            currentMap=everyMap[nextStep];//���������currentMap�ߵ�Ԥ���õ���һ��λ�á�
            cout<<"\n������λ�ã�("<<currentMap.x<<","<<currentMap.y<<")\n\n";
    }
    keepStep_index=0;
    //�����ӡ   ��x��y��==����x��y��==��������·����ʽ
    while(keepStep[keepStep_index]!='\0'){      
            cout<<"("<<everyMap[keepStep[keepStep_index]].x<<","<<everyMap[keepStep[keepStep_index]].y<<")==>";
            keepStep_index++;
    }

    return 0;
}

