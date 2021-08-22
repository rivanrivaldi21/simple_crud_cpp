#include <iostream>
#include <fstream>
#include <string>
#include "crud.h"

int main(){
    std::fstream data;

    crud::checkDatabase(data);
    int option = crud::getOption();
    char is_continue;

    enum option{CREATE = 1, READ, UPDATE, DELETE, FINISH};
    while(option != FINISH){
        switch (option) {
            case CREATE:
                std::cout<< "Adding ad new student" << std::endl;
                crud::addStudentData(data);
                break;
            case READ:
                std::cout << "Showing the current data of student" << std::endl;
                crud::displayDataStudent(data);
                break;
            case UPDATE:
                std::cout << "Update data of the student" << std::endl;
                crud::displayDataStudent(data);
                crud::updateRecord(data);
                crud::displayDataStudent(data);
                break;
            case DELETE:
                std::cout << "Delete the data of student" << std::endl;
                crud::displayDataStudent(data);
                crud::deleteRecord(data);
                crud::displayDataStudent(data);
                break;
            default:
                std::cout << "Sorry, your option is not available" << std::endl;
                break;
        }

        label_continue:

        std::cout << "Do you want continue (y/n) : ";
        std::cin >> is_continue;
        if ((is_continue == 'y') | (is_continue == 'Y')){
            option = crud::getOption();
        } else if ((is_continue == 'n') | (is_continue == 'N')) {
                break;
        } else {
            goto label_continue;
        }
    }

    std::cout << "End of Program" << std::endl;

    std::cin.get();
    return 0;
}
