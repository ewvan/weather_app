#pragma once

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
//#include "dotenv.h"

using json = nlohmann::json;
//using namespace dotenv;


struct Coordinates {
  std::string city;
  double latitude;
  double longitude;

  Coordinates(std::string city_, double latitude_, double longitude_): city(city_), latitude(latitude_), longitude(longitude_) {};
};

json getWeatherData(const std::string& city);
void getDayData(const json& temperature_2m,
				const json& visibility,
				const json& precipitation_probability,
				const json& precipitation,
				const json& weathercode,
				const json& winddirection_10m,
				const json& hourly_units,
				const json& hourly_time,
				const json& windspeed_10m,
				const int& dayCounter,
				json& response);

template <typename T>
T findMostFrequent(const json& arr, int from, int to);

template <typename T>
T findMax(const json& arr, int from, int to);

template <typename T>
T findMin(const json& arr, int from, int to);

template <typename T>
double findAvg(const json& arr, int from, int to);