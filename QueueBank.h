#pragma once
#include <iostream>
#include <deque>
#include <string>
#include <fstream>

class Client {

private:
    int number;
    std::string name;
    int time_of_entry;
    int time_of_service;
    std::string choice;
    int time_of_end;

public:
    Client();

    Client(int number, std::string name, int time_of_entry, int time_of_service, std::string choice){
        this->number = number;
        this->name = name;
        this->time_of_entry = time_of_entry;
        this->time_of_service = time_of_service;
        this->choice = choice;
        this->time_of_end = time_of_entry + time_of_service;
    }

    int get_number(){ 
        return number; 
    }

    std::string get_name(){
        return name;
    }

    int get_time_of_entry(){
        return time_of_entry;
    }

    int get_time_of_end(){
        return time_of_end;
    }

    std::string get_choice(){
        return choice;
    }

    int get_time_of_service(){
        return time_of_service;
    }

    void set_time_of_end(int value){
        time_of_end = value;
    }
    
};


class Bank {
private:
    int cash[3];
    int ATM[8];
    std::deque<Client> Queue;

public:
    void make_start_data(){
        std::string name_of_file;
        std::cout << "Введите название файла с добавлением .txt в конец названия файла: " << std::endl;
        std::cin >> name_of_file;
        std::ifstream file(name_of_file.c_str());
        if (file.is_open()){
            int num, t_of_e, t_of_s;
            std::string n, ch;
            while (file >> num >> n >> t_of_e >> t_of_s >> ch){
                Client client(num, n, t_of_e, t_of_s, ch);
                Queue.push_back(client);
            }
            file.close();
        }
        else{
            std::cout<<"Файл невозможно открыть. Возможно, вы ввели некорректное имя файла!" << std::endl;
        }
    }

    void display_data(){
        for (Client client : Queue){
            std::cout << "Клиент №" << client.get_number() << ": " << std::endl;
            std::cout << "Имя: " << client.get_name() << ". Время входа в банк: " << client.get_time_of_entry()/60 << ":";
            if (client.get_time_of_entry()%60 < 10) std::cout << "0";
            std::cout << client.get_time_of_entry()%60 << ". Время выхода из банка: " << client.get_time_of_end()/60 << ":";
            if (client.get_time_of_end()%60 < 10) std::cout << "0";
            std::cout << client.get_time_of_end()%60 << std::endl;
        }
    }

    void display_data_in_file(){
        std::ofstream file("ticket.txt");
        if (file.is_open()){
            for (Client client : Queue){
                file << "Клиент №" << client.get_number() << ": " << std::endl;
                file << "Имя: " << client.get_name() << ". Время входа в банк: " << client.get_time_of_entry()/60 << ":";
                if (client.get_time_of_entry()%60 < 10) file << "0";
                file << client.get_time_of_entry()%60 << ". Время выхода из банка: " << client.get_time_of_end()/60 << ":";
                if (client.get_time_of_end()%60 < 10) file << "0";
                file << client.get_time_of_end()%60 << std::endl;
            }
        }
        else {
            std::cout << "Не удалось создать файл!" << std::endl;
        }
    }

    void work(){
        for (Client & client : Queue){
            bool serviced = false;
            for (int &el : cash){
                if (client.get_time_of_entry() >= el){
                    el = client.get_time_of_end();
                    serviced = true;
                    break;
                }
            }
            if (!serviced && client.get_choice() == "К"){
                int min_el = 100000;
                for (int el : cash) min_el = std::min(min_el, el);
                for (int &el : cash){
                    if (el == min_el){
                        el = el + client.get_time_of_service(); 
                        client.set_time_of_end(el);
                        break; 
                    } 
                }
                serviced = true;
            }
            if (!serviced && client.get_choice() == "Б"){
                for (int & el : ATM){
                    if (client.get_time_of_entry() >= el){
                        el = client.get_time_of_end();
                        serviced = true;
                        break;
                    }
                }
            }
            if (!serviced && client.get_choice() == "Б"){
                int min_el = 100000;
                for (int el : ATM) min_el = std::min(min_el, el);
                for (int & el : ATM){
                    if (el == min_el){
                        el += client.get_time_of_service(); 
                        client.set_time_of_end(el);
                        break; 
                    } 
                }
                serviced = true;
            }
        }
    }

};

