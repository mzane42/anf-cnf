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

#include <stdio.h>
#include <stdlib.h> 

/***********************************************************************************************
*	The given algorithm for generating combinations is given by Donald Knuth and was the code
*	in C was taken from the link:http://www.daniweb.com/software-development/computer-science/threads/41584
*	The code was modified by Akshay Gupta to be abled to be used in the anf-cnf converter.
*************************************************************************************************/

void comgen(int n,int k,int *arr,int choice)
{
	int i, j=1, *c, x,count=0;
	
	c = malloc( (k+3) * sizeof(int));
 
	for (i=1; i <= k; i++) c[i] = i;
	c[k+1] = n+1;
	c[k+2] = 0;
	j = k;
visit:
	for (i=k; i >= 1; i--) 
	{
	
	
	arr[i-1]=c[i];
	
	}
	
	count++;
	if(count==choice)return;
	
	if (j > 0) {x = j+1; goto incr;}
	if (c[1] + 1 < c[2])
	 {
	 c[1] += 1;
	 goto visit;
	 }
	j = 2;
do_more:
	c[j-1] = j-1;
	x = c[j] + 1;
	if (x == c[j+1]) {j++; goto do_more;}
	if (j > k) return;
incr:
	c[j] = x;
	j--;
	goto visit;
}

/********************************************************************************************
*	The given function returns the number of variables in a given anf equation
*****************************************************************************************/
int nofvar(FILE *fs)
{
	
	char str[20],tmp[2]="t";
	int count=0;
	
	fscanf(fs,"%20[^|]|",str);
	while(strcmp(str,tmp))
	{
		count++;
		fscanf(fs,"%20[^|]|",str);
	}
	return count;

}

/********************************************************************************************
*	The given function returns the value of nCk
*****************************************************************************************/

int comval(int n,int k)
{	
	int nfac=1,kfac=1,i=0;
	for(i=n;i>(n-k);i--)
	{
		nfac*=i;
	}
	
	for(i=k;i>=1;i--)
	{
		kfac*=i;
	}

	return (nfac/kfac);
}

/********************************************************************************************
*	The given function alloctes values to the store array according to the parameters
*	of the anf equation.
*****************************************************************************************/

void calkeys(int *store,int nvar,int choice)
{
	
	int j;
	int ek=0,ok=1;
	if(choice==0)
	{
		j=0;
		while(ok<=nvar)
		{
			store[j]=ok;
			ok+=2;j++;
		}
		store[j]=-1;
	}
	
	else
	{
		j=0;
		while(ek<=nvar)
		{
			store[j]=ek;
			ek+=2;j++;
		}
		store[j]=-1;
	}
}



