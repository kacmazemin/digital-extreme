#include <stdio.h>
#include <iostream>

#include "PathNode.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "Health.h"
#include "Armor.h"
#include <math.h>
#include <queue>
#include <unordered_map>
#include <unordered_set>

static PathNodes sPathNodes;
static PowerUps sPowerUps;

auto comparePQ = [&](std::pair<PathNode*, int>& firstNode, std::pair<PathNode*, int>& secondNode)
{
    return firstNode.second > secondNode.second;
};

float distanceBetweenTwoNode(const PathNode& nodeA, const PathNode& nodeB)
{
    const float distX = std::pow((nodeA.GetVertex().x - nodeB.GetVertex().x), 2);
    const float distY = std::pow((nodeA.GetVertex().y - nodeB.GetVertex().y), 2);
    //const float distZ = std::pow((nodeA.GetVertex().z - nodeB.GetVertex().z), 2); Since all nodes on same z coordinate, no need to calculate.

    return sqrt(distX + distY  /*+ distZ */);
}

bool FindPowerUp(PathNodes& path, PowerUpType mType, PathNode* start)
{
    std::priority_queue < std::pair<PathNode*, int>, std::vector<std::pair<PathNode*, int>>, decltype(comparePQ) > frontier(comparePQ);

    std::unordered_map<PathNode*, int> costSoFar;
    std::unordered_map<PathNode*, PathNode*> cameFrom;
    std::unordered_set<PathNode*> visitiedPaths;

    cameFrom[start] = start;
    costSoFar[start] = 0;

    frontier.push(std::make_pair( start, 0 ));

    while (!frontier.empty()) {

        PathNode* currentNode = frontier.top().first;

        frontier.pop();

        if (visitiedPaths.find(currentNode) != visitiedPaths.end())
        {
            continue;
        }

        if (currentNode->HasPowerType(mType))
        {
            auto parentNode = currentNode;

            while (parentNode != start )
            {
                path.push_back(parentNode);
                parentNode = cameFrom[parentNode];
            }
            path.push_back(start);

            std::reverse(path.begin(), path.end());
            return true;
        }


        for (const auto& neighbor : currentNode->GetLinks())
        {
            auto new_cost = costSoFar[currentNode] + distanceBetweenTwoNode(*currentNode, *neighbor);
            
            if (costSoFar.find(neighbor) == costSoFar.end() || new_cost < costSoFar[neighbor]) 
            {
                costSoFar[neighbor] = new_cost;
                cameFrom[neighbor] = currentNode;
                frontier.push(std::make_pair(neighbor, new_cost));
            }
        }

        visitiedPaths.insert(currentNode);
    }

    return(false); // No path found.
}

// For this example, all links are symmetric.
inline void LinkNodes(PathNode* n1, PathNode* n2)
{
    n1->AddLink(n2);
    n2->AddLink(n1);
}

int main(int, char* [])
{
    sPathNodes.push_back(new PathNode("Node0", Vertex(300, 60, 0)));
    sPathNodes.push_back(new PathNode("Node1", Vertex(100, 60, 0)));
    sPathNodes.push_back(new PathNode("Node2", Vertex(80, 560, 0)));
    sPathNodes.push_back(new PathNode("Node3", Vertex(280, 650, 0)));
    sPathNodes.push_back(new PathNode("Node4", Vertex(300, 250, 0)));
    sPathNodes.push_back(new PathNode("Node5", Vertex(450, 400, 0)));
    sPathNodes.push_back(new PathNode("Node6", Vertex(450, 60, 0)));
    sPathNodes.push_back(new PathNode("Node7", Vertex(450, 400, 0)));

    LinkNodes(sPathNodes[1], sPathNodes[4]);
    LinkNodes(sPathNodes[0], sPathNodes[1]);
    LinkNodes(sPathNodes[0], sPathNodes[6]);
    LinkNodes(sPathNodes[0], sPathNodes[4]);
    LinkNodes(sPathNodes[7], sPathNodes[4]);
    LinkNodes(sPathNodes[7], sPathNodes[5]);
    LinkNodes(sPathNodes[2], sPathNodes[4]);
    LinkNodes(sPathNodes[2], sPathNodes[3]);
    LinkNodes(sPathNodes[3], sPathNodes[5]);

    sPowerUps.push_back(new Weapon("Weapon0", Vertex(340, 670, 0)));
    sPathNodes[3]->AddPowerUp(sPowerUps[0]);
    sPowerUps.push_back(new Weapon("Weapon1", Vertex(500, 220, 0)));
    sPathNodes[7]->AddPowerUp(sPowerUps[1]);

    sPowerUps.push_back(new Health("Health0", Vertex(490, 10, 0)));
    sPathNodes[6]->AddPowerUp(sPowerUps[2]);
    sPowerUps.push_back(new Health("Health1", Vertex(120, 20, 0)));
    sPathNodes[1]->AddPowerUp(sPowerUps[3]);

    sPowerUps.push_back(new Armor("Armour0", Vertex(500, 360, 0)));
    sPathNodes[5]->AddPowerUp(sPowerUps[4]);
    sPowerUps.push_back(new Armor("Armour1", Vertex(180, 525, 0)));
    sPathNodes[2]->AddPowerUp(sPowerUps[5]);

    PathNodes path;

    if (!FindPowerUp(path, PowerUpType::WEAPON, sPathNodes[4]))
    {
       
        printf("No path found: IMPOSSIBLE!\n");
    }
    else
    {
        printf("Path found: ");

        for (PathNodes::iterator i = path.begin(); i != path.end(); ++i)
        {
            PathNode* n = *i;
            printf("%s ", n->GetName());
        }

        printf("\n");
    }


    return(0);
}
