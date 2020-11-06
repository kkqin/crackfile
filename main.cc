#include <iostream>
#include <fstream>
#include <memory>
#include <random>

char* random_block(size_t size) {
	char* buf = new char[size];
	char* head = buf;
	std::random_device rd;
	std::mt19937 mt(rd());
	srand(time(0));
	while(size--) {
		*buf = (char)mt(); 
		buf++;
	}

	return head;
}

int main(int argc, char** argv) {
	std::string filename = argv[1];
	std::shared_ptr<std::ofstream> myfile = std::shared_ptr<std::ofstream>(new std::ofstream());
	if(argc < 2) {
		std::cout << "filename empty" << std::endl;
		return -1;
	}
	myfile->open(filename, std::ifstream::in | std::ofstream::out | std::ifstream::binary);

	myfile->seekp(0, std::ios_base::end);
	auto filesize = myfile->tellp();
	//auto filesize = 197397;//myfile->tellp();
	std::cout << "filesize:" << filesize << std::endl;

	auto sector = 512;
	auto count = 4;
	auto random_area = (sector * count);
	auto entry_point = filesize / random_area;
	auto less = filesize % random_area;
	std::cout << entry_point << std::endl;
	
	for(auto i = 0; i < entry_point; i++) {
		auto pos = i * random_area;
		//std::cout << pos << std::endl;
		myfile->seekp(pos);
		char* block = random_block(random_area); 
		myfile->write(block, random_area);
		free(block);
	}

	return 0;
}
