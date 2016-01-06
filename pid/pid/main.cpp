//
//  main.cpp
//  pid
//
//  Created by Александр on 22.12.15.
//  Copyright © 2015 Alexandr Fedorov. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

//модель робота с кинематикой автомобиля (Dubins car)
class Robot
{
protected:
    //координаты положения центральной точки задней оси
    double x;
    double y;
    //ориентация шасси
    double orientation;
    //расстояние между осями - длина робота
    double length;
public:
    //конструктор
    //создает робот с заданной длиной
    Robot(double l = 20.0):
    x(0.0), y(0.0), orientation(0.0),length(l){}
    
    //функция задания положения робота
    void set_pose(double x, double y, double fi)
    {
        this->x = x;
        this->y = y;
        this->orientation = fi;
        if ( orientation > M_PI*2 )
            orientation -= floor(orientation/M_PI/2)*M_PI*2;
        else
            if ( orientation < -M_PI*2 )
                orientation += floor(-orientation/M_PI/2)*M_PI*2;
    }
    //функция движения робота с заданным углом поворота колес (steering)
    //на заданное расстояние (distance)
    // tolerance - параметр точности расчета
    // max_steering_angle - ограничение поворота колес
    void move(double steering, double distance,
              double tolerance = 0.00001, double max_steering_angle = M_PI/4)
    {
        //ограничение угла поворота колес
        if ( steering > max_steering_angle )
            steering = max_steering_angle;
        if ( steering < -max_steering_angle )
            steering = -max_steering_angle;
        // едем только вперед
        if ( distance < 0 )
            distance = 0;
        
        //угол на который повернется робот в процессе заданного движения
        double turn = tan(steering) * distance/ length;
        
        
        if ( fabs(turn) < tolerance )
        {
            //движение по прямой
            x += distance * cos(orientation);
            y += distance * sin(orientation);
            orientation += turn;
        }
        else
        {
            //движение по дуге окружности
            double radius = distance / turn;
            //координаты центра окружности
            double cx = x - (sin(orientation) * radius);
            double cy = y + (cos(orientation) * radius);
            orientation += turn;
            //новые координаты робота
            x = cx + (sin(orientation) * radius);
            y = cy - (cos(orientation) * radius);
        }
        
        if ( orientation > M_PI*2 )
            orientation -= floor(orientation/M_PI/2)*M_PI*2;
        else
            if ( orientation < -M_PI*2 )
                orientation += floor(-orientation/M_PI/2)*M_PI*2;
    }
    
    //********************************************************************
    //********************************************************************
    // функция вычисления ошибки управления - расстояния до ближайшей точки траектории
    // менять здесь для решения пункта 2
    double cte(double radius)
    {
        double ex, ey;
        if (x <= radius) {
            
            ex = x - radius;
            ey = y - radius;
            
        }
        else if ( x > radius && x <= 5*radius)
        {
            
        }
        else {
            
            ex = x - 5*radius;
            ey = y - radius;
            
        }
    
//        double ex = x - radius;
//        double ey = y - radius;
        
        return sqrt(ex*ex + ey*ey) - radius;
    }
    
    //печать положения робота
    void print()
    {
        std::cout<<" "<<x<<"\t "<<y<<std::endl;
    }
};
//********************************************************************
//********************************************************************

//функция движения робота по траектории с регулятором
// k_prop - коэффициент пропорциональной составляющей регулятора
// k_diff - коэффициент дифференциальной составляющей
// k_int - коэффициент интегральной составляющей
// radius - параметр траектории
// print_flag - флаг печати печати
// в функции эмулируется 2*N итерация движения робота с регулятором
// возвращается средняя ошибка за последние N итерация
double run(double k_prop, double k_diff, double k_int,
           double radius, bool print_flag = true )
{
    //создаем робота
    Robot myrobot;
    //ставим его на траекторию
    myrobot.set_pose(0.0, radius, M_PI / 2.0);
    //условная скорость движения робота , она же определяет длину пробега на каждой итерации
    //так как dt = 1
    double speed = 1;
    //суммарная ошибка на второй половине пробега
    double err = 0.0;
    //начальное значение интегральной ошибки
    double int_crosstrack_error = 0.0;
    //количество итераций
    int N = 200;
    //начальное значение ошибки управления
    double crosstrack_error = myrobot.cte(radius);
    
    for( int i = 0; i < 2*N; i++)
    {
        double diff_crosstrack_error = - crosstrack_error;
        crosstrack_error = myrobot.cte(radius);
        diff_crosstrack_error += crosstrack_error;
        int_crosstrack_error += crosstrack_error;
        //вычисление управляющего параметра - поворота рудевых колес робота
        double steer = - k_prop * crosstrack_error
        - k_diff * diff_crosstrack_error
        - k_int * int_crosstrack_error;
        myrobot.move(steer, speed);
        //на второй половине пробега считаем суммарную ошибку
        if ( i >= N)
            err += crosstrack_error * crosstrack_error;
        if (print_flag)
        {
            myrobot.print();
            std::cout<<"error = "<<err<<std::endl;
        }
        
    }
    
    return err/N;
}

int main(int argc, const char * argv[]) {
    double radius = 25;
    //Значения коэффициентов регулирования
    
    //для движения по сложной форме
//    double k_prop = 1;
//    double k_diff = 25;
//    double k_int = 0.05;
    
    // для движения по окружности
        double k_prop = 1;
        double k_diff = 25;
        double k_int = 0.05;
    
    //  запуск основной функции программы
    double err = run(k_prop, k_diff, k_int, radius);
    std::cout<<"error = "<<err<<std::endl;
}
