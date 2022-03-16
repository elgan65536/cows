#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <list>

class Cow {
    int id;
    int lowestWeight;
    int latestWeight;
    double avgMilk;
    int totalMilk;
    int amtMilk;

public:
    /* creates a cow with the given id */
    Cow(int i) {
        id = i;
        latestWeight = 0;
        lowestWeight = INT32_MAX;
        avgMilk = 0.0;
        totalMilk = 0;
        amtMilk = 0;
    }
    /* getter functions */
    int getId() {
        return id;
    }
    int getLowestWeight() {
        return lowestWeight;
    }
    int getLatestWeight() {
        return latestWeight;
    }
    double getAverageMilk() {
        return avgMilk;
    }
    /* takes in a weight value and updates lowest weight and latest weight */
    void updateWeight(int weight) {
        latestWeight = weight;
        if (weight < lowestWeight) {
            lowestWeight = weight;
        }
    }
    /* takes in a milk amount and updates average milk */
    void updateMilk(int milk) {
        amtMilk++;
        totalMilk += milk;
        avgMilk = ((double)totalMilk) / amtMilk;
    }
    /* returns true if the cow's data should be printed */
    bool isValid() {
        return amtMilk > 0 && lowestWeight < INT32_MAX;
    }
    /* prints the cow's record */
    std::string getRecord() {
        return std::to_string(id) + ' ' + 
        std::to_string(lowestWeight) + ' ' + 
        std::to_string(latestWeight) + ' ' + 
        std::to_string((int)avgMilk);
    }
};

/* comparison function to be used in sorting */
bool cowComparator(Cow c1, Cow c2) {
    if (c1.getLowestWeight() != c2.getLowestWeight()) {
        return c1.getLowestWeight() < c2.getLowestWeight();
    }
    if (c1.getLatestWeight() != c2.getLatestWeight()) {
        return c1.getLatestWeight() < c2.getLatestWeight();
    }
    if (c1.getAverageMilk() != c2.getAverageMilk()) {
        return c1.getAverageMilk() < c2.getAverageMilk();
    }
    return c1.getId() < c2.getId();
}

int main() {
    std::string fileName;
    std::cout << "enter file name: " << std::endl;
    std::cin >> fileName;
    std::ifstream cowFile(fileName, std::ios::in);
    std::string data;
    std::unordered_map<int, Cow> cowMap;
    std::getline(cowFile, data);
    int amtRecords = std::stoi(data); //first line of file converted to int

    while (std::getline(cowFile, data) && amtRecords--) { //repeat until the end of file or specified number of recoards read
        std::stringstream stream(data);
        std::string idString, mode, amountString;
        std::getline(stream, idString, ' '); //obtaining first three tokens from line 
        std::getline(stream, mode, ' ');
        std::getline(stream, amountString, ' ');
        int id = std::stoi(idString);
        int amount = std::stoi(amountString);
        
        if (cowMap.find(id) == cowMap.end()) { //testing if the cow is already in the map
            Cow cow(id);
            if (mode == "M" || mode == "m") {
                cow.updateMilk(amount);
            }
            if (mode == "W" || mode == "w") {
                cow.updateWeight(amount);
            }
            cowMap.insert({id, cow});
        } else { // case where cow already exists
            std::unordered_map<int,Cow>::iterator cowIterator = cowMap.find(id); //extracting the cow from the map
            if (mode == "M" || mode == "m") {
                cowIterator->second.updateMilk(amount);
            }
            if (mode == "W" || mode == "w") {
                cowIterator->second.updateWeight(amount);
            }
        }
    }

    std::vector<Cow> cowList;
    for (const auto& item : cowMap) {
        Cow cow = item.second;
        if (cow.isValid()) {
            cowList.push_back(cow); //creating a list of the cows from the map
        }
    }

    std::sort(cowList.begin(), cowList.end(), &cowComparator);

    std::cout << "output:" << std::endl;
    for (Cow cow : cowList) {
        std::cout << cow.getRecord() << std::endl;
    }

    return 0;
}