

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "sample_p5.h"

using namespace std;

ofstream output_file6("out.6", ios::app);

class LINEAR_SOLVER: public MATRIX{
   public:
	LINEAR_SOLVER(int);  
			// constructor; example: s.LINEAR_SOLVER(5);
			// there are 5 equations and 5 variables;

	void SOLVE_LINEAR_EQUATION(char *); 
			// example: s.SOLVE_LINEAR_EQUATION("ASCEND");
			// solve the linear equations and
			// sort the output in ascending order;
			// if the input is "DESCEND" then the order
			// of the output is descending;
			// returns no values;

	void SOLVE_BY_MATLAB(void); 
			// example: s.SOLVE_BY_MATLAB();
			// generate and run a MATLAB program to 
			// solve a set of linear equations;
			// returns no values;

	void INHERITED_INVERT(void); 
			// example: s.INHERITED_INVERT();
			// perform matrix inversion on
			// the input system by inheriting
			// from PROGRAM_BANK class;
			// returns no values;

	void INVERT_BY_MATLAB(void); 
			// example: s.INVERT_BY_MATLAB();
			// generate and run a MATLAB program to 
			// invert a matrix;
			// returns no values;
   private:
	int n; 		// max of n is 50
	float A[50][50];
	float B[50];
};


LINEAR_SOLVER::LINEAR_SOLVER(int x)
  	:MATRIX(x, x, "in.6") 	// instantiate MATRIX with input file in.6 and 
  				// dim1=x, dim2=x;
{
int i = 0;
int j = 0;
	
	// your code for LINEAR_SOLVER constructor goes here
	
	n = x;
  	ifstream input("in.6", ios::in);
  	for(int i=0;i<n;i++)
	{
  		B[i]=0;
  		for(int j=0;j<n;j++)
		{
      			A[i][j]=0;
    		}
  	}   
  	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
		      input>>A[i][j];
		}
	}
  	for(int i=0;i<n;i++)
	{
		input>> B[i];
	}	
	output_file6 << " ********** P6 BEGIN ************* " << endl;
	output_file6 << " *** OUTPUT FROM P6_LINEAR_SOLVER: " << endl;
        output_file6 << " *** INSTANTIATED AN OBJECT WITH " << n << " EQUATIONS " << endl;
        output_file6 << " *********** P6 END ************** " << endl;





}
void 
LINEAR_SOLVER::SOLVE_LINEAR_EQUATION(char * commd)
{
int column;
int row, i, j, k;
int find=1;
float multiply, temp, sum;   
float temp_A[50][50];
float temp_B[50];
float X[50];
int temp_pos[50], minp, maxp, temp1;
float temp_v[50], minv, maxv, temp2;
	
	for(column=0; column<n;column++)
	{
    		temp_B[column]=B[column];
    		for(row=0; row<n; row++)
		{
      			temp_A[column][row]=A[column][row];
    		}
  	}               
  	for(column=0;column<n&&find==1; column++)
	{                   
    		if(temp_A[column][column]==0)
		{
      			find=0;
      			for(i=column+1;i<n&&find==0;i++)
			{
    				if(temp_A[i][column]!=0)
				{
      					temp=temp_B[column];
      					temp_B[column]=temp_B[i];
      					temp_B[i]=temp;
      					
					for(j=0;j<n;j++)
					{
        					temp=temp_A[column][j];
        					temp_A[column][j]=temp_A[i][j];
        					temp_A[i][j]=temp;
      					}                   
      					find=1;
    				}
      			}
    		}       
    		else{   
      			for(row=column+1;row<n;row++)
			{
    				multiply= (-1*temp_A[row][column])/(temp_A[column][column]);
    				
				for(i=column;i<n;i++)
				{
      					temp_A[row][i]=(multiply*temp_A[column][i])+temp_A[row][i];
    				}
    				temp_B[row]=(multiply*temp_B[column])+temp_B[row];
      			}
    		}
  	}
  	if(find==0)
	{
    		output_file6 << " ********** P6 BEGIN *************"<<endl;
    		output_file6 << " *** MY GAUSSIAN ELIMINATION SOLUTION:"<<endl;
    		output_file6 << " *** EQUATION IS SINGULAR"<<endl;
    		output_file6 << " *********** P6 END **************"<<endl;
  	}
  	else{   
    		for(row=n-1;row>=0;row--)
		{
      			sum=0;
      			for(k=n-1;k>row;k--)
			{
    				sum+=temp_A[row][k]*X[k];
      			}
      			X[row]=(temp_B[row]-sum)/temp_A[row][row];
    		}
    		if(strcmp(commd, "NONE")==0)
		{
     	 		output_file6 << " ********** P6 BEGIN *************"<<endl;
          		output_file6 << " *** MY GAUSSIAN ELIMINATION SOLUTION (SORTED IN ASCENDING ORDER):" << endl;
      		
			for(i=0;i<n;i++)
			{
    				output_file6 << " X["<<temp_pos[i]<<"]= " << setprecision(2) << setiosflags(ios::fixed | ios::showpoint) << X[i] <<endl;
      			}
      			output_file6<<"*********** P6 END **************"<<endl;
    		}
    		else if(strcmp(commd, "ASCEND")==0)
		{
      			for(i=0;i<n;i++)
			{
    				temp_pos[i] = i;
    				temp_v[i] = X[i];
    			}
      			for(i=0;i<n;i++)
			{
    				
				minv=temp_v[i];
    				minp=i;
    				
				for(j=i;j<n;j++)
				{
      					if (temp_v[j]<minv)
					{
        					minv=temp_v[j];
        					minp=j;
      					}
      					else{}
				}   
    				temp1=temp_pos[i];
    				temp_pos[i]=temp_pos[minp];
    				temp_pos[minp]=temp1;
    			
				temp2=temp_v[i];
    				temp_v[i]=temp_v[minp];
    				temp_v[minp]=temp2;
      			}           
      
			output_file6 << " ********** P6 BEGIN *************"<<endl;
      			output_file6 << " *** MY GAUSSIAN ELIMINATION SOLUTION (SORTED IN ASCENDING ORDER):"<<endl;
      			
			for(i=0;i<n;i++)
			{
    				output_file6<<"X["<<temp_pos[i]<<"]= " <<setprecision(2) <<setiosflags(ios::fixed | ios::showpoint) <<temp_v[i] <<endl;
      			}
      			output_file6<<"*********** P6 END **************"<<endl;
    		}
    		else if(strcmp(commd, "DESCEND")==0)
		{
      			for(i=0;i<n;i++)
			{
    				temp_pos[i] = i;
    				temp_v[i]=X[i];
    			}
      			for(i=0;i<n;i++)
			{
    				maxv= temp_v[i];
    				maxp=i;
    				for(j=i;j<n;j++)
				{
      					if(temp_v[j]>maxv)
					{
        					maxv=temp_v[j];
        					maxp=j;
      					}
      					else{}
    				}   
    				temp1=temp_pos[i];
    				temp_pos[i]=temp_pos[maxp];
    				temp_pos[maxp]= temp1;
    				temp2=temp_v[i];
    				temp_v[i]=temp_v[maxp];
    				temp_v[maxp]=temp2;
      			}
     
      			output_file6 << " ********** P6 BEGIN *************"<<endl;
      			output_file6 << " *** MY GAUSSIAN ELIMINATION SOLUTION (SORTED IN DESCENDING ORDER):"<<endl;
      			
			for(i=0;i<n;i++)
			{
    				output_file6 << "X[" <<temp_pos[i] << "]= "<<setprecision(2) <<setiosflags(ios::fixed | ios::showpoint) <<temp_v[i] <<endl;
      			}
      			output_file6<<"*********** P6 END **************"<<endl;
    		}
    		else{}
  	}   
}
void
LINEAR_SOLVER::SOLVE_BY_MATLAB()
{
int i,j;
char copying[100];
	
	ofstream matlabout_file("out_62.m", ios::out);    
    
     	matlabout_file<<"A=[";    
     	
	for(i=0;i<n;i++)
	{
      		matlabout_file<<A[i][0];
      		for(j=1;j<n;j++)
		{
        		matlabout_file<<","<<A[i][j];
      		}
      		if(i==n-1)
		{
        		matlabout_file<<"];"<<endl;
      		}
      		else{
        		matlabout_file<<";";
      		}
     	}
     	
	matlabout_file<<"B=["<<B[0];
     	
	for(i=1;i<n;i++)
	{
      		matlabout_file<<";"<<B[i];
     	}
     	matlabout_file<<"];"<<endl;
     	matlabout_file<<"X=inv(A)*B;"<<endl;
        matlabout_file<<"fid=fopen('out.6','a');"<<endl;
        matlabout_file<<"fprintf(fid,'********** P6 BEGIN *************\\n');"<<endl;
        matlabout_file<<"fprintf(fid,'*** RESULT FROM MATLAB (UNSORTED):\\n');"<<endl;
        matlabout_file<<"for k=1:"<<n<<endl;
        matlabout_file<<"fprintf(fid,'X[%d]=%6.2f\\n',k-1,X(k));"<<endl;
        matlabout_file<<"end"<<endl;

    	matlabout_file<<"fprintf(fid,'*********** P6 END **************\\n');"<<endl;
    	system("/bin/csh /usr/tools/EE259/IO/run_out_62");
}
void 
LINEAR_SOLVER::INHERITED_INVERT()
{
int i, j;
char copying[100];
	
	ofstream out_file2("in.6", ios::out);
  	ifstream in_file2("out.5", ios::in);
  
	for(i=0;i<n;i++)
	{
    		for(j=0;j<n;j++)
		{
      			out_file2<<A[i][j]<< " ";
    		}
    		out_file2 << endl;
  	}	
	MATRIX temp_m(n, n,"in.6"); // create a temp matrix from in.6 file;

	1/temp_m; // use the friend function in MATRIX for inversion;
	
	output_file6<<"********** P6 BEGIN *************"<<endl;
  	output_file6<<"*** AFTER INHERITING FROM MATRIX CLASS, MY RESULT IS:"<<endl;
  	
	for(i=0;!in_file2.eof();i++)
	{
    		in_file2.getline(copying ,100,'\n');
    		if(i>2&&!in_file2.eof())
		{
      			output_file6<<copying <<endl;
    		}
    		else{}
  	}
  	output_file6<<"*********** P6 END **************"<<endl;


}

void
LINEAR_SOLVER::INVERT_BY_MATLAB()
{
int i, j;
char copying[100];
 
	ofstream matlabout_file2("out_63.m", ios::out);
	
	matlabout_file2<<"A=[";    
 
	for(i=0;i<n;i++)
	{
   		matlabout_file2<<A[i][0];
   		for(j=1;j<n;j++)
		{
     			matlabout_file2<<","<<A[i][j];
   		}
   		if(i==n-1)
		{
     			matlabout_file2<<"];"<<endl;
   		}
   		else{
     			matlabout_file2<<";";
   		}
 	}
 	matlabout_file2<<"X=inv(A);"<<endl;
   	matlabout_file2<<"fid=fopen('out.6','a');"<<endl;
	matlabout_file2<<"fprintf(fid,'********** P6 BEGIN *************\\n');"<<endl;
	matlabout_file2<<"fprintf(fid,'*** INVERSION RESULT FROM MATLAB: \\n');"<<endl;
	matlabout_file2<<"for i=1:"<<n<<endl;
	matlabout_file2<<"for j=1:"<<n<<endl;
	matlabout_file2<<"fprintf(fid,'X[%d][%d]=%6.2f ',i-1,j-1,X(i,j));"<<endl;
	matlabout_file2<<"end"<<endl;
	matlabout_file2<<"fprintf(fid,'\\n');"<<endl;
	matlabout_file2<<"end"<<endl;
        matlabout_file2<<"fprintf(fid,'*********** P6 END **************\\n');"<<endl;
 	system("/bin/csh /usr/tools/EE259/IO/run_out_63");
    
}
