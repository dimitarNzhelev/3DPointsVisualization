#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

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

    friend ostream &operator<<(ostream &out, Point3D &p)
    {
        out << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return out;
    }

    friend istream &operator>>(istream &in, Point3D &p)
    {
        // input type: (x, y, z)
        string line;
        getline(in, line);
        stringstream ss(line);
        string x, y, z;
        getline(ss, x, ',');
        getline(ss, y, ',');
        getline(ss, z, ',');
        x.erase(0, 1);
        z = z.substr(0, z.size() - 1);
        stringstream xs(x), ys(y), zs(z);
        xs >> p.x;
        ys >> p.y;
        zs >> p.z;
        return in;
    };
};

class File
{
    fstream fs;

public:
    File(const string &filePath, int flags)
    {
        // Check if the file exists
        this->fs.open(filePath, ios::in);
        if (!this->fs)
        {
            throw std::runtime_error("File " + filePath + " does not exist! :(");
        }
        this->fs.close();

        this->fs.open(filePath, static_cast<ios_base::openmode>(flags)); // compilatora mi ne struva
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

class FileManager
{
public:
    static Point3D readPoint3D(File &file, int position)
    {
        Point3D point;
        file.getFileStream().seekg(position);
        file.getFileStream() >> point;
        return point;
    }
};

int main()
{
    File file("tmp.txt", ios::in | ios::out | ios::app);
    vector<Point3D> points;

    while (!file.getFileStream().eof())
    {
        Point3D point = FileManager::readPoint3D(file, file.getFileStream().tellg());
        cout << point << endl;
        points.push_back(point);
    }

    // it is working :)

    return 0;
}