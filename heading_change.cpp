//
// Created by DeltaEcho192 on 2019/03/07.
//

//Calculates the change in missile heading to intercept the target when it experiances a change in heading.

//Only works when the missile turns towards the missile.

#include <cmath>
#include <iostream>
using namespace std;

inline double heading_change(double new_heading,double missile_angle,double old_heading, double intercept_dist_old,double remaining_dist_intercpt)
{

    double E = 0, I = 0, var1 = 0;
    double pi = 3.1415;

    E = pi - (new_heading + (pi -(old_heading + missile_angle)));
    cout << E << "\n";

    I = (sin((pi - (new_heading + (pi -(old_heading + missile_angle)))))/intercept_dist_old) * (intercept_dist_old - (remaining_dist_intercpt / sin(E)) * sin(new_heading));
    cout<< "I: " << I << "\n";

    new_heading = pi - (asin(I) + E);

    return new_heading;


}