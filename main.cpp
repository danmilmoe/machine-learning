// Project UID db1f506d06d84ab787baf250c265e24e
#include <iostream>
#include <map>
#include <fstream>
#include <set>
#include <string>
#include "csvstream.h"
#include <cmath>

using namespace std;

set<string> unique_words_func(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
}

class Classifier {
    private:

    //Member Variables
    int num_posts = 0;
    map<string, int> unique_words;
    map<string, int> posts_with_w;
    map<string, int> posts_with_c;
    map<string, map<string, int>> posts_with_c_and_w;

    public:

    //Default Constructor - does nothing
    Classifier() {}

    //Member Functions
    int get_num_posts() {return num_posts;}

    int get_num_posts_with_c(const string c) {return posts_with_c[c];}

    int get_num_posts_with_w(const string w) {return posts_with_w[w];}

    int get_num_unique_words() {return unique_words.size();}

    int get_num_posts_with_c_and_w(const string c, const string w) 
    {return posts_with_c_and_w[c][w];}

    vector<string> get_vec_of_tags() {
        vector<string> vec_of_tags;
        for(auto& tag: posts_with_c) {
            vec_of_tags.push_back(tag.first);
        }
        return vec_of_tags;
    }

    map<string, map<string, int>> get_posts_with_c_and_w() {
        return posts_with_c_and_w;
    }

    double calc_log_prior(const string c) {
        return log((1.0 * get_num_posts_with_c(c)) / (1.0 * num_posts));
    }

    double calc_log_likelihood(const string c, const string w) {
        if(unique_words.find(w) == unique_words.end()) {
            return log(1.0 / (1.0 * num_posts));
        }
        else if(posts_with_c_and_w[c].find(w) == posts_with_c_and_w[c].end()) {
            return log((1.0 * get_num_posts_with_w(w)) / num_posts);
        }
        else {
            return log((1.0 * get_num_posts_with_c_and_w(c, w)) 
                     / (1.0 * get_num_posts_with_c(c)));
        }
    }

    vector<pair<string, string>> process_data(istream &fin) {
        csvstream csvin(fin);
        map<string, string> row;
        vector<pair<string, set<string>>> vec_pairs; //Vec of pairs to store tag/word info
        pair<string, string> train_raw_pair; //Pair of {tag, content}
        vector<pair<string, string>> raw_output;
        while(csvin >> row) {
            ++num_posts; //Count total number of posts, store in member variable
            pair<string, set<string>> pairs; //Pairs for vector

            for (auto &col:row) {
            const string &column_name = col.first;
            const string &datum = col.second;

            //Store number of posts for each unique tag in member variable
            if(column_name == "tag") {
                string tag = datum;
                ++posts_with_c[tag];
                pairs.first = tag;
                train_raw_pair.first = datum;
            }

            //Store number of posts for each unique word w in member variable
            //Store all unique words in map member variable; ignore value, keep size
            if(column_name == "content") {
                set<string> words = unique_words_func(datum);
                for(auto& it: words) {
                    ++posts_with_w[it];
                    unique_words[it];
                }
                pairs.second = words;
                train_raw_pair.second = datum;
            }
            }
            vec_pairs.push_back(pairs);
            raw_output.push_back(train_raw_pair);
        }
        //Store pairs of unique words and tags in member variable
        for (auto &pair:vec_pairs) {
            const string &tag = pair.first;
            const set<string> &words = pair.second;
            for(auto &word: words) {
                ++posts_with_c_and_w[tag][word];
            }
        }

        return raw_output;
    }
};

void print_helper_debug_1(vector<pair<string,string>> train_raw_data) {
    cout << "training data:" << endl;
        for(auto& pair_data: train_raw_data) {
            cout << "  label = " << pair_data.first;
            cout << ", content = " << pair_data.second << endl;
        }
}

void print_helper_debug_2(Classifier classifier) {
    cout << "vocabulary size = " << classifier.get_num_unique_words() << endl;
        cout << endl << "classes:" << endl;
        vector<string> tag_vector = classifier.get_vec_of_tags();
        for(auto& tag : tag_vector) {
            cout << "  " << tag << ", ";
            cout << classifier.get_num_posts_with_c(tag) << " examples, ";
            cout << "log-prior = " << classifier.calc_log_prior(tag) << endl;
        }
        cout << "classifier parameters:" << endl;
        for(auto& it_c : classifier.get_posts_with_c_and_w()) {
            for(auto& it_w : it_c.second) {
                cout << "  " << it_c.first << ":";
                cout << it_w.first << ", count = ";
                cout << it_w.second << ", log-likelihood = ";
                cout << classifier.calc_log_likelihood(it_c.first, it_w.first) << endl;
            }
        }
}

void print_final_results_debug(Classifier classifier,
                    bool debug, vector<pair<string,string>> train_raw_data) {
    if(debug) {
        print_helper_debug_1(train_raw_data);
    }
    cout << "trained on " << classifier.get_num_posts() << " examples" << endl;
    if (debug) {
        print_helper_debug_2(classifier);
    }
}

void print_final_results_test(vector<pair<string, string>> test_data_raw,
                            vector<pair<string, double>> test_log_prob_scores) {
    cout << endl << "test data:" << endl;
    auto it1 = test_data_raw.begin();
    auto it2 = test_log_prob_scores.begin();
    int num_right = 0;
    int num_tests = 0;
    while(it1 != test_data_raw.end() && it2 != test_log_prob_scores.end()) {
        cout << "  correct = " << it1->first;
        cout << ", predicted = " << it2->first;
        cout << ", log-probability score = " << it2->second << endl;
        cout << "  content = " << it1->second << endl << endl;
        if(it1->first == it2->first) {++num_right;}
        ++num_tests;
        ++it1;
        ++it2;
    }
    cout << "performance: " << num_right << " / ";
    cout << num_tests << " posts predicted correctly" << endl;
}

vector<pair<string, double>> calc_test_log_prob_scores(
            vector<pair<string, set<string>>> test_data, Classifier classifier) {

    vector<pair<string, double>> test_log_prob_scores;
    for(auto& it: test_data) {
        pair<string, double> insertion;
        double log_prob_score;
        double max_score= -1000000;
        string predicted_tag;
        for(auto& tag: classifier.get_vec_of_tags()) {
            double log_prob_prior = classifier.calc_log_prior(tag);
            double log_prob_likelihood = 0;
            for(auto& word: it.second) {
                log_prob_likelihood += classifier.calc_log_likelihood(tag, word);
            }
            log_prob_score = log_prob_prior + log_prob_likelihood;
            if(log_prob_score > max_score) {
                max_score = log_prob_score;
                predicted_tag = tag;
            }
        }
        insertion.first = predicted_tag;
        insertion.second = max_score;
        test_log_prob_scores.push_back(insertion);
    }
    return test_log_prob_scores;
}

int main(int argc, char* argv[]) {
    cout.precision(3);
    string train_set;
    string test_set;
    bool debug = false;
    if(argc == 3) {
        train_set = string(argv[1]);
        test_set = string(argv[2]);
    }
    else if (argc == 4 && string(argv[3]) == "--debug") {
        train_set = string(argv[1]);
        test_set = string(argv[2]);
        debug = true;
    }
    else {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }

    ifstream fin_train(train_set);
    ifstream fin_test(test_set);
    if(!fin_train.is_open()) {
        cout << "Error opening file: " << train_set << endl;
        return 1;
    }
    if(!fin_test.is_open()) {
        cout << "Error opening file: " << test_set << endl;
        return 1;
    }
    
    //Processes training set
    Classifier classifier;
    vector<pair<string,string>> train_raw_data;
    train_raw_data = classifier.process_data(fin_train);

    //Processes test set
    csvstream csvtest(fin_test);
    map<string, string> test_row;
    vector<pair<string, set<string>>> test_data;
    vector<pair<string, string>> test_data_raw;
    string test_tag;
    string test_words;
    while(csvtest >> test_row) {
        pair<string, set<string>> pair_processed; // {correct tag, words}
        pair<string, string> pair_raw; // {correct tag, content}
        for(auto& col: test_row) {
            const string &column_name = col.first;
            const string &datum = col.second;

            if(column_name == "tag") {
                pair_processed.first = datum;
                pair_raw.first = datum;
            }
            if(column_name == "content") {
                pair_processed.second = unique_words_func(datum);
                pair_raw.second = datum;
            }
        }
        test_data.push_back(pair_processed);
        test_data_raw.push_back(pair_raw);
    }

    //Calculate log probability scores for test set
    vector<pair<string, double>> test_log_prob_scores;
    test_log_prob_scores = calc_test_log_prob_scores(test_data, classifier); // {predicted tag, score}

    //Print results
    print_final_results_debug(classifier, debug, train_raw_data);
    print_final_results_test(test_data_raw, test_log_prob_scores);
}