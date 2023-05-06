#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Point3D
{
    double x, y, z;

public:
    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

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
        Point3D point = Point3D(0, 0, 0);
        file.getFileStream().seekg(position);
        file.getFileStream() >> point;
        return point;
    }
};

void CalculateTriangle(vector<Point3D> &points)
{

    for (int i = 0; i < points.size(); i += 3)
    {
        // Point3D point1, point2, point3, point12, point13;
        // point12 and point13 are vectors of points
        // point12 -> vector of point 1 and point 2
        // point13 -> vector of point 1 and point 3
        Point3D point1 = points[i];
        Point3D point2 = points[i + 1];
        Point3D point3 = points[i + 2];
        // point12 = (x2-x1, y2-y1, z2-z1)
        Point3D point12 = Point3D(point2.getX() - point1.getX(), point2.getY() - point1.getY(), point2.getZ() - point1.getZ());
        // cout << point12 << endl;

        //// point13 = (x3-x1, y3-y1, z3-z1)
        Point3D point13 = Point3D(point3.getX() - point1.getX(), point3.getY() - point1.getY(), point3.getZ() - point1.getZ());
        // cout << point13 << endl;

        // point12 * point13 (scalar equation)

        // X:
        // |point12y point12z|
        // |point13y point13z|
        int newPointX = (point12.getY() * point13.getZ()) - (point12.getZ() * point13.getY());
        cout << "X: " << newPointX << endl;

        // Y:
        // |point12z point12x|
        // |point13z point13x|
        int newPointY = (point12.getZ() * point13.getX()) - (point12.getX() * point13.getZ());
        cout << "Y: " << newPointY << endl;

        // Y:
        // |point12x point12y|
        // |point13x point13y|
        int newPointZ = (point12.getX() * point13.getY()) - (point12.getY() * point13.getX());
        cout << "Z: " << newPointZ << endl;

        // check if it is equal to the null vector
        if (newPointX != 0 || newPointY != 0 || newPointZ != 0)
        {
            cout << "These points can form a triangle :)" << endl;
        }
        else
        {
            cout << "These points cannot form a triangle :(" << endl;
        }
    }
}

int main()
{
    File file("tmp.txt", ios::in | ios::out | ios::app);
    vector<Point3D> points;

    while (!file.getFileStream().eof())
    {
        Point3D point = FileManager::readPoint3D(file, file.getFileStream().tellg());
        // cout << point << endl;
        points.push_back(point);
    }
    cout << points.size() << endl;
    CalculateTriangle(points);

    return 0;
}