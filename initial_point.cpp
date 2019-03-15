//
// Created by admin on 2019/03/06.
//
#include <iostream>
#include <cmath>
#include <tuple>
#include <string>
#include <stdexcept>

using namespace std;

inline std::tuple<double, double> initial_point (double distance_over_ground, double altitude, double heading, double speed, double angle_of_change, double missileSpeed)
{
    int refreshRate = 10;
    double refreshTime = 1/refreshRate;
    double distance_target = 0;
    double change_alt = 0, new_alt = 0;
    double heading_rad = 0;
    double angle_of_change_rad = 0;
    double direct_distance = 0;
    double vertRise = 0;
    double flight_time = 0;
    double distanceCovered = 0;
    double newDirectdistance = 0, newOvergroundDistance = 0;
    double missileheading = 0;
    double var1 = 0, var2 = 0, var3 = 0, var4 = 0, var5 = 0, var6 = 0,var7 = 0;
    double output = 0;
    double pi = 3.1415;
    double missileDistance = 0;

    var4 = pow(distance_over_ground, 2) + pow(altitude, 2);
    direct_distance = sqrt(var4);
    cout << direct_distance << "\n";

    missileDistance = missileSpeed / refreshRate;

        heading_rad = heading * pi / 180;
        angle_of_change_rad = angle_of_change * pi / 180;


        var4 = pow(distance_over_ground, 2) + pow(altitude, 2);
        direct_distance = sqrt(var4);
        cout << direct_distance << "\n";

        //Vert rise givin in radians
        vertRise = atan(altitude / distance_over_ground);
        cout << vertRise << "\n";
        flight_time = direct_distance / missileSpeed;
        cout << flight_time << "\n";
        distanceCovered = speed * flight_time;
        cout << distanceCovered << "\n";

        var1 = pow(distanceCovered, 2) + pow(direct_distance, 2);
        var2 = 2 * distanceCovered * direct_distance * cos(heading_rad);
        output = var1 - var2;
        newDirectdistance = sqrt(output);
        cout << newDirectdistance << "\n";

        var7 = pow(newDirectdistance, 2) - pow(altitude, 2);
        newOvergroundDistance = sqrt(var7);
        cout << newOvergroundDistance << "\n";

        var3 = (sin(heading_rad) / newDirectdistance) * distanceCovered;
        missileheading = asin(var3);
        cout << missileheading << "\n";


        if (angle_of_change == 0) {
            cout << "No decent or accend";
        } else {
            change_alt = distanceCovered * tan(angle_of_change_rad);
            cout << change_alt << "\n";


            new_alt = altitude + change_alt;
            cout << new_alt << "\n";

            var6 = pow(newOvergroundDistance, 2) + pow(new_alt, 2);
            newDirectdistance = sqrt(var6);
            cout << newDirectdistance;
        }

        distance_target = newDirectdistance - missileDistance;

        return std::make_tuple(newDirectdistance,missileheading);

    }


