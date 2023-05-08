#include <iostream>
#include <fstream>
#include <vector>


class BasicFile
{
    std::string filePath;

public:

    BasicFile(std::string filePath):filePath(filePath){}

    void setFilePath(std::string filePath)
    {
        this->filePath = filePath;
    }

    std::string getFilePath()
    {
        return this->filePath;
    }

    template<class Type>
    void write(Type token, bool append = true)
    {
        std::ofstream file;

        if(append)
        {
            file.open(filePath, std::ios_base::app);
        }
        else
        {
            file.open(filePath);
        }

        file << token << std::endl;
        file.close();
    }

    std::vector<std::string> read()
    {
        std::ifstream file(filePath);
        std::vector<std::string> result;
        std::string line;

        while(getline(file, line))
        {
            result.push_back(line);
        }

        file.close();
        return result;
    }
};


int32_t main()
{

    BasicFile file("file.txt");
    file.write<int>(5, false);
    file.write<std::string>("next item");
    file.write<float>(5.212);
    file.write<int>(212);

    std::vector<std::string> lines = file.read();
    for(std::string line:lines)
    {
        std::cout<<line<<std::endl;
    }

    return 0;
}
