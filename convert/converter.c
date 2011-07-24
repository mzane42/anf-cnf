/*******************************************************************************************************
*	This software is developed by Akshay Gupta.
*	It is under GNU GPL 3.

*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
*	IN THE SOFTWARE.


*********************************************************************************************************/

/*******************************************************************************************************
*	The header files xor.h and subsitution.h have been custom made and if chnages are made to the 
*	source code then please change the address of the header files to the new location.
*	The header file xor.h contains two functions xor and counteq. xor() converts anf equations with unit monomials to 
*	respective cnf equations. counteq() function is used to calculate the total number of equations in the cnf file.
*	The header file subsitution.h contains the function called sub(). It subsitutes all monomials containing 'AND'
*	with respective cnf clauses.
********************************************************************************************************/


# include <stdio.h>
# include <stdlib.h>
# include </home/akshay/anf-cnf/xor.h>
# include </home/akshay/anf-cnf/subsitution.h>


/************************************************************************************

*	The main() function only serves as a menu to call upon other functions in the header files

********************************************************************************/

void main(int argc,char * argv[])
{
	sub(argv[1]);
	xor();
	counteq();		
}

