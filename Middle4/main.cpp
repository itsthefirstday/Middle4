//
//  main.cpp
//  Middle4
//
//  Created by Юрий Филиппов on 04.04.2021.
//

#include <iostream>
#include <vector>


class Wheel
{
public:
    Wheel(float d):m_diameter(d) {}
    float getDiameter() const {return m_diameter;}
private:
    float m_diameter;
};

class Engine
{
public:
    Engine(float p):m_power(p) {}
    float getPower() const {return m_power;}
    virtual std::ostream& print(std::ostream &out) const
    {
        out << "Engine: " << m_power;
        return out;
    }
    friend std::ostream& operator<<(std::ostream& out, const Engine& e)
    {
        return e.print(out);
    }
private:
    float m_power;
};

class Vehicle
{
public:
    virtual std::ostream& print(std::ostream &out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Vehicle& v)
    {
        return v.print(out);
    }
    virtual const Engine* getEngine() const = 0;
    virtual ~Vehicle() {}
};

class WaterVehicle : public Vehicle
{
public:
    WaterVehicle(float s):m_sinking(s) {}
    std::ostream& print(std::ostream &out) const override
    {
        out << "Sinking: " << m_sinking;
        return out;
    }
    const Engine* getEngine() const override
    {
        return NULL;
    }
private:
    float m_sinking;
};

class RoadVehicle : public Vehicle
{
public:
    RoadVehicle(float c):m_clearance(c) {}
    std::ostream& print(std::ostream &out) const override
    {
        out << "Ride height: " << m_clearance;
        return out;
    }
    const Engine* getEngine() const override
    {
        return NULL;
    }
private:
    float m_clearance;
};

class Bicycle : public RoadVehicle
{
public:
    Bicycle(Wheel fw, Wheel rw, float clearance):
    RoadVehicle(clearance),
    m_frontWheel(fw),
    m_rearWheel(rw)
    {}
    std::ostream& print(std::ostream &out) const override
    {
        out << "Bicycle Wheels: " << m_frontWheel.getDiameter() << ' '
            << m_rearWheel.getDiameter() << ' ';
        RoadVehicle::print(out);
        return out;
    }
private:
    Wheel m_frontWheel, m_rearWheel;
};

class Car : public RoadVehicle
{
public:
    Car(Engine e, Wheel flw, Wheel frw, Wheel rlw, Wheel rrw, float clearance):
    RoadVehicle(clearance),
    m_engine(e),
    m_frontLeftWheel(flw),
    m_frontRightWheel(frw),
    m_rearLeftWheel(rlw),
    m_rearRightWheel(rrw)
    {}
    std::ostream& print(std::ostream &out) const override
    {
        out << "Car " << m_engine << " Wheels: " << m_frontLeftWheel.getDiameter() << ' '
                                                << m_frontRightWheel.getDiameter() << ' '
                                                << m_rearLeftWheel.getDiameter() << ' '
                                                << m_rearRightWheel.getDiameter() << ' ';
        RoadVehicle::print(out);
        return out;
    }
    const Engine* getEngine() const override
    {
        return &m_engine;
    }
private:
    Wheel m_frontLeftWheel, m_frontRightWheel, m_rearLeftWheel, m_rearRightWheel;
    Engine m_engine;
};

float getHighestPower(const std::vector<Vehicle*>& v)
{
    float max = 0.f;
    for (size_t i = 0; i < v.size(); i++)
    {
        const Engine *engine = v[i]->getEngine();
        if (engine)
            if (engine->getPower() > max)
                max = engine->getPower();
    }

    return max;
}


int main(int argc, const char * argv[]) {
    // Part I
    Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);
    std::cout << c << '\n';

    Bicycle t(Wheel(20), Wheel(20), 300);
    std::cout << t << '\n';

    // Part II
    std::vector<Vehicle*> v;
    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));
    //v.push_back(new Circle(Point(1, 2, 3), 7));
    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));
    v.push_back(new WaterVehicle(5000));

    //TODO: Вывод элементов вектора v здесь
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << *v[i] << '\n';
    }

    std::cout << "The highest power is " << getHighestPower(v) << '\n'; // реализуйте эту функцию

    //TODO: Удаление элементов вектора v здесь
    for (size_t i = 0; i < v.size(); i++)
    {
        delete v[i];
    }
    v.clear();

    return 0;
}
