#pragma once
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

inline void trim(std::string &str) {
  str = str.substr(1);

  if (str[str.size() - 1] == '*') {
    str = str.substr(0, str.size() - 1);
  }
}

inline void trimForLeaderboard(std::string &str) { str = str.substr(1); }

inline int timeStringToSeconds(const std::string &timeStr) {
  std::stringstream ss(timeStr);
  std::vector<int> timeArray;

  std::string line;

  while (std::getline(ss, line, ':')) {
    if (line[0] == '0') {
      line = line.substr(1);
    }
    try {
      timeArray.push_back(std::stoi(line));
    } catch (...) {
      std::cout << "Trouble converting: " << line << std::endl;
    }
  }

  return timeArray[0] * 60 + timeArray[1];
}

inline std::string secondsToTimeString(const int &timeNum) {
  int minutes = timeNum / 60;
  int seconds = timeNum % 60;
  std::ostringstream oss;
  oss << std::setfill('0') << std::setw(2) << minutes << ":"
      << std::setfill('0') << std::setw(2) << seconds;
  return oss.str();
}

inline void setScore(std::string username, int time) {
  std::fstream file("./files/leaderboard.txt", std::ios::out | std::ios::in);

  std::cout << "Adding new score!\n";

  std::map<std::string, int> sortedScores;

  std::vector<std::pair<std::string, int>> pairOfScores;

  std::string line;
  while (std::getline(file, line)) {
    std::string substr;
    std::pair<std::string, int> entry;
    std::stringstream stream(line);

    std::getline(stream, substr, ',');
    int time = timeStringToSeconds(substr);

    std::getline(stream, substr, ',');

    std::string name = substr;
    trim(name);

    entry.first = name;
    entry.second = time;

    pairOfScores.push_back(entry);
  }

  std::string newName = username + "*";
  int newTime = time;

  std::pair<std::string, int> newEntry = {newName, newTime};
  pairOfScores.push_back(newEntry);

  std::sort(
      pairOfScores.begin(), pairOfScores.end(),
      [](const std::pair<std::string, int> &a,
         const std::pair<std::string, int> &b) { return a.second < b.second; });

  file.close();
  file.open("./files/leaderboard.txt", std::ios::out | std::ios::trunc);

  for (const std::pair<std::string, int> &score : pairOfScores) {
    std::cout << "Adding: " << score.first << " with time of "
              << secondsToTimeString(score.second) << "\n";
    file << secondsToTimeString(score.second) + ", " + score.first + "\n";
  }
  std::cout << "New score successfully added! Closing file now!\n";

  file.close();
}

inline std::string leaderString() {
  std::fstream file("./files/leaderboard.txt", std::ios::out | std::ios::in);

  std::vector<std::pair<std::string, int>> pairOfScores;

  std::string line;
  while (std::getline(file, line)) {
    std::string substr;
    std::pair<std::string, int> entry;
    std::stringstream stream(line);

    std::getline(stream, substr, ',');
    int time = timeStringToSeconds(substr);

    std::getline(stream, substr, ',');

    std::string name = substr;
    trimForLeaderboard(name);

    entry.first = name;
    entry.second = time;

    pairOfScores.push_back(entry);
  }

  int size = (pairOfScores.size() < 5) ? pairOfScores.size() : 5;

  std::ostringstream oss;

  for (int x = 0; x < size; ++x) {
    oss << std::to_string(x + 1) << ".\t"
        << secondsToTimeString(pairOfScores[x].second) << "\t"
        << pairOfScores[x].first << "\n\n";
  }

  return oss.str();
}
