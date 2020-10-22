#include <stdio.h>
#include <iostream>

#include "PathNode.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "Health.h"
#include "Armor.h"
#include "UnitTest.h"
#include <math.h>
#include <queue>
#include <unordered_map>
#include <unordered_set>

static PathNodes sPathNodes;
static PowerUps sPowerUps;

//compare function for priority queue to get the lowest value

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


/**
Since movement costs vary, I chose Dijkstra. Dijkstra algorithm lets us prioritize which paths to explore.
Instead of exploring all possible paths equally,
it favors lower cost paths. We can assign lower
costs to encourage moving on roads
*/
bool FindPowerUp(PathNodes& path, PowerUpType mType, PathNode* start)
{
    //The PriorityQueue is created to get the node with the lowest value first.
    std::priority_queue < std::pair<PathNode*, int>, std::vector<std::pair<PathNode*, int>>, decltype(comparePQ) > frontier(comparePQ);

    //to keep distance costs
    std::unordered_map<PathNode*, int> costSoFar;

    //to keep the where we came from
    std::unordered_map<PathNode*, PathNode*> cameFrom;

    //for visited indices
    std::unordered_set<PathNode*> visitiedPaths;

    cameFrom[start] = start;
    costSoFar[start] = 0;

    frontier.push(std::make_pair( start, 0 ));

    while (!frontier.empty()) {

        PathNode* currentNode = frontier.top().first;

        frontier.pop();

        //if node is already visited skip it.
        if (visitiedPaths.find(currentNode) != visitiedPaths.end())
        {
            continue;
        }

        //found
        if (currentNode->HasPowerType(mType))
        {
            auto parentNode = currentNode;

            while (parentNode != start )
            {
                path.push_back(parentNode);
                parentNode = cameFrom[parentNode];
            }
            path.push_back(start);

            //since it is backwards path I call reverse
            std::reverse(path.begin(), path.end());

            return true;
        }

        for (const auto& neighbor : currentNode->GetLinks())
        {
            auto newCost = costSoFar[currentNode] + distanceBetweenTwoNode(*currentNode, *neighbor);
            
            if (costSoFar.find(neighbor) == costSoFar.end() || newCost < costSoFar[neighbor]) 
            {
                costSoFar[neighbor] = newCost;
                cameFrom[neighbor] = currentNode;
                frontier.push(std::make_pair(neighbor, newCost));
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

    UnitTest* test = new UnitTest();

    test->executeTest(path, 1);

    PathNodes path2;
    FindPowerUp(path2, PowerUpType::WEAPON, sPathNodes[6]);
    test->executeTest(path2, 2);

    PathNodes path3;
    FindPowerUp(path3, PowerUpType::ARMOUR, sPathNodes[0]);
    test->executeTest(path3, 3);

    PathNodes path4;
    FindPowerUp(path4, PowerUpType::HEALTH, sPathNodes[3]);
    test->executeTest(path4, 4);

    PathNodes path5;
    test->executeTest(path5, 5);

    delete test;

    return(0);
}
