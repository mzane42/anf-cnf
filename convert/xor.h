/*******************************************************************************************************
*	This software is developed by Akshay Gupta.

*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
*	IN THE SOFTWARE.


*********************************************************************************************************/

/*******************************************************************************************************
*	The header file cal.h has been custom made and if chnages are made to the 
*	source code then please change the address of the header files to the new location.
*	The header file cal.h contains four functions comgen(),calkeys(),comval() anf nofvar().
*	Their description has been given in the Header file.
********************************************************************************************************/


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include </home/akshay/anf-cnf/cal.h>


void xor()
{
	char tmps[2]=" ";
	char tmpc[2]="-";
	char tmpt[2]="t";
	char tmp0[3]="0\n";
	char strtmp[10];

	FILE *fread,*fwrite;
	fread=fopen("output.txt","r");
	fwrite=fopen("cnf.txt","a");
	long pos;
	
	int no_of_var,choice,i,j,count,*store,*arr,k,val;
	fscanf(fread,"%s",strtmp);
	fscanf(fread,"%s",strtmp);
	while(!feof(fread))
	{//1
		pos=ftell(fread);
		
		fscanf(fread,"%10[^|]|",strtmp);
		choice=atoi(strtmp);// To determine the constant

		no_of_var=nofvar(fread);// To get the number of monomials in the equation
		fseek(fread,pos,SEEK_SET);

		
		
		

		if(no_of_var%2)
			store=malloc(sizeof(int)*((no_of_var/2)+2));

		if(((no_of_var%2)==0)&(choice==1))
			store=malloc(sizeof(int)*((no_of_var/2)+2));

		if(((no_of_var%2)==0)&(choice==0))
			store=malloc(sizeof(int)*((no_of_var/2)+1));

		calkeys(store,no_of_var,choice);
		
		i=0;
		while(store[i]!=-1)
		{//2
			k=store[i];
			

			val=comval(no_of_var,k);
			
			fseek(fread,pos,SEEK_SET);
			
			arr=malloc(sizeof(int)*k);
			for(choice=1;choice<=val;choice++)
			{//3
				fseek(fread,pos,SEEK_SET);
				count=1;j=0;
				comgen(no_of_var,k,arr,choice);
				
				fscanf(fread,"%10[^|]|",strtmp);
				fscanf(fread,"%10[^|]|",strtmp);
				while(strcmp(strtmp,tmpt))
				{//4
					
					if(count==arr[j])
					{
						fputs(tmpc,fwrite);
						fputs(strtmp,fwrite);
						fputs(tmps,fwrite);
						count++;j++;
					}
					
					else
					{
						fputs(strtmp,fwrite);
						fputs(tmps,fwrite);
						count++;
					}
					fscanf(fread,"%10[^|]|",strtmp);
				}//4
				fputs(tmp0,fwrite);
			}//3
			i++;
			free(arr);
		}//2
		i=fgetc(fread);
		pos=ftell(fread);
		i=fgetc(fread);
		if(i!=-1)
			fseek(fread,pos,SEEK_SET);
		free(store);
	}//1
	fclose(fread);
	fclose(fwrite);
	remove("output.txt");
}

void counteq()
{
	FILE *fread,*fwrite;
	fread=fopen("cnf.txt","r");
	fwrite=fopen("cnf1.txt","w");
	
	char str[100];
	fscanf(fread,"%s",str);
	fscanf(fread,"%s",str);
	fscanf(fread,"%s",str);
	int count=0,ch;
	char c2;
	long pos;
	while(!feof(fread))
	{
		fscanf(fread,"%s",str);
		
		ch=fgetc(fread);
		pos=ftell(fread);
		c2=(char)ch;
		if(ch=='\n')
			count++;
		ch=fgetc(fread);
		if(ch!=-1)
			fseek(fread,pos,SEEK_SET);
	}
	fseek(fread,0l,SEEK_SET);
	char tmpe[]=" ";
	fscanf(fread,"%s",str);
	fputs(str,fwrite);
	fputs(tmpe,fwrite);
	fscanf(fread,"%s",str);
	fputs(str,fwrite);
	sprintf(str,"%d",count);
	
	fputs(tmpe,fwrite);
	fputs(str,fwrite);
	char tmpt[]="\n";
	char tmp0[]="0";
	fputs(tmpt,fwrite);
	fscanf(fread,"%s",str);
	while(!feof(fread))
	{
		fscanf(fread,"%s",str);
		fputs(str,fwrite);
		fputs(tmpe,fwrite);
		ch=fgetc(fread);
		pos=ftell(fread);
		ch=fgetc(fread);
		if(ch!=-1)
			fseek(fread,pos,SEEK_SET);
		if(!strcmp(str,tmp0))
			fputs(tmpt,fwrite);
	}
	char tmps[]="\0";
	fputs(tmps,fwrite);
	fclose(fread);
	fclose(fwrite);
	char old2[]="cnf1.txt";
	char new2[]="cnf.txt";
	remove("cnf.txt");
	rename(old2,new2);
}	

