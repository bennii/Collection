import igraph as igraph

def readEdgeList(filename):
    edgeList = []
    with open(filename, 'r', encoding='utf-8', errors='replace') as file:
        for line in file:
            entries = line.rstrip('\n').split(';')
            edgeList.append((entries[0], entries[1]))

    return edgeList

def getVertices(edgeList):
    vertexList = []

    for edge in edgeList:
        # Treu dem Motto: wenn es dumm ist und funtioniert ist es nicht dumm
        try:
            vertexList.index(edge[0])
        except ValueError:
            vertexList.append(edge[0])

        try:
            vertexList.index(edge[1])
        except:
            vertexList.append(edge[1])

    return vertexList

def getIncidenceMap(vertexList, edgeList):
    incidenceMap = []

    for vertex in vertexList:
        outgoingEdges = []
        incomingEdges = []
        incidenceEntry = (vertex,)

        for key, vert in enumerate(edgeList):
            # ausgehende Kante.
            if vert[0] == vertex:
                outgoingEdges.append(vert,)

            # eingehende Kante
            elif vert[1] == vertex:
                incomingEdges.append(vert,)

        incidenceEntry += (outgoingEdges, incomingEdges)
        incidenceMap.append(incidenceEntry)

    return incidenceMap

def determineMaxOutDegree(incidenceMap):
    vertex = None
    edgeCount = -1

    for incidence in incidenceMap:
        if len(incidence[1]) > edgeCount:
                vertex = incidence[0]
                edgeCount = len(incidence[1])

    return vertex

def determineMaxInDegree(incidenceMap):
    vertex = None
    edgeCount = -1

    for incidence in incidenceMap:
        if len(incidence[2]) > edgeCount:
                vertex = incidence[0]
                edgeCount = len(incidence[2])

    return vertex

if __name__ == '__main__':
    edges = readEdgeList('data.csv')
    vertices = getVertices(edges)
    incidences = getIncidenceMap(vertices, edges)
    famous = determineMaxInDegree(incidences)
    superLiker = determineMaxOutDegree(incidences)

    print("Anzahl an Knoten im Graphen: " + str(len(vertices)))
    print("Super-Liker ist: " + superLiker)
    print("Beliebtester ist: " + famous)

    graph = igraph.Graph()
    graph.add_vertices(vertices)

    for edge in edges:
        try:
            source = vertices.index(edge[0])
            target = vertices.index(edge[1])
        except ValueError:
            pass
        else:
            graph.add_edge(source, target)

    # Vielleicht kann man hier noch etwas an den Einstellungen ändern, so dass
    # das Bild etwas lesbarer wirdarer wird
    layout = graph.layout_drl()
    igraph.plot(graph, layout = layout)
