#include "weather.h"
const int maxCount = 16;

template<typename T>
double findAvg(const json& arr, int from, int to) {
  double sum = 0;
  int count = 0;

  for (const auto& elem : arr) {
	if (elem.is_null()) {
	  return -1;
	}
	if (count > to) {
	  break;
	}
	if (count < from) {
	  count++;
	  continue;
	}
	sum += elem.get<T>();
	count++;
  }

  if (count == 0) {
	return 0;
  }

  return sum / (count - from);
}

template<typename T>
T findMax(const json& arr, int from, int to) {
  T maxNum = INT_MIN;

  int count = 0;
  for (const auto& elem : arr) {
	if (elem.is_null()) {
	  return -1;
	}
	if (count > to) {
	  break;
	}
	if (count < from) {
	  count++;
	  continue;
	}
	int num = elem.get<T>();
	if (num > maxNum) {
	  maxNum = num;
	}
	count++;
  }

  return maxNum;
}
template<typename T>
T findMin(const json& arr, int from, int to) {
  T minNum = INT_MAX;

  int count = 0;
  for (const auto& elem : arr) {
	if (elem.is_null()) {
	  return -1;
	}
	if (count > to) {
	  break;
	}
	if (count < from) {
	  count++;
	  continue;
	}
	int num = elem.get<T>();
	if (num < minNum) {
	  minNum = num;
	}
	count++;
  }

  return minNum;
}

template<typename T>
T findMostFrequent(const json& arr, int from, int to) {
  std::unordered_map<T, int> freqMap;
  T mostFrequent;
  int maxFreq = 0;

  int count = 0;
  for (const auto& elem : arr) {
	if (elem.is_null()) {
	  return -1;
	}
	if (count > to) {
	  break;
	}
	if (count < from) {
	  count++;
	  continue;
	}
	int key = elem.get<T>();
	if (freqMap.find(key) != freqMap.end()) {
	  freqMap[key]++;
	} else {
	  freqMap[key] = 1;
	}
	count++;
  }
  for (auto& [key, value] : freqMap) {
	if (value > maxFreq) {
	  mostFrequent = key;
	  maxFreq = value;
	}
  }

  return mostFrequent;
}

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
				json& response) {

  int range = 24 * dayCounter;
  std::string day = hourly_time[range].dump().substr(1, 10);

  json morning;
  json afternoon;
  json evening;
  json night;
  json whole_day;

  // calculating for each part of day
  for (int part = -1; part < 4; part++) {
	json sample;

	int weather_id = findMostFrequent<int>(weathercode,
										   part == -1 ? range : part * 6 + range,
										   part == -1 ? range + 24 : (part + 1) * 6 - 1 + range);

	int max_temperature = findMax<double>(temperature_2m,
										  part == -1 ? range : part * 6 + range,
										  part == -1 ? range + 24 : (part + 1) * 6 - 1 + range);

	int min_temperature = findMin<double>(temperature_2m,
										  part == -1 ? range : part * 6 + range,
										  part == -1 ? range + 24 : (part + 1) * 6 - 1 + range);

	int wind_direction = findAvg<double>(winddirection_10m,
										 part == -1 ? range : part * 6 + range,
										 part == -1 ? range + 24 : (part + 1) * 6 - 1 + range);

	int avg_visibility = findAvg<double>(visibility,
										 part == -1 ? range : part * 6 + range,
										 part == -1 ? range + 24 : (part + 1) * 6 - 1 + range) / 1000;

	int max_windspeed = findMax<double>(windspeed_10m,
										part == -1 ? range : part * 6 + range,
										part == -1 ? range + 24 : (part + 1) * 6 - 1 + range);
	int min_windspeed = findMin<double>(windspeed_10m,
										part == -1 ? range : part * 6 + range,
										part == -1 ? range + 24 : (part + 1) * 6 - 1 + range);

	int avg_precipitation_probability = findAvg<int>(precipitation_probability,
													 part == -1 ? range : part * 6 + range,
													 part == -1 ? range + 24 : (part + 1) * 6 - 1 + range);
	int avg_precipitation_sum = findAvg<double>(precipitation,
												part == -1 ? range : part * 6 + range,
												part == -1 ? range + 24 : (part + 1) * 6 - 1 + range) * part == -1 ? 24
																												   : 6;

	sample["weather_id"] = {
		{"unit", "vmo code"},
		{"id", weather_id}
	};

	sample["min_max_temperature"] = {
		{"unit", hourly_units["temperature_2m"]},
		{"min", min_temperature},
		{"max", max_temperature}
	};
	sample["wind_direction"] = {
		{"unit", hourly_units["winddirection_10m"]},
		{"angle", wind_direction}
	};
	sample["visibility"] = {
		{"unit", "km"},
		{"range", avg_visibility}
	};
	sample["wind_speed"] = {
		{"unit", hourly_units["windspeed_10m"]},
		{"max", max_windspeed},
		{"min", min_windspeed}
	};
	sample["precipitation"] = {
		{"precipitation_probability", {
			{"percent", avg_precipitation_probability},
			{"unit", hourly_units["precipitation_probability"]}
		}},
		{
			"precipitation_sum", {
			{"height", avg_precipitation_sum},
			{"unit", hourly_units["precipitation"]}
		}
		}
	};

	switch (part) {
	  case 0: morning = sample;
		break;
	  case 1: afternoon = sample;
		break;
	  case 2: evening = sample;
		break;
	  case 3: night = sample;
		break;
	  case -1: whole_day = sample;
		break;
	  default: std::destroy(sample.begin(), sample.end());
		break;
	}
  }

  response.push_back({
						 {"day", day},
						 {"morning", morning},
						 {"afternoon", afternoon},
						 {"evening", evening},
						 {"night", night},
						 {"whole_day", whole_day}
					 });
}

json getWeatherData(const std::string& city) {
//  env.load_dotenv("../../.env");
  const std::string API_TOKEN="2Ivb0JLaMkSqUYRmp+N2Vw==DhhSsgDJxbyd0hfy";
  const auto cityCoords = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city?name=" + city},
								   cpr::Header{{"X-Api-Key", API_TOKEN}});

  const json file = json::parse(cityCoords.text.substr(1, cityCoords.text.length() - 2));

  const auto Coords = Coordinates(city, file["latitude"], file["longitude"]);

  const auto weather = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
								cpr::Parameters{{"latitude", std::to_string(Coords.latitude)},
												{"longitude", std::to_string(Coords.longitude)},
												{"hourly", "temperature_2m"},
												{"hourly", "visibility"},
												{"hourly", "precipitation_probability"},
												{"hourly", "precipitation"},
												{"hourly", "weathercode"},
												{"hourly", "windspeed_10m"},
												{"hourly", "winddirection_10m"},
												{"forecast_days", std::to_string(maxCount)},
												{"timezone", "GMT"}}
  );

  auto weatherJson = json::parse(weather.text);

  json response = json::array();


  // hourly
  auto temperature_2m = weatherJson["hourly"]["temperature_2m"];
  auto visibility = weatherJson["hourly"]["visibility"];
  auto precipitation_probability = weatherJson["hourly"]["precipitation_probability"];
  auto precipitation = weatherJson["hourly"]["precipitation"];
  auto weathercode = weatherJson["hourly"]["weathercode"];
  auto winddirection_10m = weatherJson["hourly"]["winddirection_10m"];
  auto windspeed_10m = weatherJson["hourly"]["windspeed_10m"];

  auto hourly_units = weatherJson["hourly_units"];
  auto hourly_time = weatherJson["hourly"]["time"];

  for (int day = 0; day < maxCount; day++) {
	getDayData(temperature_2m,
			   visibility,
			   precipitation_probability,
			   precipitation,
			   weathercode,
			   winddirection_10m,
			   hourly_units,
			   hourly_time,
			   windspeed_10m,
			   day,
			   response);
  }

  return response;
}
