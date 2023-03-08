#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <limits>

using namespace std;

ifstream& data_reader(ifstream& input, int &user, int &movie, double &rating) {
    input >> user;
    input.ignore();
    input >> movie;
    input.ignore();
    input >> rating;

    return input;
}

ifstream& test_reader(ifstream& input, int &id, int &user, int &movie) {
    input >> id;
    input.ignore();
    input >> user;
    input.ignore();
    input >> movie;

    return input;
}

double average(unordered_map<int, double> &input) {
    double sum = 0;
    for (auto& i : input) {
        sum += i.second;
    }
    return input.size() == 0 ? 0 : sum / input.size();
}

double similiarity(unordered_map<int, double> &input1, unordered_map<int, double> &input2) {
    double upper = 0;
    double lower1 = 0;
    double lower2 = 0;

    double average_input1 = average(input1);
    double average_input2 = average(input2);

    for (auto& i : input1) {
        if (input2.find(i.first) != input2.end()) {
            upper += (i.second - average_input1) * (input2.at(i.first) - average_input2);
            lower1 += pow(i.second - average_input1, 2);
            lower2 += pow(input2.at(i.first), 2);
        }
    }

    if (lower1 == 0 || lower2 == 0) return 0;
    return upper / (sqrt(lower1) * sqrt(lower2));
}

double forsee(unordered_map<int, unordered_map<int, double>> &rating_data, int user, int movie) {
    double sum = 0;
    double sum_of_weights = 0;

    for (auto& i : rating_data) {
        if (i.second.find(movie) != i.second.end() && i.first != user) {
            double sim = similiarity(rating_data[user], rating_data[i.first]);

            sum += sim * (i.second.at(movie) - average(i.second));
            sum_of_weights += abs(sim);
        }
    }

    if (sum_of_weights == 0) { return average(rating_data[user]); }
    return average(rating_data[user]) + (sum / sum_of_weights);
}

/*
unordered_map<int, unordered_map<int, double>> transpose(unordered_map<int, unordered_map<int, double>> &input) {
    unordered_map<int, unordered_map<int, double>> output;
}
*/

int main() {
    unordered_map<int, unordered_map<int, double>> rating_data;

    //Reading Data From CSV
    ifstream data_in("./train.csv");

    if (data_in.is_open()) {
        int user;
        int movie;
        double rating;

        data_in.ignore(numeric_limits<streamsize>::max(), '\n');

        while (data_reader(data_in, user, movie, rating)) {
            rating_data[user][movie] = rating;
        }
    }
    else {
        cout << "File couldn't be opened.";
        return 0;
    }

    cout << "File read.";

    //Reading Test Values From CSV and Making Predictions
    ifstream test_in("./test.csv");
    ofstream submit_out("./submission.csv");

    if (test_in.is_open() && submit_out.is_open()) {
        int id;
        int user;
        int movie;

        test_in.ignore(numeric_limits<streamsize>::max(), '\n');
        submit_out << "ID,Predicted\n";

        while (test_reader(test_in, id, user, movie)) {
            submit_out << id << "," << forsee(rating_data, user, movie) << endl;
        }
    }
    else {
        cout << "File couldn't be opened.";
        return 0;
    }

    cout << "Prediction done.";

    //Printing Top 10 Users and Movies by Number of Ratings

    return 0;
}
