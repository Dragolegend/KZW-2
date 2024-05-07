#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

struct Task{
    int time;
    int weight;
    int max_time;
    int n;
};

class Resolver{
    public:
    std::vector<Task> tasks;

    std::vector<std::string> files;

    std::vector <std::string> custom_split(std::string str, char separator) {
        std::vector <std::string> strings;
        int startIndex = 0, endIndex = 0;
        for (int i = 0; i <= str.size(); i++) {
            
            if (str[i] == separator || i == str.size()) {
                endIndex = i;
                std::string temp;
                temp.append(str, startIndex, endIndex - startIndex);
                strings.push_back(temp);
                startIndex = endIndex + 1;
            }
        
        }
        return strings;
    }

    void load_data(std::string path){
        std::ifstream inputFile(path);
        
        tasks.erase(tasks.begin(), tasks.end());
        
        if (inputFile.is_open()) {
            std::string line;
            int count = 1;
            while (std::getline(inputFile, line)) {

                std::vector<std::string> parts = custom_split(line, ' ');
                
                if(parts.size() == 3){
                    Task tmp;
                    tmp.time = stoi(parts.at(0));
                    tmp.weight = stoi(parts.at(1));
                    tmp.max_time = stoi(parts.at(2));
                    tmp.n = count++;

                    tasks.push_back(tmp);
                }
            }

            inputFile.close();
        }
    }

    void print_tasks(std::vector <Task> tasks) {
        std::cout << "\n\n\n";
        for(Task e : tasks){
            std::cout << "Time: " << e.time << " Weight: " << e.weight << " Max time: " << e.max_time <<  " n: " << e.n << "\n";
        }

        std::cout << "\nOrder: ";

        for(Task e : tasks){
            std::cout << e.n << ' ';
        }
        std::cout << "\n\n\n";
    }

    int penalty(std::vector <Task> tasks){
        int time = 0;
        int penalty = 0;

        for(int i = 0; i < tasks.size(); ++i){
            time += tasks.at(i).time;
            if(tasks.at(i).max_time < time){
                penalty += tasks.at(i).weight * (time - tasks.at(i).max_time);
            }
        }

        return penalty;
    }

    void sort(){
        std::vector <Task> tmp = tasks;

        std::sort( tasks.begin( ), tasks.end( ), [ ]( const auto& lhs, const auto& rhs )
        {
            return lhs.max_time < rhs.max_time;
        });
    }

    void search2(int k_max){
        for(int i = 0; i < tasks.size(); ++i){
                for(int j = 1; j < tasks.size(); ++j){

                    Task temp;
                    for(int k = 0; k <= k_max; ++k){
                        if(j >= k){
                            int pen = penalty(tasks);

                            temp = tasks.at(i);
                            tasks.at(i) = tasks.at(j - k);
                            tasks.at(j - k) = temp;

                            if(pen > penalty(tasks)){
                                std::cout << penalty(tasks) << "\n";
                            }else{
                                temp = tasks.at(i);
                                tasks.at(i) = tasks.at(j - k);
                                tasks.at(j - k) = temp;
                            }
                        }
                    }
                }
            }
    }

    void resolve2() {
        sort();

        search2(0);
    }

    Resolver(){
        files = {"./data.10", "./data.11", "./data.12", "./data.13", "./data.14", "./data.15", "./data.16", "./data.17", "./data.18", "./data.19" , "./data.20"};
    }

};



int main(){
    
    auto start = std::chrono::high_resolution_clock::now();
    
    Resolver r1;

    for(std::string x : r1.files){
        r1.load_data(x);
        r1.resolve2();

        r1.print_tasks(r1.tasks);

        std::cout << "Penalty: " << r1.penalty(r1.tasks) << "\n\n\n";
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
 
    std::cout << "Execution time(microseconds): " << duration.count() << "\n";
}