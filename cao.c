#include<stdio.h>
#include<string.h>
#include<stdlib.h>



typedef struct
{
    unsigned short id;
    unsigned short flags;
    unsigned short questions;
    unsigned short answer;
    unsigned short authority;
    unsigned short additional;
}DNS_HEADER;

typedef struct
{
    char qname[256];
    unsigned short qtype;
    unsigned short qclass;
}DNS_QUESTION;

typedef struct 
{
    char name[256];
    unsigned short type;
    unsigned short Class;
    unsigned int ttl;
    unsigned int rdlength;
    unsigned short DL;
}DNS_ANSWER;

typedef struct
{
    char *domain;
    char *ip;
}DNS_ITEM;

//unsigned char BUF[128] = {0};

int dns_create_header(DNS_HEADER *header);//构造报文首部部分；
int dns_create_question(DNS_QUESTION *question, const char *hostname);//构造报文问题部分；
int dns_build_request(DNS_HEADER *header, DNS_QUESTION *question, char *request, int rlen);//建立请求‘
void dns_parse_name();//解析名字信息；
int dns_parse_response();//解析响应信息； 

/*输出格式
Header Section
ID: 0x****;
Flag:
QR: 0;OPCODE: 2;AA: 0;TC: 1;
RD: 0;RA: 0;Z: 3;RCODE: 4;
QCOUNT: ****;ANCOUNT: ****;NSCOUNT: ****;ARCOUNT: ****;
-------------------------------------------------------
Question Section
QNAME:*******
QTYPE: ****;
QCLASS: ****;
-------------------------------------------------------
Answer Section
NAME:****;
TYPE:****;
CLASS:****;
TTL:****;
EDLENGTH:****;
RDATA:****;
*/

void Header_Output(DNS_HEADER *header);
void Question_Output(DNS_QUESTION *question);
void Answer_Output(DNS_ANSWER *answer);

void Flag_Output(unsigned short flag);

void Parse_Header(char BUF[], DNS_HEADER *header);

int main()
{
    DNS_HEADER header;
    DNS_QUESTION question;
    DNS_ANSWER answer;

    header.id = 0x1111;header.flags=0x1234;
    header.questions=0x0001,header.answer=0x0000,header.authority=0x0000,header.additional=0x0000;
    strcpy(question.qname,"www.baidu.com");
    question.qtype=0x0001;question.qclass=0x0001;
    strcpy(answer.name,"www.baidu.com");
    answer.type=0x0001;answer.Class=0x0001;answer.ttl=0x1234;answer.rdlength=0x0004;answer.DL=0x0001;

    char BUF[256]="6dca0100000100000000000003777777056170706c6503636f6d0000010001";
    Parse_Header(BUF,&header);

    /*
    Header_Output(&header);
    Question_Output(&question);
    Answer_Output(&answer);
    */

    return 0;
}

void Header_Output(DNS_HEADER *header)
{
    printf("Header Section\n");
    printf("ID: 0x%.4x\n",header->id);
    Flag_Output(header->flags);
    printf("QCOUNT: %x;ANCOUNT: %x;NSCOUNT: %x;ARCOUNT: %x;\n",header->questions,header->answer,header->authority,header->additional);
    printf("--------------------------\n");
}

void Flag_Output(unsigned short flag)
{
    int RCODE=flag&15;
    flag>>=4;
    int Z=flag&7;
    flag>>=3;
    int RA=flag&1;
    flag>>=1;
    int RD=flag&1;
    flag>>=1;
    int TC=flag&1;
    flag>>=1;
    int AA=flag&1;
    flag>>=1;
    int OPCODE=flag&15;
    flag>>=4;
    int QR=flag&1;

    printf("Flag:\n");
    printf("QR: %x;OPCODE: %x;AA: %x;TC: %x;\n",QR,OPCODE,AA,TC);
    printf("RD: %x;RA: %x;Z: %x;RCODE: %x;\n",RD,RA,Z,RCODE);
}

void Question_Output(DNS_QUESTION *question)
{
    printf("Question Section\n");
    printf("QNAME: %s;\nQTYPE: %x;QCLASS: %x;\n",question->qname,question->qtype,question->qclass);
    printf("--------------------------\n");
}

void Answer_Output(DNS_ANSWER *answer)
{
    printf("Answer Section\n");
    printf("NAME: %s;\nTYPE: %x;CLASS: %x;\nTTL: %d;\nEDLENGTH: %d;\nRDATA: %x;\n",answer->name,answer->type,answer->Class,answer->ttl,answer->rdlength,answer->DL);
    printf("--------------------------\n");
}

void Parse_Header(char *BUF, DNS_HEADER *header)
{
    /*
    long long buf;
    sscanf(BUF,"%x",&buf);
    printf("%s\n",BUF);
    printf("%x\n",buf);
    */

    char *ptr=BUF;
    while (*ptr==' '||*ptr=='\n')
    {
        ptr++;
    }
    
    char id[4];
    //printf("%c",*ptr);
    for (int i = 0; i < 4 ; i++)
    {
        if (*ptr==' '||*ptr=='\n')
        {
            ptr++;
            i--;
            continue;
        }
        else
        {
            id[i]=*ptr;
            ptr++;
        }
    }
    sscanf(id,"%x",&header->id);
    printf("%x\n",header->id);

    //printf("%c***\n",*ptr);
    //char *ptr=BUF;
    char flag[4]={0};
    for (int i = 0; i < 4 ; i++)
    {
        if (*ptr==' '||*ptr=='\n')
        {
            ptr++;
            i--;
            continue;
        }
        else
        {
            flag[i]=*ptr;
            ptr++;
        }
        //printf("%c***\n",*ptr);
    }
    //printf("++%s++",flag);
    sscanf(flag,"%x",&header->flags);
    printf("%.4x",header->flags);
}
