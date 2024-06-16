#include <iostream>
#include <vector>
#include <map>

class Vehicle;

class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode;

class TransportService {
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip);

private:
    std::string name;
    BinaryTreeNode* BSThead;
};

class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) const {

        return nullptr;
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(std::string droplocation) {
        return nullptr;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* node;

public:
    BinaryTree() : node(nullptr) {}

    int getHeight() const {

        // Implement this function to return the height of the tree
        return calculateHeight(node) ; // Placeholder
    }
    private:
    int calculateHeight(BinaryTreeNode* node) const {
        // Base case: If the node is null, the height is 0
        if (node == nullptr) {
            return 0;
        }

        // Recursively calculate the height of the left and right subtrees
        int leftHeight = calculateHeight(node->getLeftPtr());
        int rightHeight = calculateHeight(node->getRightPtr());

        // Return the maximum of the left and right subtree heights, plus 1 for the current node
        return std::max(leftHeight, rightHeight) + 1;
    }

    int getNumberOfNodes() const {
        // Implement this function to return the number of nodes in the tree
        return preorder(node); // Placeholder
    }
    private:
    int preorder (BinaryTreeNode* root) const{
        int count = 0;
        if (node == nullptr){
        return 0;
        };

        count ++;
        preorder(root -> getLeftPtr());
        preorder(root -> getRightPtr());
        return count;
    }
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey(BinaryTreeNode* node) const {
        if (node == nullptr){
            return nullptr;
        }        // Implement this function to return the element with the minimum key
        while (node -> getLeftPtr() != nullptr) {
            node = node -> getLeftPtr(); 
    }
           return node;
    }


    BinaryTreeNode* getElementWithMaximumKey(BinaryTreeNode* node) const {
        if (node == nullptr){
            return nullptr;
        }       
        while (node -> getRightPtr() != nullptr) {
            node = node -> getRightPtr(); 
    }
           return node;
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        
        // Implement this function to search for a node with the given key or the next larger key
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the successor node of the given node
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        // Implement this function to return the successor node by key
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the predecessor node of the given node
        return nullptr; // Placeholder
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        // Implement this function to return the predecessor node by key
        return nullptr; // Placeholder
    }
};

class TravelDesk {
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        // Implement this function to add a trip
    }

    std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range
        return {}; // Placeholder
    }
    std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        return {}; // Placeholder
    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        // Implement this function to book a trip
        return nullptr; // Placeholder
    }
    Location* getLocation(std::string location){
        return nullptr;
    }

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};

