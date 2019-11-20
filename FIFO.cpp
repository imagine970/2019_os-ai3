#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define max_page 10    //内存页面数
int Page[320]={0};    //虚拟存储区,存储320条指令,32个页面 
int Page_flu[320]={0};    //存储320个页地址流
int count=0;    //计算随机产生的指令条数
double lack_page=0;    //记录缺页数 
int count_page=max_page;     //计算队列空页面个数 
int circle=1;    //在队列中循环指向被调出的进程 
struct Memo{    //用结构体存储内存页面块
    int num;     //给每个页面编号,方便将其从队列中找到并调出 
    int a; 
    struct Memo *next;
};
int Judge_Page(int value){    //输入指令,返回指令对面的页面号 
    return value/10;
}
int scan_queen(struct Memo *hear,int value){    //value代表页面号,扫描队列,缺页返回0,否则返回1
    struct Memo *move;
    move=hear->next;
    while(move!=NULL){
        if(move->a==value){
            return 1;
        }
        move=move->next;
    }
    return 0;
}
void print(struct Memo *hear){    //输出内存页面
    struct Memo *move;
    move=hear->next;
    while(move!=NULL){
        printf("%d ",move->a);
        move=move->next;
    }
    printf("\n");
}
void insert(struct Memo *hear,int value,int ZL){    //将页面value调入内存,ZL为对应指令 
    if(count_page>=1){    //内存页面空间充足
        struct Memo *move;
        move=hear->next;
        while(move->a!=-1){
            move=move->next;
        }
        move->a=value;    //将页面调入 
        count_page--;
        printf("页面 %d 被调入————对应指令为: %d \n",value,ZL);
    }
    else{    //内存空间不足，调出最先进入的页面后，将页面value后调入
        struct Memo *move;
        move=hear->next;
        while(move->num!=circle){    //circle存储的是需要调出的页面编号 
            move=move->next;
        }
        printf("页面 %d 被调出,页面 %d 被调入————指令为: %d \n",move->a,value,ZL);
        move->a=value;    //将页面调入
        circle++;
        if(circle==max_page+1){    //当circle>max_page+1时,最先进入的页面为队列首页面 
            circle=1;
        }
    }
    print(hear);    }
void FIFO(struct Memo *hear){
    int i=0;
    for(i=0;i<=319;i++){    //循环扫描页面 
        if( scan_queen(hear,Page_flu[i])==0){    //判断是否缺页
            lack_page++;
            insert(hear,Page_flu[i],Page[i]);            }
        else{    //不缺页 
            printf("指令 %d 对应页面 %d 已在内存\n",Page[i],Page_flu[i]);
        }
             }
}
void Pro_Page(){    //形成页地址流函数 
    int m=0;    //在[0,319]的指令地址之间随机选取一起点m
    m=rand()%320;
    
    Page[count]=m;
    count++;
    if(count==320){
        return;
    }
    int m_=0;    //在前地址[0,m+1]中随机选取一条指令并执行
    m_=rand()%(m+1);
    
    Page[count]=m_;
    count++;
    if(count==320){
        return;
    }
    Page[count]=m_+1;
    count++;
    if(count==320){
        return;
    }
    int m__=0;
    m__=(m_+2)+rand()%( 319-(m_+2)+1 );    //在后地址[m_+2,319]的指令地址之间随机选取一条指令并执行
    Page[count]=m__;
    count++;
    if(count==320){
        return;
    }
    
    Pro_Page();
}
void Flu(){    //将指令转换为页地址流
    int i=0;
    for(i=0;i<=319;i++){
        Page_flu[i]=Judge_Page( Page[i] );
    }
}
int main(){
    struct Memo Stu[max_page+1];
    struct Memo *hear;
    hear=&Stu[0];
    int i=0;
    for(i=0;i<=max_page;i++){    //形成内存页面队列
        if(i==max_page){
            Stu[i].a=-1;
            Stu[i].next=NULL;
            Stu[i].num=i;
            break;
        }
        Stu[i].next=&Stu[i+1];
        Stu[i].a=-1;
        Stu[i].num=i;
    }
    //*************************************
    srand(time(0));    //放在Pro_Page函数外面
    Pro_Page();    //形成页地址流
    Flu();    //形成页地址流 
    /*
    printf("页地址流：\n");
    for(i=0;i<=319;i++){    //输出页地址流
        printf("%d ",Page[i]);
        if(i%3==0 && i!=0){
            printf("\n");
        }
    }
    printf("\n");
    */  
    FIFO(hear);
    printf("缺页次数为： %0.0lf\n",lack_page);
    printf("命中率为：%lf\n",1-lack_page/320);
    return 0;
}
