double knots_to_miles_per_minute(int knot) {
    constexpr int feet_per_nautical_mile = 6076; // Number of feet in a nautical mile
    constexpr int feet_per_mile = 5280;          // Number of feet in a statute mile
    constexpr int minutes_per_hour = 60;         // Number of minutes in an hour

    double miles_per_hour = (knot * feet_per_nautical_mile) / feet_per_mile;
    return miles_per_hour / minutes_per_hour;
}

