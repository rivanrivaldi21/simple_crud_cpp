#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "crud.h"

void crud::writeData(std::fstream &data, int position, crud::Student &inputData){
    data.seekp((position - 1)*sizeof(crud::Student), std::ios::beg);
    data.write(reinterpret_cast<char*>(&inputData), sizeof(crud::Student));
}

crud::Student crud::readData(std::fstream &data, int position){
    crud::Student readStudent;
    data.seekg((position - 1)*sizeof(Student), std::ios::beg);
    data.read(reinterpret_cast<char*>(&readStudent),sizeof(crud::Student));
    return readStudent;
}

void crud::displayDataStudent(std::fstream &data){
    int size = crud::getDataSize(data);
    crud::Student showStudent;
    std::cout << "no.\tpk.\tNIM.\tNama.\tJurusan." << std::endl;
    for (int i=1; i <= size; i++){
        showStudent = crud::readData(data, i);
        std::cout << i << "\t";
		std::cout << showStudent.pk << "\t";
		std::cout << showStudent.NIM << "\t";
		std::cout << showStudent.name << "\t";
		std::cout << showStudent.jurusan << std::endl;
    }
}

void crud::updateRecord(std::fstream &data){
    int num;
    crud::Student updatedStudent;
    std::cout << "Choose the number : ";
    std::cin >> num;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    updatedStudent = crud::readData(data, num);
    std::cout << "\n\npilihan data: " << std::endl;
	std::cout << "NIM : " << updatedStudent.NIM << std::endl;
	std::cout << "nama : " << updatedStudent.name << std::endl;
	std::cout << "jurusan : " << updatedStudent.jurusan << std::endl;

	std::cout << "\nMerubah data: "<< std::endl;
	std::cout << "NIM:";
	std::getline(std::cin,updatedStudent.NIM);
	std::cout << "nama:";
	std::getline(std::cin,updatedStudent.name);
	std::cout << "jurusan:";
	std::getline(std::cin,updatedStudent.jurusan);

	crud::writeData(data,num,updatedStudent);
}

void crud::deleteRecord(std::fstream &data){
    int num,size,offset;
    crud::Student blankStudent, tempStudent;
    std::fstream dataSementara;

    size = crud::getDataSize(data);
    std::cout << "Choose number to be deleted : ";
    std::cin >> num;

    crud::writeData(data,num,blankStudent);
    dataSementara.open("temp.dat", std::ios::trunc|std::ios::in|std::ios::out|std::ios::binary);

    offset = 0;

    for (int i=1; i <= size; i++){
        tempStudent = crud::readData(data, i);
        if (!tempStudent.name.empty()){
            crud::writeData(dataSementara, i - offset, tempStudent);
        } else {
            offset++;
            std::cout << "Deleted Item" << std::endl;
        }
    }

    size = crud::getDataSize(dataSementara);
    data.close();
    data.open("data.bin", std::ios::trunc|std::ios::out|std::ios::binary);
    data.close();
    data.open("data.bin", std::ios::out|std::ios::in|std::ios::binary);

    for (int i = 1; i <= size; i++){
        tempStudent = crud::readData(dataSementara,i);
        crud::writeData(data,i,tempStudent);
    }

}

int crud::getDataSize(std::fstream &data){
    int start, end;
    data.seekg(0, std::ios::beg);
    start = data.tellg();
    data.seekg(0, std::ios::end);
    end = data.tellg();

    return (end-start)/sizeof(crud::Student);
}

void crud::checkDatabase(std::fstream &data){
    data.open("data.bin", std::ios::out | std::ios::in | std::ios::binary);

    // Check wheter file is exist or not
    if (data.is_open()){
        std::cout << "Database file is found" << std::endl;
    } else {
        std::cout << "Database is not found, system create a new DB" << std::endl;
        data.open("data.bin", std::ios::trunc | std::ios::out | std::ios::in | std::ios::binary);
    }
}

int crud::getOption(){
	int input;
	std::system("cls");
	// system("cls");
	std::cout << "\nPROJECT CRUD MULTIFILE" << std::endl;
	std::cout << "Program CRUD data mahasiswa" << std::endl;
	std::cout << "=============================" << std::endl;
	std::cout << "1. Tambah data mahasiswa" << std::endl;
	std::cout << "2. Tampilkan data mahasiswa" << std::endl;
	std::cout << "3. Ubah data mahasiswa" << std::endl;
	std::cout << "4. Hapus data mahasiswa" << std::endl;
	std::cout << "5. Selesai" << std::endl;
	std::cout << "=============================" << std::endl;
	std::cout << "pilih [1-5]? : ";
	std::cin >> input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	return input;
}

void crud::addStudentData(std::fstream &data){
    crud::Student inputData, LastStudent;
    int sizeDB = crud::getDataSize(data);

    std::cout << "Data Size :" << sizeDB <<std::endl;
    if (sizeDB == 0) {
        inputData.pk = 1;
    } else {
        LastStudent = crud::readData(data, sizeDB);
        std::cout << "PK = " << LastStudent.pk << std::endl;
        inputData.pk = LastStudent.pk + 1;
    }
    std::cout << "Name: ";
    std::getline(std::cin, inputData.name);
    std::cout << "Jurusan :";
    std::getline(std::cin, inputData.jurusan);
    std::cout << "NIM :";
    std::getline(std::cin, inputData.NIM);

    crud::writeData(data,sizeDB + 1,inputData);
}
