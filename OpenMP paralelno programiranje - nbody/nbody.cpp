#include "nbody.h"
#include <stdexcept>
#include <random>
#include <cassert>
#include <fstream>
#include <sstream>

// Izračunaj razliku dviju točaka/vektora.
Point difference(const Point a, const Point b)
{
    Point d;

    d.x = a.x - b.x;
    d.y = a.y - b.y;

    return d;
}

// Izračunaj normu vektora.
double norm(const Point a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}

// Izračunaj silu/akceleraciju na sva tijela.  Prva verzija (direktna).
void calc_force1(const double * mass, const Point * pos, Point * acc, int N, double G, double limiter)
{
    Point d;
    double d_norm;

  #pragma omp parallel for private(d, d_norm)
    for(int i = 0; i < N; i++)
    {
      for(int j = 0; j < N; j++)
      {
        if(i != j)
         {  
            d = difference(pos[i], pos[j]); // d.x = pos[i].x - pos[j].x; d.y = pos[i].y - pos[j].y;

            d_norm = norm(d);  //d_norm = sqrt(d.x*d.x + d.y*d.y);  


            double koeficijent = G * mass[j] / pow(d_norm + limiter, 3);

            acc[i].x -= koeficijent * d.x; 

            acc[i].y -= koeficijent * d.y;
          }
      }
    }
}

// Izračunaj silu/akceleraciju na sva tijela. Druga verzija (optimizirana).
void calc_force2(const double * mass, const Point * pos, Point * acc, int N, double G, double limiter)
{
    Point d;
    double d_norm;

    Point forceIJ;

    for(int i = 0; i < N; i++)
    {

      double i_x = acc[i].x;
      double i_y = acc[i].y;

    #pragma omp parallel for private(d, d_norm, forceIJ) reduction(-: i_x, i_y)
      for(int j = i + 1; j < N; j++)
      {
        d = difference(pos[i], pos[j]);  // d.x = pos[i].x - pos[j].x; d.y = pos[i].y - pos[j].y;

        d_norm = norm(d);   //d_norm = sqrt(d.x*d.x + d.y*d.y);  


        double koeficijent = G * mass[i] * mass[j] / pow(d_norm + limiter, 3);

			  forceIJ.x = koeficijent * d.x;
        forceIJ.y = koeficijent * d.y;

        i_x -= forceIJ.x / mass[i];
        i_y -= forceIJ.y / mass[i];

        acc[j].x += forceIJ.x / mass[j];
        acc[j].y += forceIJ.y / mass[j];
      }

      acc[i].x = i_x;
      acc[i].y = i_y;
    }
}

// Pomakni sve točke.
void advance(double dt, Point * pos, const Point * vel, int N)
{
  #pragma omp parallel for
    for(int i = 0; i < N; i++)
    {
      pos[i].x = pos[i].x + dt * vel[i].x;  // Može i operatorom +=

      pos[i].y = pos[i].y + dt * vel[i].y;
    }
}

// Izračunaj nove brzine.
void velocity(double dt, Point * vel, const Point * acc,  int N)
{
  #pragma omp parallel for
    for(int i = 0; i < N; i++)
    {
      vel[i].x = vel[i].x + dt * acc[i].x;

      vel[i].y = vel[i].y + dt * acc[i].y;
    }
}

// Alociraj memoriju za sile/ubrzanja i inicijaliziraj ih nulama.
Point* init_force(int N)  // acceleration umjesto force
{
    Point* acc = new Point[N];

    for(int i = 0; i < N; i++)
    {
      acc[i].x = 0.0;
      acc[i].y = 0.0;
    }

    return acc;
}

// Rutine za čitanje i pisanje su zadane.
template <typename T>
void read(std::ifstream & in, std::string & line, T & t){
  std::getline(in, line); 
  while(line[0] == '#') 
		std::getline(in, line); 
  std::istringstream iss(line);
  iss >> t;
}

void read_file(std::string const & filename, 
		       double ** mass, Point ** pos, Point ** vel, 
		       int & N, double & dt, int & Nstep, double & G, double & limit)
{
  std::ifstream in(filename);
  if(!in)
    throw std::runtime_error("Cannot open " + filename + " for reading.");

  std::string line;
//  in >> std::ws;

  read<int>(in, line, N);
  read<double>(in, line, dt);
  read<int>(in, line, Nstep);
  read<double>(in, line, G);
  read<double>(in, line, limit);  // limit za slučaj bez kolicizije
  
  *mass = new double [N];
  if(!*mass)
    throw std::runtime_error("Alloc error 1.");

  *pos = new Point[N];
  if(!*pos)
    throw std::runtime_error("Alloc error 3.");

  *vel = new Point[N];
  if(!*vel)
    throw std::runtime_error("Alloc error 4.");

  std::getline(in, line); 
  while(line[0] == '#') 
		std::getline(in, line);

  int i=0;
  do{
    std::istringstream  iss(line);
    iss >> (*mass)[i] >> (*pos)[i].x >> (*pos)[i].y >> (*vel)[i].x >> (*vel)[i].y;
    ++i;
  }
  while(std::getline(in, line));
  assert(i == N);

  in.close();
}

void write_file(std::ostream & out, const double * mass, const Point * pos, 
               const Point * vel, const Point * force, int N, double dt, int Nstep, double G, double limit)
{
 
  out << N     << "  # N\n";
  out << dt    << "  # dt\n";
  out << Nstep << "  # Nstep\n";
  out << G     << "  # G\n";
  out << limit << "  # Limit\n";
  
  int i=0;
  while(i <N){
    out << "m = " << mass[i] << ", pos=(" << pos[i].x << "," << pos[i].y 
		<< "), vel=(" << vel[i].x << "," << vel[i].y <<"),"
		<< " force=(" << force[i].x << "," << force[i].y <<  ")\n";
    ++i;
  }  
}


