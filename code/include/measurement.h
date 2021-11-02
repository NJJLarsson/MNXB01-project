#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>
class Measurement {
public:
  Measurement(std::string date, double measurement);

private:
  const std::string date;
  const double measurement;
};

#endif
