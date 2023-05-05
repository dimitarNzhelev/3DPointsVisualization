#include <iostream>
#include <fstream>

using namespace std;
// writing - fstreamFileName >> "You are writing in a file";
class Point3D
{
    double x, y, z;

public:
    void setX(double x)
    {
        this->x = x;
    }
    void setY(double y)
    {
        this->y = y;
    }
    void setZ(double z)
    {
        this->z = z;
    }
    double getX()
    {
        return this->x;
    }
    double getY() const
    {
        return this->y;
    }
    double getZ() const
    {
        return this->z;
    }

    // friend istream &operator>>
};

class File
{
    fstream fs;

public:
    File(const string &filePath, int flags)
    {
        this->fs.open(filePath, ios_base::in);
        if (!this->fs.is_open())
        {
            throw std::runtime_error("File " + filePath + "could not be opened!");
        }
    }

    ~File()
    {
        this->fs.close();
    }

    fstream &getFileStream()
    {
        return this->fs;
    }
};