#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object
{
private:
    static int totalCreated;
    static int totalActive;

    std::string* operations;
    int opCount;
    int opCapacity;

protected:
    void addOp(const std::string& op);
    void addOp(const std::string& op) const;   // для const-методов Vector3d
    void clearOp();
    void printOp() const;

public:
    Object();
    Object(const Object& other);
    Object& operator=(const Object& other);
    virtual ~Object();

    static void printTotalInfo();
    static int getTotalCreated() { return totalCreated; }
    static int getTotalActive()  { return totalActive; }
};

#endif
