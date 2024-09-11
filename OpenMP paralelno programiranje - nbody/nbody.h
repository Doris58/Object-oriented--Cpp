#pragma once

#include <cmath>
#include <iostream>

// Točka u prostoru odnosno vektor.
struct Point
{
   // Vaša implementacija

   double x;
   double y;
};

// Eventualne dodatne inline funkcije i operatori na tipu Point
// Izračunaj razliku dviju točaka/vektora.
Point difference(const Point a, const Point b);

// Izračunaj normu vektora.
double norm(const Point a);


// Alociraj memoriju za sile/ubrzanja i inicijaliziraj ih nulama.
Point *init_force(int N);

// Izračunaj silu na sva tijela. Prva (direktna) verzija.
void calc_force1(const double *mass, const Point *pos, Point *acc, int N, double G, double limit);

// Izračunaj silu na sva tijela. Druga, optimizirana verzija.
void calc_force2(const double *mass, const Point *pos, Point *acc, int N, double G, double limit);

// Pomakni sve točke.
void advance(double dt, Point *pos, const Point *vel, int N);

// Izračunaj nove brzine.
void velocity(double dt, Point *vel, const Point *acc, int N);

// Učitaj sve podatke iz datoteke.
void read_file(std::string const &filename, double **mass, Point **pos,
               Point **vel, int &N, double &dt, int &Nstep, double &G, double &limit);

            // float **radius  ?

// Ispiši sve podatke u datoteku.
void write_file(std::ostream &out, const double *mass, const Point *pos,
                const Point *vel, const Point *force, int N, double dt, int Nstep,
                double G, double limit);

            // const float *radius ?