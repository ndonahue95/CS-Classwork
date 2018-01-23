#include "Airport_Manager.h"


// CODING THIS IN A T-BELL YEEEEEEAAAAAHHHHH


/* - = - = - = - = - = - = - = - = - = - = - = -
 
typedef struct Airport{
	char * name; The airport name
	int numDestinations; The number of destinations the airport offers flights to
	struct Airport ** destinations; The array of destinations the airport offers flights to
}Airport;

 - = - = - = - = - = - = - = - = - = - = - = - */


//Airport ** airports; /*The array of all airports managed  by the company*/
//int numAirports; /*The current number of airports managed by the company*/
//int maxAirports; /*The max number of airports the airports array can store*/


// init global variables
void createAirportArray() {
    airports = (Airport**)malloc(20 * sizeof(Airport*));
    maxAirports = 20;
    numAirports = 0;
}

// add airport to globs
int addAirport(Airport * airport) {
    
    // null check
    if (airport == NULL)
        return -1;
    
    // check if already exists
    int i;
    for (i = 0; i < maxAirports; i++) {
        if (airports[i] == airport)
            return 0;
    }
    
    // increase airports count
    numAirports++;
    
    
    // put in WERKKK
    if (numAirports == maxAirports) {
        maxAirports = maxAirports * 2;
        
        Airport ** newPorts = (Airport**)malloc(maxAirports * sizeof(Airport*));
        
        int j;
        for (j = 0; j < numAirports-1; j++) {
            newPorts[j] = airports[j];
        }
        
        free(airports);

        airports = newPorts;
    }
    
    // add it dood
    airports[numAirports-1] = airport;
    
    // 0 for already exists
    // 1 for added
    // -1 for invalid
    return 1;
}

// create dat airport, yo
Airport * createAirport(const char * name) {
    
    // null check
    if (name == NULL)
        return NULL;
    
    Airport * portToReturn = malloc(sizeof(Airport));
    char * nameDupe = strdup(name);
    
    portToReturn->name = nameDupe;
    portToReturn->numDestinations = 0;
    portToReturn->destinations = NULL;
    
    
    return portToReturn;
}

int addDestination(Airport * airport, Airport * dest) {
    
    // null check
    if (airport == NULL || dest == NULL)
        return -1;
    
    // check if first time
    int firstTime = 0;
    if (airport->destinations == NULL) {
        airport->destinations = (Airport**)malloc(sizeof(Airport*));
        firstTime = 1;
    }
    
    // check if already added
    if (firstTime == 0) {
        int i;
        for (i = 0; i < airport->numDestinations; i++) {
            if (airport->destinations[i] == dest)
                return 0;
        }
    }
    
    // adddddddd it!
    if (firstTime == 1) {
        airport->destinations[0] = dest;
    } else if (firstTime == 0) {
        Airport ** toDest = (Airport**)malloc(airport->numDestinations+1 * sizeof(Airport*));
        
        int i;
        for (i = 0; i < airport->numDestinations; i++) {
            toDest[i] = airport->destinations[i];
        }
        
        free(airport->destinations);
        
        airport->destinations = toDest;
        
        airport->destinations[airport->numDestinations] = dest;
    }
    
    // increaes numDest
    airport->numDestinations++;
    
    // 0 for already exists
    // 1 for added
    // -1 for invalid
    return 1;
}

void printAirports() {
    printf("NumberOfAirports: %d\n", numAirports);
    
    int i;
    for (i = 0; i < numAirports; i++) {
        Airport * workingPort = airports[i];
        printf("%s\n", workingPort->name);
    }
    
    printf("\n");
}

int hasOneStopFlight(Airport * start, Airport * dest) {
    
    // null check
    if (start == NULL || dest == NULL)
        return -1;
    
    int i;
    for (i = 0; i < start->numDestinations; i++) {
        if (start->destinations[i] == dest)
            return 1;
    }
    
    return 0;
}

int hasTwoStopFlight(Airport * start, Airport * dest) {
    
    // null check
    if (start == NULL || dest == NULL)
        return -1;
    
    // check onestop first
    if (hasOneStopFlight(start, dest))
        return 2;
    
    int i;
    for (i = 0; i < start->numDestinations; i++) {
        if (hasOneStopFlight(start->destinations[i], dest) == 1)
            return 1;
    }
    
    return 0;
}

void freeAllAirports() {
    int i;
    for (i = 0; i < numAirports; i++) {
        free(airports[i]->name);
        free(airports[i]->destinations);
        free(airports[i]);
    }
}

int main() {
    
    createAirportArray();
    
    Airport * LAX = createAirport("LAX");
    addAirport(LAX);
    
    Airport * MID = createAirport("MID");
    addAirport(MID);
    
    Airport * EWR = createAirport("EWR");
    addAirport(EWR);
    
    Airport * DANK = createAirport("DANK");
    addAirport(DANK);
    
    int a;
    for (a = 0; a < 25; a++) {
        Airport * toAdd = createAirport("TEST");
        addAirport(toAdd);
    }
    
    printAirports();
    
    addDestination(LAX, MID);
    addDestination(MID, EWR);
    
    // COMMENT OUT FOR TWO FLIGHT TEST
    //addDestination(LAX, EWR);
    
    addDestination(LAX, DANK);
    
    printf("%d\n", hasTwoStopFlight(LAX, EWR));
    
    freeAllAirports();
    
    return 0;
}
