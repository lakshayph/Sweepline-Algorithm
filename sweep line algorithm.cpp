//Phatela,Lakshay

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#include <bits.h>

using namespace std;

int left_rotations=0;
int right_rotations=0;
int p=0;
int q=0;
int g=0;
int h=0;
int a=0;
int z=0;
int m=0;
int v=0;
int o=0;
int min_d=999999;
int old_dist=0;
int min_distance=0;
int r=0;
int s=0;
int c[100000];
int d[100000];

struct T_Node // REFERENCE: www.geeksforgeeks.org/treap-set-2-implementation-of-search-insert-and-delete
{
    int key_y, priority, key_x;
    T_Node *left, *right;
};
 
T_Node* rightRotate(T_Node *b)
{
    right_rotations++;
	T_Node *a = b->left,  *T2 = a->right;
 
    // Perform rotation
    a->right = b;
    b->left = T2;
 
    // Return new root
    return a;
}
 
T_Node* leftRotate(T_Node *a)
{
	left_rotations++;
    T_Node *b = a->right, *T2 = b->left;
 
    // Perform rotation
    b->left = a;
    a->right = T2;
 
    // Return new root
    return b;
}
 
T_Node* newNode(int a,int b)
{
    T_Node* temp = new T_Node;
    temp->key_y = a;
	temp->key_x = b;
    temp->priority = rand()%100;
    temp->left = temp->right = NULL;
    return temp;
}

T_Node* insert(T_Node* root, int key_y, int key_x)
{
    if (!root)
        return newNode(key_y,key_x);
 
    if (key_y <= root->key_y)
    {
        root->left = insert(root->left, key_y, key_x);
 
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else 
    {
        
        root->right = insert(root->right, key_y, key_x);
         
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }

	return root;
}
 
T_Node* deleteNode(T_Node* root, int key_y, int key_x)
{
    if (root == NULL)
        return root;
 
    if (key_y < root->key_y)
        root->left = deleteNode(root->left, key_y, key_x);
    else if (key_y > root->key_y)
        root->right = deleteNode(root->right, key_y, key_x);

    // IF KEY IS AT ROOT
    else if((key_y == root->key_y)&&(key_x==root->key_x))
    {
     // If left is NULL
     if (root->left == NULL)
     {
		 T_Node *temp = root->right;
         delete(root);
         root = temp;  // Make right child as root
     }
 
     // If Right is NULL
     else if (root->right == NULL)
     {
         T_Node *temp = root->left;
         delete(root);
         root = temp;  // Make left child as root
     }

	     else if (root->left->priority < root->right->priority)
    {
        root = leftRotate(root);
        root->left = deleteNode(root->left, key_y, key_x);
    }
	  else
    {
        root = rightRotate(root);
        root->right = deleteNode(root->right, key_y, key_x);
    }


    }

	 else if ((root->left != NULL)&&(key_y == root->left ->key_y)&&(key_x==root->left->key_x))
	 {
		 root->left = deleteNode(root->left, key_y, key_x);
	}
 
    // If key is at root and both left and right are not NULL

   
 
    return root;
	
}

void traversal_inorder(T_Node* root, int data_y, int data_x)
{
	int temp;

    if (root)
    {
        traversal_inorder(root->left, data_y, data_x);

        /*
		cout << "key: "<< root->key_y << " | priority: %d "
            << root->priority;
        if (root->left)
            cout << " | left child: " << root->left->key_y;
        if (root->right)
            cout << " | right child: " << root->right->key_y;
        cout << endl;
		*/

		if(root->key_x >= (data_x-min_distance) && root->key_y <= (data_y + min_distance) && root->key_y >= (data_y - min_distance))
		{
			temp = (((data_x - root->key_x) * (data_x - root->key_x)) + ((data_y - root->key_y) * (data_y - root->key_y)));

			if(temp < old_dist)
			{
				old_dist = temp;

				p=data_x;
				q=data_y;
				g=root->key_x;
				h=root->key_y;
			}
		}

		else
		{
			c[r] = root->key_y;
			r++;
			d[s] = root->key_x;
			s++;
		}

        traversal_inorder(root->right, data_y, data_x);
    }
}
 
void sweep(T_Node* root, int (&data_x)[100000], int (&data_y)[100000], int &n)
{
	for(int i=0;i<n;i++)
	{
		
		if(i==0)
		{
		 
		 root = insert(root, data_y[i], data_x[i]); 
		 o++;
		}
		
		else if(i==1)
		{
		 old_dist = (((data_x[1]-data_x[0])*(data_x[1]-data_x[0]))+((data_y[1]-data_y[0])*(data_y[1]-data_y[0])));
		
		 
		 root = insert(root, data_y[i], data_x[i]);
		 o++;

		 min_distance = old_dist;

		 
		}

		else 
		{
			r=s=0;
			traversal_inorder(root, data_y[i], data_x[i]);
			
			root = insert(root, data_y[i], data_x[i]);
			o++;
			
			
			 for(int k=0;k<r;k++)
			 {
				root = deleteNode(root, c[k], d[k]);
				o--;
			}

			if(old_dist < min_distance)
			{
				min_distance = old_dist;
			}
	    }
	}
}

void quickSort(int (&data_x)[100000], int (&data_y)[100000], int l, int r) /* REFERENCE: stackoverflow.com/questions/11975214/quick-sort-code-explanation */
 {
  int i = l, j = r;
  int temp,temp1;
  int p = data_x[abs((l + r) / 2)];
  
  while (i <= j) {
        while (data_x[i] < p)
              i++;
        while (data_x[j] > p)
              j--;
        if (i <= j) {
              temp = data_x[i];
			  temp1 =data_y[i];
              data_x[i] = data_x[j];
			  data_y[i] = data_y[j];
              data_x[j] = temp;
			  data_y[j] = temp1;
              i++;
              j--;
    }
}
  
       if (l < j)
        quickSort(data_x, data_y, l, j);

       if (i < r)
        quickSort(data_x, data_y, i, r);

	   //for(int i=0;i<5;i++)
        //cout<<endl<<data_x[i]<<" "<<data_y[i]<<endl ;

}

void remove_duplicate(int (&data_x)[100000],int (&data_y)[100000], int &n)
{
	int i,j,k;
	   for(i=0;i<n;i++)
	   {
		for(j=i+1;j<n;j++)
		{
		 if((data_x[i]==data_x[j])&&(data_y[i]==data_y[j]))
		 {
		  for(k=j;k<n-1;k++)
		  {
			data_x[k]=data_x[k+1];
			data_y[k]=data_y[k+1];
		  }
		  n--;
		 }
		}
	   }

	//for(i=0;i<n;i++)
		//cout<<data_x[i]<<data_y[i]<<endl;
}

void bruteforce(int (&data_x)[100000], int (&data_y)[100000], int &n)
{
	int t;
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i!=j)
			{
				t=(data_x[i]-data_x[j])*(data_x[i]-data_x[j])+(data_y[i]-data_y[j])*(data_y[i]-data_y[j]);
				
				if(min_d>t)
				{
					 min_d=t;
					 a=data_x[i];
					 z=data_y[i];
					 m=data_x[j];
					 v=data_y[j];
				}
			
		     }
         }
    }
}

int main()
{
  	/*
	//for dynamic input
  int n;
  cout<<"Enter the number of points: ";
  cin>>n;
   		
  int **data = new int*[n];

  for(int i=0; i<n; i++)
  {
   data[i]=new int[2];
  }

  for(int i=0;i<n;i++)
  {
   for(int j=0;j<2;j++)
   {
    cin>>data[i][j];
   }
  }
  
  //output
for(int i=0;i<10;i++)
{
 for(int j=0;j<10;j++)
 {
  cout<<d[i][j]<<"/t";
 }
 cout<<endl;
}

   delete []data;
 */

    srand(time(NULL));
    struct T_Node *root = NULL;

	int d_x[100000];
    int d_y[100000];
    int n;

	flag:
	cout<<"Enter the number of points you want to enter."<<endl;
    cin>>n; //input number of points

	if(n>100000000)
	{
		cout<<endl<<"Number of points can not exceed 100000000. Please re-enter the number of points.";
		goto flag;
	}
	
    for(int i=0;i<n;i++) //input x and y dimensions of points
    {
     cin>>d_x[i]>>d_y[i];

	 if((d_x[i] < (-16000) || d_x[i] > 16000) || (d_y[i] < (-16000) || d_y[i] > 16000))
	 {
		 cout<<endl<<"Value entered is out of bounds. Please re-enter the values.";
		 goto flag;
	 }
    }

	clock_t s2 = clock();
    quickSort(d_x, d_y, 0, n-1); //calling quicksort
	clock_t e2 = clock();
	double t2 = double(e2-s2)/CLOCKS_PER_SEC; //calculating time for quicksort

	cout<<endl<<"sorting "<<n<<endl; //printing number of points

    remove_duplicate(d_x, d_y, n); //removing duplicate points

	clock_t s = clock();
	bruteforce(d_x, d_y, n); //calling bruteforce
	clock_t e = clock();
	double t = double(e-s)/CLOCKS_PER_SEC; //calculating time for bruteforce

	clock_t s1 = clock();
	sweep(root, d_x, d_y, n); // calling sweep line
	clock_t e1 = clock();
	double t1 = double(e1-s1)/CLOCKS_PER_SEC; //calculating time for sweep line algorithm

	cout<<"qsort time "<<t2<<endl;
	cout<<"duplicate removal"<<endl;
	cout<<"closest pair ("<<p<<","<<q<<") ("<<g<<","<<h<<") at distance "<<min_distance<<endl;
	cout<<"sweep time "<<t1<<endl<<"max BST nodes "<<o;
	cout<<endl<<"Rotations: "<<left_rotations<<" with left "<<right_rotations<<" with right"<<endl;
	cout<<"closest pair ("<<m<<","<<v<<") ("<<a<<","<<z<<") at distance "<<min_d<<endl;
	cout<<"bruteforce time "<<t;  

	getch(); 
    return 0;
}

