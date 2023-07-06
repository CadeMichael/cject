/*
 * File: file.cc
 * Author: Cade Lueker
 * Date: July 5, 2023
 * Description: File operations on the project file
 * License: MIT
 */
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

class ProjectFile {
private:
  std::string homeDir = std::string(std::getenv("HOME"));
  bool check_proj(std::string path);

public:
  bool append_proj(std::string path);
  std::vector<std::string> read_proj();
  std::vector<std::string> read_path(std::string path);
  void remove_proj(std::string path);
};

/**
 * Checks if a project path is valid
 *
 * takes a string as input and returns a boolean
 *
 * @param path the path of the project
 * @return validity of the path
 */
bool ProjectFile::check_proj(std::string path) {
  if (std::filesystem::exists(path)) {
    std::vector<std::string> projs = read_proj();
    for (auto p : projs) {
      if (p == path)
        return false;
    }
    return true;
  }
  return false;
}

/**
 * Append a project path to the project file
 *
 * take a string and output a boolean
 *
 * @param path the path of the project
 * @return validity of adding the project
 */
bool ProjectFile::append_proj(std::string path) {
  std::ofstream outputFile(homeDir + "/cproj", std::ios::app);
  if (outputFile.is_open()) {
    if (check_proj(path)) {
      outputFile << path << std::endl;
      outputFile.close();
      std::cout << path << " <- added to proj file" << std::endl;
      return true;
    }
    std::cout << path << " <- invalid or exists" << std::endl;
    return false;
  }
  std::cout << "failed to append to ~/cproj" << std::endl;
  return false;
}

/**
 * Read the project file and output paths
 *
 * no parameters and a vector of string is returned
 *
 * @return a vector of project paths as strings
 */
std::vector<std::string> ProjectFile::read_proj() {
  std::vector<std::string> projs;
  std::ifstream inputFile(homeDir + "/cproj");
  if (inputFile.is_open()) {
    std::string proj;
    while (std::getline(inputFile, proj)) {
      projs.push_back(proj);
    }
    return projs;
  }
  return projs;
}

/**
 * Read files from defined path
 *
 * @param path of the selected project
 * @return a vector of files in project path as strings
 */
std::vector<std::string> ProjectFile::read_path(std::string path) {
  namespace fs = std::filesystem;
  std::vector<std::string> files;
  for (const auto &entry : fs::directory_iterator(path)) {
    files.push_back(entry.path().filename().string());
  }
  return files;
}

/**
 * Delete a project path
 *
 * @param path of the project to be deleted
 * @return a vector of project paths as strings
 */
void ProjectFile::remove_proj(std::string path) {
  std::vector<std::string> projs = read_proj();
  std::vector<std::string> updated;

  for (auto p : projs) {
    if (p != path) {
      updated.push_back(p);
    }
  }

  std::ofstream outputFile(homeDir + "/cproj", std::ios::trunc);

  if (outputFile.is_open()) {
    for (auto p : updated) {
      outputFile << p << std::endl;
    }
    outputFile.close();
  }
}
