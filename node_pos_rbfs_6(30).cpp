#include<stdlib.h>
#include<time.h>
#include <limits.h>
#include<bits/stdc++.h>
#include<math.h>
#include<algorithm>
#include<stack>
#include<utility>
#include<vector>
#include<set>
#include<map>
#include<iterator>
using namespace std;
#define M_PI 3.1416
#define nd_num 30
#define ch_num 3

int pos_lower=0,pos_upper=5,number_of_exploring_node=0;      //for findMinChild .......
float up_bound=INFINITY,f_value=0,hold_ch_weight=0;
float node_weight[nd_num][nd_num][ch_num];
int node_connect[nd_num][nd_num];
float node_st_dis[nd_num][nd_num];

typedef pair<int,double>pairss;   //saving the nodes and distances.......(global var) for backtracking purpose...
typedef vector<pairss>vectors;
map<int,vectors>linked_nodes;
vectors v;
stack <int> save_node;

int qq=1;

struct pos
{
   int x,y;
};

float rand_normal(float mean, float stddev)
{
    static float n2 = 0.0;
    float x, y, r;
    static int n2_cached = 0;
    if (!n2_cached)
    {
        do
        {
            x = 2.0*rand()/RAND_MAX - 1;
            y = 2.0*rand()/RAND_MAX - 1;
            r = x*x + y*y;
        } while (r==0.0 || r>1.0);
        float d = sqrt(-2.0*log(r)/r);
        float n1 = x*d;
        float result = n1*stddev + mean;
        n2 = y*d;
        n2_cached = 1;
        return result;
    }
    else
    {
        n2_cached = 0;
        return n2*stddev + mean;
    }
}


float get_weight(float x){
    float var=1/pow(x,3);
    srand(time(NULL));
    float weight=sqrt(var)*abs(rand_normal(0.0,1.0));
    return  weight;
}

int printRandoms(int lower, int upper,int count)
{
    int i;
    for (i = 0; i < count; i++) {
        int num = (rand() %
           (upper - lower + 1)) + lower;
        return num;
    }
}

void save_info(int nd_key)    //save information...
{
    linked_nodes.insert({nd_key,v});
    v.clear();
}
void show()          // show all saved information..
{
    map<int,vectors>::iterator itm;
    vector<pairss>::iterator itv;
        cout<<"\n\n\n";
      for(itm = linked_nodes.begin(); itm != linked_nodes.end();itm++)
      {
          cout<<itm->first<<"-----> ";
          vectors v1 = itm->second;

       for(itv = v1.begin();itv!=v1.end();itv++)
          {
              pairss p1=*itv;
             cout<<"("<<p1.first<<" "<<p1.second<<")"<<"  ";
          }
        cout<<endl<<endl;
      }
}

stack<int>findChild(int nd)
{
    stack<int>ch_list;
    for(int i=0;i<nd_num;i++)
    {
        if(node_connect[nd][i]==1)
            ch_list.push(i);
    }
   /*while(!ch_list.empty())
    {
        cout<<ch_list.top()<<' ';
        ch_list.pop();
    }*/
    return ch_list;
}

bool isdes(int n,int des)
{
    if (n==des)
        return true;
    return false;
}

int findMinChild(int start,int destination)
{
int node1,node2;
double nd_1_cost,nd_2_cost;
typedef pair<int,double>pairs;
set<pairs>sets;

stack<int>st=findChild(start);
while(!st.empty())
{
    int x=st.top();
    pairs p=make_pair(x,(hold_ch_weight+node_weight[start][x][2] + node_st_dis[x][destination]));
    sets.insert(p);
         pairss ps;
         ps.first=p.first; //updating vector...with pair....
         ps.second=p.second;
         v.push_back(ps);

    st.pop();
}

  save_info(start);   //calling save_info function for adding info....

 //sorting of sets starts....
float arr[nd_num];
for(int i=0 ; i<nd_num ; i++ )
    arr[i]=-1;
int z=0;
set<pairs>:: iterator  it;
 for (it = sets.begin(); it!= sets.end(); it++) {

        pairs p = *it;
        arr[z]=p.second;
        z=z+1;
    }
  sort(arr,arr+(z));

 /*for(int i=0 ; i<10 ; i++ )
    cout<<endl<<arr[i]<<endl;*/

    for (it = sets.begin(); it!= sets.end(); it++) {
        pairs p = *it;
        if(p.second==arr[0])
        {
            node1=p.first;
            nd_1_cost=p.second;
        }

        else if(p.second==arr[1])
        {
            node2=p.first;
            nd_2_cost=p.second;
        }
    }
    hold_ch_weight+=node_weight[start][node1][2];



   /*for(it = sets.begin(); it!= sets.end(); it++) {

        pairs p = *it;
        cout << "(" << p.first << ", "
             << p.second << ")"
             << " ";
    }*/
//cout<<endl<<node1<<"  " <<node2;
//cout<<endl;
/*for(int i=0 ; i<10 ; i++ )
    cout<<arr[i]<<endl;*/


f_value=nd_1_cost;
if(nd_2_cost<=up_bound)
    up_bound=nd_2_cost;

    return node1;

}


int findMinChild_2(int start,int destination)
{
int node1,node2;
typedef pair<int,double>pairs;
set<pairs>sets;

stack<int>st=findChild(start);
while(!st.empty())
{
    int x=st.top();
    pairs p=make_pair(x,(hold_ch_weight+node_weight[start][x][2] + node_st_dis[x][destination]));
    sets.insert(p);
    st.pop();
}


 //sorting of sets starts....
float arr[nd_num];
for(int i=0 ; i<nd_num ; i++ )
    arr[i]=-1;
int z=0;
set<pairs>:: iterator  it;
 for (it = sets.begin(); it!= sets.end(); it++) {

        pairs p = *it;
        arr[z]=p.second;
        z=z+1;
    }
  sort(arr,arr+(z));

    for (it = sets.begin(); it!= sets.end(); it++) {
        pairs p = *it;
        if(p.second==arr[0])
        {
            node1=p.first;
        }
    }

    return node1;
}


void rbfs(int n,int des)
{
   int s=n;
  // save_node.push_back(s);
  cout<<"PATH: "<<qq<<": "<<s<<"-->";
        block1:
             number_of_exploring_node+=1;   // total node explored...
             save_node.push(s); //save nodes in global variable save_node...
             s= findMinChild(s,des);
               cout<<s<<"-->";
            if(up_bound>=f_value && isdes(s,des)!=true)
                goto block1;
            else    //backtrack......
            {
                int a=findMinChild(s,des);

                linked_nodes.erase(s);
                int b=save_node.top();
                hold_ch_weight=hold_ch_weight-node_weight[s][a][2]-node_weight[b][s][2];//update ch weight factor for backtrack...
                vectors vv=linked_nodes[b];
                vector<pairss>::iterator itv;
                  for(itv=vv.begin();itv!=vv.end();itv++){
                    pairss p2=*itv;
                    if(p2.first==s){
                        p2.second=f_value;
                        float t=up_bound;
                        up_bound=f_value;
                        f_value=t;
                     }
                  }

               if(up_bound>=f_value && isdes(s,des)!=true)
                 {
                   s=findMinChild_2(b,des);
                   save_node.pop();
                   goto block1;
                }

            }



}


int main()
{
 while(qq<=100){
pos node[nd_num];
float t_hold=0.036025;

node[0].x=1;           //inti node position.
node[0].y=2;

node[1].x=2;
node[1].y=8;

node[2].x=5;
node[2].y=2;

node[3].x=5;
node[3].y=4;

node[4].x=8;
node[4].y=10;

node[5].x=10;           //inti node position.
node[5].y=20;

node[6].x=11;
node[6].y=8;

node[7].x=2;
node[7].y=30;

node[8].x=50;
node[8].y=40;

node[9].x=20;
node[9].y=10;

node[10].x=12;           //inti node position.
node[10].y=24;

node[11].x=25;
node[11].y=8;

node[12].x=35;
node[12].y=20;

node[13].x=15;
node[13].y=34;

node[14].x=28;
node[14].y=10;

node[15].x=30;           //inti node position.
node[15].y=25;

node[16].x=11;
node[16].y=28;

node[17].x=22;
node[17].y=30;

node[18].x=52;
node[18].y=34;

node[19].x=24;
node[19].y=16;

node[20].x=22;           //inti node position.
node[20].y=24;

node[21].x=25;
node[21].y=83;

node[22].x=32;
node[22].y=10;

node[23].x=11;
node[23].y=34;

node[24].x=22;
node[24].y=11;

node[25].x=31;           //inti node position.
node[25].y=26;

node[26].x=14;
node[26].y=23;

node[27].x=40;
node[27].y=31;

node[28].x=51;
node[28].y=21;

node[29].x=22;
node[29].y=14;



for (int i=0;i<nd_num;i++)       //reset weight.
    for(int j=0;j<nd_num;j++)
        for(int k=0;k<ch_num;k++)
          node_weight[i][j][k]=0;

for (int i=0;i<nd_num;i++)       //reset node connect.
    for(int j=0;j<nd_num;j++)
          node_connect[i][j]=0;

/*node_connect[0][1]=1;
node_connect[0][4]=1;
node_connect[1][0]=1;
node_connect[1][2]=1;
node_connect[1][4]=1;
node_connect[2][1]=1;
node_connect[2][4]=1;
node_connect[2][3]=1;
node_connect[3][2]=1;
node_connect[3][4]=1;
node_connect[4][0]=1;
node_connect[4][1]=1;
node_connect[4][2]=1;
node_connect[4][3]=1;*/

   srand(time(0));
    for(int i=0;i<nd_num;i++){               //change node position.
        node[i].x += printRandoms(pos_lower, pos_upper,1);
        node[i].y += printRandoms(pos_lower, pos_upper,1);
    }

    for(int i=0;i<nd_num;i++)              //get st. dis.
        for(int j=0;j<nd_num;j++)
          node_st_dis[i][j]=sqrt(pow((node[i].x-node[j].x),2) + pow((node[i].y-node[j].y),2));

    for(int i=0;i<nd_num;i++)              //get ch weight.
        for(int j=0;j<nd_num;j++){
                int k=0;
                node_weight[i][j][k]=get_weight(node_st_dis[i][j]);
                node_weight[i][j][k+1]=get_weight(node_st_dis[i][j]);
                node_weight[i][j][k+2]=get_weight(node_st_dis[i][j]);

                    sort(node_weight[i][j],node_weight[i][j]+ch_num);
        }

    for (int i=0;i<nd_num;i++)       //node connect as high weight.
        for(int j=0;j<nd_num;j++)
            if( node_weight[i][j][2]>= t_hold)
                node_connect[i][j]=1;

//show
/*
cout<<"\n node positions: \n\n";
    for (int i=0;i<nd_num;i++)
        cout<<node[i].x<<ends<<node[i].y<<endl;
cout<<"\n st. dis. between nodes: \n\n";
    for(int i=0;i<nd_num;i++){
        for(int j=0;j<nd_num;j++){
           cout<<node_st_dis[i][j]<<ends;
           }
           cout<<endl;
        }
cout<<"\n channel weight between nodes: \n\n";
    for (int i=0;i<nd_num;i++){
        for(int j=0;j<nd_num;j++){
                cout<<"node: "<<i<<" to "<<j<<" = ";
            for(int k=0;k<ch_num;k++){
               cout<< node_weight[i][j][k]<<ends;
            }
        cout<<endl;
        }
        cout<<endl;
    }
cout<<"\n connections among nodes: \n\n";
    for(int i=0;i<nd_num;i++){
        for(int j=0;j<nd_num;j++){
           cout<<node_connect[i][j]<<ends;
           }
           cout<<endl;
        }
  ///////////////////////////////////////////
*/

int source=1,destination=28;
//findMinChild(source,destination);
rbfs(source,destination);
//show() ;
number_of_exploring_node+=1;
cout  << endl << number_of_exploring_node << endl;

qq++;
 }
float avg=number_of_exploring_node/100;
cout<<"avg = "<<avg<<endl;


    return 0;
}

