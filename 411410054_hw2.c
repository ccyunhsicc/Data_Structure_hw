#include<stdio.h>
#include<stdlib.h>

void print_link(int *link, int size){
    for(int i=0;i<size;++i){
        printf("%d ",*link);
        link+=1;
    }
    printf("\n");
    return;
}

struct stack_node{
    struct stack_node *next;
    int value;
};

struct stack_node *top=NULL;

void stack_init(){
    while(1){
        struct stack_node *temp=top;
        if(temp==NULL){
            break;
        }
        top=top->next;
        free(temp);
    }
    return;
}

void stack_push(int value){
    struct stack_node *temp=(struct stack_node*)malloc(sizeof(struct stack_node));
    temp->value=value;
    temp->next=NULL;
    if(top==NULL){//no data in stack
        top=temp;
    }else{
        temp->next=top;
        top=temp;
    }
    return;
}

int stack_pop(){
    int return_value;
    if(top==NULL){//no data in stack
        return -1;
    }else{
        struct stack_node *temp=top;
        return_value=temp->value;
        top=top->next;
        free(temp);
        return return_value;
    }
}

int stack_size(){
    if(top==NULL){
        return 0;
    }
    int count=0;
    struct stack_node *temp=top;
    while(1){
        if(temp==NULL){
            break;
        }
        temp=temp->next;
        count++;
    }
    return count;
}

int main(){
    int num;
    int step_num=0;
    int print_old_flag=0;
    int print_new_flag=0;
    scanf("%d",&num);
    int old_link[num];
    int new_link[num];
    int temp_link[num];
    for(int i=0;i<num;++i){
        scanf("%d",&old_link[i]);
    }
    for(int i=0;i<num;++i){
        scanf("%d",&new_link[i]);
    }
    for(int i=0;i<num;++i){
        temp_link[i]=old_link[i];
    }

    //into stack
    stack_push(0);
    int point=new_link[0];
    while(1){
        if(new_link[point]==-1){
            break;
        }
        if(old_link[point]!=-1){
            stack_push(point);
        }
        point=new_link[point];
    }
    step_num=stack_size()+1;// the last point
    for(int i=0;i<num-1;++i){// old link have -1
        if(old_link[i]==-1){
            step_num++;
            print_old_flag=1;
            break;
        }
    }
    for(int i=0;i<num-1;++i){// new link have -1
        if(new_link[i]==-1){
            step_num++;
            print_new_flag=1;
            break;
        }
    }
    printf("%d\n",step_num);


    print_link(old_link,num);
    
    //first change if old link have -1
    if(print_old_flag==1){
        for(int i=0;i<num;++i){
            if(old_link[i]==-1){
                temp_link[i]=new_link[i];
            }
        }
        print_link(temp_link,num);
    }
    

    while(1){
        point=stack_pop();
        if(point==-1){
            break;
        }
        temp_link[point]=new_link[point];
        print_link(temp_link,num);
    }

    //last change if new link have -1
    if(print_new_flag==1){
        for(int i=0;i<num;++i){
            if(new_link[i]==-1){
                temp_link[i]=-1;
            }
        }
        print_link(new_link,num);
    }
    
    return 0;
}