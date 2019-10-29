#include <iostream>

using namespace std;
//函数声明

#define MapSize 100
#define LINE 1//横竖 消耗
#define SKEW 1.41//斜 消耗


//定义地图块结构体
struct A_map{
    int Map_symbol;//1为普通  2为围墙  3为起点 4为重点
    int x;//坐标 x
    int y;//坐标 y
    //网上找的g(n)可以看做从start到current所花费的cost，h(n)从current到end的花费。  这里虽然是感觉是多余的，但是这样应该清晰点吧。。。火火火。
    float already_Cost;//实际走过的路径的花费
    float expect_Cost;//估计花费 算法使用那个什么哦，因为简单，地图全都被分成了块状，简单，简单。
    float Cost;//总花费
    int Visit_symbol;//1是已经访问 2是没访问 3是准备访问  
    //struct A_map *next;
};

//函数-计算两个地图之间的 expect_Cost   return  int  曼哈顿距离？？？
//传入两点的 xy
int GetExpect_Cost(int x1,int y1,int x2,int y2){
    int x=x2-x1;
    int y=y2-y1;
    if(x<0) x=-x;
    if(y<0) y=-y;
    return x+y;
}

//获得周围的8个地图块  传入当前坐标
int * GetExpect_Map(A_map currentMap,A_map maps[]){
    static int Map_Index[8];
    int index=0;
    int i;
    //测试方法输出
    //cout<<currentMap.x<<","<<currentMap.y<<"   "<<currentMap.Map_symbol<<" |";
    for(i=0;i<MapSize;i++){
        if(currentMap.x-1<=maps[i].x&&maps[i].x<=currentMap.x+1&&currentMap.y-1<=maps[i].y&&maps[i].y<=currentMap.y+1){//写出条件
            if(maps[i].Visit_symbol==2){//如果是1 就是未被访问。那么要即将访问。
                maps[i].Visit_symbol=3;//准备访问
                Map_Index[index++]=i;//记录下标
            }
        }
    }
    return Map_Index;
}

//初始化地图
void MapInit(A_map maps[],int goods[]){
    int i,j=0;
    //int index=0;
    for(i=0;i<MapSize;i++){
        maps[i].Map_symbol=1;//map 1是平地
        maps[i].x=i%10;
        maps[i].Visit_symbol=2;//2是没访问的
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
        if(i==0){//开始点 开始点是已访问的
            maps[goods[i]].Map_symbol=3;
            maps[goods[i]].Visit_symbol=1;
        }else if(i==8){//结束点   结束点是可访问的。
            maps[goods[i]].Map_symbol=4;
            maps[goods[i]].Visit_symbol=2;
        }else{//障碍物 已访问的(不用再访问)。
            maps[goods[i]].Map_symbol=2;
            maps[goods[i]].Visit_symbol=1;
        }
    }
}

//对比地图块的代价
int CompareToMap(A_map maps[],int Expect_Index[]){
    int index=0;
    int record_index=0;//记录最小下标
    float areadyCost=maps[Expect_Index[index]].already_Cost;
    float expectCost=maps[Expect_Index[index]].expect_Cost;
    float cost=maps[Expect_Index[index]].Cost;
    //对比大小
    index=1;
    record_index=index;
    while(Expect_Index[index]!='\0'){
        if(cost>maps[Expect_Index[index]].Cost){//>对比cost
            cost=maps[Expect_Index[index]].Cost;
            record_index=index;
        }else if(cost==maps[Expect_Index[index]].Cost){//=cost相同
            if(expectCost>maps[Expect_Index[index]].expect_Cost){//>对比 expect
                expectCost=maps[Expect_Index[index]].expect_Cost;
                record_index=index;
            }else if(expectCost==maps[Expect_Index[index]].expect_Cost){//= expect相同
                if(areadyCost>maps[Expect_Index[index]].already_Cost){//>对比 areadycost
                    areadyCost=maps[Expect_Index[index]].already_Cost;
                    record_index=index;
                }
            }
        }
        index++;
    }
    return record_index;
}


//循环计算欲走的路 并输出下一步的map
int ReckonTheExpect(int Expect_Index[],A_map maps[],A_map EndPoint,A_map *currentMap){
    //要先初始化float类型的变量要不然输出试一串-3242232+008
    int index=0;//下一步要走的下标
    int AlreadyCost=currentMap->already_Cost;//记录从起点到当前的消耗。
    int MHD_distance=0;
    //那就先计算消耗吧
    //cout<<"   Cost:"<<maps[Expect_Index[index]].Cost<<"\n";
    while(Expect_Index[index]!='\0'){
        //先计算曼哈距离 存入
        MHD_distance=GetExpect_Cost(maps[Expect_Index[index]].x,maps[Expect_Index[index]].y,EndPoint.x,EndPoint.y);
        maps[Expect_Index[index]].expect_Cost=MHD_distance;
        if(maps[Expect_Index[index]].x==currentMap->x||maps[Expect_Index[index]].y==currentMap->y){//上下左右
            maps[Expect_Index[index]].already_Cost=AlreadyCost+LINE;//横向加1      
        }else{
            maps[Expect_Index[index]].already_Cost=AlreadyCost+SKEW;//纵向加1.41
        }
    //  maps[Expect_Index[index]].expect_Cost=MHD_distance;

        maps[Expect_Index[index]].Cost=maps[Expect_Index[index]].already_Cost+maps[Expect_Index[index]].expect_Cost;

        cout<<"MHD_distance:"<<MHD_distance<<" Expect_Index[index]:"<< Expect_Index[index]<<"   Cost:"<<maps[Expect_Index[index]].Cost<<"\n";
        index++;
    }
    //测试输出的最佳路子，并且包出下一个节点的坐标
    cout<<"最佳路子："<<Expect_Index[CompareToMap(maps,Expect_Index)]<<"  地图块的位置("<<maps[Expect_Index[CompareToMap(maps,Expect_Index)]].x<<","<<maps[Expect_Index[CompareToMap(maps,Expect_Index)]].y<<")\n";
    return Expect_Index[CompareToMap(maps,Expect_Index)]; 
}



//打印地图----------------------------------------------------------以下  辅助函数------------------------------------------------------

void PrintMap(A_map everyMap[]){
    for(int i=0;i<MapSize;i++){
        if(i%10==0){
            cout<<"\n";
        }
        cout<<everyMap[i].Map_symbol<<"-"<<"("<<everyMap[i].x<<","<<everyMap[i].y<<") ";
    }
    cout<<"\n------------------------------- map is already ok  ----------------------------\n\n";  
}

//打印检测形态
void PrintMap2(A_map everyMap[]){
    for(int i=0;i<MapSize;i++){
        if(i%10==0){
            cout<<"\n";
        }
        cout<<everyMap[i].Visit_symbol<<"-"<<"("<<everyMap[i].x<<","<<everyMap[i].y<<") ";
    }
    cout<<"\n------------------------------- ExpectMap is already ok  ----------------------------\n\n";    
}

//打印即将走的路线
void PrintExpect(int *expect_Point){
    int h=0;
    while(*(expect_Point+h)!='\0'){
        cout<<"index: "<<*(expect_Point+h++)<<" \n";
    }
    cout<<"   count:"<<h<<"\n";
    cout<<"\n------------------------------- printExpect is already ok  ----------------------------\n\n";
}

//--------------------------------------------------------以上 辅助函数--------------------------------------------------------------------



//将路径连接起来，并且改变symbol
void NextStep(A_map *currentMap,A_map maps[],int nextStep,int Expect_Index[]){
    //前面的位置检测
    cout<<"前一位置：("<<currentMap->x<<","<<currentMap->y<<")\n";
    int index=0;
    if(currentMap->Visit_symbol==3){//是3就跳1
        currentMap->Visit_symbol=1;
    }   
    //currentMap->next=&maps[nextStep];//当前路径指向下一个选定的路
    while(Expect_Index[index]!='\0'){
        maps[Expect_Index[index]].Visit_symbol=1;
        index++;
    }
    PrintMap2(maps);//地图下一步要检测的范围检测 

}




main(){

    cout<<"程序启动，初始化地图\n";   

    A_map currentMap;

    A_map everyMap[MapSize];//定义一个10*10的地图 100个map

    int goods[]={12,41,42,43,44,45,46,47,76};//记录  起点，障碍物的排列数字，终点的排列数字

    int *expect_Point;//定义指向像一个的指针
    //保存路线-定义-开始
    int keepStep[50];
    //keepStep的索引变量
    int keepStep_index=0;
    //保存路线-定义-结束
    int nextStep=0;//下一步 maps索引值 的记录
    //int init_i=0;//初始化循环变量
    /*测试结构体是否可用 
    eveyMap[0].Map_symbol=1;
    cout<<"eveyMap[0].Map_symbol: "<<eveyMap[0].Map_symbol;
    */
    /*
    地图绘制-参考
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
    //goods元素计数-----------饿用到上面吧不知道为什么传入函数数组的长度会变成4能试sizeof出了指针的地址长度
    //printf("%d",sizeof(goods)/sizeof(int));

    MapInit(everyMap,goods);//地图初始化
    PrintMap(everyMap); //地图初始化检验

    currentMap=everyMap[goods[0]];//当前位置初始化，初始化的化，地图的当前位置就是起点

//★主要循环体，里面的函数对照上面的说明，可以看。
    while(nextStep!=goods[sizeof(goods)/sizeof(int)-1]){
            expect_Point=GetExpect_Map(currentMap,everyMap);//寻找下一个圈需要检测的，准备走的路
            nextStep=ReckonTheExpect(expect_Point,everyMap,everyMap[goods[sizeof(goods)/sizeof(int)-1]],&currentMap);
            cout<<"1  next-Step:"<<nextStep<<"\n";
            keepStep[keepStep_index++]=nextStep;//保存路径
            NextStep(&currentMap,everyMap,nextStep,expect_Point);
            currentMap=everyMap[nextStep];//这个就是让currentMap走到预定好的下一个位置。
            cout<<"\n★现在位置：("<<currentMap.x<<","<<currentMap.y<<")\n\n";
    }
    keepStep_index=0;
    //输出打印   （x，y）==》（x，y）==》……的路径格式
    while(keepStep[keepStep_index]!='\0'){      
            cout<<"("<<everyMap[keepStep[keepStep_index]].x<<","<<everyMap[keepStep[keepStep_index]].y<<")==>";
            keepStep_index++;
    }

    return 0;
}

