#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

static const std::string g_HomeDirectory = "~/.local/bin/VOJData/";
static const std::string g_MainURL = "https://codeforces.com/group/FLVn1Sc504/";

void showHelp();
std::string strToUpper(char *cTask);

namespace ProcessJSON {
void readJson(json &j, std::string dataFileName) {
    std::ifstream in(g_HomeDirectory + dataFileName);
    in >> j;
}

};  // namespace ProcessJSON

namespace VOJ {

enum class LoadType {
    Open,
    Submit
};

LoadType LT;

std::vector<std::string> splitString(std::string s, char delimiter) {
    std::stringstream ss(s);
    std::vector<std::string> ret;

    while (ss.good()) {
        std::string substr;
        std::getline(ss, substr, delimiter);
        ret.emplace_back(substr);
    }

    return ret;
}

std::vector<std::string> getIDs(const json &j, const std::string &s) {
    std::stringstream ss;
    ss << j[s];
    std::string t = ss.str();
    t.erase(t.begin());
    t.pop_back();
    return splitString(t, ',');
}

void loadProblem(const json &j, const std::string &s) {
    std::vector<std::string> contestInfo = splitString(s, '/');
    std::string contestID = contestInfo[0];
    std::string problemLetter = contestInfo[1];

    std::cout << "Loading contest " << j[contestID] << ", problem " << problemLetter << "..." << std::endl;

    std::string URL = g_MainURL + "contest/" + contestID + "/problem/" + problemLetter;
    std::string command;
    if (LT == LoadType::Open) {
        command = "xdg-open " + URL;
    }
    else {
        command = "cf submit " + URL;
    }

    try {
        system(command.data());
    }
    catch (...) {
        std::cout << "Error." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Done" << std::endl;
}

void Open(char *cTask) {
    std::string taskName = strToUpper(cTask);
    json j_ProblemIDs;
    json j_Contests;
    ProcessJSON::readJson(j_ProblemIDs, "links.json");
    ProcessJSON::readJson(j_Contests, "contest_name.json");

    if (j_ProblemIDs.contains(taskName)) {
        std::vector<std::string> IDs = getIDs(j_ProblemIDs, taskName);

        if (IDs.size() == 1) {
            loadProblem(j_Contests, IDs[0]);
        }
        else {
            std::cout << "There are several contests to submit to this problem to:" << std::endl;

            for (size_t id = 0; id < IDs.size(); id++) {
                std::vector<std::string> contestInfo = splitString(IDs[id], '/');
                std::cout << ">>> (" << id + 1 << ") " << j_Contests[contestInfo[0]] << std::endl;
            }

            int option;
            std::cin >> option;

            if (1 <= option && option <= static_cast<int>(IDs.size())) {
                loadProblem(j_Contests, IDs[option - 1]);
            }
            else {
                std::cout << "Invalid option. Quitting..." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    else {
        std::cout << "hey u sure the problem exists?" << std::endl;
        exit(EXIT_FAILURE);
    }
}


};  // namespace VOJ

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Not enough arguments." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) {
        showHelp();
    }

    if (argc < 3) {
        std::cout << "Not enough arguments." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "open") != 0 && strcmp(argv[1], "submit") != 0) {
        std::cout << "Illegal command." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "open") == 0) {
        VOJ::LT = VOJ::LoadType::Open;
    }
    else if (strcmp(argv[1], "submit") == 0) {
        VOJ::LT = VOJ::LoadType::Submit;
    }
    else {
        showHelp();
    }

    VOJ::Open(argv[2]);

    return EXIT_SUCCESS;
}

void showHelp() {
    std::cout << "voj open [problem name]" << std::endl;
    std::cout << "voj submit [problem name]" << std::endl;
    exit(EXIT_FAILURE);
}

std::string strToUpper(char *c) {
    int n = strlen(c);
    for (int i = 0; i < n; i++) {
        c[i] = toupper(c[i]);
    }
    return std::string(c);
}

