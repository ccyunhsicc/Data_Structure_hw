#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int maze[500][500];
int bfs_maze[500][500];//just for bfs
char src1_step[10000];
char src2_step[10000];
char steps[20000];
int queue_pop_arr[3];//0:value, 1:maze_x, 2:maze_y

int src1x,src1y;
int src2x,src2y;
int des1x,des1y;
int des2x,des2y;
int maze_size;
int print_value;//0:not print, 1:print
int step_value;//1:step 1, 2:step 2

struct queue_node{
    struct queue_node *next;
    int value;
    int maze_x;
    int maze_y;
};

struct queue_node *front=NULL;
struct queue_node *last=NULL;

void queue_init(){
    while(1){
        struct queue_node *temp=front;
        if(temp==NULL){
            break;
        }
        front=front->next;
        free(temp);
    }
    last=NULL;
    return;
}

void queue_push(int value,int maze_x,int maze_y){
    struct queue_node *temp=(struct queue_node*)malloc(sizeof(struct queue_node));
    temp->maze_x=maze_x;
    temp->maze_y=maze_y;
    temp->value=value;
    temp->next=NULL;
    if(front==NULL){//no data in queue
        front=temp;
        last=temp;
    }else{
        last->next=temp;
        last=temp;
    }
    return;
}

void queue_pop(){
    if(front==NULL){//no data in queue
        return;
    }else if(front==last){//only one data in queue
        struct queue_node *temp=front;
        queue_pop_arr[0]=front->value;
        queue_pop_arr[1]=front->maze_x;
        queue_pop_arr[2]=front->maze_y;
        front=NULL;
        last=NULL;
        free(temp);
        return;
    }else{
        struct queue_node *temp=front;
        queue_pop_arr[0]=front->value;
        queue_pop_arr[1]=front->maze_x;
        queue_pop_arr[2]=front->maze_y;
        front=front->next;
        free(temp);
        return;
    }
}

void bfs_maze_init(){
    for(int i=0;i<maze_size;++i){
        for(int j=0;j<maze_size;++j){
            if(maze[i][j]==1){
                bfs_maze[i][j]=-1;
            }else{
                bfs_maze[i][j]=__INT32_MAX__;
            }
        }
    }
    return;
}

int BFS(int srcx,int srcy,int desx,int desy){
    int count=0;
    bfs_maze_init();
    queue_init();
    bfs_maze[srcx][srcy]=0;
    int x=srcx,y=srcy;
    while(1){
        if(x==desx && y==desy){
            break;
        }
        bfs_maze[x][y]=count;
        if(bfs_maze[x+1][y]!=-1 && bfs_maze[x+1][y]>count){
            queue_push(count+1,x+1,y);
        }
        if(bfs_maze[x-1][y]!=-1 && bfs_maze[x-1][y]>count){
            queue_push(count+1,x-1,y);
        }
        if(bfs_maze[x][y+1]!=-1 && bfs_maze[x][y+1]>count){
            queue_push(count+1,x,y+1);
        }
        if(bfs_maze[x][y-1]!=-1 && bfs_maze[x][y-1]>count){
            queue_push(count+1,x,y-1);
        }
        queue_pop();
        count=queue_pop_arr[0];
        x=queue_pop_arr[1];
        y=queue_pop_arr[2];
        //printf("%d %d %d\n",count,x,y);
    }
    //add source steps to char array
    if(print_value==1){
        x=desx;
        y=desy;
        while(1){
            if(x==srcx && y==srcy){
                break;
            }
            if(bfs_maze[x+1][y]!=-1 && bfs_maze[x+1][y]<bfs_maze[x][y]){//up
                x=x+1;
                if(step_value==1){
                    strcat(src1_step,"0");
                }
                if(step_value==2){
                    strcat(src2_step,"0");
                }
            }
            if(bfs_maze[x-1][y]!=-1 && bfs_maze[x-1][y]<bfs_maze[x][y]){//down
                x=x-1;
                if(step_value==1){
                    strcat(src1_step,"2");
                }
                if(step_value==2){
                    strcat(src2_step,"2");
                }
            }
            if(bfs_maze[x][y+1]!=-1 && bfs_maze[x][y+1]<bfs_maze[x][y]){//left
                y=y+1;
                if(step_value==1){
                    strcat(src1_step,"3");
                }
                if(step_value==2){
                    strcat(src2_step,"3");
                }
            }
            if(bfs_maze[x][y-1]!=-1 && bfs_maze[x][y-1]<bfs_maze[x][y]){//right
                y=y-1;
                if(step_value==1){
                    strcat(src1_step,"1");
                }
                if(step_value==2){
                    strcat(src2_step,"1");
                }
            }
        }
    }
    return count;
}

int main(){
    int swap_temp;
    scanf("%d",&maze_size);
    for(int i=0;i<maze_size;++i){
        for(int j=0;j<maze_size;++j){
            scanf("%d",&maze[i][j]);
        }
    }
    scanf("%d %d %d %d",&src1x,&src1y,&src2x,&src2y);
    scanf("%d %d %d %d",&des1x,&des1y,&des2x,&des2y);
    //make x value to the problem value
    swap_temp=src1y;
    src1y=src1x;
    src1x=maze_size-swap_temp-1;
    swap_temp=src2y;
    src2y=src2x;
    src2x=maze_size-swap_temp-1;
    swap_temp=des1y;
    des1y=des1x;
    des1x=maze_size-swap_temp-1;
    swap_temp=des2y;
    des2y=des2x;
    des2x=maze_size-swap_temp-1;
    //printf("%d",BFS(src1x,src1y,des1x,des1y));
    
    //find the shorter solution
    print_value=0;
    int sol1=BFS(src1x,src1y,des1x,des1y)+BFS(src2x,src2y,des2x,des2y);
    int sol2=BFS(src1x,src1y,des2x,des2y)+BFS(src2x,src2y,des1x,des1y);
    print_value=1;

    //print the path
    int change_value=0;//0: no change, 1:change
    char temp[10]="\0";
    if(sol1>=sol2){
        step_value=1;//src1 move
        BFS(src1x,src1y,des1x,des1y);
        int length=strlen(src1_step);
        for(int i=length-1;i>=0;--i){
            temp[0]=src1_step[i];
            strcat(steps,temp);
            src1_step[i]='\0';
        }
        for(int i=0;i<length;++i){
            printf("%c",steps[i]);
            if(steps[i]=='2'){//down
                src1x++;
                if(maze[src2x+1][src2y]==0){
                    src2x++;
                }
            }
            if(steps[i]=='0'){//up
                src1x--;
                if(maze[src2x-1][src2y]==0){
                    src2x--;
                }
            }
            if(steps[i]=='1'){//right
                src1y++;
                if(maze[src2x][src2y+1]==0){
                    src2y++;
                }
            }
            if(steps[i]=='3'){//left
                src1y--;
                if(maze[src2x][src2y-1]==0){
                    src2y--;
                }
            }
            if(src2x==des1x && src2y==des1y){
                change_value=1;
                break;
            }
            if(src1x==des2x && src1y==des2y){
                change_value=2;
                break;
            }
        }

        step_value=2;//src2 move
        strcpy(steps,"\0");
        if(change_value==0){
            BFS(src2x,src2y,des2x,des2y);
        }else if(change_value==1){
            BFS(src1x,src1y,des2x,des2y);
        }else{
            BFS(src2x,src2y,des1x,des1y);
        }
        length=strlen(src2_step);
        for(int i=length-1;i>=0;--i){
            temp[0]=src2_step[i];
            strcat(steps,temp);
            src2_step[i]='\0';
        }
        printf("%s",steps);
    }else{
        step_value=1;
        BFS(src1x,src1y,des2x,des2y);
        int length=strlen(src1_step);
        for(int i=length-1;i>=0;--i){
            temp[0]=src1_step[i];
            strcat(steps,temp);
            src1_step[i]='\0';
        }
        for(int i=0;i<length;++i){
            printf("%c",steps[i]);
            if(steps[i]=='2'){//down
                src1x++;
                if(maze[src2x+1][src2y]==0){
                    src2x++;
                }
            }
            if(steps[i]=='0'){//up
                src1x--;
                if(maze[src2x-1][src2y]==0){
                    src2x--;
                }
            }
            if(steps[i]=='1'){//right
                src1y++;
                if(maze[src2x][src2y+1]==0){
                    src2y++;
                }
            }
            if(steps[i]=='3'){//left
                src1y--;
                if(maze[src2x][src2y-1]==0){
                    src2y--;
                }
            }
            if(src2x==des2x && src2y==des2y){
                change_value=1;
                break;
            }
            if(src1x==des1x && src1y==des1y){
                change_value=2;
                break;
            }
        }

        step_value=2;
        strcpy(steps,"\0");
        if(change_value==0){
            BFS(src2x,src2y,des1x,des1y);
        }else if(change_value==1){
            BFS(src1x,src1y,des1x,des1y);
        }else{
            BFS(src2x,src2y,des2x,des2y);
        }
        length=strlen(src2_step);
        for(int i=length-1;i>=0;--i){
            temp[0]=src2_step[i];
            strcat(steps,temp);
            src2_step[i]='\0';
        }
        printf("%s",steps);
    }
    return 0;
}