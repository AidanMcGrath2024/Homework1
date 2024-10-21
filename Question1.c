#include <stdio.h>
#include <math.h>

int main() {
  //Plane Limitations
  const float maxallowablegrossweight = 2950; //pounds
  const float forwardCGlimit = 82.1; //inches
  const float aftCGlimit = 84.7; //inches 

  //Airplane Empty Weight User Input
  printf("What is the empty weight of the airplane? Type the weight in pounds and press enter: \n");
  int emptyweight;
  scanf("%d", &emptyweight);

  //Airplane Empty Weight Moment User Input
  printf("What is the empty weight moment of the airplane? Type the weight in pounds-inches and press enter: \n");
  int emptyweightmoment;
  scanf("%d", &emptyweightmoment);
  
  //Front Seat Occupant Total Weight User Input
  printf("How many passengers will be flying in the front? Type the number of passengers and press enter: \n");
  int frontseatoccupants;
  scanf("%d", &frontseatoccupants);
  int weightfrontseatoccupants = 0;
  for (int frontpassengerindex = 1; frontpassengerindex < (frontseatoccupants+1); frontpassengerindex++)
  {
    int weightoffrontseatoccupant;
    printf("What is the weight of passenger %d in the front? Type the weight of passenger in pounds and press enter: \n",frontpassengerindex);
    scanf("%d", &weightoffrontseatoccupant);
    weightfrontseatoccupants = weightfrontseatoccupants + weightoffrontseatoccupant;
  }

  //Front Seat Moment Arm User Input
  printf("What is the front seat moment arm? Type the length in inches and press enter: \n");
  int frontseatmomentarm;
  scanf("%d", &frontseatmomentarm);

  //Rear Seat Occupant Total Weight User Input
  printf("How many passengers will be flying in the rear? Type the number of passengers and press enter: \n");
  int rearseatoccupants;
  scanf("%d", &rearseatoccupants);
  int weightrearseatoccupants = 0;
  for (int rearpassengerindex = 1; rearpassengerindex < (rearseatoccupants+1); rearpassengerindex++)
  {
    int weightofrearseatoccupant;
    printf("What is the weight of passenger %d in the rear? Type the weight of passenger in pounds and press enter: \n",rearpassengerindex);
    scanf("%d", &weightofrearseatoccupant);
    weightrearseatoccupants = weightrearseatoccupants + weightofrearseatoccupant;
  }

  //Rear Seat Moment Arm User Input
  printf("What is the rear seat moment arm? Type the length in inches and press enter: \n");
  int rearseatmomentarm;
  scanf("%d", &rearseatmomentarm);

  //Gallons of Fuel User Input
  printf("How many gallons of fuel is usable? Type the volume of fuel in gallons and press enter: \n");
  int usablefuel;
  scanf("%d", &usablefuel);

  //Usable Fuel Weight per Gallon User Input
  printf("What is the weight per gallon of the usable fuel? Type the conversion in pounds per gallon and press enter: \n");
  int fuelweightpergallon;
  scanf("%d", &fuelweightpergallon);

  //Fuel Tank Moment Arm User Input
  printf("What is the fuel tank's moment arm? Type the length in inches and press enter: \n");
  int fueltankmomentarm;
  scanf("%d", &fueltankmomentarm);

  //Baggage Weight User Input
  printf("What is the total baggage weight? Type the weight in pounds and press enter: \n");
  int baggageweight;
  scanf("%d", &baggageweight);

  //Baggage Moment Arm User Input
  printf("What is the baggage weight's moment arm? Type the length in inches and press enter: \n");
  int baggagemomentarm;
  scanf("%d", &baggagemomentarm);

  int grossweight = emptyweight + weightfrontseatoccupants + weightrearseatoccupants + (usablefuel*fuelweightpergallon) + baggageweight;
  float centerofgravity;
  centerofgravity = (float)((emptyweightmoment) + (frontseatmomentarm*weightfrontseatoccupants) + (rearseatmomentarm*weightrearseatoccupants) + (fueltankmomentarm*usablefuel*fuelweightpergallon) + (baggagemomentarm*baggageweight))/(grossweight);
  if (centerofgravity < forwardCGlimit) //Weight adjustment needed
  {
    //Calculating the new usable fuel needed to set the center of gravity at forward CG limit
    float newusablefuel;
    newusablefuel = (float)(((emptyweightmoment) + (frontseatmomentarm*weightfrontseatoccupants) + (rearseatmomentarm*weightrearseatoccupants) + (baggagemomentarm*baggageweight)) - (forwardCGlimit * (emptyweight + weightfrontseatoccupants + weightrearseatoccupants + baggageweight)))/(forwardCGlimit*fuelweightpergallon - fueltankmomentarm*fuelweightpergallon);
    float grossweight;
    grossweight = (float)(emptyweight + weightfrontseatoccupants + weightrearseatoccupants + (newusablefuel*fuelweightpergallon) + baggageweight);
    float centerofgravity;
    centerofgravity = (float)((emptyweightmoment) + (frontseatmomentarm*weightfrontseatoccupants) + (rearseatmomentarm*weightrearseatoccupants) + (fueltankmomentarm*newusablefuel*fuelweightpergallon) + (baggagemomentarm*baggageweight))/(grossweight);
    float fueldiff;
    fueldiff = (float)fabs((newusablefuel-usablefuel)*fuelweightpergallon);
    double precfueldiff;
    precfueldiff = (double)(round(fueldiff*100)/100); //Fuel difference to a precision of the hundredths
    if (grossweight > maxallowablegrossweight) //Failure case: gross weight exceeds max weight tolerance
    {
      printf("Your loading is not within the aircraft's tolerances!\n");
    }
    else if ((newusablefuel-usablefuel) < 0) //Failure case: Fuel is drained into the negatives (no more fuel to drain)
    {
      printf("Fuel drainage cannot adjust the center of gravity within the planes tolerances!\n");
    }
    else //Success: fuel is drained to set the center of gravity within the tolerances of the plane
    {
        if (fueldiff > 0) //If statement for case of adding or draining fuel from the tank
        {
            printf("The amount of fuel added is %f pounds. \n", (precfueldiff));
            printf("The new gross weight of the aircraft is: %f pounds.\n",grossweight);
            printf("The new center of gravity of the aircraft is: %f inches from the engine's firewall.\n",centerofgravity);
        }
        else 
        {
            printf("The amount of fuel drained is %f pounds. \n", (precfueldiff));
            printf("The new gross weight of the aircraft is: %f pounds.\n",grossweight);
            printf("The new center of gravity of the aircraft is: %f inches from the engine's firewall.\n",centerofgravity);
        }
    }
  }
  else if (centerofgravity > aftCGlimit) //Weight adjustment needed
  {
    float newusablefuel;
    newusablefuel = (float)(((emptyweightmoment) + (frontseatmomentarm*weightfrontseatoccupants) + (rearseatmomentarm*weightrearseatoccupants) + (baggagemomentarm*baggageweight)) - (aftCGlimit * (emptyweight + weightfrontseatoccupants + weightrearseatoccupants + baggageweight)))/(aftCGlimit*fuelweightpergallon - fueltankmomentarm*fuelweightpergallon);
    float grossweight;
    grossweight = (float)(emptyweight + weightfrontseatoccupants + weightrearseatoccupants + (newusablefuel*fuelweightpergallon) + baggageweight);
    float centerofgravity;
    centerofgravity = (float)((emptyweightmoment) + (frontseatmomentarm*weightfrontseatoccupants) + (rearseatmomentarm*weightrearseatoccupants) + (fueltankmomentarm*newusablefuel*fuelweightpergallon) + (baggagemomentarm*baggageweight))/(grossweight);
    float fueldiff;
    fueldiff = (float)fabs((newusablefuel-usablefuel)*fuelweightpergallon);
    double precfueldiff;
    precfueldiff = (double)(round(fueldiff*100)/100); //Fuel difference to a precision of the hundredths
    if (grossweight > maxallowablegrossweight) //Failure case: gross weight exceeds max weight tolerance
    {
      printf("Your loading is not within the aircraft's tolerances!\n");
    }
    else if ((newusablefuel-usablefuel) < 0) //Failure case: Fuel is drained into the negatives (no more fuel to drain)
    {
      printf("Fuel drainage cannot adjust the center of gravity within the planes tolerances!\n");
    }
    else //Success: fuel is drained to set the center of gravity within the tolerances of the plane
    {
        if (fueldiff > 0) //If statement for case of adding or draining fuel from the tank
        {
            printf("The amount of fuel added is %f pounds. \n", (precfueldiff));
            printf("The new gross weight of the aircraft is: %f pounds.\n",grossweight);
            printf("The new center of gravity of the aircraft is: %f inches from the engine's firewall.\n",centerofgravity);
        }
        else 
        {
            printf("The amount of fuel drained is %f pounds. \n", (precfueldiff));
            printf("The new gross weight of the aircraft is: %f pounds.\n",grossweight);
            printf("The new center of gravity of the aircraft is: %f inches from the engine's firewall.\n",centerofgravity);
        }
    }
  }
  else //Weight adjustment not necessary, loading is within the tolerances
  {
    printf("The gross weight of the aircraft is %d pounds.\n", grossweight);
    printf("Fuel amount was not adjusted, the center of gravity is within the aircraft's limits: %f inches from the engine's firewall.\n", centerofgravity);
  }
  return 0;
}
