#include <fstream>
#include <string>

namespace crud {
    struct Student {
        int pk;
        std::string NIM;
        std::string name;
        std::string jurusan;
    };

    int getOption();
    void checkDatabase(std::fstream &data);
    void writeData(std::fstream &data, int position, Student &inputDataStudent);
    int getDataSize(std::fstream &data);
    Student readData(std::fstream &data, int position);
    void displayDataStudent(std::fstream &data);
    void addStudentData(std::fstream &data);
    void updateRecord(std::fstream &data);
    void deleteRecord(std::fstream &data);
}
