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

# include <stdio.h>
# include <string.h>
# include <stdlib.h>



/********************************************************************************************
*	This function is used to clear a given string buffer and replace all charachter with ' '.
*****************************************************************************************/
void clearstr(char *str,int limit)
	{
	int i=0;
	for(;i<limit;i++)
		str[i]=' ';
	}

/********************************************************************************************
*	The checks whether the given monomial has already been subsituted or not.
*****************************************************************************************/
	
int strcheck(char *str,int nvar)
	{
	int pos=nvar+1;
	char str2[100];
	FILE *fr;
	fr=fopen("temp.txt","r");
	
	if(fr==NULL)
		return 0;
	else
		{
		fscanf(fr,"%s",str2);
		while(!feof(fr))
			{	
			if(!strcmp(str,str2))
				{
				return pos;// If it is subsituted we return its previous position
				}
			else
				{
				fscanf(fr,"%s",str2);
				pos++;
				}
			}
		}
	return 0;// If it has not been subsituted then it 0 is returned
	}

/********************************************************************************************
*	This function subsitutes monomials containing 'AND' in them with repective 
*	cnf clause.
*****************************************************************************************/
 void sub(char * str2) 
	{
	// Predefined strings to add in the cnf file
	char tmps[2]=" ";
	char tmp0[3]="\n0";
	char tmp1[3]="\n1";
	char tmpc[2]="-";
	char tmpt[2]="t";
	char tmpb[2]="|";
	char tmp[2]="\n";	
	char tmpp[2]="p";
	char str[100],strtmp[10],ch;
	int k,n=0,i,nvar,c1,j,num,pos;
	
	
	FILE *fr,*fw,*ftemp;
	fr=fopen(str2,"r");
	fw=fopen("output.txt","w");
	
	fscanf(fr,"%s",strtmp);
	fputs(strtmp,fw);
	fputs(tmps,fw);
	fscanf(fr,"%s",strtmp);
	nvar=atoi(strtmp);
	fscanf(fr,"%20[^|]|",str);

	while(!feof(fr))
		{
		fputs(str,fw);
		fputs(tmpb,fw);
		fscanf(fr,"%20[^|]|",str);// To read a monomial
		i=0;c1=0;
		while(strcmp(tmpt,str))// To check for the end of the monomial
			{
			c1=0,i=0;
			while(str[i]!='\0')
				{
				if(str[i]==',') // To check whether the monomial cointains 'AND' or not.
					{
					c1=1;
					break;
					}
				i++;
				}
		
			if(c1==0)// If c1=0 then the monomial does not contain 'AND' and will be written as it is.
				{
				fputs(str,fw);
				fputs(tmpb,fw);
				
				}
			else
				{
				c1=strcheck(str,nvar);
				if(c1)
					{
					sprintf(strtmp,"%d",c1);
					fputs(strtmp,fw);
					fputs(tmpb,fw);
					}
				else // To subsitute the variable and record it in temp.txt
					{
					ftemp=fopen("temp.txt","a");
					fputs(str,ftemp);
					fputs(tmp,ftemp);
					fclose(ftemp);
					c1=strcheck(str,nvar);
					pos=c1;
					sprintf(strtmp,"%d",c1);
					fputs(strtmp,fw);
					fputs(tmpb,fw);
					}
				}
			fscanf(fr,"%20[^|]|",str);
			}
		fputs(str,fw);
		fputs(tmpb,fw);
		fscanf(fr,"%20[^|]|",str);
		}
	fclose(fr);
	fclose(fw);
	fr=fopen("temp.txt","r");
	fw=fopen("cnf.txt","w");	
	fputs(tmpp,fw);
	fputs(tmps,fw);
	sprintf(strtmp,"%d",pos);
	fputs(strtmp,fw);
	fputs(tmp,fw);
	
	char zero[3]="0\n";
	char tess[10];
	int eq=0;
	
	fscanf(fr,"%s",str);
	while(!feof(fr))
		{
		nvar++;
		sprintf(tess,"%d",nvar);
		fputs(tess,fw);
		fputs(tmps,fw);
		i=0,j=0;
		while(str[i]!='\0')
			{
			fputs(tmpc,fw);
			j=0;
			while((str[i]!=',')&&(str[i]!='\0'))
				{
				strtmp[j]=str[i];
				j++;i++;
				}
			if(str[i]!='\0')
				i++;
			num=atoi(strtmp);
			clearstr(strtmp,10);
			sprintf(strtmp,"%d",num);
			fputs(strtmp,fw);
			fputs(tmps,fw);
			clearstr(strtmp,10);
			}
		fputs(zero,fw);
		eq++;
		i=0,j=0;
		while(str[i]!='\0')
			{
			fputs(tmpc,fw);
			fputs(tess,fw);
			fputs(tmps,fw);
			j=0;
			while((str[i]!=',')&&(str[i]!='\0'))
				{
				strtmp[j]=str[i];
				j++;i++;
				}
			if(str[i]!='\0')
				i++;
			num=atoi(strtmp);
			clearstr(strtmp,10);
			sprintf(strtmp,"%d",num);
			fputs(strtmp,fw);
			fputs(tmps,fw);
			clearstr(strtmp,10);
			fputs(zero,fw);
			eq++;
			}
		fscanf(fr,"%s",str);
		}
	fclose(fw);
	remove("temp.txt");
	fw=fopen("output1.txt","w");
	fr=fopen("output.txt","r");
	
	c1=fgetc(fr);
	ch=(char)c1;
	c1=fputc(ch,fw);
	
	c1=fgetc(fr);
	ch=(char)c1;
	c1=fputc(ch,fw);
	
	sprintf(strtmp,"%d",nvar);
	fputs(strtmp,fw);
	c1=fgetc(fr);
	while(!feof(fr))
		{
		
		ch=(char)c1;
		c1=fputc(ch,fw);
		c1=fgetc(fr);
		}
	fclose(fr);
	fclose(fw);
	remove("output.txt");
	char old[20]="output1.txt";
	char new[20]="output.txt";
	
	rename(old,new);

	fw=fopen("cnf1.txt","w");
	fr=fopen("cnf.txt","r");
	
	c1=fgetc(fr);
	ch=(char)c1;
	c1=fputc(ch,fw);
	
	c1=fgetc(fr);
	ch=(char)c1;
	c1=fputc(ch,fw);
	
	sprintf(strtmp,"%d",nvar);
	fputs(strtmp,fw);
	
	c1=fgetc(fr);
	
	fputs(tmps,fw);
	sprintf(strtmp,"%d",eq);
	fputs(strtmp,fw);
	fscanf(fr,"%s",strtmp);
	
	c1=fgetc(fr);
	while(!feof(fr))
		{
		
		ch=(char)c1;
		
		c1=fputc(ch,fw);
		c1=fgetc(fr);
		}
	fclose(fr);
	fclose(fw);
	remove("cnf.txt");
	char old1[20]="cnf1.txt";
	char new1[20]="cnf.txt";
	
	rename(old1,new1);
	
	}
									
				
