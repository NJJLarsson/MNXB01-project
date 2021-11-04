#include "measurement.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLegend.h"

Measurement::Measurement(std::string date, double measurement)
    : date(date), measurement(measurement) {}

Measurement measurementFromLine(std::string line) {
  std::stringstream ss(line);
  std::vector<std::string> row;
  std::string cell;

  while (ss.good() && std::getline(ss, cell, ';')) {
    // Initialize and add <colname, int vector> pairs to result
    row.push_back(cell);
  }

  return Measurement(row[0], std::stod(row[2]));
}

std::vector<std::string> Measurement::parse_date() const {
  // why c++ wouln't have date parsing in the std is beyond be
  std::stringstream date(Measurement::date);
  std::string date_item;
  std::vector<std::string> parsed_date_items;
  while (date.good() && getline(date, date_item, '-')) {
    parsed_date_items.push_back(date_item);
  }

  return parsed_date_items;
}
Month Measurement::measurement_month() const {
  auto parsed_date_items = Measurement::parse_date();

  return (Month)std::stoi(parsed_date_items[1]);
}
int Measurement::measurement_year() const {
  auto parsed_date_items = Measurement::parse_date();

  return std::stoi(parsed_date_items[0]);
}

double Measurements::mean() const {
  if (Measurements::measurements.size() == 0) {
    return 0.0;
  }

  double sum{0};
  for (Measurement m : Measurements::measurements) {
    sum += m.measurement;
  }

  return sum / Measurements::measurements.size();
}
void Measurements::push_back(Measurement m) {
  Measurements::measurements.push_back(m);
}

void run(std::string path_to_file, int month_int) {
  Month month = (Month)month_int;
  std::ifstream file(path_to_file);

  std::string line;
  // Read until we encouter "Datum;", which means that the next lines will be
  // the actual data
  while (getline(file, line)) {
    if (line.rfind("Datum;", 0) == 0) {
      break;
    }
  }

  Measurements measurements{};
  while (getline(file, line)) {
    Measurement measurement = measurementFromLine(line);
    if (measurement.measurement_month() == month) {
      measurements.push_back(measurementFromLine(line));
    }
  }

  // bucket measurements per year
  std::map<int, Measurements> measurements_per_year;
  for (Measurement m : measurements.measurements) {
    measurements_per_year[m.measurement_year()].push_back(m);
  }

  std::cout << measurements.measurements.size() << std::endl;
  std::cout << measurements.measurements[0].measurement_month() << std::endl;
  std::cout << measurements_per_year.size() << std::endl;

  TCanvas *c4 = new TCanvas("c4", "4 - Example yearly mean graph", 200, 10, 500, 300);
  TGraph *gr = new TGraph();

  for (auto p : measurements_per_year) {
    gr->SetPoint(gr->GetN(), p.first, p.second.mean());
  }

  TF1 *f = new TF1("func", "[1] + [0]*x", 1800, 2025);
  f->SetLineStyle(1);
  f->SetLineWidth(6);
  f->SetLineColor(8);
  gr->Fit(f);
  f->Draw();

  // A - draw axis
  // L - draw line between points
  // * - draw points
  gr->Draw("AL*");

  std::string out = "measurement" + std::to_string(month_int) + ".png";
  c4->SaveAs(out.c_str());
}
