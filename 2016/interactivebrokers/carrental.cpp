#include <iostream>
#include <vector>
#include <memory>
#ifdef DEBUG
#include <typeinfo>
#include <cxxabi.h>
#endif
using namespace std;

#define DEFAULT_SEATS 5
#define THREE_ROW_SEATS 8

class Car {
 string m_sPlate;
 string m_sBrand;
public:
 Car(const string &plate, const string &brand) : m_sPlate(plate), m_sBrand(brand) {}
 virtual ~Car() {}
 const string& GetPlate() const { return m_sPlate; } 
 const string& GetBrand() const { return m_sBrand; } 
 virtual unsigned GetNumberOfSeats() const = 0;
#ifdef DEBUG
 virtual ostream& Print(ostream &os) const {
  os << "Plate#: " << GetPlate() << ",\tBrand: " << GetBrand() << ",\tType: " << abi::__cxa_demangle(typeid(*this).name(), 0, 0, 0) << ",\t" << GetNumberOfSeats() << " seats,\t";
  return os;
 }
#endif
};

#ifdef DEBUG
ostream& operator<<(ostream &os, const Car& car) {
 return car.Print(os);
}
#endif

class Sedan : public Car {
 bool m_bSportPackage;
public:
 Sedan(const string &plate, const string &brand, bool sportPackage) : Car(plate, brand), m_bSportPackage(sportPackage) {}
 bool HasSportPackage() const { return m_bSportPackage; }
 virtual unsigned GetNumberOfSeats() const { return DEFAULT_SEATS; };
#ifdef DEBUG
 ostream& Print(ostream &os) const {
  Car::Print(os);
  os << ((HasSportPackage()) ? "with" : "without") << " sport package ";
  return os;
 }
#endif
};

class SUV : public Car {
 bool m_bThirdRow;
public:
 SUV(const string &plate, const string &brand, bool thirdRow) : Car(plate, brand), m_bThirdRow(thirdRow) {}
 bool HasThirdRow() const { return m_bThirdRow; }
 unsigned GetNumberOfSeats() const { 
  return (HasThirdRow()) ? THREE_ROW_SEATS : DEFAULT_SEATS;
 }
#ifdef DEBUG
 ostream& Print(ostream &os) const {
  Car::Print(os);
  os << ((HasThirdRow()) ? "with" : "without") << " third row ";
  return os;
 }
#endif
};

class CarRental {
 vector<shared_ptr<Car> > m_vspCars;
public:
 CarRental(vector<shared_ptr<Car> > &&cars) : m_vspCars(move(cars)) {}
 const vector<shared_ptr<Car> >& getInventory() const { return m_vspCars; }  
};

#ifdef DEBUG
ostream& operator<<(ostream &os, const CarRental& carRental) {
 const vector<shared_ptr<Car> > &cref = carRental.getInventory();
 for(size_t i(0); i < cref.size(); ++i) {
  os << *(cref[i]) << endl;
 }
}
#endif

int main() {
#ifdef DEBUG
 vector<shared_ptr<Car> > cars = { shared_ptr<Car>(new Sedan("123", "BMW", true)), shared_ptr<Car>(new SUV("456", "Kia", false)), shared_ptr<Car>(new SUV("789", "GMC", true)), shared_ptr<Car>(new Sedan("101112", "Toyota", false)) };
 CarRental cr(move(cars));
 cout << cr;
#endif
 return 0; 
}

/*
Compile: g++ -std=c++11 -DDEBUG -g carrental.cpp 
Run: ./a.out 
Verify expected output:
Plate#: 123,	Brand: BMW,	Type: Sedan,	5 seats,	with sport package 
Plate#: 456,	Brand: Kia,	Type: SUV,	5 seats,	without third row 
Plate#: 789,	Brand: GMC,	Type: SUV,	8 seats,	with third row 
Plate#: 101112,	Brand: Toyota,	Type: Sedan,	5 seats,	without sport package 
*/
