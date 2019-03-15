//
// DeltaEcho 15/03/2019
//

//TODO Comment and clean code.


#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

#include "speed_change.cpp"
#include "heading_change.cpp"

double speed_change();
double heading_change();

int main() {

    int refreshRate = 10;
    double refreshTime = 1/refreshRate;
    double distance_target = 0;
    double distance_over_ground = 30000;
    double altitude = 10000, change_alt = 0, new_alt = 0;
    double heading = 90, heading_rad = 0;
    double speed = 200;
    double angle_of_change = 0, angle_of_change_rad = 0;
    double direct_distance = 0;
    double vertRise = 0, vertRiseDeg = 0, vertChange = 0, vertAdj = 0;
    double flight_time = 0;
    double missileSpeed = 1138;
    double distanceCovered = 0;
    double interceptDistance = 0, newOvergroundDistance = 0;
    double missileheading = 0,missileheadingDeg = 0;
    double var1 = 0, var2 = 0, var3 = 0, var4 = 0, var5 = 0, var6 = 0,var7 = 0,var8 = 0;
    double output = 0;
    double pi = 3.1415;
    double missileDistance = 0;
    double speed_old = 0;
    double missile_change = 0;

    int q = 1;

    ofstream headingChange1;
    headingChange1.open("Missile_Adjustments.txt",ios::app);
    if(headingChange1.is_open())
    {
        cout << "File Found and Open." << "\n";


    } else{
        cout << "Unable to Open File." << "\n";
    }


    clock_t begin0 = clock();

    missileDistance = missileSpeed / refreshRate;
    heading_rad = heading * pi / 180;
    angle_of_change_rad = angle_of_change * pi / 180;


    var4 = pow(distance_over_ground, 2) + pow(altitude, 2);

    //Vert rise givin in radians
    vertRise = atan(altitude / distance_over_ground);
    vertRiseDeg = vertRise * (180/pi);
    cout << "Verticle Adjustment of the Missile "<< vertRiseDeg << "\n";
    flight_time = sqrt(var4) / missileSpeed;
    cout << "Flight Time to Target " << flight_time << "\n";
    distanceCovered = speed * flight_time;
    cout << "Distance covered by Target " << distanceCovered << "\n";

    interceptDistance = sqrt(pow(distanceCovered, 2) + pow(sqrt(var4), 2) - (2 * distanceCovered * sqrt(var4) * cos(heading_rad)));
    cout << "Distance to the interception Point " << interceptDistance << "\n";

    var7 = pow(interceptDistance, 2) - pow(altitude, 2);
    newOvergroundDistance = sqrt(var7);
    cout << "Over ground distance to intercept point " << newOvergroundDistance << "\n";

    var3 = (sin(heading_rad) / interceptDistance) * distanceCovered;
    missileheading = asin(var3);
    missileheadingDeg = missileheading * (180/pi);
    cout << "Firing solution for missile " << missileheading << "\n";

    headingChange1 << missileheading << "," << vertRise << "\n";


    if (angle_of_change == 0) {
        cout << "No decent or accend";
        
        
    } else {
        change_alt = distanceCovered * tan(angle_of_change_rad);
        cout << "Change in Altitude " << change_alt << "\n";


        new_alt = altitude + change_alt;
        cout << "New altitude at intercept Point " << new_alt << "\n";

        var6 = pow(newOvergroundDistance, 2) + pow(new_alt, 2);
        interceptDistance = sqrt(var6);
        cout << "New Intercept Distance with new Altitude " << interceptDistance << "\n";

        vertChange = atan(new_alt/newOvergroundDistance);
        cout << "Missile Angle adjustment: " << vertChange << "\n";
        
    }

    clock_t end0 = clock();
    double elapsed_secs0 = double(end0 - begin0) / CLOCKS_PER_SEC;
    cout << elapsed_secs0 << " Amount of time elapsed" << "\n";

    distance_target = interceptDistance - missileDistance;

    //
    //
    //


    double missile_covered = 0, target_traveled = 0, newDistanceCovered = 0;
    missile_covered = missileSpeed / refreshRate;
    target_traveled = speed / refreshRate;

    if(speed != speed_old)
        {
            clock_t begin = clock();
            missile_change = speed_change(direct_distance,heading,missile_covered,target_traveled,missileSpeed,missileheading,speed);

            missileheading  = missileheading - missile_change;
            cout << "Missile heading change " << missile_change << "\n";
            headingChange1 << missile_change << "," << 0 << "\n";
            cout << "New Missile Heading " << missileheading << "\n";
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            cout << elapsed_secs << "Amount of time elapsed";
        }
    else if (speed != speed_old && angle_of_change_rad != 0)
    {
        
            clock_t begin = clock();
            missile_change = speed_change(direct_distance,heading,missile_covered,target_traveled,missileSpeed,missileheading,speed);
            missileheading  = missileheading - missile_change;
            cout << "Missile heading change " << missile_change << "\n";
            headingChange1 << missile_change << "," << 0 << "\n";
            cout << "New Missile Heading " << missileheading << "\n";

            change_alt = distanceCovered * tan(angle_of_change_rad);
            cout << "Change in Altitude " << change_alt << "\n";

            new_alt = altitude + change_alt;
            cout << "New altitude at intercept Point " << new_alt << "\n";

            var6 = pow(newOvergroundDistance, 2) + pow(new_alt, 2);
            interceptDistance = sqrt(var6);
            cout << "New Intercept Distance with new Altitude " << interceptDistance << "\n";

            vertChange = atan(new_alt/newOvergroundDistance);
            cout << "Missile Angle adjustment: " << vertChange << "\n";

            vertAdj = vertRise - vertChange;

            headingChange1 << missile_change << "," << vertAdj << "\n";

            vertRise = vertChange;

            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            cout << elapsed_secs << "Amount of time elapsed";
    }
    


    //
    //
    //


/*
    double new_heading = 0.0174533 , remaing_dist = distanceCovered,old_heading1 = 1.5708
    ,intercept_dist_old = interceptDistance, missile_ang = missileheading ,target_traveled1 = 0, new_missile_ang = 0;
    bool closer = true;

    if (new_heading < 3.1415 && closer == true) {
        clock_t begin = clock();
        target_traveled1 = speed / refreshRate;
        remaing_dist = remaing_dist - target_traveled1;

        new_missile_ang = heading_change(new_heading, missile_ang, old_heading1, intercept_dist_old, remaing_dist);


        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout << "New Missile Angle: " << new_missile_ang << "\n";
        headingChange1 << new_missile_ang << "," <<  0 << "\n";
        cout << elapsed_secs << " Amount of time elapsed";

    }
    headingChange1.close();
    return 0;
    */
 }