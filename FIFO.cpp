#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define max_page 10    //�ڴ�ҳ����
int Page[320]={0};    //����洢��,�洢320��ָ��,32��ҳ�� 
int Page_flu[320]={0};    //�洢320��ҳ��ַ��
int count=0;    //�������������ָ������
double lack_page=0;    //��¼ȱҳ�� 
int count_page=max_page;     //������п�ҳ����� 
int circle=1;    //�ڶ�����ѭ��ָ�򱻵����Ľ��� 
struct Memo{    //�ýṹ��洢�ڴ�ҳ���
    int num;     //��ÿ��ҳ����,���㽫��Ӷ������ҵ������� 
    int a; 
    struct Memo *next;
};
int Judge_Page(int value){    //����ָ��,����ָ������ҳ��� 
    return value/10;
}
int scan_queen(struct Memo *hear,int value){    //value����ҳ���,ɨ�����,ȱҳ����0,���򷵻�1
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
void print(struct Memo *hear){    //����ڴ�ҳ��
    struct Memo *move;
    move=hear->next;
    while(move!=NULL){
        printf("%d ",move->a);
        move=move->next;
    }
    printf("\n");
}
void insert(struct Memo *hear,int value,int ZL){    //��ҳ��value�����ڴ�,ZLΪ��Ӧָ�� 
    if(count_page>=1){    //�ڴ�ҳ��ռ����
        struct Memo *move;
        move=hear->next;
        while(move->a!=-1){
            move=move->next;
        }
        move->a=value;    //��ҳ����� 
        count_page--;
        printf("ҳ�� %d �����롪��������Ӧָ��Ϊ: %d \n",value,ZL);
    }
    else{    //�ڴ�ռ䲻�㣬�������Ƚ����ҳ��󣬽�ҳ��value�����
        struct Memo *move;
        move=hear->next;
        while(move->num!=circle){    //circle�洢������Ҫ������ҳ���� 
            move=move->next;
        }
        printf("ҳ�� %d ������,ҳ�� %d �����롪������ָ��Ϊ: %d \n",move->a,value,ZL);
        move->a=value;    //��ҳ�����
        circle++;
        if(circle==max_page+1){    //��circle>max_page+1ʱ,���Ƚ����ҳ��Ϊ������ҳ�� 
            circle=1;
        }
    }
    print(hear);    }
void FIFO(struct Memo *hear){
    int i=0;
    for(i=0;i<=319;i++){    //ѭ��ɨ��ҳ�� 
        if( scan_queen(hear,Page_flu[i])==0){    //�ж��Ƿ�ȱҳ
            lack_page++;
            insert(hear,Page_flu[i],Page[i]);            }
        else{    //��ȱҳ 
            printf("ָ�� %d ��Ӧҳ�� %d �����ڴ�\n",Page[i],Page_flu[i]);
        }
             }
}
void Pro_Page(){    //�γ�ҳ��ַ������ 
    int m=0;    //��[0,319]��ָ���ַ֮�����ѡȡһ���m
    m=rand()%320;
    
    Page[count]=m;
    count++;
    if(count==320){
        return;
    }
    int m_=0;    //��ǰ��ַ[0,m+1]�����ѡȡһ��ָ�ִ��
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
    m__=(m_+2)+rand()%( 319-(m_+2)+1 );    //�ں��ַ[m_+2,319]��ָ���ַ֮�����ѡȡһ��ָ�ִ��
    Page[count]=m__;
    count++;
    if(count==320){
        return;
    }
    
    Pro_Page();
}
void Flu(){    //��ָ��ת��Ϊҳ��ַ��
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
    for(i=0;i<=max_page;i++){    //�γ��ڴ�ҳ�����
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
    srand(time(0));    //����Pro_Page��������
    Pro_Page();    //�γ�ҳ��ַ��
    Flu();    //�γ�ҳ��ַ�� 
    /*
    printf("ҳ��ַ����\n");
    for(i=0;i<=319;i++){    //���ҳ��ַ��
        printf("%d ",Page[i]);
        if(i%3==0 && i!=0){
            printf("\n");
        }
    }
    printf("\n");
    */  
    FIFO(hear);
    printf("ȱҳ����Ϊ�� %0.0lf\n",lack_page);
    printf("������Ϊ��%lf\n",1-lack_page/320);
    return 0;
}
