//
// Created by DeltaEcho192 on 2019/03/06.
//

//TODO Calculate the new Distance covered by the missile.
//TODO Optimise equation to better speed.

#include <cmath>
#include <iostream>

using namespace std;

inline double speed_change(double last_direct_distance, double last_heading, double missile_dist_covered,
                    double distancecovered,double missileSpeed, double missileAngle,double speed)
{
    double var1 = 0,var2 = 0,var3 = 0,var4 = 0,var5 = 0,var6 = 0,var7 = 0,var8 = 0,var9 = 0,var10 = 0,var11 = 0,var12 = 0,var13 = 0;
    double reqAngle = 0,reqAngle2 = 0, reqAngle3 = 0,reqAngle4 = 0;
    double direct_to_current = 0,planeAngleChange = 0, F =0,direct_distance = 0, newHeadingtoCalc = 0, distanceToIntercept = 0,angleToAdjust = 0, newDistanceTraveled = 0;
    double pi = 3.1415;
    double degreeConv = 180/3.1415;
    double radianConv = pi / 180;

    cout << last_direct_distance << "\n";
    cout << last_heading  << "\n" << missile_dist_covered << "\n" << distancecovered << "\n" << missileAngle << "\n";

    last_heading = last_heading * radianConv;

    //Calculates the distance from the last missile position to the plane position.
    var1 = pow(distancecovered,2) + pow(last_direct_distance,2);
    var2 = 2 * distancecovered * last_direct_distance * cos(last_heading);
    direct_to_current =  sqrt((var1 - var2));
    cout << "(Direct_to_current)Last Missile to new plane pos " << direct_to_current << "\n";

    //Calculates a required angle for the new heading
    var3 = pow(distancecovered,2) + pow(direct_to_current,2) - pow(last_direct_distance,2);
    var4 = var3 / (2*distancecovered*direct_to_current);
    reqAngle = acos(var4);
    cout << "Required (angle1) " << reqAngle << "\n";

    //Calculates the angle from Orignal Point of plane and the new position.
    planeAngleChange = pi - (last_heading + reqAngle);
    cout << "(planeAngleChange)angle from Orignal Point of plane and the new position " << planeAngleChange << "\n";

    //Calculates a angle, orignal missile angle - planeAngleChange.
    F = missileAngle - planeAngleChange;
    cout << "(F) orignal missile angle - planeAngleChange " << F  << "\n";

    //Calculates the distance from the new missile position to the new plane position.
    var5 = pow(missile_dist_covered,2) + pow(direct_to_current,2);
    var6 = 2 * missile_dist_covered * direct_to_current * cos(F);
    direct_distance = sqrt((var5 - var6));
    cout << "(direct_distance)Direct distance from new Mis pos to New plane Pos: " << direct_distance << "\n";

    //Calculate the new Distance Covered by the Target.
    //Calculates the flight time new
    cout << direct_distance << " Direct Distance : Missile Speed "<< missileSpeed << "\n";
    var13 = direct_distance/missileSpeed;
    cout << "New Flight Time " << var13 << "\n";
    newDistanceTraveled  = speed * var13;
    cout << "New distance traveled by the target " << newDistanceTraveled << "\n";


    //Calculates angle required to calculate the new heading.
    var7 = pow(direct_to_current,2) + pow(direct_distance,2) - pow(missile_dist_covered,2);
    var8 = var7 / (2 * direct_to_current * direct_distance);
    reqAngle2 = acos(var8);
    cout << "(reqAngle2)Required Angle to calculate Heading " << reqAngle2 << "\n";


    //Calculates the angle from current missile flight path to current plane pos.
    reqAngle3 = pi - (F + reqAngle2);
    cout << "(reqAngle3) angle from current missile flight path to current plane pos " << reqAngle3 << "\n";


    //The new heading - reqAngle2. Used to calculate the distance to new intercept point.
    newHeadingtoCalc = pi - (reqAngle2 + reqAngle);
    cout << "(newHeadingToCalc) new heading - reqAngle2. Used to calculate the distance to new intercept point " << newHeadingtoCalc << "\n";

    var9 = pow(direct_distance,2) + pow(newDistanceTraveled,2);
    var10 = 2 * direct_distance * newDistanceTraveled * cos(newHeadingtoCalc);
    distanceToIntercept = sqrt((var9-var10));
    cout << "(DistanceToIntercept)Distance to new intercept Point " << distanceToIntercept << "\n";

    //Required angle to calculate the adjustment.
    var11 = pow(direct_distance,2) + pow(distanceToIntercept,2) - pow(newDistanceTraveled,2);
    var12 = 2 * direct_distance * distanceToIntercept;
    reqAngle4 = acos((var11/var12));
    cout << "(reqAngle4)Angle to calculate Adjustment " << reqAngle4 << "\n";

    //Calculates the amount of degrees course change.
    angleToAdjust = pi - (reqAngle3 + reqAngle4);
    cout << "Angle to Adjust " << angleToAdjust << "\n";
    cout << "\n" << "\n" << "\n";


    return angleToAdjust;
}
