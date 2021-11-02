#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>
#include <vector>
enum Month {
  jan = 1,
  feb = 2,
  mar = 3,
  apr = 4,
  may = 5,
  jun = 6,
  jul = 7,
  aug = 8,
  sep = 9,
  oct = 10,
  nov = 11,
  dec = 12
};

class Measurement {
public:
  Measurement(std::string date, double measurement);

  Month measurement_month() const;
  int measurement_year() const;
  const std::string date;
  const double measurement;

private:
  std::vector<std::string> parse_date() const;
};

class Measurements {
public:
  double mean() const;
  void push_back(Measurement);

  std::vector<Measurement> measurements;
};

// takes a comma delimetered line from the dataset, and builds a measurement object
Measurement measurementFromLine(std::string line);

void run();

#endif
