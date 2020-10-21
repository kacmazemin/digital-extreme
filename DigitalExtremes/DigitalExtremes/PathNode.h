#ifndef PATH_NODE_H
#define PATH_NODE_H

#include "Vertex.h"

#include <vector>
#include <algorithm>

class PathNode;
typedef std::vector<PathNode*> PathNodes;

class PowerUp;
typedef std::vector<PowerUp*> PowerUps;

class PathNode
{
public:
    PathNode(const char* name, const Vertex& position) :
        mPosition(position)
    {
        mName = new char[strlen(name) + 1];
        strcpy_s(mName, strlen(name) + 1, name);
    }

    ~PathNode()
    {
        delete[] mName;
    }

    void AddLink(PathNode* pathNode)
    {
        mLinks.push_back(pathNode);
    }

    void RemoveLink(PathNode* pathNode)
    {
        PathNodes::iterator i = std::find(mLinks.begin(), mLinks.end(), pathNode);
        mLinks.erase(i);
    }

    void AddPowerUp(PowerUp* powerUp)
    {
        mPowerUps.push_back(powerUp);
    }

    void RemovePowerUp(PowerUp* powerUp)
    {
        PowerUps::iterator i = std::find(mPowerUps.begin(), mPowerUps.end(), powerUp);
        mPowerUps.erase(i);
    }

    const char* GetName() const
    {
        return(mName);
    }

    const PathNodes& GetLinks() const
    {
        return(mLinks);
    }

    const PowerUps& GetPowerUps() const
    {
        return(mPowerUps);
    }

    const Vertex& GetVertex() const 
    {
        return mPosition;
    }

protected:

    Vertex mPosition;
    char* mName = nullptr;

    PathNodes   mLinks;
    PowerUps    mPowerUps;
};

#endif // PATH_NODE_H
