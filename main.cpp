#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

class Planet;
vector<long double> compute_acceleration_between_two_planets(long double permanent_acceleration, Planet first_planet, Planet second_planet);
long double get_distance_lenght_between_two_planets(Planet first_planet, Planet second_planet); 

class Planet {
public:
    Planet(long double x, long double y, vector<long double> speed, unsigned long long weigth) {
        x_position = x;
        y_position = y;
        planet_speed = speed;
        planet_weight = weigth;
    }

    vector<long double> getPlanetPosition() {
        vector<long double> position = {x_position, y_position};
        return position;
    }

    vector<long double> getPlanetSpeed() {
        return planet_speed;
    }

    unsigned long long getPlanetWeight() {
        return planet_weight;
    }

    void setPlanetPosition(long double x, long double y) {
        x_position = x;
        y_position = y;
    }

    void setPlanetSpeed(long double x_speed, long double y_speed) {
        planet_speed[0] = x_speed;
        planet_speed[1] = y_speed;
    }

private:
    long double x_position;
    long double y_position;
    unsigned long long planet_weight;
    vector<long double> planet_speed;
}; 

int main() { 
    vector<long double> sun_speed = {0, 0};
    vector<long double> earth_speed = {-4.5, 3.5};
    Planet earth_planet = Planet(230, 120, earth_speed, 999999999999);
    Planet sun_planet = Planet(375, 225, sun_speed, 90999999999999);
    sf::RenderWindow window(sf::VideoMode(800, 500), "Planets Engine");
    sf::CircleShape sun_shape(15.f);
    sf::CircleShape earth_shape(8.f);
    earth_shape.setFillColor(sf::Color::Blue);
    sun_shape.setFillColor(sf::Color::Yellow);
    sun_shape.setPosition(375.f, 225.f);
    earth_shape.setPosition(230.f, 120.f);
    while (window.isOpen()) {
        long double distance_lenght_between_earth_and_sun = get_distance_lenght_between_two_planets(earth_planet, sun_planet);
        
        /* coumputing acceleration by newton's third law */
        long double earth_acceleration = 6.676 * pow(10, -11) * sun_planet.getPlanetWeight() / pow(distance_lenght_between_earth_and_sun, 2); 
        long double sun_acceleration = 6.676 * pow(10, -11) * earth_planet.getPlanetWeight() / pow(distance_lenght_between_earth_and_sun, 2);

        earth_planet.setPlanetSpeed(earth_planet.getPlanetSpeed()[0] + compute_acceleration_between_two_planets(earth_acceleration, earth_planet, sun_planet)[0], earth_planet.getPlanetSpeed()[1] + compute_acceleration_between_two_planets(earth_acceleration, earth_planet, sun_planet)[1]);
        earth_planet.setPlanetPosition(earth_planet.getPlanetPosition()[0] + earth_planet.getPlanetSpeed()[0], earth_planet.getPlanetPosition()[1] + earth_planet.getPlanetSpeed()[1]); 
        sun_planet.setPlanetSpeed(sun_planet.getPlanetSpeed()[0] + compute_acceleration_between_two_planets(sun_acceleration, sun_planet, earth_planet)[0], sun_planet.getPlanetSpeed()[1] + compute_acceleration_between_two_planets(sun_acceleration, sun_planet, earth_planet)[1]);
        sun_planet.setPlanetPosition(sun_planet.getPlanetPosition()[0] + sun_planet.getPlanetSpeed()[0], sun_planet.getPlanetPosition()[1] + sun_planet.getPlanetSpeed()[1]);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	window.clear();
        window.draw(sun_shape);
	window.draw(earth_shape);
        window.display();
	earth_shape.setPosition(earth_planet.getPlanetPosition()[0], earth_planet.getPlanetPosition()[1]); 
	sun_shape.setPosition(sun_planet.getPlanetPosition()[0], sun_planet.getPlanetPosition()[1]);
#ifdef DEBUG
        this_thread::sleep_for(1s);
#endif
    }
    return 0;
}

vector<long double> computeAccelerationBetweenTwoPlanets(long double permanent_acceleration, Planet first_planet, Planet second_planet) {
    vector<long double> first_planet_position = first_planet.getPlanetPosition();
    vector<long double> second_planet_position = second_planet.getPlanetPosition();
    vector<long double> vector_from_first_planet_to_second_planet = {second_planet_position[0] - first_planet_position[0], second_planet_position[1] - first_planet_position[1]};
    long double length_of_vector_from_first_planet_to_second_planet = sqrt(pow(vector_from_first_planet_to_second_planet[0], 2) + pow(vector_from_first_planet_to_second_planet[1], 2));
    vector<long double> acceleration_between_two_planets = {permanent_acceleration * vector_from_first_planet_to_second_planet[0] / length_of_vector_from_first_planet_to_second_planet, permanent_acceleration * vector_from_first_planet_to_second_planet[1] / length_of_vector_from_first_planet_to_second_planet};
    return acceleration_between_two_planets;
}

long double getDistanceLenghtBetweenTwoPlanets(Planet first_planet, Planet second_planet) { 
    vector<long double> first_planet_position = first_planet.getPlanetPosition();
    vector<long double> second_planet_position = second_planet.getPlanetPosition();
    vector<long double> vector_from_first_planet_to_second_planet = {second_planet_position[0] - first_planet_position[0], second_planet_position[1] - first_planet_position[1]};
    long double length_of_vector_from_first_planet_to_second_planet = sqrt(pow(vector_from_first_planet_to_second_planet[0], 2) + pow(vector_from_first_planet_to_second_planet[1], 2));
    return length_of_vector_from_first_planet_to_second_planet;
}
