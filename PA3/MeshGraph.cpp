#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    // TODO:
    for(int i=0; i< vertexPositions.size() ; i++){
        Vertex element;
        element.id = i;
        element.position3D = vertexPositions[i];
        vertices.push_back(element);
    }
    adjList.resize(vertices.size());
    /*for(int i=0; i< vertices.size(); i++){
        adjList[i].clear();
        adjList[i].push_front(&vertices[i]);
    }*/
    for(int i=0; i < edges.size(); i++){
        adjList[edges[i].vertexId0].push_front(&vertices[edges[i].vertexId1]);
        adjList[edges[i].vertexId1].push_front(&vertices[edges[i].vertexId0]);
    }
    for(int i=0; i<adjList.size(); i++){
        adjList[i].sort();
    }
    
    
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    double total_distance = 0;
    double n = 0;
    for(int i=0; i<adjList.size(); i++){
        for(std::list<Vertex*>::const_iterator it = adjList[i].begin(); it != adjList[i].end(); it++){
            total_distance += Double3::Distance(vertices[i].position3D, (*it)->position3D);
            n++;
        }
    }
    return total_distance/n;
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    double total = 0;
    for(int i=0; i<adjList.size(); i++){
        total += adjList[i].size();
        
    }
    
    return total /(2* adjList.size()); 
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    double total = 0;
    for(int i=0; i<adjList.size(); i++){
        total += adjList[i].size();
        
    }
    return total/2;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
    if(vertexId >= adjList.size()) return -1;
    return adjList[vertexId].size();
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    // TODO:
    outVertexIds.resize(0);
    if(vertexId >= adjList.size()) return;
    

    for(std::list<Vertex*>::const_iterator it = adjList[vertexId].begin(); it != adjList[vertexId].end(); it++){
        outVertexIds.push_back((*it)->id);
    }
    
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    // TODO:
    outputColorAllVertex.resize(0);
    if(vertexIdFrom >= adjList.size() || vertexIdTo >= adjList.size() || vertexIdFrom < 0 || vertexIdTo < 0) return;
    
    
    BinaryHeap pq;
    std::vector<double> dist(vertices.size(), INFINITY);
    std::vector<int> from(vertices.size(), -1);
  
    pq.Add(vertexIdFrom, 0);
    dist[vertexIdFrom] = 0;
    from[vertexIdFrom] = vertexIdFrom;
  
    while (pq.HeapSize() != 0) {
        
        int uniqueId ;
        double weight;
        pq.PopHeap(uniqueId, weight);
        for(std::list<Vertex*>::const_iterator it = adjList[uniqueId].begin(); it != adjList[uniqueId].end(); it++){
            double distance = Double3::Distance((*it)->position3D, vertices[uniqueId].position3D) + dist[uniqueId];
            if(dist[(*it)->id] > distance){
                
                if(dist[(*it)->id] == INFINITY){
                    pq.Add((*it)->id, distance);
                }
                else{
                    if(!pq.ChangePriority((*it)->id, distance)) pq.Add((*it)->id, distance);
                }
                dist[(*it)->id] = distance;
                from[(*it)->id] = uniqueId;
            }
        }
    }
    outputColorAllVertex.resize(vertices.size());
    for(int i=0; i<outputColorAllVertex.size(); i++){
        Color black; black.r=0; black.g=0; black.b=0;
        outputColorAllVertex[i] = black;
    }
    for(int i=vertexIdTo; from[i] != i; i=from[i]){
        outputColorAllVertex[i] = color;
    }
    /*int i = vertexIdTo;
    while(from[i] != vertexIdFrom){
        outputColorAllVertex[i] = color;
        i = from[i];
    }*/
    outputColorAllVertex[vertexIdFrom] = color;
    
    
}

double MeshGraph::calculate(FilterType type, double a, double x) const{
    if(type == FILTER_GAUSSIAN){
        return std::exp(-(x*x)/(a*a));
    }
    else{
        if(x < a && x > -a) return 1;
        else return 0;
    }
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    // TODO:
    outputColorAllVertex.resize(0);

    if(vertexId >= adjList.size() ||  vertexId < 0 ) return;
    Color black; black.r=0; black.g=0; black.b=0;
    outputColorAllVertex.assign(vertices.size(), black);
    
    BinaryHeap pq1, pq2;
    std::vector<double> dist(vertices.size() ,0);
    std::vector<bool> visited(vertices.size(), false);
    pq1.Add(vertexId, 0);
    dist[vertexId] = 0;
    double n=1;
    if(maxDepth == 0){
        Double3 dummy;
        dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
        double constant = calculate(type, alpha, 0);
        outputColorAllVertex[vertexId].r = dummy.x * constant; outputColorAllVertex[vertexId].g = dummy.y * constant; outputColorAllVertex[vertexId].b = dummy.z * constant;
    }
    for(int i=0; i<maxDepth; i++){
        if(i%2 == 0){
            while(pq1.HeapSize() != 0){
                int id;
                double depth;
                pq1.PopHeap(id, depth);
                if(!visited[id]){
                    Double3 dummy;
                    dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
                    double constant = calculate(type, alpha, dist[id]);
                    outputColorAllVertex[id].r = dummy.x * constant; outputColorAllVertex[id].g = dummy.y * constant; outputColorAllVertex[id].b = dummy.z * constant;
                    visited[id] = true;
                }
                for(std::list<Vertex*>::const_iterator it = adjList[id].begin(); it != adjList[id].end(); it++){
                    if(!visited[(*it)->id]){
                        double distance = Double3::Distance((*it)->position3D, vertices[id].position3D) + dist[id];
                        dist[(*it)->id] = distance;
                        pq2.Add((*it)->id, n++);
                        Double3 dummy;
                        dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
                        double constant = calculate(type, alpha, distance);
                        outputColorAllVertex[(*it)->id].r = dummy.x * constant; outputColorAllVertex[(*it)->id].g = dummy.y * constant; outputColorAllVertex[(*it)->id].b = dummy.z * constant;
                        visited[(*it)->id] = true;
                    }
                }
            }
        }
        else{
            while(pq2.HeapSize() != 0){
                int id;
                double depth;
                pq2.PopHeap(id, depth);
                if(!visited[id]){
                    Double3 dummy;
                    dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
                    double constant = calculate(type, alpha, dist[id]);
                    outputColorAllVertex[id].r = dummy.x * constant; outputColorAllVertex[id].g = dummy.y * constant; outputColorAllVertex[id].b = dummy.z * constant;
                    visited[id] = true;
                }
                for(std::list<Vertex*>::const_iterator it = adjList[id].begin(); it != adjList[id].end(); it++){
                    if(!visited[(*it)->id]){
                        double distance = Double3::Distance((*it)->position3D, vertices[id].position3D) + dist[id];
                        dist[(*it)->id] = distance;
                        pq1.Add((*it)->id, n++);
                        Double3 dummy;
                        dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
                        double constant = calculate(type, alpha, distance);
                        outputColorAllVertex[(*it)->id].r = dummy.x * constant; outputColorAllVertex[(*it)->id].g = dummy.y * constant; outputColorAllVertex[(*it)->id].b = dummy.z * constant;
                        visited[(*it)->id] = true;
                    }
                }
            }
        }
    }

}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    // TODO:
    outputColorAllVertex.resize(0);
    
    if(vertexId >= adjList.size() ||  vertexId < 0 ) return;
    Color black; black.r=0; black.g=0; black.b=0;
    outputColorAllVertex.assign(vertices.size(), black);
    
    BinaryHeap pq1, pq2;
    std::vector<double> dist(vertices.size() ,0);
    std::vector<bool> visited(vertices.size(), false);
    pq1.Add(vertexId, 0);
    dist[vertexId] = 0;
    double n=1;
    if(maxDepth == 0){
        Double3 dummy;
        dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
        double constant = calculate(type, alpha, 0);
        outputColorAllVertex[vertexId].r = dummy.x * constant; outputColorAllVertex[vertexId].g = dummy.y * constant; outputColorAllVertex[vertexId].b = dummy.z * constant;
    }
    for(int i=0; i<maxDepth; i++){
        if(i%2 == 0){
            while(pq1.HeapSize() != 0){
                int id;
                double depth;
                pq1.PopHeap(id, depth);
                if(!visited[id]){
                    Double3 dummy;
                    dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
                    double constant = calculate(type, alpha, dist[id]);
                    outputColorAllVertex[id].r = dummy.x * constant; outputColorAllVertex[id].g = dummy.y * constant; outputColorAllVertex[id].b = dummy.z * constant;
                    visited[id] = true;
                }
                for(std::list<Vertex*>::const_iterator it = adjList[id].begin(); it != adjList[id].end(); it++){
                    if(!visited[(*it)->id]){
                        double distance = Double3::Distance((*it)->position3D, vertices[vertexId].position3D);
                        dist[(*it)->id] = distance;
                        pq2.Add((*it)->id, n++);
                        Double3 dummy;
                        dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
                        double constant = calculate(type, alpha, distance);
                        outputColorAllVertex[(*it)->id].r = dummy.x * constant; outputColorAllVertex[(*it)->id].g = dummy.y * constant; outputColorAllVertex[(*it)->id].b = dummy.z * constant;
                        visited[(*it)->id] = true;
                    }
                }
            }
        }
        else{
            while(pq2.HeapSize() != 0){
                int id;
                double depth;
                pq2.PopHeap(id, depth);
                if(!visited[id]){
                    Double3 dummy;
                    dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
                    double constant = calculate(type, alpha, dist[id]);
                    outputColorAllVertex[id].r = dummy.x * constant; outputColorAllVertex[id].g = dummy.y * constant; outputColorAllVertex[id].b = dummy.z * constant;
                    visited[id] = true;
                }
                for(std::list<Vertex*>::const_iterator it = adjList[id].begin(); it != adjList[id].end(); it++){
                    if(!visited[(*it)->id]){
                        double distance = Double3::Distance((*it)->position3D, vertices[vertexId].position3D);
                        dist[(*it)->id] = distance;
                        pq1.Add((*it)->id, n++);
                        Double3 dummy;
                        dummy.x = color.r; dummy.y = color.g; dummy.z = color.b;
                        double constant = calculate(type, alpha, distance);
                        outputColorAllVertex[(*it)->id].r = dummy.x * constant; outputColorAllVertex[(*it)->id].g = dummy.y * constant; outputColorAllVertex[(*it)->id].b = dummy.z * constant;
                        visited[(*it)->id] = true;
                    }
                }
            }
        }
    }
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}