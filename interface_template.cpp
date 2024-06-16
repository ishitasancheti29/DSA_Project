#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Vehicle;
int max(int a, int b){ return a>b ? a:b; }

class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const { return vehicle; }
    std::string getPickUpLocation() const { return pick_up_location; }
    std::string getDropLocation() const { return drop_location; }
    int getDepartureTime() const { return departure_time; }
    int getBookedSeats() const { return booked_seats; }

    // Setter functions
    void setVehicle(Vehicle* v) { vehicle = v; }
    void setPickUpLocation(std::string location) { pick_up_location = location; }
    void setDropLocation(std::string location) { drop_location = location; }
    void setDepartureTime(int time) { departure_time = time; }
    void setBookedSeats(int seats) { booked_seats = seats; }

private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};


class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const { return leftptr; }
    BinaryTreeNode* getRightPtr() const { return rightptr; }
    BinaryTreeNode* getParentPtr() const { return parentptr; }
    int getDepartureTime() const { return departuretime; }

    Trip* getTripNodePtr() const { return tripnodeptr; }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) { leftptr = left; }
    void setRightPtr(BinaryTreeNode* right) { rightptr = right; }
    void setParentPtr(BinaryTreeNode* parent) { parentptr = parent; }
    void setDepartureTime(int time) { departuretime = time; }
    void setTripNodePtr(Trip* trip) { tripnodeptr = trip; }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class TransportService {
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName(){ return name; }
    BinaryTreeNode* getBSTHead(){ return BSThead; }

    // Setter functions
    void setName(std::string service_name) { name = service_name; }
    void setBSTHead(BinaryTreeNode* node) { BSThead = node; }

    void addTrip(int key, Trip* trip){
        BinaryTreeNode* temp = BSThead;
        BinaryTreeNode* parent = NULL;
        BinaryTreeNode* n = new BinaryTreeNode(key, trip, nullptr);
        if(!temp){
            BSThead = n;
            return;
        }

        bool done = false;
        int dir;

        while(temp){
            if(temp->getDepartureTime() < key){
                dir = 1;
                parent = temp;
                temp = temp->getRightPtr();
            } else if(temp->getDepartureTime() > key){
                dir = -1;
                parent = temp;
                temp = temp->getLeftPtr();
            }
        }

        if(dir == 1){
            parent->setRightPtr(n);
            n->setParentPtr(parent);
        } else if(dir == -1){
            parent->setLeftPtr(n);
            n->setParentPtr(parent);
        }
    }

private:
    std::string name;
    BinaryTreeNode* BSThead;
};


class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const { return vehicle_number; }
    int getSeatingCapacity() const { return seating_capacity; }

    // Setter functions
    void setVehicleNumber(std::string number) { vehicle_number = number; }
    void setSeatingCapacity(int capacity) { seating_capacity = capacity; }
    void addTrip(Trip* trip) { trips.push_back(trip); }
    vector<Trip*> getTrips(){return trips;}

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const { return name; } 

    TransportService* getServicePtr(std::string droplocation){
        for(int i=0; i<serviceptrs.size(); i++){
            if(serviceptrs[i]->getName() == droplocation){return serviceptrs[i];}
        }
        return nullptr;
    }

    // Setter functions
    void setName(std::string location_name) { name = location_name; }

    TransportService* setServicePtr(std::string droplocation) {
        TransportService* s = new TransportService(droplocation);
        for(int i=0; i<serviceptrs.size(); i++){
            if(serviceptrs[i]->getName() == droplocation){return nullptr;}
        }
        serviceptrs.push_back(s);
        return s;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    vector<Trip*> getTrips(){return trips;}
    vector<TransportService*> getServices(){return serviceptrs;}

private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree(BinaryTreeNode* n = nullptr) : root(n) {}

    int getHeight(){
        // Implement this function to return the height of the tree
        if(!root){ return 0; }
        BinaryTree left(root->getLeftPtr());
        BinaryTree right(root->getRightPtr());
        return max(left.getHeight(), right.getHeight())+1;
    }

    int getNumberOfNodes() const {
        if(!root){return 0;}
        BinaryTree left(root->getLeftPtr());
        BinaryTree right(root->getRightPtr());
        return left.getNumberOfNodes() + right.getNumberOfNodes() +1;
    }
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree(BinaryTreeNode* n = nullptr) {root = n;}

    BinaryTreeNode* getElementWithMinimumKey(){
        BinaryTreeNode* temp = root;
        if(!temp){return nullptr;}
        while(temp->getLeftPtr()){
            temp = temp->getLeftPtr();
        }
        return temp;
    }

    BinaryTreeNode* getElementWithMaximumKey(){
        BinaryTreeNode* temp = root;
        if(!temp){return nullptr;}
        while(temp->getParentPtr()){
            temp = temp->getRightPtr();
        }
        return temp;
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        if(!root || root->getTripNodePtr()->getDepartureTime()==key){return root;}
        if(root->getTripNodePtr()->getDepartureTime() > key){
            BinarySearchTree left(root->getLeftPtr());
            return left.searchNodeWithKey(key);
        }
        if(root->getTripNodePtr()->getDepartureTime() < key){
            BinarySearchTree right(root->getRightPtr());
            return right.searchNodeWithKey(key);
        }
        return nullptr;
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        if(!root || !root->getRightPtr() || !node){return nullptr;}
        BinarySearchTree right(root->getRightPtr());
        return right.getElementWithMinimumKey();
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        BinaryTreeNode* curr = searchNodeWithKey(key);
        return getSuccessorNode(curr);
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        if(!root || !root->getLeftPtr() || !node){return nullptr;}
        BinarySearchTree left(root->getLeftPtr());
        return left.getElementWithMaximumKey();
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        BinaryTreeNode* curr = searchNodeWithKey(key);
        return getPredecessorNode(curr);
    }

    BinaryTreeNode* deletion(BinaryTreeNode* root, Trip* t){
        if(!root){return nullptr;}
        if(root->getDepartureTime() < t->getDepartureTime()){
            root->setRightPtr(deletion(root->getRightPtr(), t));
        }
        else if(root->getDepartureTime() > t->getDepartureTime()){
            root->setRightPtr(deletion(root->getLeftPtr(), t));
        }


        if(!root->getLeftPtr()){
            BinaryTreeNode* temp = root->getRightPtr();
            return temp;
        }
        if(!root->getRightPtr()){
            BinaryTreeNode* temp = root->getLeftPtr();
            return temp;
        }

        BinaryTreeNode* temp = getSuccessorNode(root);
        root->setTripNodePtr(temp->getTripNodePtr());
        root->setDepartureTime(temp->getDepartureTime());
        deletion(root->getRightPtr(), t);

        return root;

    }

};


class TravelDesk {
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        // Implement this function to add a trip
        Vehicle* v = nullptr;
        for(int i=0; i<vehicles.size(); i++){
            if(vehicles[i]->getVehicleNumber() == vehicle_number){v = vehicles[i]; break;}
        }
        if(!v){
            v = new Vehicle(vehicle_number, seating_capacity);
            vehicles.push_back(v);
        }

        Trip* t = new Trip(v, pick_up_location, drop_location, departure_time);
        v->addTrip(t);

        Location* l = nullptr;
        for(int i=0; i<locations.size(); i++){
            if(locations[i]->getName() == pick_up_location){l = locations[i]; break;;}
        }
        if(!l){
            l = new Location(pick_up_location);
            locations.push_back(l);
        }

        l->addTrip(t);
        l->setServicePtr(drop_location);
        l->getServicePtr(drop_location)->addTrip(departure_time, t);
    }

    std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
        vector<Trip*> v;
        Location* l = nullptr;
        for(int i=0; i<locations.size(); i++){
            if(locations[i]->getName()==pick_up_location){
                l = locations[i]; break;
            }
        }

        vector<Trip*> t_vec = l->getTrips();
        for(int i=0; i<t_vec.size(); i++){
            int dept = t_vec[i]->getDepartureTime();
            if(dept>after_time && dept<before_time){
                v.push_back(t_vec[i]);
            }
        }
        return v; 
    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        Location* l = nullptr;
        for(int i=0; i<locations.size(); i++){
            if(locations[i]->getName()==pick_up_location){
                l = locations[i]; break;
            }
        }
        BinaryTreeNode* head = l->getServicePtr(drop_location)->getBSTHead();
        BinaryTreeNode* temp = head;

        Trip* res = nullptr;
        

        while(true){
            if(!temp){break;}
            if(temp->getDepartureTime()==departure_time && temp->getTripNodePtr()->getVehicle()->getVehicleNumber()==vehicle_number){
                res = temp->getTripNodePtr();
                res->setBookedSeats(res->getBookedSeats()+1);

                if(res->getBookedSeats() == res->getVehicle()->getSeatingCapacity()){
                    // delete if max cap reached
                    BinarySearchTree bt(temp);
                    bt.deletion(head ,res);
                    
                }
                break;            
            } else {
                if(temp->getDepartureTime() < departure_time){
                    temp = temp->getRightPtr();
                } 
                if(temp->getDepartureTime() > departure_time){
                    temp = temp->getLeftPtr();
                }
            }
        }
        
        return res;
    }


    Location* getLocation(std::string location){
        for(int i=0; i<locations.size(); i++){
            if(locations[i]->getName() == location){
                return locations[i];
            }
        }
        return nullptr;
    }

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};


