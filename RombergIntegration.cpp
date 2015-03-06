#include "RombergIntegration.h"
#include "RecursiveIntegration.h"
#include "QueueLinked.h"
#include "Double.h"
using CSC2110::Double;

#include <math.h>

//a is the lower limit and b is the upper limit
double RombergIntegration::accurateRomberg(MultiVarFunction* f, double a, double b, int level)
{
   Double* db;  //use this variable to place and retrieve values on the queue
   Double* temp_db; //a temporary variable used to work with values returned as primitives
   
   QueueLinked<Double>* q1 = new QueueLinked<Double>;//you often referred to this as qu1
   QueueLinked<Double>* q2 = new QueueLinked<Double>;//and this as qu2. I changed that
   QueueLinked<Double>* q3; //for swapping

   int n = 1;  //current number of intervals
   int counter = 0;
   while (counter < (level + 1))      //won't always be computing on level 4   
   {
      //DO THIS
	  
	  //!!!Where do we do this?
      //obtain the required number of trapezoid evaluations depending on the number of levels requested 
	  //!!!And where do we use this information?
      
	  //put all of the level 0 results on the q1

      db = new Double(RecursiveIntegration::romberg(f, a, b, n)); //f is the parameter name
	  //store the value from RecursiveIntegration as a Double* into db

	  //converted the return value of the RecursiveIntegration function to Double as defined in the CSC2110 namespace(originally returned a primitive) and stored
	  //it in the thing stored at the memory address of db since db is a pointer
	  
      q1->enqueue(db); //you had this mispelled enque and not enqueue

      n = 2*n;  //double the number of intervals
      counter++; 
   }
   //q1 now has all of the level 0 integration results

   int power = 1;  //k, used to compute the Romberg Factor
   double factor = pow (4, power);  //use this to compute the current Romberg Factor (4^k stuff)


   //if level 0 has been requested, the loop will not execute
   //the total number of executions of the loop is ??

   //DO THIS
   int iterations = level;             //can be precomputed
   while (iterations > 0)
   {
        //k, used to compute the Romberg Factor
      double factor = pow (4, power);  //use this to compute the current Romberg Factor (4^k stuff)

      Double* il; //our QueueLinked class is storing pointers to a templated type Double class, not primitives, so I declared them as such
      Double* im; //""
	  double il_val; //These are used to store the primitive values from il
	  double im_val; //and im. They are not neccessary. They are placed in for readability purposes only.
	  
      //DO THIS
      //use the algorithm described in the lab to improve the accuracy of your level 0 results
	  int its = q1->size();
      for (int i = 1; i < (its); i++)
      {  
         il = q1->dequeue();
         im = q1->peek();
		 il_val = il->getValue(); //gets the value from il and stores it
		 im_val = im->getValue();// gets the value from im and stores it
         db = new Double(((factor * im_val) - il_val) / (factor-1)); //store the result of the calculation as a new Double* into db
         q2->enqueue(db);
         if (q1->size() == 1)
         {
            il = q1->dequeue();
            
			delete il;
         }
      }
	  
		q3 = q1; //this is the proper method for swapping using a temporary variable (q3)
		q1 = q2;
		q2 = q3;
		
      power++;
      iterations--;
   }
   //obtain the final answer
   db = q1->dequeue();
   double result = db->getValue();  
   delete db;

   delete q1;
   delete q2;

   return result;
}