 #include <cstdio>
 #include <cstdlib>
 #include <iostream>
 #include <cstring>
 #include <fstream>
 #include <sstream>
 #include <stdexcept>
 #define MAX   10000
 #define M  10
 #define DEBUG
 using namespace std;
 class node_C{
    private: char *data;
	         int coutnum;
    public : 
            node_C():data(NULL),coutnum(0){};
			node_C(const char *t):coutnum(0){
			 data=new char[strlen(t)+1];
             strcpy(data,t);
			};
			node_C(const node_C &node_t){
			     if(node_t.data==NULL)
				 return ;
			     data=new char[strlen(node_t.data)+1];
                 strcpy(data,node_t.data);
                 coutnum=node_t.coutnum;				 
			}
            node_C & operator =(const node_C & node_t){
                    if(this==&node_t)
					return *this;
					node_C temp=node_C(node_t);
					char *temp_t=temp.data;
					temp.data=data;
					data=temp_t;
					coutnum=temp.coutnum;
					
            }
            bool operator ==(const node_C &node_t){
			     if(this==&node_t) return true;
                 if((node_t.coutnum==coutnum)&&(strcmp(node_t.data,data)==0))
					return true;
				 return false;	
			 }
			int operator++(){
                return ++coutnum;
            }	
            int operator++(int){
                int temp=coutnum;
				coutnum++;
				return temp;
            }			
			 void display(){
			    cout<<data<<"  "<<coutnum<<endl;
			 }
			 int get_coutnum(){
			    return coutnum;
			 }
			 void set_coutnum(int s_c){
			   coutnum=s_c;
			 }
			 char *get_data(){
			     return data;
			 }
			 void set_data(char *s_d){
			    data=s_d;
			 }
			~node_C(){
			   delete []data;
			}
 };
 //typedef struct node{
   // char *data;
	//int coutnum;
 //}node;
unsigned int simple_hash(const char *str)  
{  
    register unsigned int hash;  
    register  const  char *p;  
 
   for(hash = 0, p =str; *p ; p++)  
       hash = 31 * hash + *p;  
  
   return (hash & 0x7FFFFFFF)%MAX;  
}  

 //读单词文件，并把它列出来
ifstream& open_file(ifstream &in,const string &file){
     in.close();
  in.clear();
  in.open(file.c_str());
  return in;
 }
 class MakeminHeap{
   public:
        MakeminHeap(node_C *arr,int len);
		void MinHeapFixdown(node_C a[], int i, int n);
		void displayHead();
		void justHead(node_C *arr);
		~MakeminHeap(){delete []counum;}
    private: 
	         
	         node_C *counum;
             int num_len;
			 int arr_i;
 
 };
 MakeminHeap::MakeminHeap(node_C *arr,int len):num_len(len){
		  int i;
		  arr_i=0;
		  counum=new node_C[len];
	      for(i=0;i<M;i++,arr_i++){
	        while(arr_i<MAX){ 
	        if(arr[arr_i].get_data()!=NULL) {
            counum[i]=arr[arr_i];			
	        break;}
	        else arr_i++;
	        }
	      }
		   for (i = len / 2 - 1; i >= 0; i--)
		   MinHeapFixdown(counum, i, len);
 } 
 void MakeminHeap::MinHeapFixdown(node_C a[], int i, int n)
   {
      int j, temp;
	  node_C temp_n;
	  temp_n= a[i]; 
	  j = 2 * i + 1;
	   while (j < n)
	 {
		if (j + 1 < n && a[j + 1].get_coutnum() < a[j].get_coutnum()) //在左右孩子中找最小的
			j++;
		if (a[j].get_coutnum() >= temp_n.get_coutnum())
			break;
	//	a[i] = a[j];     //把较小的子结点往上移动,替换它的父结点
		a[i]=a[j];
		i = j;
		j = 2 * i + 1;
	 }
	a[i]=temp_n;
   }
 
 void   MakeminHeap::justHead(node_C *arr){
		  int i;
		  for(i=arr_i;i<MAX;i++){
              if(arr[i].get_coutnum()>counum[0].get_coutnum()){
			  counum[0]=arr[i];
	          MinHeapFixdown(counum, 0, num_len);
             }
          }
		}
 void MakeminHeap::displayHead(){
		   int i;
		   for(i=0;i<num_len;i++)
		      cout<<"<"<<counum[i].get_data()<<">"<<" has currented:"<<counum[i].get_coutnum()<<"times   "<<endl; 
		   cout<<endl;
}

 int main(int argc, char **argv)
 {
    int i;
    ifstream map_file;
	node_C  *arr=new node_C[MAX];
    if(argc!=2)
     throw runtime_error("wrong number of argument");
    if(!open_file(map_file,argv[1]))  throw runtime_error("wrong open of file");
    string word,line;
    while(getline(map_file,line)){
       istringstream stream(line);
       while(stream>>word)
     {	  
    	//cout<<word<<" ";//word 的string以空格为结尾。
	   const char *wor_temp=word.c_str();
	   unsigned int temp=simple_hash(wor_temp);
	   while(arr[temp].get_data()!=NULL){
       if(strcmp(arr[temp].get_data(),word.c_str())==0)
	      break;
		else 
            temp++;
	  }
       if(arr[temp].get_data()==NULL) {
	   // char *arr_t=new char[strlen(wor_temp)+1];
        //strcpy(arr_t,wor_temp);	
        //arr[temp].set_data(arr_t);	
         node_C temp_node=node_C(wor_temp);
         arr[temp]=temp_node;		 
       }	   
      // ++arr[temp];//有点不规范！
	   arr[temp].set_coutnum(arr[temp].get_coutnum()+1);
     }
    }
	 #ifdef DEBUG
	 for(i=0;i<MAX;i++)//进行对于arr进行堆的排序提取全10位
	     if(arr[i].get_data()!=NULL)
	       cout<<"<"<<arr[i].get_data()<<">"<<" have currented:"<<arr[i].get_coutnum()<<"times "<<endl;
		cout<<"*************************************************"<<endl;
    #endif
	
	MakeminHeap tempHeap(arr,M);
	//tempHeap.displayHead();
	tempHeap.justHead(arr);
	cout<<"display the ten most frequent words:"<<endl;
    tempHeap.displayHead();
 return 0;
 }







